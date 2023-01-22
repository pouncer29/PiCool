#ifndef CONF_LOADER
#define CONF_LOADER

#include <stdio.h>
#include <stdint.h>

typedef struct{
	uint8_t fan_pin;
	uint8_t poll_time;
	uint8_t active_thresh;
} CONFIG;

CONFIG* load_config();
uint8_t get_fan_pin();
uint8_t get_poll_time();
uint8_t get_activation_temp();
uint8_t get_cur_temp();


#endif
