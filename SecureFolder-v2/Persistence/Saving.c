#include "secureFolder.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include <errno.h>

// Structure for keeping file data
typedef struct {
  int offset;
  void* memoryLoc;
  char* result;
} FileArgs;

// Default save location if not otherwise specified
//#define DEF_SAVE_LOC "/usr/share/secure_folder/folder_contents"
#define FILE_SIZE 4096

// Helpers
int numDigits (int num);
void* do_mmap_file (char* path, int flags, mode_t mode, int filesize, int prot, int isWrite);
void do_unmap_file ();
int create_file_args (FileArgs* args, char* path, int flags, mode_t mode, int prot, int isWrite);
void save_file (void* file, void* fileArgs);
void save_perms (void* perms, void* fileArgs);

// Saving
void do_save (Node* list, char* savefile) {
  if (savefile == NULL) savefile = DEF_SAVE_LOC;

  FileArgs* args = malloc (sizeof (FileArgs));

  if (create_file_args (args, savefile, O_RDWR | O_CREAT, S_IWUSR, PROT_WRITE, 1) < 0)
    return;

  printf ("Memory Loc: %d\n", args->memoryLoc);

  list_each (list, save_file, args);

  do_unmap_file (args -> memoryLoc, FILE_SIZE);
  printf ("Unloaded\n");
  free (args);
}

void save_file (void* f, void* fileArgs) {
  FileArgs* fArgs = (FileArgs*)fileArgs;
  File* file  = (File*)f;

  // Write the data for the file
  sprintf((char*) fArgs->memoryLoc + fArgs->offset, "%s ", file->fileId);
  fArgs->offset += strlen (file->fileId) + 1;

  int numUsers = list_size (file->users);
  sprintf((char*) fArgs->memoryLoc + fArgs->offset, "%d ", numUsers);
  fArgs->offset += numDigits (numUsers) + 1;

  // Add all the users
  list_each (file -> users, save_perms, fArgs);
}

void save_perms (void* permissions, void* fileArgs) {
  FileArgs* f = (FileArgs*)fileArgs;
  Permissions* perms = (Permissions*)permissions;

  // Write as UserId canRead canWrite canExecute
  sprintf ((char*)f -> memoryLoc + f->offset, "%d ", perms->uid);
  f->offset += numDigits (perms -> uid) + 1;

  // NOTE: These are hardcoded because they are flags - will always be 1 digit.
  sprintf ((char*)f -> result + f->offset + 0, "%d ", perms->canRead);
  sprintf ((char*)f -> result + f->offset + 2, "%d ", perms->canWrite);
  sprintf ((char*)f -> result + f->offset + 4, "%d ", perms->canExecute);

  f -> offset += 6;
}

// Helper methods
int create_file_args (FileArgs* args, char* path, int flags, mode_t mode, int prot, int isWrite) {
  void* loc = do_mmap_file (path, flags, mode, FILE_SIZE, prot, isWrite);
  if ((int)loc == -1) {
    printf("Invalid\n");
    return -1;
  }

  args -> memoryLoc = loc;
  args -> offset = 0;

  return 0;
}

void* do_mmap_file (char* path, int flags, mode_t mode, int filesize, int prot, int isWrite) {
  int fd = open (path, flags, mode);

  if (isWrite) {
    for (int i=0; i<filesize; i++) write (fd, " ", 1);
    write (fd, "", 1); /* write a NULL at EOF */
  }

  void* file_memory = mmap (NULL, filesize, prot, MAP_SHARED, fd, 0);
  close (fd);

  printf ("FILE MEMORY IS MAPPED: %x\n", file_memory);
  return file_memory;
}

void do_unmap_file (void* mem, int filesize) {
  munmap (mem, filesize);
}
