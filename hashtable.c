/*
  哈希表的C库,
  自行准备键值对, 一定是key, value, next这三个成员,
  注意严格对应键值对类型, key一定是字符串, value自定义
  注意桶是键值对的数组, 而键值对被设计为堆上的节点, 所以默认是_Node** bucket,

  Example:
  char* _key; int _value, output;
  struct _Node {char* key; int value; struct _Node next;};
  struct HashTable {size_t len, size_t cap, _Node** buckets} ht = {};
  HT_PUT(ht->buckets, ht->len, ht->cap, _key, _value);
  HT_GET(ht->buckets, ht->len, ht->cap, _key, output);
  FREE_HT(ht->buckets, ht->cap);
*/

#include <string.h>
#include <stdlib.h>

static inline unsigned int hash(const char* key, unsigned int size) {
  unsigned int h = 5381;
  while (*key) {
    h = ((h << 5) + h) + *key;
    key++;
  }
  return h % size;
}

/* NOTE: 传入的buckets, key, value类型必须对应 */
/* NOTE: buckets节点的键值对名必须是key, value */
#define HT_PUT(buckets, len, cap, pt_key, pt_value)				\
  do {											\
    if (buckets == NULL) buckets = calloc((cap) = 4, sizeof(typeof(*(buckets))));	\
    /* 检查扩容 */									\
    /* NOTE: 这里只在运算前转换其中一个，运算再转换无法得到正确结果 */			        \
    else if (((float)(len) / (cap)) > 0.7) {						\
      typeof(buckets) new_buckets = calloc((cap) *= 2, sizeof(typeof(*(buckets))));	\
      len = 0;										\
      for (size_t n_idx, idx = 0; idx < (cap)/2; idx++) {				\
	if ((buckets)[idx] == NULL) continue;						\
	typeof(*(buckets)) node = (buckets)[idx];					\
	typeof(*(buckets)) next_node;							\
	do {										\
	  next_node = node->next;							\
	  n_idx = hash(node->key, (cap));						\
	  node->next = new_buckets[n_idx];						\
	  new_buckets[n_idx] = node;							\
	  (len)++;									\
	  node = next_node;								\
	} while (node != NULL);								\
      }											\
      free(buckets);									\
      buckets = new_buckets;								\
    }											\
    /* 创建并插入键值对节点 */								\
    typeof(*(buckets)) new_node = malloc(sizeof(typeof(**(buckets))));			\
    *new_node = (typeof(**(buckets))){.key = (pt_key), .value = (pt_value)};		\
    size_t idx = hash(pt_key, (cap));							\
    new_node->next = (buckets)[idx];							\
    (buckets)[idx] = new_node;								\
    (len)++;										\
    /* 重复键去重 */									\
    typeof(*(buckets)) head = new_node;							\
    typeof(*(buckets)) next_node = head->next;						\
    while (next_node) {									\
      if (strcmp(new_node->key, next_node->key) == 0) {					\
	head->next = next_node->next;							\
	free(next_node);								\
	(len)--;									\
	break;										\
      }											\
      head = next_node; next_node = next_node->next;					\
    }											\
  } while(0)

#define HT_GET(buckets, len, cap, fd_key, fd_value)	\
  do {								\
    size_t idx = hash(fd_key, cap);				\
    typeof(*buckets) node = buckets[idx];			\
    while (node != NULL) {					\
      if (strcmp(fd_key, node->key) == 0) {			\
	fd_value = node->value;					\
	break;							\
	  }							\
      node = node->next;					\
    }								\
  } while(0)

#define FREE_HT(buckets, cap)			\
  do {							\
    for (size_t i = 0; i < cap; i++) {			\
      typeof(*buckets) next_node, node = buckets[i];	\
      if (node == NULL) {continue;}			\
      do {						\
	next_node = node->next;				\
	free(node);					\
	node = next_node;				\
      } while(node != NULL);				\
    }							\
    free(buckets);					\
  } while(0)
