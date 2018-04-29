#include "driver.h"
#include "team.h"
#include "season.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct team{
    char* name_team ;
    Driver first_driver;
    Driver second_driver;
};

//*Get the name of the team, and pointer of status, from type TeamStatus* .Put in status value- memory_error/status ok*//
//*return a new team from a type team(that we create) and null if the team is not created.*//
Team TeamCreate(TeamStatus* status, char * name){
    Team new_team = malloc(sizeof(*new_team));
    if(new_team == NULL) {
        *status = DRIVER_MEMORY_ERROR;
        return NULL;
    }
    new_team->name_team = malloc(strlen(name) + 1);
    if(new_team->name_team == NULL) {
        *status = DRIVER_MEMORY_ERROR;
        free(new_team);
        return NULL;
    }
    strcpy(new_team->name_team, name);
    *status = DRIVER_STATUS_OK;
   new_team->first_driver=NULL;
   new_team->second_driver=NULL;
    return new_team;

}

//*Get team.If the input null return null.
//Else return th  ptr to the begin of the string that her name there.
const char * TeamGetName(Team team){
    if (team==NULL)
        return NULL;
    else
        return team->name_team;

}

int TeamGetPoints(Team team, TeamStatus *status) {
    int total_points = 0;
    DriverStatus status_driver;
    if (team == NULL){
        *status = TEAM_NULL_PTR;
        return total_points;     //total_points=0
    }
    else {
        *status = TEAM_STATUS_OK;
        if (team->first_driver != NULL){
            total_points=DriverGetPoints(team->first_driver,&status_driver); //status_driver cant be invalid, because the first_friver!=NULL
        }
        if (team->second_driver != NULL){
            total_points+=DriverGetPoints(team->second_driver,&status_driver);
        }
        return total_points;
    }
}

void TeamDestroy(Team team){
    free(team->name_team);
}

TeamStatus TeamAddDriver(Team team, Driver driver) {
    TeamStatus status;
    if (team == NULL || driver == NULL) {
        status = TEAM_NULL_PTR;
        return status;
    }
    if ((team->first_driver != NULL) && (team->second_driver != NULL)) {     //there is no place to more driver
        status = TEAM_FULL;
        return status;
    }
    if (team->first_driver == NULL) {
        team->first_driver = driver;
        status = TEAM_STATUS_OK;
        return status;
    } else {
        team->second_driver = driver;
        status = TEAM_STATUS_OK;
        return status;
    }
}




