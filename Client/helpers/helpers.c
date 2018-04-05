#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

/* getUserId: returns -1 on failure & userID otherwise */
int getUserId (char* username) {
  // if not given a username, return the current user's ID
  if (username == NULL) return getuid ();

  // otherwise - load the structure & return the uid from that
  struct passwd* pwd = getpwnam (username);
  if (pwd == NULL) return -1;

  return pwd -> pw_uid;
}

// Convert a string to lower case
char* strlower (char* str) {
  for(int i = 0; str[i]; i++){
    str[i] = tolower(str[i]);
  }
  return str;
}
