#include "driver.h"
#include "team.h"
#include "season.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct season {
    int year;
    int number_of_teams;
    Team array_team;
    int number_of_drivers;
    Driver array_drivers;
};

Season SeasonCreate(SeasonStatus* status,const char* season_info){
    Season new_season = malloc(sizeof(*new_season));   //create the new season
    if(new_season == NULL) {
        *status = SEASON_MEMORY_ERROR;
        return NULL;
    }
    char *token=strtok(season_info, "\n");
    printf(" %s\n", token);
}
