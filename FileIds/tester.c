#include <fileIds.h>
#include <stdio.h>

int main(){
  char result[64];

  // The path here is some test file I created. Ignore that
  get_id ("/home/student/Documents/Testing/test2.txt", result);

  fprintf (stdout, "Retrieved value is %s\n", result);
}
