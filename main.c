/*
 * test_eclipce.c
 *
 *  Created on: Apr 9, 2018
 *      Author: muhamadg
 */

#include<stdio.h>
#include<stdlib.h>
#include"driver.h"
#include"team.h"
#include"season.h"
#include<assert.h>
#include<string.h>


int main(){
	printf("starting to run the unit tests! change\n");
//	DriverUnitTest();
//	TeamUnitTest();
//	SeasonUnitTest();

	//DriverStatus driver_status;

	SeasonStatus season_status;
	char* season_info="\
2018\n\
Ferrari\n\
Sebastian Vettel\n\
Kimi Raikonen\n\
Mercedes\n\
Lewis Hamilton\n\
Valtteri Bottas\n\
RedBull Racing\n\
Daniel\n\
Max  Verstappen\n\
McLaren\n\
Fernando Alonso\n\
None\n\
";
	Season season = SeasonCreate(&season_status,season_info);
	SeasonDestroy(season);
	printf("Finished Testing Driver!\n");
	return 0;
}
