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
    if( driver==NULL || team==NULL ){        //if team or driver NULL finish the program.
        return;
    }
    driver->driver_team=team;
}

//get a driver, and return ptr to the name of the driver.
//If the func’ get NULL return NULL.
const char* DriverGetName(Driver driver){
    if (driver==NULL) {                      //if driver NULL finish the program
        return NULL;
    }
        return driver->driver_name;
}

//Get the driver name, id, and status.
//The func’ create new driver, and return the new driver from type driver.
Driver DriverCreate(DriverStatus* status, char* driver_name, int driverId) {
    *status=DRIVER_STATUS_OK;
    Driver new_driver = malloc(sizeof(*new_driver));
    if(new_driver == NULL) {
        *status = DRIVER_MEMORY_ERROR;
        return NULL;
    }
    if(driver_name==NULL || driverId<1){
        *status=INVALID_DRIVER;
        free(new_driver);
        return NULL;
    }
    char * local_driver_name=malloc(strlen(driver_name) + 1);
    if(local_driver_name == NULL) {
        *status = DRIVER_MEMORY_ERROR;
        free(new_driver);
        return NULL;
    }
    new_driver->id = driverId;                           //create the new driver with the input of new driver
    strcpy(local_driver_name, driver_name);
    new_driver->driver_name=local_driver_name;
    *status = DRIVER_STATUS_OK;
    new_driver->points=0;                                //initilize points to 0
    new_driver->driver_team=NULL;                        //initilize driver_team to null
    new_driver->driver_season=NULL;                      //initilize driver_season to null
    return new_driver;
}

//Get a driver , and return ptr to his team. If the function get NULL, return NULL
Team DriverGetTeam(Driver driver) {
    if (driver == NULL) {
        return NULL;
    }
        return driver->driver_team;
}

//the function DriverDestroy Get a driver and free the driver
void DriverDestroy(Driver driver){
    if(driver == NULL){               //if driver NULL finish the func'
        return;
    }
    free(driver->driver_name);
    free(driver);
}

//Get a driver and return his ID. If we get input null we return null.
int DriverGetId (Driver driver) {
    if (driver==NULL){
        return 0;
    }
        return driver->id;                  //return the id of the driver input
}

//Get a driver and a season.
//The func:
//1)	Update the season of the driver, based on the season that we get in the input.
//2)	 The Points of the driver will be zero 0.
void DriverSetSeason(Driver driver, Season season){
    if( driver==NULL || season==NULL ){                  //if driver or season null finish the function
        return;
    }
    driver->driver_season=season;
    driver->points=0;
}

//get a driver, and a parameter of status. return the number of points of the driver.
//if driver NULL return 0 and update status to INVALID_DRIVER
int DriverGetPoints(Driver driver, DriverStatus* status){
    if(driver==NULL){
        *status= INVALID_DRIVER;
        return 0;
    }else {
        *status=DRIVER_STATUS_OK;
        return driver->points;
    }
}

//*Get a driver, and a number of his position in a race.*//
//*The func’ update the points of the driver.*//
DriverStatus DriverAddRaceResult(Driver driver, int position){
    if( driver == NULL ) {
        return INVALID_DRIVER;
    }
    if(position<=0) {                          //if position not legal return INVALID_POSITION
        return INVALID_POSITION;
    }
    if(driver-> driver_season==NULL) {
        return SEASON_NOT_ASSIGNED;
    }
    int x= SeasonGetNumberOfDrivers(driver->driver_season);
    if(position>x) {
        return INVALID_POSITION;
    }
    int y= x-position;                           //hoe many points the driver get in the last race
    driver->points+=y;                           //update points of driver
    return DRIVER_STATUS_OK;
}