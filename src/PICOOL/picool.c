#include <picool.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

//Initialize global CONF
//fan_pin
//poll_time
//active_thresh
CONFIG* config = NULL;

void cleanup(){
	//Unload the config
	unload_config();
}

/**
 * First, load the conf file
 * Second, check the temperature
 * Third 	A, if temp is > thresh, activate fan
 * 		B, if temp is < thresh, deactivate fan
 * Fourth, sleep(<DURATION>) seconds
 */
int main(int argc, char* argv[]){

	//Register the cleanup handler
	signal(SIGINT,cleanup);
	signal(SIGQUIT,cleanup);

	//Load the config
	config = get_config(DEFAULT_CONF_FILE_LOC);

	if(config == NULL){
		fprintf(stderr,"ERROR: CONFIG FILE WAS NULL");
		return EXIT_FAILURE;
	}

	/** FOREVER */
	//HOld on, TODO: Free the config file on exit
	while(1){
		//If the read temp exceeds the threshold
		if(1 == temp_over_thresh(config->active_thresh)){
			//Activate the fan & Check return
			if(activate_fan() != 0){
				fprintf(stderr,"ERROR: FAILED TO ACTIVATE FAN");
			}
		} else {
			//Otherwise, deactivate it
			if(deactivate_fan() != 0){
				fprintf(stderr,"ERROR: FAILED TO DEACTIVATE FAN");
			}
		}

		//And then sleep for  the poll_time duration
		sleep(config->poll_time);
	}

}

