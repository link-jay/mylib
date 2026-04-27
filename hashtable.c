/* 哈希表的c库，需要搭配导入hashtable.h*/

#include <string.h>
#include <stdlib.h>

#define NotFound -1

typedef struct _HTNode {
  char* key;
  int value;
  struct _HTNode* next;
} Node;

typedef struct {
  Node** buckets;
  unsigned int size;
  unsigned int load_size;
} HashTable;

static unsigned int hash(const char* key, unsigned int size) {
  unsigned int h = 5381;
  while (*key) {
    h = ((h << 5) + h) + *key;
    key++;
  }
  return h % size;
}

static Node* create_node(const char* key, int value) {
  Node* new_node = (Node *)(malloc(sizeof(Node)));
  new_node->key  = strdup(key);
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

static void del_node(Node* nd) {
  free(nd->key);
  free(nd);
};

HashTable* create_ht(size_t size) {
  HashTable* new_ht = (HashTable *)(malloc(sizeof(HashTable)));
  new_ht->size = size;
  new_ht->buckets = (Node **)(calloc(size, sizeof(Node*)));
  new_ht->load_size = 0;
  return new_ht;
}

/* node->node->null */
/*    ^    ^q*/
/*          ^p    ^q*/

void del_ht(HashTable* ht) {
  for (unsigned int i = 0; i < ht->size; i++) {
    Node* p = ht->buckets[i];
    if (!p) {continue;}
    while (p) {
      Node* q = p->next;
      del_node(p);
      p = q;
    }
  }
  free(ht->buckets);
  free(ht);
};

/* NOTE:用于复原resize后的哈希表 */
static void _restore_ht(HashTable* new_ht, Node* node) {
  Node* current_node = node;
  while (current_node) {
    Node* next_node = current_node->next;
    
    unsigned int idx = hash(current_node->key, new_ht->size);
    current_node->next = new_ht->buckets[idx];
    new_ht->buckets[idx] = current_node;
    new_ht->load_size++;

    current_node = next_node;
  }
}

void resize_ht(HashTable** ht, unsigned int size) {
  HashTable* new_ht = create_ht(size);
  HashTable* old_ht = *ht;
  
  for (unsigned int old_idx = 0; old_idx < old_ht->size; old_idx++) {
    if (!old_ht->buckets[old_idx]) {continue;}
    _restore_ht(new_ht, old_ht->buckets[old_idx]);
  }

  *ht = new_ht;
  free(old_ht->buckets);
  free(old_ht);
}

/* NOTE: 用于去除put时重复的键值对，以键判定重复 */
static void _unify_node(Node* start_node, HashTable* ht) {
  Node* current_node = start_node;
  Node* next_node = current_node->next;

  while (next_node) {
    if (strcmp(start_node->key, next_node->key) == 0) {
      current_node->next = next_node->next;
      del_node(next_node);
      ht->load_size--;
      break;
    }
    current_node = next_node;
    next_node = next_node->next;
  }
}

void ht_put(HashTable** ht, const char* key, int value) {
  Node* new_node = create_node(key, value);
  unsigned int idx = hash(key, (*ht)->size);
  new_node->next = (*ht)->buckets[idx];
  (*ht)->buckets[idx] = new_node;
  (*ht)->load_size++;

  _unify_node(new_node, *ht);
  
  if (((float)(*ht)->load_size / (*ht)->size) > 0.7) {
    resize_ht(ht, (*ht)->size * 2);
  }
}

int ht_get(HashTable* ht, const char* key) {
  int idx = hash(key, ht->size);
  Node* p = ht->buckets[idx];
  while (p) {
    if (!strcmp(key, p->key)) {return p->value;}
    p = p->next;
  }
  return NotFound;
}
