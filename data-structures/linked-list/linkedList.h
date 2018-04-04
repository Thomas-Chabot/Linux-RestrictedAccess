#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct ListNode {
  void *data;
  struct ListNode* next;
  struct ListNode* prev;
} Node;

Node* init_list ();
int list_size(Node* head);
int list_contains(Node* head, int (*checkFunc)(void*, void*), void* additionalArgs);
void* list_get (Node* head, int (*checkFunc)(void*, void*), void* additionalArgs);
void list_push (Node** head, void* data);
int list_remove (Node** head, void* data);
void delete_list (Node** head);
void list_each (Node* head, void(*f)(void* data, void* arg), void* arg);

#endif
