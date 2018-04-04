#include "shared.h"

int numDigits (int num) {
  if (num == 0) return 1;

  int c = 0;
  while (num > 0) {
    c++;
    num /= 10;
  }
  return c;
}

void do_unmap (void* fileMapping, int size) {
  munmap (fileMapping, size);
}
