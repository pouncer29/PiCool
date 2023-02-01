export CFLAGS := -g -Wall -Wextra 
export SRC := $(shell pwd)
export ROOT_DIR := $(SRC)/..
export CONFIG_DIR := $(SRC)/CONF_LOADER

all: start conf_loader

.PHONEY: all start conf_loader

start:
	@echo "STATING"

conf_loader: 
	@echo "******************** MAKING CONF_LOADER ************************"
	$(MAKE) -C $(CONFIG_DIR)
