#include <conf_loader.h>

CONFIG* fan_config = NULL;

/**
 * Synopsis: Assigns the value within confline to the appropriate my_config field
 * precondition: conf_line is a line of input 
 * postcondition: my_config has been assigned a new value
 * return: 0 on success ,1 on bad keyword len.
 */
int assign_values(char* conf_line, CONFIG* my_config){

	//Check to see if this line contains more than one character
	if(strlen(conf_line) > 1){
			
		//conf_line i.e. FAN_PIN ##

		//Grab the index of the seperator
		char* seperator = index(conf_line, ' ');

		//The Char after the seperator begins the value
		char* value = seperator + 1;

		//Then, actually split the strings with a terminating char.
		*seperator = '\0';

		//Which means conf_line is now only the keyword
		char* keyword = conf_line;

		//check keyword len
		if(strlen(keyword) >= MAX_KEYWORD_LEN){
			errx(1,strcat(
				"INVALID CONF FILE: MAX KEYWORD LEN EXCEEDED:\n"
				,keyword)
			);
			return 1;
		}	



		//Read in the appropriate value  (CANDIATE FOR NEW FN())
		if(strcmp(keyword,"FAN_PIN") == 0){
			sscanf(value,"%hhi",&(my_config->fan_pin));
		} else if (strcmp(keyword,"POLL_TIME") == 0){
			sscanf(value,"%hhi",&(my_config->poll_time));
		} else if (strcmp(keyword,"ACTIVE_TEMP") == 0){
			sscanf(value,"%f",&(my_config->active_thresh));
		} //Else, we don't care what it is.
	}
	return 0;
}

/**
 * Synopsis: Reads the config file and assigns values to a newly created 
 * 	     config file
 * Preconditions: conf_file passed exists
 * Postconditions: CONFIG* fan_config struct is malloced, & assigned values
 * Return: Pointer to a new config object
 */
int load_config(char* config_path){

	//Load up a new config struct
	fan_config = (CONFIG*) malloc(sizeof(CONFIG));

	//Assign Default values
	fan_config->fan_pin = DEFAULT_FAN_PIN;
	fan_config->poll_time = DEFAULT_POLL_TIME;
	fan_config->active_thresh = DEFAULT_ACTIVE_TEMP;	

	//Open the file	
	FILE* conf_file = fopen(config_path,"r");
	
	if(conf_file == NULL){
		fprintf(stderr,"CONF FILE \"%s\" NOT FOUND.\n",config_path);
		return 1;
	}

	char conf_line[20];		//Holds a full line of input

	//Loop through file, and assign values
	while(fgets(conf_line,20,conf_file) != NULL){
		if(assign_values(conf_line,fan_config) != 0){
			fprintf(stderr,"Error assigning conf values: %s",config_path);
			return 2;
		}
	}

	//Close the file
	fclose(conf_file);

	if(validate_config(fan_config) > 0){
		fprintf(stderr,"INVALID CONF FILE\n");
		return 3;
	}

	//fan_config must now have values, or be invalid/null
	return 0;
}


/**
 * Frees the global "fan_config"
 */
int unload_config(){
	if(fan_config != NULL)
		free(fan_config);
	else
		return 1;

	return 0;
}

/**
 * Provides singleton like access to the config
 */
CONFIG* get_config(char* config_path){

	//If we were not given a config path, check to see if conf is loaded
	//if conf is loaded, return it
	if(config_path == NULL && fan_config != NULL){
		return fan_config;
	} else {
		//Otherwise load it 
		int did_load = load_config(config_path);

		//Check to see if return is OK or defaults assigned (NOT NULL)
		if(did_load != 0 || fan_config != NULL)
			return fan_config;
		else{
			fprintf(stderr,"FAILED TO GET CONFIG FILE %s",
				config_path);
			return NULL;
		}
	}
}

/**
 * Checks that the values of a given config struct are valid
 * return 0 on success, 1/2/3 on boundry error
 */
uint8_t validate_config(CONFIG* validate_me){
	
	//Grab the vars for easy access
	uint8_t fan_pin = validate_me->fan_pin;
	uint8_t poll_time= validate_me->poll_time;
	float active_thresh= validate_me->active_thresh;

	if(fan_pin > 30){
		fprintf(stderr,"FAN_PIN %d exceeds bounds [0,30]\n",fan_pin);
		return 1;
	}

	if(poll_time < 5){
		fprintf(stderr,"POLL_TIME %d exceeds bounds [5,255]\n",poll_time);
		return 2;
	}

	if(active_thresh <= 0.f){
		fprintf(stderr,"ACTIVE_THRESH %f exceeds bounds (0,FLOAT_MAX)\n",active_thresh);
		return 3;
	}
	
	return 0;
}

uint8_t get_fan_pin(){
	return fan_config->fan_pin;	
}

uint8_t get_poll_time(){
	return fan_config->poll_time;
}

float get_activation_temp(){
	return fan_config->active_thresh;
}
