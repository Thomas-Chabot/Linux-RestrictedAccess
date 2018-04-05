#ifndef FIFO_READ_H
#define FIFO_READ_H

int fifo_read (char* fifoPath, char* message, int size);

// Error codes
#define ERR_FR_OPEN -1
#define ERR_FR_READ -2

#endif
