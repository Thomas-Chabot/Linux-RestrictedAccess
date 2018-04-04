#include "shared.h"

typedef struct {
  int size;
} FolderSize;

#define NUM_FLAGS 3 // canRead, canWrite, canExecute

void get_file_size (void* file, void* FileSizeArg);
void get_user_size (void* perms, void* FileSizeArg);

int get_sf_size (Node* list) {
  FolderSize s;
  s.size = 0;

  list_each (list, get_file_size, &s);

  return s.size;
}

void get_file_size (void* file, void* FileSizeArg) {
  FolderSize* fs = (FolderSize*)FileSizeArg;
  File* f = (File*)file;

  // We want enough space for the File ID, # users, each user
  fs -> size += strlen (f -> fileId) + 1;
  fs -> size += numDigits (list_size (f -> users)) + 1;

  list_each (f -> users, get_user_size, FileSizeArg);
}

void get_user_size (void* perms, void* FileSizeArg) {
  FolderSize* fs = (FolderSize*)FileSizeArg;
  Permissions* user = (Permissions*)perms;

  fs -> size += numDigits (user -> uid) + 1;
  fs -> size += NUM_FLAGS * 2; // Each flag takes up two characters - the flag (0 or 1) and a space
}
