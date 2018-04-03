#include "Users.h"

int numUsers = 0;
int maxLength = 0;
User** usersArr = NULL;

// References to the helper functions, defined at the bottom
void grow();
User* init_user (int, char*);

/* The exported functions - these are called from other programs */

// Adds a new user to the users array
void add_user (int userId, char* username) {
  User* u = init_user (userId, username);

  if (numUsers + 1 >= maxLength)
    grow ();

  usersArr [numUsers ++] = u;
}

// Returns the entire list of users
User** get_users (){ return usersArr; }


// Checks if the user exists in the system, returning true or false
int user_exists (int uid) {
  return get_user (uid) != NULL;
}

// Returns the user data pointer for a user if they exist, otherwise NULL
User* get_user (int uid) {
  for (int i = 0; i < numUsers; i++) {
    if (usersArr [i] -> id == uid)
      return usersArr[i];
  }
  return NULL;
}

// Cleans up the users array, deleting all data
void users_clean () {
  for (int i = 0; i < numUsers; i++)
    free (usersArr [i]);

  numUsers = 0;
  maxLength = 0;
}

// Prints all users to the output
void users_print () {
  fprintf (stdout, "%3s    %10s\n", "Id", "Name");
  fprintf (stdout, "-----------------\n");
  for (int i = 0; i < numUsers; i++)
    fprintf (stdout, "%3d    %10s\n", usersArr[i]->id, usersArr[i]->name);
}


/* Hidden methods - these are helpers for the above */

// Initialize a new user
User* init_user (int userId, char* username) {
  User* newUser = malloc (sizeof (User));
  newUser->name = username;
  newUser->id   = userId;

  return newUser;
}

// Grow the users array
void grow () {
  int newLength = maxLength * 2;
  if (newLength < 1) newLength = 1;

  User** newArr = malloc (sizeof(User*) * newLength);
  for (int i = 0; i < numUsers; i++)
    newArr [i] = usersArr [i];

  free (usersArr);

  usersArr = newArr;
  maxLength = newLength;
}

// Persistence
void save_users () {

}
void load_users () {

}
