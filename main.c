#include <stdio.h>
#include <string.h>
#include "driver.h"
#include "team.h"
#include "season.h"
#include <assert.h>
#

int main() {
    DriverStatus status_driver = DRIVER_STATUS_OK;
    SeasonStatus status_season = SEASON_OK;
    Driver d1=DriverCreate(&status_driver,"Lewis Hamilton",1);
    char* season_info="\
2018\n\
Folo\n\
None\n\
None\n\
Mercedes\n\
Lewis Hamilton\n\
Valtteri Bottas\n\
RedBull Racing\n\
None\n\
Max  Verstappen\n\
McLaren\n\
Fernando Alonso\n\
shaked\n\
";

    Season result;
    result= SeasonCreate(&status_season,season_info);
    SeasonDestroy(result);
    DriverSetSeason(d1, result);
    int poi=DriverGetPoints(d1,&status_driver);
printf("points=%d", poi);

    //  DriverSetSeason(d1,result);
   // status_driver= DriverAddRaceResult(NULL,1);
    // assert(status_driver==INVALID_DRIVER);


  //  print_points(d1);


    // int num_teams=SeasonGetNumberOfTeams(result);
   // int num_drivers=SeasonGetNumberOfDrivers(result);
   // printf("drivers=%d,teams=%d\n", num_drivers, num_teams);

   // printf("poi=%d\n",poi);

//    TeamStatus team_status=TEAM_STATUS_OK;
    //Team t1=TeamCreate(&team_status,"chevrolet");
 //   const char* check=TeamGetName(NULL);
 //  if(check==0)
  //     printf("yes,DriverGetName");
  //  else
   //     printf("not,DriverGetName");

    //DriverSetTeam(d1,t1);
  //  int result=DriverGetId(d1);
   // assert(result==123);

    //Driver d1 = DriverCreate(&status, "driver", 123);
    //assert(status == DRIVER_STATUS_OK);
    //assert(d1 != NULL);
    // assert(DriverGetName(d1) == "driver");

    return 0;
}