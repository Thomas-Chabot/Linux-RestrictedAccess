#include <stdio.h>
#include <string.h>
#include "helpers.h"

int read_int (char** s) {
  int result;

  sscanf (*s, "%d", &result);
  *s += countDigits (result) + 1;

  return result;
}

void read_str (char** s, char* res) {
  sscanf (*s, "%s", res);
  *s += strlen (res) + 1;
}

int countDigits (int num) {
  if (num == 0) return 1;

  int c = 0;
  while (num > 0) {
    c++;
    num /= 10;
  }
  return c;
}
