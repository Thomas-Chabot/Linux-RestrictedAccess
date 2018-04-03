#ifndef USERS_H
#define USERS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char* name;
  int id;
} User;

void add_user (int, char*);
User** get_users ();

int user_exists (int);
User* get_user (int);

void users_clean();
void users_print();

#endif
