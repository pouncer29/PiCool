all: conf_loader, tests
.PHONEY: clean

CFLAGS= -Wall -Wextra 

tests: test_conf_loader


test_conf_loader: conf_loader.o
	gcc $(CFLAGS) -g -o TEST_conf_loader tests.conf_loader.c -I. conf_loader.o

conf_loader.o: conf_loader.c conf_loader.h 
	gcc $(CFLAGS) -g -c conf_loader.c -I.


clean:
	rm *.o
	rm *.a
	rm *.out
