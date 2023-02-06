#include <fan_ctrl.h>


uint8_t initialize_GPIO(){
	return 255;
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
		uint8_t path_len = strlen(GPIO_ROOT) + strlen(path) +1; //for \0

		
		//allocate path_len char*
		char* full_path = (char*) malloc(path_len);

		//Append GPIO_ROOT and PATH
		strcat(full_path,GPIO_ROOT);
		strcat(full_path,path);

		//and return the full path
		return full_path;
	}
}
