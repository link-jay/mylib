#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.c"

int sundaySearch(char* main_str, char* sub_str) {
  
  HashTable* shift_table = create_ht(32);
  int main_len    = strlen(main_str);
  int sub_len     = strlen(sub_str);
  int current_pos = 0;
  int max_pos     = main_len - sub_len;
  
  for (int relative_pos = 0; relative_pos < sub_len; relative_pos++) {
    char key[]   = {sub_str[relative_pos], '\0'};
    int offset = sub_len - relative_pos;
    put_ht(&shift_table, key, offset);
  }
  
  while (current_pos <= max_pos) {
    int relative_pos;
    for (relative_pos = 0; relative_pos < sub_len; relative_pos++) {
      if (main_str[current_pos + relative_pos] != sub_str[relative_pos]) {
	break;
      }
    }
    
    if (relative_pos == sub_len) {
      del_ht(shift_table);
      return current_pos;
    }
    
    char next_char[] = {main_str[current_pos + sub_len], '\0'};
    int k;
    if ((k = get_ht(shift_table, next_char)) != -1) {
      current_pos += k;
    } else {
      current_pos += sub_len;
    }
  }
  del_ht(shift_table);
  return -1;
}

int main()
{
  FILE* fp = fopen("test.txt", "r");
  
  char *main_str, *sub_str;
  size_t n1 = 0;
  size_t n2 = 0;
  getline(&main_str, &n1, fp); main_str[strchr(main_str, '\n') - main_str] = '\0';
  getline(&sub_str, &n2, fp); sub_str[strchr(sub_str, '\n') - sub_str] = '\0';
  
  int pos = sundaySearch(main_str, sub_str);
  printf("pos: %d\n", pos);
  return 0;
}
