#include "driver.h"
#include "team.h"
#include "season.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    //copy the file season_info, to file my_season_info.
    int length_of_season_info=strlen(season_info);       //get the length of the file - season_info
    char* my_season_info=malloc(sizeof(char)*length_of_season_info);
    strcpy(my_season_info, season_info); //copy the const array-"season_info", to "my_season_info"

    token=strtok(my_season_info, "\n");
    season_year=atoi(token);          //conveert char to int.
    new_season->year=season_year;

    token=strtok(NULL, "\n");      //continue in the file, to the first team
    while(token != NULL)
    {
        rows_number++;
        token=strtok(NULL, "\n");
    }

    //calculate the team number and the driver number with help of the rows number of the file.
    team_number=rows_number/3;
    total_driver_number=team_number*2;

    //start again ans skip the year
    token=strtok(my_season_info, "\n");
    token=strtok(NULL, "\n");
    new_season->array_team=malloc(sizeof(*(new_season->array_team))*team_number);
    temp_team = new_season->array_team;
    new_season->array_drivers=malloc(sizeof(*(new_season->array_drivers))*total_driver_number);
    temp_driver=new_season->array_drivers;
     while(token != NULL)
    {

        *temp_team=TeamCreate(&status_team,token);
        temp_team++;
        token=strtok(NULL, "\n");                 //continue to the driver
        if(token == "None"){
            continue;
        }
        *temp_driver=DriverCreate(&status_driver,token, get_id);
        get_id++;                         //get_id +1 to the next driver
        temp_driver++;
        token=strtok(NULL, "\n");                 //continue to the driver
        if(token == "None"){
            continue;
        }
        *temp_driver=DriverCreate(&status_driver,token, get_id);
        get_id++;                         //get_id +1 to the next driver
        temp_driver++;
        token=strtok(NULL, "\n");                 //continue to the next team

    }
        new_season->number_of_teams=team_number;
        new_season->number_of_drivers=get_id-1;


    free(my_season_info);
}
