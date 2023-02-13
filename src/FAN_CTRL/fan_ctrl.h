/*
2.2 Fan_Control
----------------
Task: Activates or deactivates the fan based on calling name.
NOTE: To activate/deactivate, I'm not sure if we need to initialize the folder
or not.

Methods:
a) activate_fan()
	info: Uses 2.1a to get the fan pin # and writes to the appropriate 
	      file the value '1'
	params: none
	return: 1 on failure, 0 on success
b) deactivate_fan()
	info: Uses 2.1a to get the fan pin # and writes to the appropriate file 
		  the value '0' (/sys/class/gpio/gpio<PIN#>/value)
	params: none
	return: 1 on failure, 0 on success
c) initialize_GPIO()
	info: uses 2.1 to get fan pin and initializes the appropriate sys files
		to enable GPIO on that pin
	synopsis:
		write pin# to /sys/class/gpio/export (to initialize)
		write 'out' to /sys/class/gpio/gpio<PIN#>/direction (to set output)
	params: none
	return: 1 on failure, 0 on success
d) get_GPIO_path();
	info: uses alg C if no path set, otherwise returns the path needed to 
		activate/deactivate GPIO
	params: none
	return: char* the path to the GPIO file
*/

#ifndef FAN_CONFIG
#define FAN_CONFIG

#ifdef TEST //If we are TESTING, don't use the real deal.
	#define GPIO_ROOT "./gpio"
#else
	#define GPIO_ROOT "/sys/class/gpio"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <conf_loader.h>




uint8_t initialize_GPIO();
uint8_t activate_fan();
uint8_t deactivate_fan();
char* get_GPIO_path();
char* GPIO_path_plus(char*);

#endif
