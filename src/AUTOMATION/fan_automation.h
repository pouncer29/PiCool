/*2.3 Fan_Automation
-------------------
Task: Automates the fan process by monitoring temperature and activating/
	  deactivating the fan.
Methods:
	a) run()
	 info: Uses system 2.2 and 2.1 to monitor and activate the fan appropriately
	 params: none
	 return: never
	
	b) get_cur_temp() 
	info: Uses the native temperature reading functions of the system to grab 
          the temperature and returns it as an integer.
	temperature can be found at /sys/class/thermal/thermal_zone0/temp and divide
		this by 1000 to get degrees celcius
	params: none
	return: current temperature as an integer
*/


#ifndef FAN_AUTOMATION
#define FAN_AUTOMATION

#ifdef TEST //If we are TESTING, don't use the real deal.
	#define TEMPERATURE_FILE "./test_temperature/temp"
#else
	#define TEMPERATURE_FILE "/sys/class/thermal/thermal_zone0/temp"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <conf_loader.h>

int run();
float get_cur_temp();
int compare_float(float,float);

#endif
