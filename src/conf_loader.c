#include <conf_loader.h>

CONFIG* fan_config = NULL;

/**
 * Synopsis: Assigns the value within confline to the appropriate my_config field
 * precondition: conf_line is a line of input 
 * postcondition: my_config has been assigned a new value
 * return: 0 on success 1 on failed scan, 2 on bad keyword len, 
 */
int assign_values(char* conf_line, CONFIG* my_config){

	//Check to see if this line contains more than one character
	if(strlen(conf_line) > 1){
			
		char keyword[MAX_KEYWORD_LEN]; //Buffer for the keyword only
		char* value; //Buffer for the keyword only

		//Pull out keyword
		int scan_ret = sscanf(conf_line,"%s",keyword);
		if(scan_ret > 1){
			errx(1,"FAILED TO SCAN VALUE\n");
			return 1;
		}

		//check keyword len
		if(strlen(keyword) >= MAX_KEYWORD_LEN){
			errx(1,strcat(
				"INVALID CONF FILE: MAX KEYWORD LEN EXCEEDED:\n"
				,keyword)
			);
			return 2;
		}	

		//Pull out value (everything after the space)
		value = strchr(conf_line,' ') + 1; //+1 advances past the space


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
 * Postconditions: New config struct is created and assigned values
 * Return: Pointer to a new config object
 */
CONFIG* load_config(char* config_path){

	//Load up a new config struct
	CONFIG* my_config = (CONFIG*) malloc(sizeof(CONFIG));

	//TODO: Assign Default values maybe?

	//Open the file	
	FILE* conf_file = fopen(config_path,"r");
	
	if(conf_file == NULL){
		fprintf(stderr,"CONF FILE \"%s\" NOT FOUND.\n",config_path);
		return NULL;
	}

	char conf_line[20];		//Holds a full line of input

	//Loop through file, and assign values
	while(fgets(conf_line,20,conf_file) != NULL){
		if(assign_values(conf_line,my_config) != 0){
			return NULL;
		}
	}

	//Close the file
	fclose(conf_file);

	if(validate_config(my_config) > 0){
		fprintf(stderr,"INVALID CONF FILE\n");
		return NULL;
	}

	//my_config must now contain all that it had.
	return my_config;
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
	return -1;
}

uint8_t get_poll_time(){
	return -1;
}

float get_active_temp(){
	return -1;
}

float get_cur_temp(){
	return -1;
}
