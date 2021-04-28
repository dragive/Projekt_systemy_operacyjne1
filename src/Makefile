output: main.o singleLine.o file.o commandEntity.o dayTime.o multithreading.o start_lib.o
	gcc -g main.o singleLine.o file.o commandEntity.o dayTime.o multithreading.o start_lib.o -lpthread -o output

main.o: main.c
	gcc -g -c main.c

filehandleTest.o: filehandleTest.c
	gcc -g -c filehandleTest.c

daemonTest.o: daemonTest.c
	gcc -g -c daemonTest.c

multithreading.o: multithreading.c multithreading.h
	gcc -g -c -lpthread multithreading.c

dayTime.o: dayTime.c dayTime.h
	gcc -g -c dayTime.c

commandEntity.o: commandEntity.c commandEntity.h
	gcc -g -c commandEntity.c

file.o: file.c file.h singleLine.c singleLine.h
	gcc -g -c file.c

singleLine.o: singleLine.c singleLine.h
	gcc -g -c singleLine.c

start_lib.o: start_lib.c start_lib.h
	gcc -g -c start_lib.c

clean:
	rm *.o output
