#include "fileIds.h"
#include <stdio.h>
#include <stdlib.h>

// The name for UUIDs
const char* uuid_name = "user.uuid";

// Helper methods
void get_value (const char* pathname, uuid_t* result);
ssize_t get_size (const char*, const char*);
int set_value (const char*, const void*);
int do_get_value (const char*, ssize_t, void*);
void generate_id (uuid_t*);

// The main method
void get_id (const char* pathname, char* result) {
  uuid_t uuid;
  get_value (pathname, &uuid);

  // convert it to a string & return
  uuid_unparse (uuid, result);
}

// Helpers
void get_value (const char* pathname, uuid_t* result) {
  ssize_t size = get_size (pathname, uuid_name);

  if (size < 0) {
    // Doesn't exist - create it here
    generate_id(result);
    set_value (pathname, result);
  }

  do_get_value (pathname, size, result);
}

int set_value (const char* pathname, const void* value) {
  return (setxattr (pathname, uuid_name, value, 16, XATTR_CREATE) != -1);
}

int do_get_value (const char* pathname, ssize_t size, void* result) {
  return (getxattr (pathname, uuid_name, result, size) != -1);
}

void generate_id(uuid_t* result) {
  // NOTE: This is going to be using the system call to the UUID stuff. For now, just using the main library
  //       for testing purposes
  uuid_generate (*result);
}

ssize_t get_size (const char* pathname, const char* name) {
  void* value = NULL;
  return getxattr(pathname, name, value, 0);
}
