#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <conf_loader.h>

int TEST_load_config();
int TEST_getters();
//int TEST_get_poll_time();
//int TEST_get_activation_temp();
//int TEST_get_cur_temp();


int main(){
	TEST_getters();
	TEST_load_config();
	return 0;
}

/**
 * Getter Tests
 */

/**
 * Tests the regualar use case. Fan pin in range
 * return: 0 on success, <RESULT_NUM> on error
 */
int get_fan_pin_fetches_properly(){
	uint8_t expected = 23;
	uint8_t actual = get_fan_pin();

	if(expected != actual){
		return actual;
	}
	return 0;
}

/**
 * Tests that an unset FAN_PIN results in default 23
 * return: 0 on success, <RESULT_NUM> on error
 */
int get_fan_pin_default_set(){
	uint8_t expected = 23;
	uint8_t actual = get_fan_pin();
	
	if(expected != actual){
		return actual;
	}
	return 0;
}



/**
 * Tests that poll_time is fetched from config properly
 * return: 0 on success, <RESULT_NUM> on error
 */
int get_poll_time_fetches_properly(){
	uint8_t expected = 5;
	uint8_t actual = get_poll_time();

	if(expected != actual){
		return actual;
	}
	return 0;
}

/*
 * Tests that an unset POLL_TIME results in default 60 seconds
 * return: 0 on success, <RESULT_NUM> on error
 */
int get_poll_time_default_set(){
	uint8_t expected = 60;
	uint8_t actual = get_poll_time();
	
	if(expected != actual){
		return actual;
	}
	return 0;
}


/** TEST GETTERS*/
int TEST_getters(){
	int result = 1;


	//TEST DEFAULT SET ON NO CONFIG PROVIDED
	result = get_fan_pin_default_set();

	if(result != 0){
		errx(result,"FAILED -- Expected default (23), actual %d\n", 
			result);
	} else {
		//Alert of Pass
		printf("get_fan_pin() sets default in default case -- PASSED\n");
	}

	
	//TEST BASIC USE CASE: POLL_TIME # SET PROPERLY
	result = get_fan_pin_fetches_properly();

	if(result != 0){
		errx(result,"FAILED -- Expected 28, actual %d\n", result);
	} else {
		printf("get_poll_time() gets proper value -- PASSED\n");
	}
	
	result = get_poll_time_default_set();

	if(result != 0){
		errx(result,"FAILED -- Expected default (60), actual %d\n", 
			result);
	} else {
		printf("get_poll_time() sets default in default case -- PASSED\n");
	}

	
	//TEST DEFAULT SET for get_
	result = get_poll_time_fetches_properly();

	if(result != 0){
		errx(result,"FAILED -- Expected 5, actual %d\n", result);
	} else {
		printf("get_poll_time() gets proper value -- PASSED\n");
	}

	return 0;
}

/**
	load_config TESTS
*/
int load_config_returns_CONFIG(){
	//Load Config
	CONFIG* my_config = load_config("./test_confs/test.picool.conf");

	//Check assignment
	assert(my_config != NULL);

	//Free on pass
	free(my_config);

	return 0;
}

int load_config_loads_values(){
	//These Values _MUST_ match the test.picool.conf values
	int conf_pin = 23; 
	int conf_poll = 5;
	float conf_thresh = 3.5f;

	//Load Config
	CONFIG* my_config = load_config("./test_confs/test.picool.conf");

	//Assert asssignment
	assert(my_config->fan_pin == conf_pin);
	assert(my_config->poll_time == conf_poll);
	assert(my_config->active_thresh == conf_thresh);
	free(my_config);

	return 0;
}

int load_config_ERR_on_bad_input(){
	
	//Bad config
	CONFIG* my_config = load_config("./test_confs/bad.picool.conf");
	assert(my_config == NULL);
	return 0;
}

int load_config_ERR_on_invalid_input(){

	//Empty Config
	CONFIG* my_config = load_config("./test_confs/invalid.picool.conf");
	assert(my_config == NULL);
	free(my_config);

	return 0;
}

int load_config_ERR_on_non_existing_file(){
	//File DNE
	CONFIG* my_config = load_config("./test_confs/Does_not_exist.picool.conf");
	assert(my_config == NULL);
	free(my_config);

	return 0;
} 

int load_config_ERR_on_empty_file(){
	//File DNE
	CONFIG* my_config = load_config("./test_confs/empty.picool.conf");
	assert(my_config == NULL);
	free(my_config);

	return 0;
} 


int TEST_load_config(){
	int result = 1;

	//CONFIG can be loaded
	result = load_config_returns_CONFIG();
	if(result != 0){
		errx(result,"Config returned non-CONFIG value\n");
	} else {
		//Alert of Pass
		printf("load_config() returns non-null -- PASSED\n");
	}
	
	//Config Loads Values
	result = load_config_loads_values();
	if(result != 0){
		errx(result,"FAILED -- load_config failed to assign values\n");
	} else {
		printf("load_config() reads/assigns values -- PASSED\n");
	}

	//NULL & ERRMSG on bad config
	result = load_config_ERR_on_bad_input();
	if(result != 0){
		errx(result,"load failed to error out on bad input");
	} else {
		printf("load_config() handles bad input -- PASSED\n");
	}

	//NULL & ERRMSG on invalid config
	result = load_config_ERR_on_invalid_input();
	if(result != 0){
		errx(result,"load failed to error out on invalid input\n");
	} else {
		printf("load_config() handles invalid input -- PASSED\n");
	}


	//NULL & ERRMSG on Non-existent Config
	result = load_config_ERR_on_non_existing_file();
	if(result != 0){
		errx(result,"load failed to error out on non-existent file\n");
	} else {
		printf("load_config() handles non-existent file -- PASSED\n");
	}
	
	//NULL & ERRMSG on empty Config
	result = load_config_ERR_on_empty_file();
	if(result != 0){
		errx(result,"load failed to error out on empty input");
	} else {
		printf("load_config() handles empty conf_file -- PASSED\n");
	}




	return 0;
}
/***************************************************************************/


