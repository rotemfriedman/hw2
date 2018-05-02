#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver.h"
#include "team.h"
#include "season.h"
#include <assert.h>
#include <string.h>

int main() {
    SeasonStatus season_status;
    DriverStatus driver_status;

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
    int num_of_driver=SeasonGetNumberOfDrivers(season);
    int race_results[7] = {7,1,3,2,4,5,6};
    SeasonStatus season_status_1 = SeasonAddRaceResult(season, race_results);
    assert(season_status_1 == SEASON_OK);
    // int race_results2[7] = {1,7,3,4,5,6,2};
    //  season_status = SeasonAddRaceResult( season, race_results2);
    //assert(season_status == SEASON_OK);
    printpointTeam(season);
    int number_of_teams=SeasonGetNumberOfTeams(season);
    SeasonGetTeamByPosition(season, 2, season_status);
    /// / Team * array_team = SeasonGetTeamsStandings(season);
    //printPointArrayTeam(array_team, number_of_teams);
    //Driver d1=SeasonGetDriverByPosition(season,2,&season_status);
   // int x=DriverGetId(d1);
    //printf("the driver that his position in the second place : %x\n",x);

    //int DriverGetId(Driver driver);
    //Driver * temp_drive = Season_help_check (season)


  //  assert(season_status==SEASON_NULL_PTR);

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