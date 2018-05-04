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
	DriverStatus driver_status=DRIVER_STATUS_OK;
	TeamStatus team_status=TEAM_STATUS_OK;
	Driver Lewis = DriverCreate(&driver_status, "Lewis", 44);
	Driver shaked = DriverCreate(&driver_status, "shaked", 41);
	Driver rotem = DriverCreate(&driver_status, "rotem", 42);


	Team skoda =TeamCreate(&team_status, "skoda");

	TeamStatus status1= TeamAddDriver(skoda, shaked);
	TeamStatus status2=TeamAddDriver(skoda, NULL);
	TeamStatus status3=TeamAddDriver(skoda, rotem);
	TeamStatus status4=TeamAddDriver(skoda, Lewis);


	const char* string_name_skoda1=TeamGetName(skoda);
	const char* string_name_skoda2=TeamGetName(NULL);

	Driver d1 = TeamGetDriver(NULL, FIRST_DRIVER);

	int points =  TeamGetPoints(NULL, &team_status);
	printf("point=%d\n", points);

	DriverDestroy(Lewis);
	DriverDestroy(shaked);
	DriverDestroy(rotem);

	TeamDestroy(skoda);

	


	return 0;
}
