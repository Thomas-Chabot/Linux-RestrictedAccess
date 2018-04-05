all: tester.o
	gcc -o tester tester.o -llinkedlist

lib: linkedList.o
		ar rcs liblinkedlist.a linkedList.o
		sudo mv liblinkedlist.a /usr/lib/liblinkedlist.a
		sudo cp linkedList.h /usr/include/linkedList.h

tester.o: tester.c
	gcc -c tester.c

linkedList.o: linkedList.c
	gcc -c linkedList.c

clean: cleanLib
	rm -f *.o tester *~

cleanLib:
	sudo rm -f /usr/lib/liblinkedlist.a
	sudo rm -f /usr/include/linkedList.h
