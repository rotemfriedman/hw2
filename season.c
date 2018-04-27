#include "driver.h"
#include "team.h"
#include "season.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char * copyFileSeasonCreate(const char* season_info, SeasonStatus* status);                //function that copy the const file - "season_file" to other file

struct season {
    int year;
    int number_of_teams;
    Team *array_team;
    int number_of_drivers;
    Driver *array_drivers;
};

Season SeasonCreate(SeasonStatus* status,const char* season_info){
    int season_year;
    int rows_number=0;       //the rows number of the file "season_info"
    int team_number;          //the number of teams that we have in the season
    int total_driver_number;   //the number of drivers that we have in the season, including NULL
    char *token;              //used for the function strtok
    Team *temp_team;           //pointer that help us to insert the data to the Team's array
    Driver *temp_driver;       //pointer that help us to insert the data to the Driver's araay
    int get_id=1;             //the driver need to get a id
    DriverStatus status_driver;
    TeamStatus status_team;

    Season new_season = malloc(sizeof(*new_season));   //create the new season
    if(new_season == NULL) {
        *status = SEASON_MEMORY_ERROR;
        return NULL;
    }

    char * my_season_info = copyFileSeasonCreate(season_info, status);

     token=strtok(my_season_info, "\n");
    season_year=atoi(token);          //conveert char to int.
    new_season->year=season_year;

    token=strtok(NULL, "\n");      //continue in the file, to the first team
    while(token != NULL)
     {
        rows_number++;             //rows_number increase in 1
        token=strtok(NULL, "\n");
    }

    //calculate the team number and the driver number with help of the rows number of the file.
    team_number=rows_number/3;
    total_driver_number=team_number*2;

    //start again ans skip the year
    my_season_info = copyFileSeasonCreate(season_info, status);
    token=strtok(my_season_info, "\n");
    token=strtok(NULL, "\n");
    new_season->array_team=malloc(sizeof(*(new_season->array_team))*team_number);
    if((new_season->array_team) == NULL) {
        *status = SEASON_MEMORY_ERROR;
        return NULL;
    }
    temp_team = new_season->array_team;
    new_season->array_drivers=malloc(sizeof(*(new_season->array_drivers))*total_driver_number);
    if((new_season->array_drivers) == NULL) {
        *status = SEASON_MEMORY_ERROR;
        return NULL;
    }
    temp_driver=new_season->array_drivers;
    team_number=0;
    while(token != NULL)
    {
        if(strcmp(token, "None")==0){                 //check if the team=None
            token=strtok(NULL, "\n");
            token=strtok(NULL, "\n");
            token=strtok(NULL, "\n");
            continue;
        }
        *temp_team=TeamCreate(&status_team,token);
        if (status_team == TEAM_MEMORY_ERROR)         //there was a memory error in the func' TeamCreate
            continue;
        temp_team++;
        team_number++;
        token=strtok(NULL, "\n");                 //continue to the driver
        if(strcmp(token, "None")==0){
            token=strtok(NULL, "\n");                 //continue to the driver
        }
        else {
            *temp_driver=DriverCreate(&status_driver,token, get_id);
            if (status_driver == DRIVER_MEMORY_ERROR)       //there was a memory error in the func' DriverCreate
                continue;
            get_id++;                         //get_id +1 to the next driver
            temp_driver++;
            token=strtok(NULL, "\n");                 //continue to the driver
        }
        if(strcmp(token, "None")==0){
            token=strtok(NULL, "\n");                 //continue to the next team
            continue;
        }
        *temp_driver=DriverCreate(&status_driver,token, get_id);
        if (status_driver == DRIVER_MEMORY_ERROR)       //there was a memory error in the func' DriverCreate
            continue;
        get_id++;                         //get_id +1 to the next driver
        temp_driver++;
        token=strtok(NULL, "\n");                 //continue to the next team

    }
        new_season->number_of_teams=team_number;
        new_season->number_of_drivers=get_id-1;

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

int SeasonGetNumberOfDrivers(Season season){
    return season->number_of_drivers;
}

int SeasonGetNumberOfTeams(Season season){
    return season->number_of_teams;
}