#include "driver.h"
#include "team.h"
#include "season.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//this static function used for the function: seasonCreate
static char * copyFileSeasonCreate(const char* season_info, SeasonStatus* status);                //function that copy the const file - "season_file" to other file
static int rowsNumberInSeasonInfo(char *token);
static void insertTheDataToSeason(Season season, char * season_info, Team *temp_team, Driver *temp_driver); //the main function that make the seasonCreate
static Season destroyMySeason(Season season);                               //function that destroy the season that we created in the SeasonCreate
static void destroyMyArray (Team *team, Driver *driver);                     //function that destroy the arrays of the teams and the drivers
static void destroyArrayByIndex (int team_index, int driver_index, Season season );   //
static Season destroyFinishInCreateSeason(Team *temp_team, Driver *temp_driver, Season season);

struct season {
    int year;
    int number_of_teams;
    Team *array_team;
    int number_of_drivers;
    Driver *array_drivers;
};

Season SeasonCreate(SeasonStatus* status,const char* season_info){
    Team *temp_team;           //pointer that help us to insert the data to the Team's array
    Driver *temp_driver;       //pointer that help us to insert the data to the Driver's araay
    Season new_season = malloc(sizeof(*new_season));   //create the new season
    if(new_season == NULL) {                     //free the season. return NULL
        *status = SEASON_MEMORY_ERROR;
        destroyMySeason(new_season);
    }
    char * my_season_info = copyFileSeasonCreate(season_info, status);
    char *token=strtok(my_season_info, "\n");
    int season_year=atoi(token);          //conveert char to int.
    new_season->year=season_year;      //insert the year to the season
    int team_number=(rowsNumberInSeasonInfo(token))/3;              //calculate the team number and the driver number with help of the rows number of the file.
    int total_driver_number=team_number*2;     ////the number of drivers that we have in the season, including NULL
    my_season_info = copyFileSeasonCreate(season_info, status); //start again and skip the year
    new_season->array_team=malloc(sizeof(*(new_season->array_team))*team_number);
    if((new_season->array_team) == NULL) {
        *status = SEASON_MEMORY_ERROR;
        free (new_season->array_team);
        destroyMySeason(new_season);
    }
    temp_team = new_season->array_team;
    new_season->array_drivers=malloc(sizeof(*(new_season->array_drivers))*total_driver_number);
    if((new_season->array_drivers) == NULL) {
        *status = SEASON_MEMORY_ERROR;
        destroyMyArray (new_season->array_team, new_season->array_drivers);
        destroyMySeason(new_season);    //this function return NULL
    }
    temp_driver=new_season->array_drivers;

    insertTheDataToSeason(new_season, my_season_info, temp_team, temp_driver);

    free(my_season_info);
    return new_season;
}

//copy the file season_info, to file my_season_info.
    static char * copyFileSeasonCreate(const char* season_info, SeasonStatus* status){
        int length_of_season_info=strlen(season_info);       //get the length of the file - season_info
        char* copy_season_info=malloc(sizeof(char)*length_of_season_info);
        if(copy_season_info == NULL) {
            *status = SEASON_MEMORY_ERROR;
            return NULL;
        }
        strcpy(copy_season_info, season_info);                        //copy the const array-"season_info", to "my_season_info"
        return copy_season_info;
    }

    static int rowsNumberInSeasonInfo(char *token){
        int rows=0;
        token=strtok(NULL, "\n");      //continue in the file, to the first team
        while(token != NULL)
        {
            rows++;             //rows increase in 1
            token=strtok(NULL, "\n");
        }
        return rows;
    }

    static Season destroyMySeason(Season season){
        free(season);
        return NULL;
    }

    static void destroyMyArray (Team *team, Driver *driver){
        free (team);
        free (driver);
}

    static void destroyArrayByIndex (int team_index, int driver_index, Season season ){
        int index;
        for(index=0; index<team_index; index++){          //we dont need to free the index-difference, because his allocation failed
             TeamDestroy(season->array_team[index]);
        }
        for (index = 0; index <driver_index ; index++) {
            DriverDestroy(season->array_drivers[index]);
        }
        destroyMyArray(season->array_team, season->array_drivers);       //free the arrays of team and the array of driver
    }

    static Season destroyFinishInCreateSeason(Team *temp_team, Driver *temp_driver, Season season){
        int difference_team=temp_team-(season->array_team);
        int difference_driver=temp_driver-(season->array_drivers);
        destroyArrayByIndex (difference_team, difference_driver, season);
        destroyMySeason(season);
    }

        static void insertTheDataToSeason(Season season, char * season_info, Team *temp_team, Driver *temp_driver){
        int get_id=1;             //the driver need to get a id
        DriverStatus status_driver;
        TeamStatus status_team;
        int team_number=0;
        char *token=strtok(season_info, "\n");
        token=strtok(NULL, "\n");
        while(token != NULL)
        {
            *temp_team=TeamCreate(&status_team,token);
            if (status_team == TEAM_MEMORY_ERROR){         //there was a memory error in the func' TeamCreate
                destroyFinishInCreateSeason(temp_team, temp_driver, season);
            }
            temp_team++;
            team_number++;
            token=strtok(NULL, "\n");                 //continue to the driver
            if(strcmp(token, "None")==0){
                token=strtok(NULL, "\n");                 //continue to the driver
            }
            else {
                *temp_driver=DriverCreate(&status_driver,token, get_id);
                if (status_driver == DRIVER_MEMORY_ERROR){         //there was a memory error in the func' DriverCreate
                    destroyFinishInCreateSeason(temp_team, temp_driver, season);
                }
                get_id++;                         //get_id +1 to the next driver
                temp_driver++;
                token=strtok(NULL, "\n");                 //continue to the driver
            }
            if(strcmp(token, "None")==0){
                token=strtok(NULL, "\n");                 //continue to the next team
                continue;
            }
            *temp_driver=DriverCreate(&status_driver,token, get_id);
            if (status_driver == DRIVER_MEMORY_ERROR){           //there was a memory error in the func' DriverCreate
                destroyFinishInCreateSeason(temp_team, temp_driver, season);
            }
            get_id++;                         //get_id +1 to the next driver
            temp_driver++;
            token=strtok(NULL, "\n");                 //continue to the next team
        }
        season->number_of_teams=team_number;
        season->number_of_drivers=get_id-1;
    }

    int SeasonGetNumberOfDrivers(Season season){
    return season->number_of_drivers;
}

int SeasonGetNumberOfTeams(Season season){
    return season->number_of_teams;
}