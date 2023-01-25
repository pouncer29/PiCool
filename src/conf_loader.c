#include <conf_loader.h>

CONFIG* fan_config = NULL;

CONFIG* load_config(char* config_path){

	//Load up a new config struct
	CONFIG* my_config = (CONFIG*) malloc(sizeof(CONFIG));

	//Open the file	
	FILE* conf_file = fopen(config_path,"r");

	//Collect the values
	int count = 0;
	int scan_ret = 0;
	char conf_line[20];

	//Look at the line of the file
	while(fgets(conf_line,20,conf_file) != NULL){
			
		char keyword[10]; //Buffer for the keyword only
		char* value; //Buffer for the keyword only
		int pin_num = 0;
		int poll_time = 0;
		float active_thresh  = 0.0f;
	
		//Pull out it's keyword
		scan_ret = sscanf(conf_line,"%s",keyword);
		if(scan_ret > 1){
			return NULL;
		}
		value = strchr(conf_line,' ') + 1; //Get everything after the =

		if(strcmp(keyword,"FAN_PIN=") == 0){
			return NULL;
		} else {
			return NULL;
		}

		//TODO: evaluate keyword
	}

	fclose(conf_file);

	return my_config;
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
