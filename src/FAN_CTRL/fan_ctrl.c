#include <fan_ctrl.h>


uint8_t initialize_GPIO(){
	return 255;
}

uint8_t activate_fan(){
	return 255;
}
uint8_t deactivate_fan(){
	return 255;
}

char* get_GPIO_path(){
	return "IMPLEMENT ME";
}

/**
 * synopsis: Gets the path to GPIO pin dir + an additonal path
 * params: char* path - the path to append to the end of the GPIO_ROOT
 * returns: char* the path to the GPIO root + additional path
 */
char* GPIO_path_plus(char* path){
	//Calculate string length 
	uint8_t path_len = strlen(GPIO_ROOT) + strlen(path) +1; //for \0
	
	//allocate and init path_len
	char* full_path = NULL;
	full_path = (char*) malloc(path_len);

	//Append GPIO_ROOT and PATH
	strcat(full_path,GPIO_ROOT);
	strcat(full_path,path);

	return full_path;
}
