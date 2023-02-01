all: conf_loader.o test_conf_loader

.PHONEY: clean

test_conf_loader: conf_loader.o
	@echo "MAKING CONF_LOADER TESTS"
	gcc $(CFLAGS) -o $(ROOT_DIR)/tests/TEST_conf_loader.out \
	conf_loader.tests.c -I. conf_loader.o

conf_loader.o: conf_loader.c conf_loader.h 
	@echo "MAKING CONF_LOADER"
	gcc $(CFLAGS) -c conf_loader.c -I.


clean:
	rm *.o
