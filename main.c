#include <stdio.h>
#include <string.h>
#include "driver.h"
#include "team.h"
#include "season.h"
#include <assert.h>

int main() {
    DriverStatus status_driver = DRIVER_STATUS_OK;
    SeasonStatus status_season = SEASON_OK;
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
    Season season = SeasonCreate(&status_season,season_info);


//    TeamStatus team_status=TEAM_STATUS_OK;
  //  Driver d1;
  //  d1=DriverCreate(&status,"avi",1323);
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