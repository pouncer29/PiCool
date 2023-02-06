all: conf_loader.o conf_loader.a test_conf_loader
default: conf_loader.a

.PHONEY: clean

test_conf_loader: conf_loader.o
	@echo "MAKING CONF_LOADER TESTS"
	gcc $(CFLAGS) -o $(ROOT_DIR)/tests/TEST_conf_loader.out \
	conf_loader.tests.c -I. conf_loader.o

conf_loader.a: conf_loader.o
	@echo "MAKING libconf"
	ar -rv $(ROOT_DIR)/lib/libconf.a conf_loader.o

conf_loader.o: conf_loader.c conf_loader.h 
	@echo "MAKING CONF_LOADER"
	gcc $(CFLAGS) -c conf_loader.c -I.


clean:
	rm *.o
