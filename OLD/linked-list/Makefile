all: linkedList.o tester.o
	gcc -o tester linkedList.o tester.o

tester.o: tester.c
	gcc -c tester.c

linkedList.o: linkedList.c
	gcc -c linkedList.c

clean:
	rm -f *.o tester *~
