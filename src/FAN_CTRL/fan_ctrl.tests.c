#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <fan_ctrl.h>
#include <conf_loader.h>
#include <string.h>



int get_gpio_path_gets_correct_path(){

	//set_expectations
	char* expected = (char*) malloc(strlen("/gpio28") + \
		strlen(GPIO_ROOT));
	strcat(expected,GPIO_ROOT); //provide the ../../tests/test_gpio
	strcat(expected,"/gpio28"); //provide the full path

	char* result = get_GPIO_path();

	if(strcmp(expected,result) != 0){
		printf("get_GPIO_path() expected \"%s\", got \"%s\"\n",
			expected,result);
		return 1;
	}

	free(expected);
	return 0;
}


int gpio_path_plus_constructs_path(){

	//Set expectations
	char* test_path= "ADDITION";
	char* expected = NULL;
	expected = (char*) malloc(strlen(test_path) + strlen(GPIO_ROOT) + 1);

	//Construct expectations
	strcat(expected,GPIO_ROOT);
	strcat(expected,test_path);

	//Get the path
	char* result = GPIO_path_plus(test_path);

	//Check results
	if(strcmp(expected,result) != 0){
		printf("GPIO_path_plus() expected \"%s\", got \"%s\"\n",
			expected,result);
		return 1;
	}

	//Freee the var
	free(expected);

	return 0;
}

int gpio_path_plus_returns_ROOT_GPIO_PATH_when_NULL_or_empty(){

	//Set expectations
	char* expected = GPIO_ROOT;

	//Get the path
	char* result_NULL = GPIO_path_plus(NULL);
	char* result_empty = GPIO_path_plus("");

	//Check results
	if(strcmp(expected,result_NULL) != 0){
		printf("GPIO_path_plus() expected \"%s\", got \"%s\"\n",
			expected,result_NULL);
		return 1;
	} else if (strcmp(expected,result_empty) != 0){
		printf("GPIO_path_plus() expected \"%s\", got \"%s\"\n",
			expected,result_empty);
		return 2;
	}

	return 0;
}


/*
 write pin# to /sys/class/gpio/export (to initialize)
 write 'out' to /sys/class/gpio/gpio<PIN#>/direction (to set output)
*/
int init_gpio_initializes_proper_files(){
	return 1;
}

int init_gpio_writes_to_appropriate_file(){
	return 1;
}



void TEST_gpio_init(){
	int result = 1;

	//Path Constructor constructs paths
	result = gpio_path_plus_constructs_path();
	if(result != 0){
		errx(result,"FAILED -- GPIO_path_plus() did not append proper path\n");
	} else {
		//Alert of Pass
		printf("GPIO_path_plus() returns correct path -- PASSED\n");
	}


	result = gpio_path_plus_returns_ROOT_GPIO_PATH_when_NULL_or_empty();
	if(result == 1){
		errx(result,"FAILED -- GPIO_path_plus(): Failed when passed NULL\n");
	} else if(result == 2){
		errx(result,"FAILED -- GPIO_path_plus(): Failed when passed empty string\n");
	} else if(result == 0){
		//Alert of Pass
		printf("GPIO_path_plus() returns GPIO_ROOT when provided NULL or Empty -- PASSED\n");
	} else {
		errx(result,"FAILED -- GPIO_path_plus(): Failed with unknown error %d\n",result);
	}

	//GPIO path is fetched
	result = get_gpio_path_gets_correct_path();
	if(result != 0){
		errx(result,"FAILED -- get_GPIO_path(): Fetched path was incorrect\n");
	} else {
		//Alert of Pass
		printf("get_GPIO_path() returns correct path -- PASSED\n");
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
