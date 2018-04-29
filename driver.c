#include "driver.h"
#include "team.h"
#include "season.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Season driverGetSeason (Driver driver);       //return the season of the driver


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
    new_driver->driver_team=NULL;
    new_driver->driver_season=NULL;
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
void DriverDestroy(Driver driver){
    free(driver->driver_name);
    free(driver);
}


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

//*Get a driver, and a number of his position in a race.*//
//*The func’ update the points of the driver.*//
DriverStatus DriverAddRaceResult(Driver driver, int position){
    if( driver == NULL )
    {
        return INVALID_DRIVER;
    }
    if(position<=0)
        return INVALID_POSITION;
    if(driver-> driver_season==NULL)
        return SEASON_NOT_ASSIGNED;
    int x= SeasonGetNumberOfDrivers(driver->driver_season);
    if(position>x)
        return INVALID_POSITION;
    int y= x-position;
    driver->points+=y;
    return DRIVER_STATUS_OK;

}

static Season driverGetSeason (Driver driver){
    return driver->driver_season;
}