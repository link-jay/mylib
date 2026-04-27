/* 哈希表c库的头文件，需要搭配hashtable.c合并编译*/

#include <stddef.h>

typedef struct HashTable HashTable;
HashTable* create_ht(size_t);
/* NOTE: ht_put会调用resize_ht自动扩容，一般情况下应该不需要手动调用resize_ht */
void resize_ht(HashTable** ht, unsigned int value);
void ht_put(HashTable** ht, char* key, int value);
int ht_get(HashTable* ht, char* key);
void del_ht(HashTable* ht);
