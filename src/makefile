all: conf_loader, tests
.PHONEY: clean

CFLAGS= -g -Wall -Wextra 

tests: test_conf_loader


test_conf_loader: conf_loader.o
	gcc $(CFLAGS) -o TEST_conf_loader.out conf_loader.tests.c -I. conf_loader.o

conf_loader.o: conf_loader.c conf_loader.h 
	gcc $(CFLAGS) -c conf_loader.c -I.


clean:
	rm *.o
	rm *.out
