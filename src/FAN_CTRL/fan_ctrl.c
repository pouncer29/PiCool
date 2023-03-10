#include <fan_ctrl.h>

uint8_t write_to_gpio_file(int state){

	//Get the Config
	get_config(NULL);
	
	//Construct the base_file path	
	char pin_num_str[strlen("/gpioxx/value")]; //Create a buffer for the string
	uint8_t fan_pin = get_fan_pin();
	sprintf(pin_num_str,"/gpio%hhi/value",fan_pin);
	
	//Open the file
	char* gpio_file_path = GPIO_path_plus(pin_num_str);
	FILE* gpio_file = fopen(gpio_file_path,"w");
	if(NULL == gpio_file){
		return 1;
	}

	//Write to the file
	fprintf(gpio_file,"%d",state);
	
	//free resources
	fclose(gpio_file);
	free(gpio_file_path);
	
	return 0;
}

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

	fclose(export_file);

	//TODO: WARNING - DEPENDING ON HOW FAST THIS WORKS, gpioXX may not exist.
	
	//Step TWO: write "out" to GPIO_ROOT/gpio<PIN>/direction

	//Load in our string
	int pin_path_len = strlen("/gpioXX/direction") + 1;
	char pin_path[pin_path_len];
	sprintf(pin_path,"/gpio%s/direction",pin_num_str);
	
	//Open our pin file
	char* pin_direction_path = GPIO_path_plus(pin_path);
	FILE* fan_pin_file = fopen(pin_direction_path,"w");
	if(NULL == fan_pin_file){	
		return 2;
	}

	//otherwise, we are good to set pin XX to output mode
	fprintf(fan_pin_file,"out");

	//And free any resources
	fclose(fan_pin_file);
	free(pin_direction_path);

	return 0;
}

uint8_t activate_fan(){
	return write_to_gpio_file(1);
}
uint8_t deactivate_fan(){
	return write_to_gpio_file(0);
}

/*
get_GPIO_path(): DEPRECATED
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


/*
 *FOR NEXT VERSION
 */
void handle_manual_on(){
	return;
}

/*
 *FOR NEXT VERSION
*/
void handle_auto_on(){
	return;
}
