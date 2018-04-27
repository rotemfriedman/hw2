#include "driver.h"
#include "team.h"
#include "season.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct driver {
    int id;
    char* driver_name;
    Team driver_team;
    int points;
    Season driver_season;
};

//*Get a driver and a team. The func’ update the deriver->team to be the current team the the func’ get.*//
void DriverSetTeam(Driver driver, Team team){
    driver->driver_team=team;
}


const char* DriverGetName(Driver driver){
    if (driver==NULL)
        return NULL;
    else
        return driver->driver_name;
}

Driver DriverCreate(DriverStatus* status, char* driver_name, int driverId) {
    Driver new_driver = malloc(sizeof(*new_driver));
    if(new_driver == NULL) {
        *status = DRIVER_MEMORY_ERROR;
        return NULL;
    }
    new_driver->driver_name = malloc(strlen(driver_name) + 1);
    if(new_driver->driver_name == NULL) {
        *status = DRIVER_MEMORY_ERROR;
        free(new_driver);
        return NULL;
    }
    new_driver->id = driverId;
    strcpy(new_driver->driver_name, driver_name);
    *status = DRIVER_STATUS_OK;
    return new_driver;

}

//Get a driver , and return ptr to his team. If the function get NULL, return NULL*//
Team DriverGetTeam(Driver driver) {
   if (driver == NULL) {
        return NULL;
   } else {
        return driver->driver_team;
    }
}

//const char* DriverGetName(Driver driver) {
 //   return driver->driver_name;
//}


//the function DriverDestroy Get a driver and free the driver*//
//void DriverDestroy(Driver driver){
//    free(driver);
//}


int DriverGetId (Driver driver) {
    if (driver==NULL){
        return (int)NULL;
    }
    else {
        return driver->id;
    }
}

void DriverSetSeason(Driver driver, Season season){
driver->driver_season=season;
    driver->points=0;
}

int DriverGetPoints(Driver driver, DriverStatus* status){
    if(driver==NULL){
        *status= INVALID_DRIVER;
    }
    else {
        *status=DRIVER_STATUS_OK;
        return driver->points;
    }
}