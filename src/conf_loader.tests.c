#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <conf_loader.h>

int TEST_get_config();
int TEST_getters();
//int TEST_get_poll_time();
//int TEST_get_activation_temp();
//int TEST_get_cur_temp();


int main(){
	TEST_getters();
	TEST_get_config();
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
	//Get the config file
	get_config("./test_confs/test.picool.conf");

	//Set expectations
	uint8_t expected = 28;
	uint8_t actual = get_fan_pin();

	//Run test
	if(expected != actual){
		return actual;
	}

	unload_config();
	return 0;
}

/**
 * Tests that an unset FAN_PIN results in default 23
 * return: 0 on success, <RESULT_NUM> on error
 */
int get_fan_pin_default_set(){

	//Empty Case
	get_config("./test_confs/empty.picool.conf");
	uint8_t expected = 23;
	uint8_t actual = get_fan_pin();
	
	if(expected != actual){
		return actual;
	}



	//INVALID case
	get_config("./test_confs/invalid.picool.conf");
	actual = get_fan_pin();
	if(expected != actual){
		return actual;
	}


	//DNE case
	get_config("./test_confs/DNE.picool.conf");
	actual = get_fan_pin();
	if(expected != actual){
		return actual;
	}

	unload_config();

	return 0;
}



/**
 * Tests that poll_time is fetched from config properly
 * return: 0 on success, <RESULT_NUM> on error
 */
int get_poll_time_fetches_properly(){
	get_config("./test_confs/test.picool.conf");
	uint8_t expected = 5;
	uint8_t actual = get_poll_time();

	if(expected != actual){
		return actual;
	}

	unload_config();
	return 0;
}

/*
 * Tests that an unset POLL_TIME results in default 60 seconds
 * return: 0 on success, <RESULT_NUM> on error
 */
int get_poll_time_default_set(){

	//Empty Case
	get_config("./test_confs/empty.picool.conf");
	uint8_t expected = 60;
	uint8_t actual = get_poll_time();
	
	if(expected != actual){
		return actual;
	}



	//INVALID case
	get_config("./test_confs/invalid.picool.conf");
	actual = get_poll_time();
	if(expected != actual){
		return actual;
	}


	//DNE case
	get_config("./test_confs/DNE.picool.conf");
	actual = get_poll_time();
	if(expected != actual){
		return actual;
	}

	unload_config();

	return 0;
}

/**
 * Tests that active_thresh is fetched from config properly
 * return: 0 on success, <RESULT_NUM> on error
 */
int get_active_thresh_fetches_properly(){
	get_config("./test_confs/test.picool.conf");
	float expected = 5.5f;
	float actual = get_activation_temp();

	if(expected != actual){
		return actual;
	}

	unload_config();
	return 0;
}

/*
 * Tests that an unset active_thresh results in default 60 seconds
 * return: 0 on success, <RESULT_NUM> on error
 */
int get_active_thresh_default_set(){


	//Empty Case
	get_config("./test_confs/empty.picool.conf");
	float expected = 65.0f;
	float actual = get_activation_temp();
	
	if(expected != actual){
		return actual;
	}



	//INVALID case
	get_config("./test_confs/invalid.picool.conf");
	actual = get_activation_temp();
	if(expected != actual){
		return actual;
	}


	//DNE case
	get_config("./test_confs/DNE.picool.conf");
	actual = get_activation_temp();
	if(expected != actual){
		return actual;
	}

	unload_config();

	return 0;
}


