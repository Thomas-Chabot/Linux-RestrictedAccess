Client: Client.o helpers.o functions.o
	gcc -o secure_folder Client.o helpers.o functions.o -lFifoReadWrite

tester: tester.o helpers.o
	gcc -o tester tester.o helpers.o

Client.o: Client.c
	gcc -c Client.c

tester.o: tester.c
	gcc -c tester.c

helpers.o: helpers/helpers.c
	gcc -c helpers/helpers.c

functions.o: functions/functions.c
	gcc -c functions/functions.c

clean:
	rm -f *.o tester helpers/*.o
