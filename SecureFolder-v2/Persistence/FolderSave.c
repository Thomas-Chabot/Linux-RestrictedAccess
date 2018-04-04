#include "shared.h"

typedef struct {
  int offset;
  void* fileMapping;
} FileArgs;

void save_file (void* file, void* fileArgs);
void save_perms (void* user, void* fileArgs);

void write_num (FileArgs* args, int number);
void write_str (FileArgs* args, char* str);

void* do_mmap_write (char* filePath, int filesize);

void do_sf_save (Node* list, char* saveFile, int filesize) {
  FileArgs args;
  args.offset = 0;
  args.fileMapping = do_mmap_write (saveFile, filesize); // 1 extra byte for the null character

  if (args.fileMapping == (void*)-1) {
    printf ("Could not map file for writing\n");
    return;
  }

  write_num (&args, list_size (list));

  list_each (list, save_file, &args);
  do_unmap (args.fileMapping, filesize);
}

void save_file (void* f, void* fileArgs) {
  FileArgs* args = (FileArgs*)fileArgs;
  File* file = (File*)f;

  int numUsers = list_size (file -> users);

  write_str (args, file -> fileId);
  write_num (args, numUsers);

  list_each (file -> users, save_perms, args);
}

void save_perms (void* perms, void* fileArgs) {
  FileArgs* args = (FileArgs*) fileArgs;
  Permissions* user = (Permissions*) perms;

  write_num (args, user -> uid);
  write_num (args, user -> canRead);
  write_num (args, user -> canWrite);
  write_num (args, user -> canExecute);
}


// Writing variants
void write_num (FileArgs* args, int number) {
  sprintf ((char*) args -> fileMapping + args -> offset, "%d ", number);
  args -> offset += numDigits (number) + 1;
}
void write_str (FileArgs* args, char* str) {
  sprintf ((char*) args -> fileMapping + args -> offset, "%s ", str);
  args -> offset += strlen (str) + 1;
}

// Memory mapping
void* do_mmap_write (char* filePath, int filesize) {
  int fd;
  void* file_memory;

  /* open or create a file to hold an unsigned integer  */
  fd = open (filePath, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

  /* write filesize spaces */
  for (int i=0; i<filesize; i++) write (fd, " ", 1);
  write (fd, "", 1); /* write a NULL at EOF */

  /* create the memory-mapping
     1st param=start addr of mapping into memory, NULL means chosen by OS
     2nd param=length of map (bytes)
     3rd param=protection
     4th param=options, MAP_SHARED used for interprocess communications
     5th param=file descriptor of mapped file
     6th param=offset from start of file where mapping starts
   */
  file_memory = mmap (NULL, filesize, PROT_WRITE, MAP_SHARED, fd, 0);
  close (fd);

  return file_memory;
}
