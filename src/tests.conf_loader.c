#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <conf_loader.h>

int TEST_load_config();
//int TEST_get_fan_pin();
//int TEST_get_poll_time();
//int TEST_get_activation_temp();
//int TEST_get_cur_temp();


int main(){
	printf("This is a test\n");
	TEST_load_config();
	return 0;
}

/**
	load_config TESTS
*/
int load_config_returns_CONFIG(){
	//Load Config
	CONFIG* my_config = load_config("./test.picool.conf");

	//Check assignment
	assert(my_config != NULL);

	//Free on pass
	free(my_config);

	return 0;
}

int load_config_loads_values(){
	//These Values _MUST_ match the test.picool.conf values
	int conf_pin = 1; 
	int conf_poll = 2;
	int conf_thresh = 3;

	//Load Config
	CONFIG* my_config = load_config("./test.picool.conf");

	//Assert asssignment
	assert(my_config->fan_pin == conf_pin);
	assert(my_config->poll_time == conf_poll);
	assert(my_config->active_thresh == conf_thresh);
	free(my_config);

	return 0;
}

int TEST_load_config(){
	int result = 1;

	result = load_config_returns_CONFIG();
	if(result != 0){
		errx(result,"Config returned non-CONFIG value\n");
	} else {
		//Alert of Pass
		printf("load_config() returns non-null -- PASSED\n");
	}
	
	result = load_config_loads_values();
	if(result != 0){
		errx(result,"load_config failed to assign values\n");
	} else {
		printf("load_config() reads/assigns values -- PASSED\n");
	}

	return 0;
}
/***************************************************************************/


