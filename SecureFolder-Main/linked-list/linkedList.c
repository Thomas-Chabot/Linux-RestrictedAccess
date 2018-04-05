#include "linkedList.h"

void do_each (Node* head, void (*f)(void* node, void* a));
void each (Node* head, void (*f)(void* node, void* args), void*(*g)(Node* node), void* args);

void do_delete_node (void* node, void* a);
Node* get_node (Node* head, void* data);

void* get_self (Node* node);
void* get_data (Node* node);

Node* find_node (Node* head, int (*checkFunc)(void*, void*), void* additionalArgs);

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

  if (*head == NULL) {
    newNode -> next = NULL;
  } else {
    newNode -> next = *head;
    (*head) -> prev = newNode;
  }

  *head = newNode;
}

void* list_get (Node* head, int (*checkFunc)(void*, void*), void* additionalArgs) {
  Node* n = find_node (head, checkFunc, additionalArgs);
  if (n == NULL) return NULL;
  return n->data;
}

int list_remove (Node** head, void* data) {
  Node* node = get_node (*head, data);
  if (node == NULL)
    return -1;

  if (node == *head) *head = node->next;

  if ((node -> next) != NULL)
    (node -> next) -> prev = node -> prev;

  if (node -> prev != NULL)
    node -> prev -> next = node -> next;

  free (node);
  return 0;
}

void delete_list (Node** head) {
  do_each (*head, do_delete_node);
  *head = NULL;
}

void list_each (Node* head, void(*f)(void* data, void* arg), void* args){
  each (head, f, get_data, args);
}


// Private Helpers
void* get_self (Node* node) { return node; }
void* get_data (Node* node){ return node->data; }

void do_delete_node (void* node, void* a) {
  free (node);
}

void do_each (Node* head, void (*f)(void* node, void* a)) {
  each (head, f, get_self, NULL);
}

int is_node (void* data1, void* data2) {
  return data1 == data2;
}
Node* get_node (Node* head, void* data) {
  return find_node (head, is_node, data);
}

Node* find_node (Node* head, int (*checkFunc)(void*, void*), void* additionalArgs) {
  Node* cur = head;

  while (cur != NULL) {
    if (checkFunc(cur -> data, additionalArgs))
      return cur;

    cur = cur -> next;
  }

  return NULL;
}

void each (Node* head, void (*f)(void* node, void* arg), void*(*g)(Node* node), void* args){
  Node* cur = head;
  Node* next = NULL;

  while (cur != NULL) {
    next = cur->next;

    (*f) (g (cur), args);
    cur = next;
  }
}
