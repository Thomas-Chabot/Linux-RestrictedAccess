#include "tester.h"
#include <stdio.h>

int create_account (int userId, char* username){
  add_user (userId, username);
  return 0;
}

int main (int argc, const char* argv[]) {
  create_account (1, "Test");
  create_account (2, "George");
  create_account (3, "Waffle");
  create_account (4, "Man");

  users_print();
  users_clean();

  return 0;
}
