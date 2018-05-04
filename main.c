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
	printf("starting to run the unit tests!\n");

	DriverStatus driver_status;
	TeamStatus team_status;

	Driver Lewis = DriverCreate(&driver_status, "Lewis", 44);
	Team Mercedes = TeamCreate(&team_status, "Mercedes");
	DriverSetTeam(Lewis, Mercedes);
	assert(strcmp(DriverGetName(Lewis),"Lewis")==0);
	assert(strcmp(TeamGetName(DriverGetTeam(Lewis)),"Mercedes")==0);

	DriverDestroy(Lewis);
	TeamDestroy(Mercedes);

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
shak\n\
";
	Season season = SeasonCreate(&season_status,season_info);

	int number_of_driver=SeasonGetNumberOfDrivers(season);
	int number_of_team=SeasonGetNumberOfTeams(season);
	printf("numDr=%d, numTe=%d\n", number_of_driver, number_of_team);

	int race_results[8] = {1,2,3,4,5,6,7,8};
	season_status = SeasonAddRaceResult(season, race_results);
	int race_results1[8] = {8,7,6,5,4,3,2,1};
	season_status = SeasonAddRaceResult(season, race_results1);

	assert(season_status==SEASON_OK);

	printpointTeam(season);

	Team team_in = SeasonGetTeamByPosition(NULL, 0 , &season_status);
	const char * name_team = TeamGetName(team_in);
	printf("the team is = %s\n", name_team);
	SeasonDestroy(season);

	return 0;
}
