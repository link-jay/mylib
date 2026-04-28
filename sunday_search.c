/* sunday搜索算法：用于快速搜索字符串 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.c"

int sundaySearch(char* main_str, char* sub_str) {
  typedef struct _Node {struct _Node *next; int value; char key[];} _Node;
  struct HashTable {size_t len; size_t cap; _Node** buckets;} shift_table = {};
  int main_len = strlen(main_str);
  int sub_len = strlen(sub_str);
  int current_pos = 0;
  int max_pos = main_len - sub_len;
  
  for (int relative_pos = 0; relative_pos < sub_len; relative_pos++) {
    char key[] = {sub_str[relative_pos], '\0'};
    int offset = sub_len - relative_pos;
    HT_PUT(shift_table.buckets, shift_table.len, shift_table.cap, key, offset);
  }
  
  while (current_pos <= max_pos) {
    int relative_pos;
    for (relative_pos = 0; relative_pos < sub_len; relative_pos++) {
      if (main_str[current_pos + relative_pos] != sub_str[relative_pos]) {
	break;
      }
    }
    
    if (relative_pos == sub_len) {
      FREE_HT(shift_table.buckets, shift_table.cap);
      return current_pos;
    }
    
    char next_char[] = {main_str[current_pos + sub_len], '\0'};
    int k = -1;
    HT_GET(shift_table.buckets, shift_table.len, shift_table.cap, next_char, k);
    if (k != -1) {
      current_pos += k;
    } else {
      current_pos += sub_len;
    }
  }
  FREE_HT(shift_table.buckets, shift_table.cap);
  return -1;
}

int main()
{
  /* FILE* fp = fopen("test.txt", "r"); */
  
  /* char *main_str = NULL; */
  /* char *sub_str = NULL; */
  /* size_t n1 = 0; */
  /* size_t n2 = 0; */
  
  /* getline(&main_str, &n1, fp); */
  /* char *newline1 = strchr(main_str, '\n'); */
  /* if (newline1) *newline1 = '\0'; */

  /* getline(&sub_str, &n2, fp); */
  /* char *newline2 = strchr(sub_str, '\n'); */
  /* if (newline2) *newline2 = '\0'; */
  
  char main_str[] = "hello, world";
  char sub_str[] = "world";
  
  int pos = sundaySearch(main_str, sub_str);
  printf("pos: %d\n", pos);
  return 0;
}
