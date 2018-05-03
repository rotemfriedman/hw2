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
static void destroyFinishInCreateSeason(Team *temp_team, Driver *temp_driver, Season season);
///////////////////////////////////////////////////////////////////////////////////////////////
//SeasonGetDriversStandings help and SeasonGetTeamsStandings help
//static void seasonSwapDriver(Driver *drivers1,Driver *drivers2);
//static void seasonMinSortDriver(Season season, Driver *array_dr ivers,int size_array);

static void seasonSwapTeam(Team *teams1,Team *teams2);
static void  seasonMinSortTeam(Season season, Team *array_teams,int size_array, TeamStatus * team_status);
static void seasonCopyTheArrayTeam(Season season, Team * array_team, int size_of_array);
static int seasonFindTheMinTeam (Season season, Team * array_team, int size_of_array, TeamStatus *team_status);
static void seasonSwapDriver(Driver *drivers1,Driver *drivers2);
static void seasonMinSortDriver(Season season,Driver *array_drivers,int size_array,DriverStatus *driver_status);
static void seasonCopyTheArrayDriver(Season season, Driver *array_drivers, int size_of_array);
static int seasonFindTheMinDriver (Season season, Driver *array_drivers, int size_of_array,DriverStatus *driver_status);
static void idGetDriver(Season season);

struct season {
    int year;
    int number_of_teams;
    Team *array_team;
    int number_of_drivers;
    Driver *array_drivers;
    int * race_result;
};

Season SeasonCreate(SeasonStatus* status,const char* season_info){
    Team *temp_team = NULL;           //pointer that help us to insert the data to the Team's array
    Driver *temp_driver=NULL;       //pointer that help us to insert the data to the Driver's araay
    Season new_season = malloc(sizeof(*new_season));   //create the new season
    if(new_season == NULL) {                     //free the season. return NULL
        *status = SEASON_MEMORY_ERROR;
        destroyMySeason(new_season);
    }
    char * my_season_info = copyFileSeasonCreate(season_info, status);
    if( *status == SEASON_MEMORY_ERROR ){          //there was a error memory. return NULL
        destroyMySeason(new_season);
    }
    char *token=strtok(my_season_info, "\n");
    int season_year=atoi(token);          //conveert char to int.
    new_season->year=season_year;      //insert the year to the season
    int team_number=(rowsNumberInSeasonInfo(token))/3;              //calculate the team number and the driver number with help of the rows number of the file.
    int total_driver_number=team_number*2;     ////the number of drivers that we have in the season, including NULL
    my_season_info = copyFileSeasonCreate(season_info, status); //start again and skip the year
    if( *status == SEASON_MEMORY_ERROR ){          //there was a error memory. return NULL
        destroyMySeason(new_season);
    }
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
    int length_of_season_info=strlen(season_info)+1;       //get the length of the file - season_info
    char* copy_season_info=malloc(sizeof(char)*length_of_season_info);
    if(copy_season_info == NULL) {
        *status = SEASON_MEMORY_ERROR;
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

static void destroyFinishInCreateSeason(Team *temp_team, Driver *temp_driver, Season season){
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
        if (status_team == TEAM_MEMORY_ERROR) {         //there was a memory error in the func' TeamCreate
            destroyFinishInCreateSeason(temp_team, temp_driver, season);
        }
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
            DriverSetTeam(*temp_driver, *temp_team);
            DriverSetSeason(*temp_driver, season);
            status_team = TeamAddDriver(*temp_team, *temp_driver);
            get_id++;                                 //get_id +1 to the next driver
            temp_driver++;
            token=strtok(NULL, "\n");                 //continue to the driver
        }
        if(strcmp(token, "None")==0){
            token=strtok(NULL, "\n");                 //continue to the next team
            temp_team++;
            continue;
        }
        *temp_driver=DriverCreate(&status_driver,token, get_id);
        if (status_driver == DRIVER_MEMORY_ERROR){           //there was a memory error in the func' DriverCreate
            destroyFinishInCreateSeason(temp_team, temp_driver, season);
        }
        DriverSetTeam(*temp_driver, *temp_team);
        DriverSetSeason(*temp_driver, season);
        status_team = TeamAddDriver(*temp_team, *temp_driver);
        get_id++;                         //get_id +1 to the next driver
        temp_driver++;
        token=strtok(NULL, "\n");                 //continue to the next team
        temp_team++;
    }
    season->number_of_teams=team_number;
    season->number_of_drivers=get_id-1;
}

//Get season and return number of drivers that participant in the season.
int SeasonGetNumberOfDrivers(Season season){
    if(season==NULL){
        return 0;
    }
    return season->number_of_drivers;
}
//Get season and return number of teams that participant in the season.
int SeasonGetNumberOfTeams(Season season){
    if(season==NULL){
        return 0;
    }
    return season->number_of_teams;
}

