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

	DriverStatus driver_status;
	Driver Lewis1 = DriverCreate(&driver_status, "Lewis", 44);
	Team team;
	TeamStatus status_team;
	team=TeamCreate(&status_team , "skoda");
	DriverDestroy(Lewis1);
	TeamDestroy(team);
	return 0;
}
