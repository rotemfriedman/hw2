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
	SeasonStatus season_status=SEASON_OK;
	//TeamStatus team_status;
	Driver Lewis = DriverCreate(&driver_status, "Lewis", 44);
	DriverDestroy(Lewis);
	//Team Mercedes = TeamCreate(&team_status, "Mercedes");
	//DriverSetTeam(Lewis, Mercedes);
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
	int race_results[7] = {7, 1,3,2,4,5,6};

	SeasonAddRaceResult(season, race_results);
	DriverSetSeason(Lewis,season);
	SeasonDestroy(season);
	return 0;
}
