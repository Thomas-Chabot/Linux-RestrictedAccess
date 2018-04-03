#include "linkedList.h"

void do_each (Node* head, void (*f)(void* node));
void each (Node* head, void (*f)(void* node), void*(*g)(Node* node));

void do_delete_node (void* node);
Node* get_node (Node* head, void* data);

void* get_self (Node* node);
void* get_data (Node* node);

Node* init_list () {
  return NULL;
}

int list_size (Node* head) {
  int size = 0;
  Node* cur = head;

  while (cur != NULL) {
    size ++;
    cur = cur -> next;
  }

  return size;
}

int list_contains (Node* head, int (*checkFunc)(void*, void*), void* additionalArgs) {
  return list_get (head, checkFunc, additionalArgs) != NULL;
}

void list_push (Node** head, void* data) {
  Node* newNode = malloc (sizeof (Node));
  newNode -> data = data;
  newNode -> prev = NULL;
  newNode -> next = NULL;

  printf ("Head is %d, null? %d\n", *head, *head == NULL);

  if (*head == NULL) {
    newNode -> next = NULL;
  } else {
    printf("WE CAN SET NEXT\n");
    newNode -> next = *head;
    (*head) -> prev = newNode;
  }

  printf ("Added node. Has a next? %d\n", newNode->next != NULL);
  *head = newNode;
}

void* list_get (Node* head, int (*checkFunc)(void*, void*), void* additionalArgs) {
  Node* cur = head;

  while (cur != NULL) {
    if (checkFunc(cur -> data, additionalArgs))
      return cur -> data;

    cur = cur -> next;
  }

  return NULL;
}

int list_remove (Node** head, void* data) {
  Node* node = get_node (*head, data);
  if (node == NULL)
    return -1;

  fprintf (stdout, "We have the node.\n");

  if (node == *head) *head = node->next;

  printf ("We have checked head.\n");
  printf ("Do we have a next? %d\n", (node->next) != NULL);

  if ((node -> next) != NULL){
    printf("Node -> next is %d\n", node->next);
    //(node -> next) -> prev = node -> prev;
  }

  printf ("Node -> next is valid\n");
  if (node -> prev != NULL)
    node -> prev -> next = node -> next;

  free (node);
  return 0;
}

void delete_list (Node** head) {
  do_each (*head, do_delete_node);
  *head = NULL;
}

void list_each (Node* head, void(*f)(void* data)){
  each (head, f, get_data);
}

// Private Helpers
void* get_self (Node* node) { return node; }
void* get_data (Node* node){ return node->data; }

void do_delete_node (void* node) {
  free (node);
}

void do_each (Node* head, void (*f)(void* node)) {
  each (head, f, get_self);
}

void each (Node* head, void (*f)(void* node), void*(*g)(Node* node)){
  Node* cur = head;
  Node* next = NULL;

  while (cur != NULL) {
    next = cur->next;

    (*f) (g (cur));
    cur = next;
  }
}

int is_node (void* data1, void* data2) {
  return data1 == data2;
}
Node* get_node (Node* head, void* data) {
  return list_get (head, is_node, data);
}
