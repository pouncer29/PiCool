#include <fan_ctrl.h>

/*
initialize_GPIO()
	info: uses 2.1 to get fan pin and initializes the appropriate sys files
		to enable GPIO on that pin
	synopsis:
		write pin# to /sys/class/gpio/export (to initialize)
		write 'out' to /sys/class/gpio/gpio<PIN#>/direction (to set output)
	params: none
	return: 1 on failure, 0 on success
*/
uint8_t initialize_GPIO(){

	//TODO: Check to see if everything has been configured first maybe....
	
	//Step ZERO: load the config file
	get_config(NULL);

	//Grab the string of the pin #
	char pin_num_str[3];
	uint8_t fan_pin = get_fan_pin();
	sprintf(pin_num_str,"%hhi",fan_pin);

	//Step ONE: write "PIN#" to GPIO_ROOT/export
	FILE* export_file = fopen(GPIO_path_plus("/export"),"w");
	if(NULL == export_file){	
		return 1;
	}
	//otherwise, we are good
	fprintf(export_file,"%s",pin_num_str);

	//TODO: WARNING - DEPENDING ON HOW FAST THIS WORKS, gpioXX may not exist.
	
	//Step TWO: write "out" to GPIO_ROOT/gpio<PIN>/direction

	//Load in our string
	int pin_path_len = strlen("/gpioXX/direction") + 1;
	char pin_path[pin_path_len];
	sprintf(pin_path,"/gpio%s/direction",pin_num_str);
	
	//Open our pin file
	FILE* fan_pin_file = fopen(GPIO_path_plus(pin_path),"w");
	if(NULL == fan_pin_file){	
		return 1;
	}

	//otherwise, we are good to set pin XX to output mode
	fprintf(fan_pin_file,"out");

	return 0;
}

uint8_t activate_fan(){
	return 255;
}
uint8_t deactivate_fan(){
	return 255;
}

/*
get_GPIO_path();
	info: uses alg C if no path set, otherwise returns the path needed to 
		activate/deactivate GPIO
	params: none
	return: char* the path to the GPIO file
		  the value '0' (/sys/class/gpio/gpio<PIN#>/value)
*/
char* get_GPIO_path(){
	uint8_t gpio_pin = get_fan_pin(); //Get fan_pin from config file

	//Assign it to a path
	char gpio_pin_path[strlen("/gpioxx/value")];
	sprintf(gpio_pin_path,"/gpio%hhi/value",gpio_pin);

	//construct the path
	char* pin_path = GPIO_path_plus(gpio_pin_path);
	return pin_path;
}

/**
 * synopsis: Gets the path to GPIO pin dir + an additonal path
 * params: char* path - the path to append to the end of the GPIO_ROOT
 * returns: char* the path to the GPIO root + additional path
 */
char* GPIO_path_plus(char* path){

	//If passed null, or empty string, we must just want the root path.
	if(NULL == path || strlen(path) == 0){
		return GPIO_ROOT;	
	} else {
		//otherwise, measure the lenght of the path in chars
		uint8_t path_len = strlen(GPIO_ROOT) + strlen(path);

		
		//allocate path_len char*
		char* full_path = (char*) malloc(path_len +1);
		*full_path = '\0';

		//Append GPIO_ROOT and PATH
		strcat(full_path,GPIO_ROOT);
		strcat(full_path,path);

		//and return the full path
		return full_path;
	}
}
