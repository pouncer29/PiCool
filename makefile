export CFLAGS := -g -Wall -Wextra #-DTEST
export ROOT_DIR := $(shell pwd)
export SRC := $(ROOT_DIR)/src
export LIB := $(ROOT_DIR)/lib
export BIN := $(ROOT_DIR)/bin
export CONFIG_DIR := $(SRC)/CONF_LOADER
export FAN_CTRL_DIR := $(SRC)/FAN_CTRL
export FAN_AUTOMATION_DIR:= $(SRC)/AUTOMATION
export PICOOL := $(SRC)/PICOOL

all: conf_loader fan_ctrl libpicool tests picool

default: picool

.PHONEY: all start conf_loader fan_ctrl fan_auto

picool:libpicool
	@echo "********************* MAKING PICOOL ****************************"
	$(MAKE) -C $(PICOOL)

libpicool: conf_loader fan_ctrl fan_auto
	@echo "MAKING libpicool"
	ar -rv $(LIB)/libpicool.a $(BIN)/*.o

conf_loader: 
	@echo "******************** MAKING CONF_LOADER ************************"
	$(MAKE) -C $(CONFIG_DIR)

fan_ctrl:
	@echo "********************* MAKING FAN_CTRL **************************"
	$(MAKE) -C $(FAN_CTRL_DIR)

fan_auto:
	@echo "****************** MAKING FAN_AUTOMATION ***********************"
	$(MAKE) -C $(FAN_AUTOMATION_DIR)

tests: libpicool
	@echo "****************** MAKING TESTS***********************"
clean:
	rm $(BIN)/*.o
	rm $(LIB)/*.a
