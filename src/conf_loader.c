#include <conf_loader.h>

CONFIG* fan_config = NULL;

CONFIG* load_config(char* config_path){

	//Load up a new config struct
	CONFIG* my_config = (CONFIG*) malloc(sizeof(CONFIG));

	//Open the file	
	FILE* conf_file = fopen(config_path,"r");

	//Collect the values
	int scan_ret = 0; 		//Allows us to examine the scan return.
	char conf_line[20];		//Holds a full line of input

	//Look at the line of the file
	while(fgets(conf_line,20,conf_file) != NULL){
			
		char keyword[MAX_KEYWORD_LEN]; //Buffer for the keyword only
		char* value; //Buffer for the keyword only

		//Pull out keyword
		scan_ret = sscanf(conf_line,"%s",keyword);
		if(scan_ret > 1){
			errx(1,"FAILED TO SCAN VALUE\n");
			return NULL;
		}

		//check keyword len
		if(strlen(keyword) >= MAX_KEYWORD_LEN){
			errx(1,strcat("MAX KEYWORD LEN EXCEEDED: \n",keyword));
			return NULL;
		}	

		//Pull out value (everything after the space)
		value = strchr(conf_line,' ') + 1; //+1 advances past the space

		

		//Read in the appropriate balue
		if(strcmp(keyword,"FAN_PIN") == 0){
			sscanf(value,"%hhi",&(my_config->fan_pin));
		} else if (strcmp(keyword,"POLL_TIME") == 0){
			sscanf(value,"%hhi",&(my_config->poll_time));
		} else if (strcmp(keyword,"ACTIVE_TEMP") == 0){
			sscanf(value,"%f",&(my_config->active_thresh));
		} else {
			char* err_msg = strcat("Unrecognized value: ",keyword);
			errx(1, strecat(err_msg,"\n");
			return NULL;
		}
	}

	//Close the file
	fclose(conf_file);

	if(validate_config(my_config) > 0){
		errx(2,"INVALID CONF FILE\n");
		return NULL;
	}

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
