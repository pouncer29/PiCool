all: test_fan_ctrl fan_ctrl.o 

.PHONEY: clean

test_fan_ctrl: fan_ctrl.o
	@echo "MAKING FAN_CTRL TESTS"
	gcc $(CFLAGS) -o $(ROOT_DIR)/tests/TEST_FAN_CTRL.out \
	fan_ctrl.tests.c \
	fan_ctrl.o \
	-L$(LIB) -lconf \
	-I. -I$(CONFIG_DIR)

fan_ctrl.o: fan_ctrl.c fan_ctrl.h
	@echo "MAKING FAN_CTRL"
	gcc $(CFLAGS) -c fan_ctrl.c \
	-L$(LIB) -lconf \
	-I. -I$(CONFIG_DIR)

clean:
	rm *.o
	rm *.out
