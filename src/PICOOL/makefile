all: picool
default: picool

.PHONEY: clean

picool: 
	@echo "MAKING PI_COOL"
	gcc $(CFLAGS) picool.c \
	-L$(LIB) -lconf -lpicool \
	-I. -I$(CONFIG_DIR) -I$(FAN_CTRL_DIR) -I$(FAN_AUTOMATION_DIR) \
	-o picool.out
clean:
	rm *.out
