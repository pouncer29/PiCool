all: fan_ctrl.o test_fan_ctrl

.PHONEY: clean

test_fan_ctrl: fan_ctrl.o
	@echo "MAKING FAN_CTRL TESTS"
	gcc $(CFLAGS) -o TEST_FAN_CTRL.out \
	fan_ctrl.tests.c \
	-I$(FAN_CTRL_DIR) -I$(CONFIG_DIR) \
	fan_ctrl.o

fan_ctrl.o: fan_ctrl.c fan_ctrl.h 
	@echo "MAKING FAN_CTRL"
	gcc $(CFLAGS) -c fan_ctrl.c \
	-I$(FAN_CTRL_DIR) -I$(CONFIG_DIR) \


clean:
	rm *.o
	rm *.out
