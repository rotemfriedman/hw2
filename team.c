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