// in this function, we nedd to free some things:
// *every index in the team array and in the driver array
// *the team array and the driver array
// *the stract season
void   SeasonDestroy(Season season){
    int number_of_teams=season->number_of_teams;
    int number_of_drivers=season->number_of_drivers;
    destroyArrayByIndex (number_of_teams, number_of_drivers, season ); //destroy by index the 2 arrays
    destroyMyArray (season->array_team, season->array_drivers);          //destroy the 2 arrays
    free(season);
}

Team* SeasonGetTeamsStandings(Season season){
    if(season==NULL){
        return NULL;
    }
    TeamStatus team_status;
    int size_array=season->number_of_teams;
    Team * new_array_teams=malloc(sizeof(*new_array_teams)*size_array);
    if (new_array_teams == NULL){
        return NULL;
    }
    seasonCopyTheArrayTeam(season, new_array_teams, size_array);
    seasonMinSortTeam(season, new_array_teams, size_array, &team_status);
    if(team_status == TEAM_NULL_PTR){
        free(new_array_teams);
        return NULL;
    }
    return new_array_teams;

}

//the function  get a season and position and status.
//return the team that in this position.
Team SeasonGetTeamByPosition(Season season, int position, SeasonStatus status){
    if(season == NULL){
        return NULL;
    }
    Team * array_team = SeasonGetTeamsStandings(season);
    int number_of_teams=season->number_of_teams;
    if( position <=0 || position > number_of_teams) {    //the position is not legal
        status = BAD_SEASON_INFO;
        return NULL;
    }else{
        status = SEASON_OK;
        return array_team[position-1];
    }
}


static void seasonCopyTheArrayTeam(Season season,Team * array_team, int size_of_array){
    for(int i=0; i<size_of_array; i++){
        array_team[i]=season->array_team[i];
    }
}


static int seasonFindTheMinTeam (Season season, Team * array_team, int size_of_array, TeamStatus *team_status){
    int i,j, index_min=0;
    int points_min=TeamGetPoints(array_team[0], team_status);
    if(*team_status == TEAM_NULL_PTR){
        return 0;
    }
    int points_in_index_i;
    for(i=1; i<size_of_array; i++)
    {
        points_in_index_i=TeamGetPoints(array_team[i], team_status);
        if(*team_status == TEAM_NULL_PTR){
            return 0;
        }
        if(points_min == points_in_index_i){
            Driver driver1_for_index_min = TeamGetDriver(season->array_team[index_min],FIRST_DRIVER);
            Driver driver2_for_index_min  = TeamGetDriver(season->array_team[index_min],SECOND_DRIVER);
            Driver driver3_for_index_i  = TeamGetDriver(season->array_team[i],FIRST_DRIVER);
            Driver driver4_for_index_i  = TeamGetDriver(season->array_team[i],SECOND_DRIVER);
            int id1_index_min = DriverGetId(driver1_for_index_min);
            int id2_index_min = DriverGetId(driver2_for_index_min);
            int id3_index_i = DriverGetId(driver3_for_index_i);
            int id4_index_i = DriverGetId(driver4_for_index_i);
            for(j=0; j< season->number_of_drivers; j++){
                if(season->race_result[j] == id1_index_min){
                    points_min=points_in_index_i;
                    index_min=i;
                    break;
                }
                else if(season->race_result[j] == id2_index_min){
                    points_min=points_in_index_i;
                    index_min=i;
                    break;
                }
                else if(season->race_result[j] == id3_index_i){
                    break;
                }
                else if(season->race_result[j] == id4_index_i){
                    break;
                }
            }
        }
            if(points_min > points_in_index_i){
                points_min=points_in_index_i;
                index_min=i;
        }
    }
    *team_status=TEAM_STATUS_OK;
    return index_min;
}

static void seasonMinSortTeam(Season season, Team *array_teams,int size_array, TeamStatus * team_status){
    int length;
    for(length=size_array;length>1;length--) {
        int i_min = seasonFindTheMinTeam(season,array_teams, length, team_status);
        if( *team_status == TEAM_NULL_PTR){
            return;
        }
        seasonSwapTeam(&array_teams[i_min],&array_teams[length - 1]);
    }

}

static void seasonSwapTeam(Team *teams1,Team *teams2){
    Team temp = *teams1;
    *teams1 = *teams2;
    *teams2 = temp;
}


static void seasonCopyTheArrayDriver(Season season,Driver * array_drivers, int size_of_array){
    for(int i=0; i<size_of_array; i++){
        array_drivers[i]=season->array_drivers[i];
    }
}


