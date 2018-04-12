#include "secureFolder.h"

int main () {
  char* uuid = "the-maniacal-georgie";
  char* uuid1 = "my-name-is-pennywise";
  char* uuid2 = "strangers-smaller";

  int userId = 15;
  int userId2 = 16;

  secure_folder_load ();
  printf ("Secure folder contains %s: %d\n", uuid, secure_file_exists (uuid));
  printf ("Secure folder contains %s: %d\n", uuid1, secure_file_exists (uuid1));
  printf ("Secure folder contains %s: %d\n", uuid2, secure_file_exists (uuid2));

  printf ("Secure file 1 contains %d: %d\n", userId, user_can_access (uuid, userId));
  printf ("Secure file 1 contains %d: %d\n", userId, user_can_access (uuid, userId2));
  printf ("Secure file 2 contains %d: %d\n", userId, user_can_access (uuid1, userId));
  printf ("Secure file 2 contains %d: %d\n", userId, user_can_access (uuid1, userId2));
  printf ("Secure file 3 contains %d: %d\n", userId, user_can_access (uuid2, userId));
  printf ("Secure file 3 contains %d: %d\n", userId, user_can_access (uuid2, userId2));
}
