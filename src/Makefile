output: daemonTest.o singleLine.o file.o commandEntity.o dayTime.o multithreading.o
	gcc daemonTest.o singleLine.o file.o commandEntity.o dayTime.o multithreading.o -lpthread -o output

functionalitiesTest.o: functionalitiesTest.c
	gcc -c functionalitiesTest.c

filehandleTest.o: filehandleTest.c
	gcc -c filehandleTest.c

daemonTest.o: daemonTest.c
	gcc -c daemonTest.c

multithreadingTest.o: multithreadingTest.c
	gcc -c multithreadingTest.c

multithreading.o: multithreading.c multithreading.h
	gcc -c -lpthread multithreading.c

dayTime.o: dayTime.c dayTime.h
	gcc -c dayTime.c

commandEntity.o: commandEntity.c commandEntity.h
	gcc -c commandEntity.c

file.o: file.c file.h singleLine.c singleLine.h
	gcc -c file.c

singleLine.o: singleLine.c singleLine.h
	gcc -c singleLine.c

newFile.o: newFile.c newFile.h singleLine.c singleLine.h
	gcc -c newFile.c

clean:
	rm *.o output
