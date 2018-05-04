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
    if(status==NULL ) {
        return NULL;
    }
    if(name==NULL){
       *status=TEAM_NULL_PTR;
        return NULL;
    }
    Team new_team = malloc(sizeof(*new_team));
    if(new_team == NULL) {
        *status = TEAM_MEMORY_ERROR;
        return NULL;
    }

    new_team->first_driver=NULL;
    new_team->second_driver=NULL;
    char * local_team_name= malloc(strlen(name) + 1);       //allocate a place for the name team. a local team name
    if( local_team_name== NULL) {
        *status = TEAM_MEMORY_ERROR;                      //update the status of the team
        free(new_team);
        return NULL;
    }

    strcpy(local_team_name, name);         //copy the name of the team, to the field new_team->name_team
    new_team->name_team=local_team_name;
    *status = TEAM_STATUS_OK;
    return new_team;

}

//*Get team. If the input null return null.
//Else return th  ptr to the begin of the string that her name there.
const char * TeamGetName(Team team){
    if (team==NULL){
        return NULL;
    }
        return team->name_team;

}

//Get name of Team and status
//The fanc return the number of points that the team collect untill now.
int TeamGetPoints(Team team, TeamStatus *status) {
    int total_points = 0;
    DriverStatus status_driver=DRIVER_STATUS_OK;
    if (team == NULL){
        *status = TEAM_NULL_PTR;
        return total_points;                             //total_points will be 0
    } else {
        if (team->first_driver != NULL){
            total_points=DriverGetPoints(team->first_driver,&status_driver); //status_driver cant be invalid, because the first_driver!=NULL
        }
        if (team->second_driver != NULL){
            total_points+=DriverGetPoints(team->second_driver,&status_driver);
        }
    }
    *status = TEAM_STATUS_OK;
    return total_points;
}

//this function destroy all the allocation that are under the struct team struct
//we need to destroy the name_team, the drivers, and the struct team
void TeamDestroy(Team team){
    if( team == NULL ){
        return;
    }
    free(team->name_team);
    free(team);
}

//Get a driver and a team, and add the driver to the current team.
//The func’ return status frim type TeamStatus
TeamStatus TeamAddDriver(Team team, Driver driver) {
    TeamStatus status;
    if (team == NULL || driver == NULL) {               //check if everything is ok, if the argument that we get is not NULL
        status = TEAM_NULL_PTR;
        return status;
    }
    if ((team->first_driver != NULL) && (team->second_driver != NULL)) {     //check if there is no place to more driver
        status = TEAM_FULL;
        return status;
    }
    if (team->first_driver == NULL) {
        team->first_driver = driver;                                         //insert the driver to the field "first_driver"
        status = TEAM_STATUS_OK;
        return status;
    } else {
        team->second_driver = driver;                                        //insert the driver to the field "second_driver"
        status = TEAM_STATUS_OK;
        return status;
    }
}

//The function get a team and a driver_number from a type of enum.
//return a pointer to the driver, on base of driver_number
Driver TeamGetDriver(Team team, DriverNumber driver_number){
    if(team==NULL)
        return NULL;
    if((driver_number != FIRST_DRIVER) && (driver_number != SECOND_DRIVER) )  //check also that driver number difference from NULL
        return  NULL;
    if(driver_number == FIRST_DRIVER) {                //check if we need to return the pointer of the first driver
        if(team->first_driver==NULL) {
            return NULL;
        }else
            return team->first_driver;
    } else {                                          //we need to return the pointer of the second driver
        if(team->second_driver==NULL)
            return NULL;
        else
            return team->second_driver;
    }

}

void print_the_position_team (Team team){
    printf("the team is %s", team->name_team);
}