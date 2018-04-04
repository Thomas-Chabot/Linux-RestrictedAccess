#include "shared.h"

#define UUID_LEN 36

typedef struct {
  int offset;
  void* fileMapping;
  int size;
} FileArgs;

void load_file (FileArgs* fileArgs);
void load_user (char* fileId, FileArgs* fileArgs);

void load_num (FileArgs* args, int* number);
void load_str (FileArgs* args, char* string);
void load_character(FileArgs* args, char* c);

void* do_mmap_read (char* filePath, int* fileSize);

// The main method
void do_sf_load (char* saveFile) {
  FileArgs args;
  args.offset = 0;
  args.fileMapping = do_mmap_read (saveFile, &args.size);

  Node* newList = init_list ();
  int numFiles;

  load_num (&args, &numFiles);
  for (int i = 0; i < numFiles; i++) {
    load_file (&args);
  }
}

// Helper methods
void load_file (FileArgs* fileArgs) {
  char fileId[UUID_LEN + 1]; // extra character for the NULL character
  int numUsers;

  load_str (fileArgs, fileId);
  load_num (fileArgs, &numUsers);

  add_to_secure_folder (fileId);

  // load the users
  for (int i = 0; i < numUsers; i++)
    load_user (fileId, fileArgs);
}

void load_user (char* fileId, FileArgs* fileArgs) {
  int uid, cr, cw, ce;
  load_num (fileArgs, &uid);
  load_num (fileArgs, &cr);
  load_num (fileArgs, &cw);
  load_num (fileArgs, &ce);

  add_user_access (fileId, uid, cr, cw, ce);
}

void load_character(FileArgs* args, char* c) {
  sscanf ((char*)args -> fileMapping + args -> offset, "%c", c);
  // note: this is only used as a check -> does not affect offset
}
void load_num (FileArgs* args, int* number) {
  sscanf ((char*)args -> fileMapping + args -> offset, "%d", number);
  args -> offset += numDigits (*number) + 1;
}
void load_str (FileArgs* args, char* string) {
  int len = sscanf ((char*)args -> fileMapping + args -> offset, "%s", string);
  args -> offset += strlen (string) + 1;
}

void* do_mmap_read (char* filePath, int* fileSize) {
  int fd;
  void* file_memory;
  struct stat sb;

  fd = open (filePath, O_RDWR, S_IRUSR | S_IWUSR);
  if (fd < 0) {
    fprintf (stderr, "Could not open file\n");
    return (void*)-1;
  }

  fstat (fd, &sb);
  *fileSize = sb.st_size;

  /* create the memory-mapping */
  file_memory = mmap (NULL, *fileSize, PROT_READ | PROT_WRITE,
		      MAP_SHARED, fd, 0);
  close (fd);

  return file_memory;
}
