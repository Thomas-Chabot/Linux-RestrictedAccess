lib: fileIds.o
	ar rcs libFileIds.a fileIds.o
	sudo mv libFileIds.a /usr/lib/libFileIds.a
	sudo cp fileIds.h /usr/include/fileIds.h
	rm fileIds.o

test: fileIds.o tester.o
	gcc -o tester tester.o -lFileIds -luuid

fileIds.o: fileIds.c
	gcc -c fileIds.c

tester.o: tester.c
	gcc -c tester.c

clean: cleanLib
	rm -f *.o tester *~

cleanLib:
	sudo rm -f /usr/lib/libFileIds.a
	sudo rm -f /usr/include/fileIds.h
