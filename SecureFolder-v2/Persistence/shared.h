#ifndef PERSISTENCE_SHARED_H
#define PERSISTENCE_SHARED_H

#include "secureFolder.h"
#include <linkedList.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>


int numDigits (int num);
void do_unmap (void* fileMapping, int size);


#endif