static int seasonFindTheMinDriver(Season season, Driver * array_drivers, int size_of_array,DriverStatus *driver_status){
    int i, index_min=0;
    int points_min=DriverGetPoints(array_drivers[0], driver_status);
    if(*driver_status == INVALID_DRIVER){
        return 0;
    }
    int points_in_index_i;
    for(i=1; i<size_of_array; i++)
    {
        points_in_index_i=DriverGetPoints(array_drivers[i], driver_status);
        if(*driver_status == INVALID_DRIVER){
            return 0;
        }
        if(points_min==points_in_index_i){
            int id_index_min=DriverGetId(season->array_drivers[index_min]);
            int id_i=DriverGetId(season->array_drivers[i]);
            for(int j=0;j<season->number_of_drivers;j++)
            {
            if(season->race_result[j]==id_index_min){
                index_min=i;
                points_min=points_in_index_i;
            }
                else if(season->race_result[j]==id_i){

                break;
                }
            }
        }
        if(points_min > points_in_index_i){
            index_min=i;
            points_min=points_in_index_i;
        }

    }
    *driver_status=DRIVER_STATUS_OK;
    return index_min;
}

static void seasonMinSortDriver(Season season,Driver *array_drivers,int size_array,DriverStatus *driver_status){
    int length;
    for(length=size_array;length>1;length--) {
        int i_min = seasonFindTheMinDriver(season,array_drivers, length,driver_status);
        if(*driver_status == INVALID_DRIVER){
            return;
        }
        seasonSwapDriver(&array_drivers[i_min],&array_drivers[length - 1]);
    }
}

static void seasonSwapDriver(Driver *drivers1,Driver *drivers2) {
    Driver temp = *drivers1;
    *drivers1 = *drivers2;
    *drivers2 = temp;
}


Driver* SeasonGetDriversStandings(Season season){
    DriverStatus driver_status = DRIVER_STATUS_OK;
    int size_array=season->number_of_drivers;
    Driver *new_array_drivers=malloc(sizeof(*new_array_drivers)*size_array);
    if(new_array_drivers==NULL){
        return NULL;
        }
    seasonCopyTheArrayDriver(season,new_array_drivers,size_array);
    seasonMinSortDriver(season,new_array_drivers,size_array,&driver_status);
    if(driver_status == INVALID_DRIVER){
        free(new_array_drivers);
        return NULL;
    }
    return new_array_drivers;
}

Driver SeasonGetDriverByPosition(Season season, int position, SeasonStatus* status){
    if(season==NULL){
        return NULL;
    }
    int size_array=season->number_of_drivers;
    Driver *new_array_drivers;
    new_array_drivers=SeasonGetDriversStandings(season);
    if( position <=0 || position > size_array) {    //the position is not legal
        *status = BAD_SEASON_INFO;
        return NULL;
    }else{
        *status = SEASON_OK;
        return new_array_drivers[position-1];

    }
}
//* the function get id and return the driver from the season with this id*//
static void idGetDriver(Season season)
{
    int size_array=season->number_of_drivers;
    int driver_id;
    for(int j=0;j<size_array;j++)      //position array
    {
        for(int i=0;i<size_array;i++) {
            driver_id = DriverGetId(season->array_drivers[i]);
            if (driver_id == season->race_result[j]) {
                DriverAddRaceResult(season->array_drivers[i], j + 1);
                break;
            }
        }
    }
}

//Get a season, and array in length of the numbers of the drivers in the season
//add race result to race_result in struct season.
SeasonStatus SeasonAddRaceResult(Season season, int* results){
    if( season==NULL || results==NULL ) {
        return SEASON_NULL_PTR;
    }
    season->race_result=malloc(sizeof(*(season->race_result))*season->number_of_drivers);///// check the maloc and free if null!!!!
    for(int i=0; i<season->number_of_drivers; i++){
        season->race_result[i]=results[i];
    }
    idGetDriver(season);
    return SEASON_OK;
}



Driver* Season_help_check (Season season){
    return season->array_drivers;
}


//func that help us for check:
void printpointDriver(Season season)
{
    DriverStatus status;
for(int i=0;i<season->number_of_drivers;i++) {
    int x = DriverGetPoints(season->array_drivers[i], &status);
    printf("the point of the driver number %d his points is %d\n", i+1,x);
}
}

//func that help us for check:
void printpointTeam(Season season)
{
    TeamStatus status;
    for(int i=0;i<season->number_of_teams;i++) {
        int x = TeamGetPoints (season->array_team[i], &status);
        printf("the point of the driver number %d his points is %d\n", i+1,x);
    }
}

void printPointArrayTeam(Team* array_team, int number_of_teams){
    for(int i=0; i<number_of_teams; i++){
       const char* name_team= TeamGetName(array_team[i]);
        printf("the team in the place %d, is %s\n", i+1, name_team);
    }
}

