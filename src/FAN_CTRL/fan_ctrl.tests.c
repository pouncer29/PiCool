#include <fan_ctrl.h>
#include <conf_loader.h>
#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int get_gpio_path_gets_correct_path(){


	//Setup the config
	char* config_path = "../tests/test_confs/default.picool.conf";
	CONFIG* config = get_config(config_path);	
	int expected_size = strlen("/gpio23/value") + strlen(GPIO_ROOT);

	//set_expectations
	
	//initialize and declare expected
	char expected[expected_size];
	strncpy(expected,"",expected_size);

	//Build the expected value
	strcat(expected,GPIO_ROOT); //provide the ../../tests/test_gpio
	strcat(expected,"/gpio23/value"); //provide the full path

	char* result = get_GPIO_path();

	if(strcmp(expected,result) != 0){
		printf("get_GPIO_path() expected \"%s\", got \"%s\"\n",
			expected,result);
		return 1;
	}

	return 0;
}


int gpio_path_plus_constructs_path(){

	//Set expectations
	char* test_path= "ADDITION";
	char* expected = NULL;
	expected = (char*) malloc(strlen(test_path) + strlen(GPIO_ROOT) + 1);
	*expected = '\0';

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
int init_gpio_initializes_file_properly(){
	uint8_t initialize_result = initialize_GPIO();

	// If we report error, then it failed... duh.
	if(initialize_result != 0){
		printf("initialize_GPIO() returned error: %hhi \n", 
			initialize_result);
		return initialize_result;
	}

	//First we check if the export stage was hit
	char* export_file_path = GPIO_path_plus("/export");
	FILE* export_file = fopen(export_file_path,"r");
	if(NULL == export_file){
			printf("failed to open \"export\" file: %s\n",
			export_file_path);
		return -1;
	} 

	//Then check if the 'out' stage was hit
	char* pin_mode_path = GPIO_path_plus("/gpio23/direction");
	FILE* pin_mode_file = fopen(pin_mode_path,"r");
	if(NULL == pin_mode_file){
		printf("failed to open \"mode\" file: %s\n",
			pin_mode_path);
		return -1;
	}

	//Then check if they contain the proper values
	char buffer[4];

	//Read the export file
	int did_scan = fscanf(export_file,"%s",buffer);
	if(did_scan == 1){
		if(strcmp("23",buffer) != 0){
			printf("export file contained %s, expected %s\n",
				buffer,"23");
			return -2;
		}
	} else {
		return -3;
	}

	//read the pin file
	if(fscanf(pin_mode_file,"%s",buffer) == 1){
		if(strcmp("out",buffer) != 0){
			printf("Out file contained %s, expected %s\n",
				buffer,"out");
			return -2;
		}
	} else {
		return -3;
	}

	return 0;
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

	//GPIO export file is initialized properly
	result = init_gpio_initializes_file_properly();
	if(result != 0){
		errx(result,"FAILED -- initialize_GPIO(): Failed to initalize GPIO\n");
	} else {
		//Alert of Pass
		printf("initialize_GPIO() initialized the proper file to proper values -- PASSED\n");
	}
}

int activate_fan_writes_proper_value_to_file(){
	int success = activate_fan();
	return success;
}

int deactivate_fan_writes_proper_value_to_file(){
	int success = deactivate_fan();
	return success;
}

void TEST_gpio_ctrl(){
	int result = 1;

	//Path Constructor constructs paths
	result = activate_fan_writes_proper_value_to_file();
	if(result != 0){
		errx(result,"FAILED -- activate_fan() did not write correctly\n");
	} else {
		//Alert of Pass
		printf("activate_fan() writes proper value to proper file -- PASSED\n");
	}
	
	result = deactivate_fan_writes_proper_value_to_file();
	if(result != 0){
		errx(result,"FAILED -- deactivate_fan() did not write correctly\n");
	} else {
		//Alert of Pass
		printf("deactivate_fan() writes proper value to proper file -- PASSED\n");
	}

}

int main(){
	printf("TESTING FAN_CTRL\n");
	TEST_gpio_ctrl();
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
