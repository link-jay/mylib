#include <stdio.h>
#include <string.h>
#include "array.c"

typedef struct {
  char** interface;
  size_t len;
  size_t cap;
} String;

String split_str(char* src, char sep) {
  String res = {.len = 0, .cap = 0, .interface = NULL};
  char* start = src;
  char* pos = NULL;
  while(pos = strchr(start, sep)) {
    size_t len = pos - start;
    char* member = malloc((len+1) * sizeof(char));
    memcpy(member, start, len);
    member[len] = 0;
    ARRAY_PUSH(res.interface, res.len, res.cap, member);
    start = pos + 1;
  }
  if (start == src) {
    char* member = malloc((strlen(src)+1)*sizeof(char));
    strcpy(member, src);
    ARRAY_PUSH(res.interface, res.len, res.cap, member);
  } else {
    char* member = malloc((strlen(start)+1) * sizeof(char));
    strcpy(member, start);
    ARRAY_PUSH(res.interface, res.len, res.cap, member);
  }
  return res;
}

char* join_str(String src, char sep) {
  size_t lenght = 0;
  for (size_t i = 0; i < src.len; i++) {
    lenght += strlen(src.interface[i]) + 1;
  }
  char* res = malloc((lenght)*sizeof(char));
  char* pos = res;
  for (size_t i = 0; i < src.len; i++) {
    size_t str_len = strlen(src.interface[i]);
    memcpy(pos, src.interface[i], str_len);
    pos[str_len] = sep;
    pos += str_len + 1;
  }
  res[lenght-1] = '\0';
  return res;
}

void dump_str(String src) {
  putc('{', stdout);
  for (size_t i = 0; i < src.len; i++) {
    printf("%s, ", src.interface[i]);
  }
  puts("}");
}

void clear_str(String src) {
  for (size_t i = 0; i < src.len; i++) {
    free(src.interface[i]);
  }
  free(src.interface);
}
