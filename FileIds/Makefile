all: fileIds.o tester.o
	gcc -o tester tester.o -lFileIds -luuid

lib: fileIds.o
	ar rcs libFileIds.a fileIds.o
	sudo mv libFileIds.a /usr/lib/libFileIds.a
	sudo cp fileIds.h /usr/include/fileIds.h
	rm fileIds.o

fileIds.o: fileIds.c
	gcc -c fileIds.c

tester.o: tester.c
	gcc -c tester.c

clean:
	rm -f *.o tester *~

cleanLib:
	sudo rm /usr/lib/libFileIds.a
	sudo rm /usr/include/fileIds.h
