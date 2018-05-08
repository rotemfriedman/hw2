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
        int id_d1 =DriverGetId(d1);
        printf("id= %d\n", id_d1);

        const char* driver_name = DriverGetName(Lewis);
        printf("driver name is (sposed to be Leois) %s\n", driver_name);

        Team team1 = DriverGetTeam(shaked);
        const char * name = TeamGetName(team1);
        printf("name=%s", name);
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
None\n\
Mercedes\n\
None\n\
Valtteri Bottas\n\
RedBull Racing\n\
None\n\
Max  Verstappen\n\
McLaren\n\
Fernando Alonso\n\
None\n\
";
        Season season = SeasonCreate(&season_status,season_info);
        int race_results[4] = {1,2,3,4};
        SeasonAddRaceResult(season, race_results);
        int race_results1[4] = {4,3,2,1};
        SeasonAddRaceResult(season, race_results1);

         int number_of_drivers = SeasonGetNumberOfDrivers (season);
        int number_of_teams = SeasonGetNumberOfTeams(season);
        printf("num_team = %d, num_driver = %d\n", number_of_teams, number_of_drivers);

        Team team_number_1 = SeasonGetTeamByPosition(season, 4 , &season_status);
        Driver driver_number_1 = SeasonGetDriverByPosition(season, 1, &season_status);
        int id = DriverGetId(driver_number_1);
        printf("new_id=%d\n", id);
        const char * name1 = TeamGetName(team_number_1);
        printf( "name_team_position is = %s\n", name1);

        SeasonDestroy(season);
        printf("Finished Testing Driver!\n");

return 0;
}