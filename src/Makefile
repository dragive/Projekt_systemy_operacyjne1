output: filehandleTest.o singleLine.o file.o commandEntity.o dayTime.o
	gcc filehandleTest.o singleLine.o file.o commandEntity.o dayTime.o -fno-stack-protector -lpthread -o output

functionalitiesTest.o: functionalitiesTest.c
	gcc -c functionalitiesTest.c

filehandleTest.o: filehandleTest.c
	gcc -c filehandleTest.c

multithreadingTest.o: multithreadingTest.c
	gcc -c multithreadingTest.c

dayTime.o: dayTime.c dayTime.h
	gcc -c dayTime.c

commandEntity.o: commandEntity.c commandEntity.h
	gcc -c commandEntity.c

file.o: file.c file.h singleLine.c singleLine.h
	gcc -c file.c

singleLine.o: singleLine.c singleLine.h
	gcc -c singleLine.c



clean:
	rm *.o output
