#include "can_access.h"
#include <stdio.h>

int main (int argc, char* argv[]) {
  if (argc < 2) return;
  fprintf (stdout, "Can access ? %d\n", can_open (argv[1]));
}
