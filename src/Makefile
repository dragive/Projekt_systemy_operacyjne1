output: daemonTest.o singleLine.o file.o commandEntity.o dayTime.o multithreading.o daemon_start.o
	gcc daemonTest.o singleLine.o file.o commandEntity.o dayTime.o multithreading.o daemon_start.o -lpthread -o output

ultimateGamerVersion.o: ultimateGamerVersion.c
	gcc -c ultimateGamerVersion.c

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

start_lib.o: start_lib.c start_lib.h
	gcc -c start_lib.c

daemon_start.o: daemon_start.c daemon_start.h
	gcc -c daemon_start.c

clean:
	rm *.o output
