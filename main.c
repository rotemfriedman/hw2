#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver.h"
#include "team.h"
#include "season.h"
#include <assert.h>
#include <string.h>

int main() {
    DriverStatus status_driver = DRIVER_STATUS_OK;
    SEASON_OK
    assert(status_season==SEASON_NULL_PTR);

    // Team * new_array_team = SeasonGetTeamsStandings(result);
    // int num_of_teams=SeasonGetNumberOfTeams(result);
    // for (int i=0; i<num_of_teams; i++){
    //     printf("%d", new_array_team[i]);
    // }

    //Team tean_position_3= SeasonGetDriverByPosition(result, 2, SeasonStatus* status);

    //DriverSetSeason(d1,result);
    //status_driver= DriverAddRaceResult(NULL,1);
    //assert(status_driver==INVALID_DRIVER);


    // int num_teams=SeasonGetNumberOfTeams(result);
    // int num_drivers=SeasonGetNumberOfDrivers(result);
    // printf("drivers=%d,teams=%d\n", num_drivers, num_teams);
    // DriverSetSeason(d1, result);

    //  int poi=DriverGetPoints(NULL,&status_driver);
    // printf("poi=%d\n",poi);

//    TeamStatus team_status=TEAM_STATUS_OK;

    //Team t1=TeamCreate(&status_team,"chevrolet");
    //TeamAddDriver(t1, d1);
    //TeamAddDriver(t1, d2);
    //Driver d3;
    //d//3=TeamGetDriver(NULL,SECOND_DRIVER);
    // if(d3!=NULL)
    //DriverSetTeam(d1,t1);
    //assert(strcmp(TeamGetName(DriverGetTeam(d1)),"evrolet")==0);
    //DriverSetTeam(d1,t1);
    //  int result=DriverGetId(d1);
    // assert(result==123);

    //Driver d1 = DriverCreate(&status, "driver", 123);
    //assert(status == DRIVER_STATUS_OK);
    //assert(d1 != NULL);
    // assert(DriverGetName(d1) == "driver");

    return 0;

}