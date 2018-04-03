all: tester.o
	gcc -o tester tester.o liblinkedlist.a

lib: linkedList.o
		ar rcs liblinkedlist.a linkedList.o

tester.o: tester.c
	gcc -c tester.c

linkedList.o: linkedList.c
	gcc -c linkedList.c

clean:
	rm -f *.o tester *~
