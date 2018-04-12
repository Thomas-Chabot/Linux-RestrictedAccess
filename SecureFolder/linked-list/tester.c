#include <linkedList.h>
#include <stdio.h>

int isData (void* data, void* n) {
  return *((int*)data) == 12;
}

int main (int argc, char* argv[]) {
  Node* list = init_list ();

  int data = 12;
  list_push (&list, &data);

  printf("exists? %d\n", list_contains(list, isData, NULL));
  list_remove (&list, &data);

  printf("size is now %d\n", list_size (list));
  delete_list (&list);

  return 0;
}