/** TEST GETTERS*/
int TEST_getters(){
	int result = 1;


	//TEST DEFAULT SET ON NO CONFIG PROVIDED
	result = get_fan_pin_default_set();

	if(result != 0){
		errx(result,"FAILED -- get_fan_pin() Expected default (23), actual %d\n", 
			result);
	} else {
		//Alert of Pass
		printf("get_fan_pin() sets default in default case -- PASSED\n");
	}

	
	//TEST BASIC USE CASE: POLL_TIME # SET PROPERLY
	result = get_fan_pin_fetches_properly();

	if(result != 0){
		errx(result,"FAILED -- get_fan_pin() Expected 28, actual %d\n", result);
	} else {
		printf("get_fan_pin() gets proper value -- PASSED\n");
	}
	


	//TESTING POLL TIME RETRIVAL
	result = get_poll_time_default_set();

	if(result != 0){
		errx(result,"FAILED -- get_poll_time() Expected default (60), actual %d\n", 
			result);
	} else {
		printf("get_poll_time() sets default in default case -- PASSED\n");
	}

	
	result = get_poll_time_fetches_properly();

	if(result != 0){
		errx(result,"FAILED -- get_poll_time() Expected 5, actual %d\n", result);
	} else {
		printf("get_poll_time() gets proper value -- PASSED\n");
	}

	result = get_active_thresh_default_set();

	if(result != 0){
		errx(result,"FAILED -- get_activation_temp() Expected default (65.0), actual %d\n", 
			result);
	} else {
		printf("get_active_thresh() sets default in default case -- PASSED\n");
	}

	
	result = get_active_thresh_fetches_properly();

	if(result != 0){
		errx(result,"FAILED -- get_activation_temp() Expected 5.5, actual %d\n", result);
	} else {
		printf("get_active_thresh() gets proper value -- PASSED\n");
	}


	return 0;
}

/**
	get_config TESTS
*/
int get_config_returns_CONFIG(){
	//Load Config
	CONFIG* my_config = get_config("./test_confs/test.picool.conf");

	//Check assignment
	assert(my_config != NULL);

	//Free on pass
	free(my_config);

	return 0;
}

int get_config_loads_values(){
	//These Values _MUST_ match the test.picool.conf values
	int conf_pin = 28; 
	int conf_poll = 5;
	float conf_thresh = 5.5f;

	//Load Config
	CONFIG* my_config = get_config("./test_confs/test.picool.conf");

	//Assert asssignment
	assert(my_config->fan_pin == conf_pin);
	assert(my_config->poll_time == conf_poll);
	assert(my_config->active_thresh == conf_thresh);
	free(my_config);

	return 0;
}

int get_config_ERR_on_bad_input(){
	
	//Bad config
	CONFIG* my_config = get_config("./test_confs/bad.picool.conf");
	assert(my_config != NULL);
	return 0;
}

int get_config_ERR_on_invalid_input(){

	//Empty Config
	CONFIG* my_config = get_config("./test_confs/invalid.picool.conf");
	assert(my_config != NULL);
	free(my_config);

	return 0;
}

int get_config_ERR_on_non_existing_file(){
	//File DNE
	CONFIG* my_config = get_config("./test_confs/Does_not_exist.picool.conf");
	assert(my_config != NULL);
	free(my_config);

	return 0;
} 

int get_config_ERR_on_empty_file(){
	//File DNE
	CONFIG* my_config = get_config("./test_confs/empty.picool.conf");
	assert(my_config != NULL);
	free(my_config);

	return 0;
} 


int TEST_get_config(){
	int result = 1;

	//CONFIG can be loaded
	result = get_config_returns_CONFIG();
	if(result != 0){
		errx(result,"Config returned non-CONFIG value\n");
	} else {
		//Alert of Pass
		printf("get_config() returns non-null -- PASSED\n");
	}
	
	//Config Loads Values
	result = get_config_loads_values();
	if(result != 0){
		errx(result,"FAILED -- get_config failed to assign values\n");
	} else {
		printf("get_config() reads/assigns values -- PASSED\n");
	}

	//NULL & ERRMSG on bad config
	result = get_config_ERR_on_bad_input();
	if(result != 0){
		errx(result,"load failed to error out on bad input");
	} else {
		printf("get_config() handles bad input -- PASSED\n");
	}

	//NULL & ERRMSG on invalid config
	result = get_config_ERR_on_invalid_input();
	if(result != 0){
		errx(result,"load failed to error out on invalid input\n");
	} else {
		printf("get_config() handles invalid input -- PASSED\n");
	}


	//NULL & ERRMSG on Non-existent Config
	result = get_config_ERR_on_non_existing_file();
	if(result != 0){
		errx(result,"load failed to error out on non-existent file\n");
	} else {
		printf("get_config() handles non-existent file -- PASSED\n");
	}
	
	//NULL & ERRMSG on empty Config
	result = get_config_ERR_on_empty_file();
	if(result != 0){
		errx(result,"load failed to error out on empty input");
	} else {
		printf("get_config() handles empty conf_file -- PASSED\n");
	}




	return 0;
}
/***************************************************************************/


