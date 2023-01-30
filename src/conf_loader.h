#ifndef CONF_LOADER
#define CONF_LOADER

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#define VAL_MAX 255
#define MAX_KEYWORD_LEN 15

typedef struct{
	uint8_t fan_pin;
	uint8_t poll_time;
	float active_thresh;
} CONFIG;

CONFIG* get_config(char*);
int unload_config();
uint8_t validate_config(CONFIG*);
uint8_t get_fan_pin();
uint8_t get_poll_time();
float get_activation_temp();
float get_cur_temp();


#endif
