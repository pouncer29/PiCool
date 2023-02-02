#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <fan_ctrl.h>
#include <conf_loader.h>
#include <string.h>


int get_gpio_path_gets_correct_path(){

	//set_expectations
	char* expected = (char*) malloc(strlen("/gpio/gpio28") + \
		strlen(GPIO_ROOT));
	strcat(expected,GPIO_ROOT); //provide the ../../tests/test_gpio
	strcat(expected,"/gpio/gpio28"); //provide the full path

	char* result = get_GPIO_path();

	if(strcmp(expected,result) != 0){
		printf("get_GPIO_path() expected \"%s\", got \"%s\"\n",
			expected,result);
		return 1;
	}
	return 0;
}

/*
	write pin# to /sys/class/gpio/export (to initialize)
	write 'out' to /sys/class/gpio/gpio<PIN#>/direction (to set output)
*/
int init_gpio_initializes_proper_files(){
	//Check that /gpio/export contains 'pin#'

	int result = initialize_GPIO();


	//check that /gpio contains /gpio/gpiopin# contains 'out'

return 1;
	
}

int init_gpio_writes_to_appropriate_file(){
	return 1;
}



void TEST_gpio_init(){
	int result = 1;

	//GPIO path is fetched
	result = get_gpio_path_gets_correct_path();
	if(result != 0){
		errx(result,"FAILED -- Fetched path was incorrect\n");
	} else {
		//Alert of Pass
		printf("get_gpio_path() returns correct path -- PASSED\n");
	}

}

int main(){
	printf("TESTING FAN_CTRL\n");
	
	TEST_gpio_init();


	return 0;
}


/*
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
