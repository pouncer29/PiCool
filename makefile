export CFLAGS := -g -Wall -Wextra -DTEST
export ROOT_DIR := $(shell pwd)
export SRC := $(ROOT_DIR)/src
export LIB := $(ROOT_DIR)/lib
export CONFIG_DIR := $(SRC)/CONF_LOADER
export FAN_CTRL_DIR:= $(SRC)/FAN_CTRL

all: start conf_loader fan_ctrl

.PHONEY: all start conf_loader fan_ctrl

start:
	@echo "STATING"

conf_loader: 
	@echo "******************** MAKING CONF_LOADER ************************"
	$(MAKE) -C $(CONFIG_DIR)

fan_ctrl:
	@echo "********************* MAKING FAN_CTRL **************************"
	$(MAKE) -C $(FAN_CTRL_DIR)
