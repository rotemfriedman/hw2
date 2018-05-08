#include <stdio.h>



#include <stdlib.h>
#include "driver.h"
#include "team.h"
#include "season.h"
#include <assert.h>
#include <string.h>

int main() {

        printf("Testing Driver!\n");
        DriverStatus driver_status;
        TeamStatus team_status;
        Driver Lewis = DriverCreate(&driver_status, "Lewis", 44);
        Team Mercedes = TeamCreate(&team_status, "Mercedes");
        DriverSetTeam(Lewis, Mercedes);
        assert(strcmp(DriverGetName(Lewis),"Lewis")==0);
        assert(strcmp(TeamGetName(DriverGetTeam(Lewis)),"Mercedes")==0);

        team_status = TeamAddDriver(Mercedes,Lewis);
       const char * team_name = TeamGetName(Mercedes);
        printf("team name is (sposed to be mercedes) %s\n", team_name);
        Driver shaked = DriverCreate(&driver_status, "shakedi", 14);
        DriverSetTeam(shaked, Mercedes);
        team_status = TeamAddDriver(Mercedes,shaked);
        Driver d1 = TeamGetDriver(Mercedes, FIRST_DRIVER);

        const char* driver_name = DriverGetName(Lewis);
        printf("driver name is (sposed to be Leois) %s\n", driver_name);

        Team team1 = DriverGetTeam(shaked);
        int id_shaked =DriverGetId(shaked);
        printf("id= %d\n", id_shaked);

        DriverDestroy(Lewis);
        DriverDestroy(shaked);
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
None\n\
";
        Season season = SeasonCreate(&season_status,season_info);
        int race_results[7] = {1,2,3,4,5,6,7};
        SeasonAddRaceResult(season, race_results);
        int race_results1[7] = {7,6,5,4,3,2,1};
        SeasonAddRaceResult(season, race_results1);

         int number_of_drivers = SeasonGetNumberOfDrivers (season);
        int number_of_teams = SeasonGetNumberOfTeams(season);

        SeasonDestroy(season);
        printf("Finished Testing Driver!\n");

return 0;
}