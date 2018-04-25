#include <stdio.h>
#include <string.h>
#include "driver.h"
#include "team.h"
#include "season.h"
#include <assert.h>

int main() {
    DriverStatus status = DRIVER_STATUS_OK;
    TeamStatus team_status=TEAM_STATUS_OK;
    Driver d1;
    //d1=DriverCreate(&status,"avi",123);
    Team t1=TeamCreate(&team_status,"chevrolet");
    const char* check=TeamGetName(NULL);
   if(check==0)
       printf("yes,DriverGetName");
    else
        printf("not,DriverGetName");

    //DriverSetTeam(d1,t1);

    //assert(strcmp(TeamGetName(DriverGetTeam(d1)),"chevrole")==0);

    //Driver d1 = DriverCreate(&status, "driver", 123);
    //assert(status == DRIVER_STATUS_OK);
    //assert(d1 != NULL);
    // assert(DriverGetName(d1) == "driver");

    return 0;
}