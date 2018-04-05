#ifndef FIFO_WRITE_H
#define FIFO_WRITE_H

int fifo_write (char* message, char* fifoPath);

#define ERR_FW_MK_FIFO -1
#define ERR_FW_OPEN -2
#define ERR_FW_WRITE -3

#endif
