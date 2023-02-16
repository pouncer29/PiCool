all: test_fan_automation fan_automation.o 

.PHONEY: clean

test_fan_automation: fan_automation.o
	@echo "MAKING FAN_AUTOMATION TESTS"
	gcc $(CFLAGS) -o $(ROOT_DIR)/tests/TEST_FAN_AUTOMATION.out \
	fan_automation.tests.c \
	fan_automation.o \
	-L$(LIB) -lconf \
	-I. -I$(CONFIG_DIR)

fan_automation.o: fan_automation.c fan_automation.h
	@echo "MAKING FAN_AUTOMATION"
	gcc $(CFLAGS) -c fan_automation.c \
	-L$(LIB) -lconf \
	-I. -I$(CONFIG_DIR)

clean:
	rm *.o
	rm *.out
