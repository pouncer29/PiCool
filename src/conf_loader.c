#include <conf_loader.h>

CONFIG* fan_config = NULL;

CONFIG* load_config(char* config_path){

	//Load up a new config struct
	CONFIG* my_config = (CONFIG*) malloc(sizeof(CONFIG));

	//Open the file	
	FILE* conf_file = fopen(config_path,"r");

	//Collect the values
	uint8_t vals[3];
	int val = 0;
	while(fscanf(conf_file,"%s",vals[val])){
		val++;
	}

	//Assign Values
	my_config->fan_pin= vals[0];
	my_config->poll_time= vals[1];
	my_config->active_thresh= vals[2];

	return my_config;
}

uint8_t get_fan_pin(){
	return -1;
}

uint8_t get_poll_time(){
	return -1;
}

uint8_t get_active_temp(){
	return -1;
}

uint8_t get_cur_temp(){
	return -1;
}
