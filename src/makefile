all: conf_loader, tests
.PHONEY: clean

tests: test_conf_loader

test_conf_loader: conf_loader.o
	gcc -Wall -Wextra -o TEST_conf_loader tests.conf_loader.c -I. conf_loader.o

conf_loader.o: conf_loader.c conf_loader.h 
	gcc -Wall -Wextra -c conf_loader.c -I.

clean:
	rm *.o
	rm *.a
	rm *.out
