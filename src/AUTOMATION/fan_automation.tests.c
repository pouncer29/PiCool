#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <conf_loader.h>
#include <math.h>
#include <fan_automation.h>


int compare_float_compares_properly(){

	//have two really close values
	float greater = 5.005f;
	float lesser =  5.002f;

	//Check if we know what greater-than means...
	if(compare_float(greater,lesser) != 0){
		printf("%f > %f, compare_float says otherwise...\n",
			greater, lesser);
		return 1;
	} else if (compare_float(lesser,greater) != 1){
		printf("%f < %f, compare_float says otherwise...\n",
			lesser,greater);
		return 1;
	} 

	//Otherwise, return success
	return 0;
}


int get_temp_reads_proper_value(){
	float result = get_cur_temp();
	float expected = 55.5f;

	if (fabs(expected - result) > 0.0001){
		printf("get_cur_temp() expectef %f, got %f\n",expected,result);
		return -1;
	}

	return 0;
}


int main(){
	int result = 1;


	result = compare_float_compares_properly();
	if(result != 0){
		errx(result,"FAILED -- compare_float() compaired incorrectly\n");
	} else {
		//Alert of Pass
		printf("compare_float() does proper comparison -- PASSED\n");
	}


	result = get_temp_reads_proper_value();
	if(result != 0){
		errx(result,"FAILED -- get_cur_temp() failed to retrieve temperature\n");
	} else {
		//Alert of Pass
		printf("get_cur_temp() fetches temperature -- PASSED\n");
	}

	return 0;
}


