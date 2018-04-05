all: FifoWrite.o FifoRead.o
	ar rcs libFifoReadWrite.a FifoWrite.o FifoRead.o
	sudo mv libFifoReadWrite.a /usr/lib/libFifoReadWrite.a
	sudo cp FifoRead.h /usr/include/FifoRead.h
	sudo cp FifoWrite.h /usr/include/FifoWrite.h
	rm FifoWrite.o FifoRead.o

FifoWrite.o: FifoWrite.c
	gcc -c FifoWrite.c

FifoRead.o: FifoRead.c
	gcc -c FifoRead.c
