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
static void destroyArrayByIndex (int team_index, int driver_index, Season season );   //destroy the array team and sriver by index

//destroy the index of the team and driver array, the array and the season
static void destroyFinishInCreateSeason(Team *temp_team, Driver *temp_driver, Season season);

static void seasonDestroyWithOutRaceResult(Season season); // destroy Season but with out destroy the feild "race_result"
static void updateSeasonErrorMemoryAndDestroy (Season season, SeasonStatus * status_season); //update the status_season to Error memory and destroy
static void updateSeasonErrorMemory (SeasonStatus * status_season);  //update the status_season to Error memory
//check if the team_status return a "TEAM_NULL_PTR"
static void checkIfTeamStatusIsNull(Season season, Team *temp_team, Driver *temp_driver, TeamStatus * status_team);

//this function put in the array of drivers and the array of teams NULL
static void putNullInTheTeamArray(Team * temp_team, int number_of_team);
static void putNullInTheDriverArray(Driver* temp_driver, int number_of_driver);
static void checkStatusDriver(DriverStatus status_driver,Season season,Team *temp_team, Driver *temp_driver);

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
//static void destroyDriverByIndex (Driver *array_drivers, Season season );

struct season {
    int year;
    int number_of_teams;
    Team *array_team;
    int number_of_drivers;
    Driver *array_drivers;
    int * race_result;
};
//Get *status, and a pointer to char – season_info.
//The job if the func’ is to:
//1)	Insert a year
//2)	Insert the numbers of team
//3)	Make a array of the names of the team
//4)	Insert the numbers of drivers
//5)	Make a array if the names of the drivers
Season SeasonCreate(SeasonStatus* status,const char* season_info){
   if(status!=NULL)
       *status = SEASON_OK;
    Team *temp_team = NULL;                                             //pointer that help us to insert the data to the Team's array
    Driver *temp_driver=NULL;                                           //pointer that help us to insert the data to the Driver's araay
    Season new_season = malloc(sizeof(*new_season));                    //create the new season
    if(new_season == NULL) {                                            //free the season. return NULL
        updateSeasonErrorMemoryAndDestroy(new_season, status);
        return NULL;
    }
    char * my_season_info = copyFileSeasonCreate(season_info, status);
    if(status==NULL) {
        updateSeasonErrorMemoryAndDestroy(new_season, status);
        return NULL;
    }
    char *token=strtok(my_season_info, "\n");
    int season_year=atoi(token);                                         //conveert char to int.
    new_season->year=season_year;                                        //insert the year to the season
    int team_number=(rowsNumberInSeasonInfo(token))/3;                   //calculate the team number and the driver number with help of the rows number of the file.
    int total_driver_number=team_number*2;                               //the number of drivers that we have in the season, including NULL
    free (my_season_info);
    char * new_season_info = copyFileSeasonCreate(season_info, status);  //start again and skip the year
    if(status!=NULL) {
        if (*status == SEASON_MEMORY_ERROR) {                                //there was a error memory. return NULL
            destroyMySeason(new_season);
            return NULL;
        }
    }
    new_season->array_team=malloc(sizeof(*(new_season->array_team))*team_number);
    if((new_season->array_team) == NULL) {
        updateSeasonErrorMemory(status);
        free(new_season_info);
        destroyMySeason(new_season);
        return NULL;
    }
    temp_team = new_season->array_team;
    putNullInTheTeamArray(temp_team, team_number);
    new_season->array_drivers=malloc(sizeof(*(new_season->array_drivers))*total_driver_number);
    if((new_season->array_drivers) == NULL) {
        updateSeasonErrorMemory(status);
        free(new_season_info);
        free(new_season->array_team);
        destroyMySeason(new_season);                                           //this function return NULL
    return NULL;
    }
    temp_driver=new_season->array_drivers;
    putNullInTheDriverArray(temp_driver, total_driver_number);
    insertTheDataToSeason(new_season, new_season_info, temp_team, temp_driver);
    free(new_season_info);
    return new_season;
}

//update the status_season to Error memory and destroy the season
static void updateSeasonErrorMemoryAndDestroy (Season season, SeasonStatus * status_season){
    if(status_season!=NULL)
        *status_season = SEASON_MEMORY_ERROR;
    destroyMySeason(season);
}

//update the status_season to Error memory
static void updateSeasonErrorMemory (SeasonStatus * status_season){
    if(status_season!=NULL)
        *status_season = SEASON_MEMORY_ERROR;
}


//copy the file season_info, to file my_season_info.
static char * copyFileSeasonCreate(const char* season_info, SeasonStatus* status){
    int length_of_season_info=strlen(season_info)+1;             //get the length of the file - season_info
    char* copy_season_info=malloc(sizeof(char)*length_of_season_info);
    if(copy_season_info == NULL) {
        if(status!=NULL) {
            *status = SEASON_MEMORY_ERROR;
        }
        return NULL;
    }
    strcpy(copy_season_info, season_info);                        //copy the const array-"season_info", to "my_season_info"
    return copy_season_info;
}

static int rowsNumberInSeasonInfo(char *token){
    int rows=0;
    token=strtok(NULL, "\n");                                     //continue in the file, to the first team
    while(token != NULL ){
        rows++;                                                   //rows increase in 1
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
    for(index=0; index<team_index; index++){                        //we dont need to free the index-difference, because his allocation failed
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
    int get_id=1;                                             //the driver need to get a id
    DriverStatus status_driver=DRIVER_STATUS_OK;
    TeamStatus status_team=TEAM_STATUS_OK;
    int team_number=0;
    char *token=strtok(season_info, "\n");
    token=strtok(NULL, "\n");
    while(token != NULL){
     *temp_team=TeamCreate(&status_team,token);
        if (status_team == TEAM_MEMORY_ERROR) {              //there was a memory error in the func' TeamCreate
            destroyFinishInCreateSeason(temp_team, temp_driver, season);
            return;
        }
        team_number++;
        token=strtok(NULL, "\n");                            //continue to the driver
        if(strcmp(token, "None")==0){
            token=strtok(NULL, "\n");                        //continue to the driver
        } else {
            *temp_driver=DriverCreate(&status_driver,token, get_id);
            checkStatusDriver(status_driver,season,temp_team, temp_driver);
            DriverSetTeam(*temp_driver, *temp_team);
            DriverSetSeason(*temp_driver, season);
            status_team = TeamAddDriver(*temp_team, *temp_driver);
            checkIfTeamStatusIsNull(season, temp_team, temp_driver, &status_team);
            if(status_team==TEAM_NULL_PTR)
                return;
            get_id++;                                       //get_id +1 to the next driver
            temp_driver++;
            token=strtok(NULL, "\n");                       //continue to the driver
        }
        if(strcmp(token, "None")==0){
            token=strtok(NULL, "\n");                        //continue to the next team
            temp_team++;
            continue;
        }
        *temp_driver=DriverCreate(&status_driver,token, get_id);
        checkStatusDriver(status_driver,season,temp_team, temp_driver);
        DriverSetTeam(*temp_driver, *temp_team);
        DriverSetSeason(*temp_driver, season);
        status_team = TeamAddDriver(*temp_team, *temp_driver);
        checkIfTeamStatusIsNull(season, temp_team, temp_driver, &status_team);
        if(status_team==TEAM_NULL_PTR)
            return;
        get_id++;                                           //get_id +1 to the next driver
        temp_driver++;
        token=strtok(NULL, "\n");                           //continue to the next team
        temp_team++;
    }
    season->number_of_teams=team_number;
    season->number_of_drivers=get_id-1;
    season->race_result=malloc(sizeof(*(season->race_result))*season->number_of_drivers);
    if(season->race_result==NULL) {
        seasonDestroyWithOutRaceResult(season);
        return;
    }
}

static void checkStatusDriver(DriverStatus status_driver,Season season,Team *temp_team, Driver *temp_driver) {
    if (status_driver == DRIVER_MEMORY_ERROR) {           //there was a memory error in the func' DriverCreate
        destroyFinishInCreateSeason(temp_team, temp_driver, season);
        return;
    }
}

static void checkIfTeamStatusIsNull(Season season, Team *temp_team, Driver *temp_driver, TeamStatus * status_team){
    if(status_team!=NULL) {
        if (*status_team ==
            TEAM_NULL_PTR) {                  //it's not good because  it's mean *temp_team or *temp_driver are NULL
            destroyFinishInCreateSeason(temp_team, temp_driver, season);
            return;
        }
    }
    return;
}
static void seasonDestroyWithOutRaceResult(Season season){
    int number_of_teams=season->number_of_teams;
    destroyArrayByIndex (number_of_teams, number_of_teams*2, season ); //destroy by index the 2 arrays
    free(season);
}


static void putNullInTheTeamArray(Team * temp_team, int number_of_team){
    for(int i=0; i<number_of_team; i++){
        temp_team[i]=NULL;
    }
}

static void putNullInTheDriverArray(Driver* temp_driver, int number_of_driver){
    for(int i=0; i<number_of_driver; i++){
        temp_driver[i]=NULL;
    }
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
    destroyArrayByIndex (number_of_teams, number_of_teams*2, season ); //destroy by index the 2 arrays
    free(season->race_result);
    free(season);
}

//the function gets season and return array of teams.
//the array that we return shoud be sort .
Team* SeasonGetTeamsStandings(Season season){
    if(season==NULL){
        return NULL;
    }
    TeamStatus team_status=TEAM_STATUS_OK;
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
Team SeasonGetTeamByPosition(Season season, int position, SeasonStatus * status){
    if(season == NULL){
        if(status!=NULL) {
            *status = SEASON_NULL_PTR;
        }
        return NULL;
    }
    if( position <=0 || position > (season->number_of_teams)) {    //the position is not legal
        if(status!=NULL) {
            *status = BAD_SEASON_INFO;
        }
        return NULL;
        }
    Team * array_team = SeasonGetTeamsStandings(season);
    int number_of_teams=season->number_of_teams;
    if(status!=NULL) {
        *status = SEASON_OK;
    }
        Team result = array_team[position-1];
        free (array_team);
        return result;
}

//the function copy the season->array_team to the input
static void seasonCopyTheArrayTeam(Season season,Team * array_team, int size_of_array){
    for(int i=0; i<size_of_array; i++){
        array_team[i]=season->array_team[i];
    }
}

//the function return the index_min between the points of all team in array team.
static int seasonFindTheMinTeam (Season season, Team * array_team, int size_of_array, TeamStatus *team_status){
    int i,j, index_min=0;
    int points_min=TeamGetPoints(array_team[0], team_status);
    if(team_status!=NULL)
        if (*team_status == TEAM_NULL_PTR)
            return 0;
    int points_in_index_i;
    for(i=1; i<size_of_array; i++)
    {
        points_in_index_i=TeamGetPoints(array_team[i], team_status);
        if(team_status!=NULL)
            if(*team_status == TEAM_NULL_PTR)
              return 0;
        if(points_min == points_in_index_i){
            Driver driver1_for_index_min = TeamGetDriver(array_team[index_min],FIRST_DRIVER);
            Driver driver2_for_index_min  = TeamGetDriver(array_team[index_min],SECOND_DRIVER);
            Driver driver3_for_index_i  = TeamGetDriver(array_team[i],FIRST_DRIVER);
            Driver driver4_for_index_i  = TeamGetDriver(array_team[i],SECOND_DRIVER);
            int id1_index_min = DriverGetId(driver1_for_index_min);
            int id2_index_min = DriverGetId(driver2_for_index_min);
            int id3_index_i = DriverGetId(driver3_for_index_i);
            int id4_index_i = DriverGetId(driver4_for_index_i);
            for(j=0; j< season->number_of_drivers; j++){
                if(season->race_result[j] == id1_index_min){
                    points_min=points_in_index_i;
                    index_min=i;
                    break;
                } else if(season->race_result[j] == id2_index_min){
                    points_min=points_in_index_i;
                    index_min=i;
                    break;
                } else if(season->race_result[j] == id3_index_i){
                    break;
                } else if(season->race_result[j] == id4_index_i){
                    break;
                }
            }
        } else if(points_min > points_in_index_i){
                points_min=points_in_index_i;
                index_min=i;
        }
    }
    if(team_status!=NULL)
        *team_status = TEAM_STATUS_OK;
    return index_min;
}

//the function sort all the teams in array team according to there points.
static void seasonMinSortTeam(Season season, Team *array_teams,int size_array, TeamStatus * team_status){
    int length;
    for(length=size_array;length>1;length--) {
        int i_min = seasonFindTheMinTeam(season,array_teams, length, team_status);
        if(team_status!=NULL) {
            if( *team_status == TEAM_NULL_PTR){
            return;
            }
        }
        seasonSwapTeam(&array_teams[i_min],&array_teams[length - 1]);
    }

}
//swap function
static void seasonSwapTeam(Team *teams1,Team *teams2){
    Team temp = *teams1;
    *teams1 = *teams2;
    *teams2 = temp;
}

//the function copy the season->array_drivers to the input
static void seasonCopyTheArrayDriver(Season season,Driver * array_drivers, int size_of_array){
    for(int i=0; i<size_of_array; i++){
        array_drivers[i]=season->array_drivers[i];
    }
}

//the function return the index_min between the points of all drivers in array_drivers.
static int seasonFindTheMinDriver(Season season, Driver * array_drivers, int size_of_array,DriverStatus *driver_status){
    int i, index_min=0;
    int points_min=DriverGetPoints(array_drivers[0], driver_status);
    if(driver_status!=NULL) {
        if(*driver_status == INVALID_DRIVER){
        return 0;
        }
    }
    int points_in_index_i;
    for(i=1; i<size_of_array; i++)
    {
        points_in_index_i=DriverGetPoints(array_drivers[i], driver_status);
        if(driver_status!=NULL) {
            if (*driver_status == INVALID_DRIVER) {
                return 0;
            }
        }
        if(points_min==points_in_index_i){
            int id_index_min=DriverGetId(array_drivers[index_min]);
            int id_i=DriverGetId(array_drivers[i]);
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
    if(driver_status!=NULL) {
        *driver_status = DRIVER_STATUS_OK;
    }
    return index_min;
}
//the function sort all the drivers in array_drivers according to there points.
static void seasonMinSortDriver(Season season,Driver *array_drivers,int size_array,DriverStatus *driver_status){
    int length;
    for(length=size_array;length>1;length--) {
        int i_min = seasonFindTheMinDriver(season,array_drivers, length,driver_status);
        if(driver_status!=NULL) {
            if (*driver_status == INVALID_DRIVER) {
                return;
            }
        }
        seasonSwapDriver(&array_drivers[i_min],&array_drivers[length - 1]);
    }
}
//swap function
static void seasonSwapDriver(Driver *drivers1,Driver *drivers2) {
    Driver temp = *drivers1;
    *drivers1 = *drivers2;
    *drivers2 = temp;
}

//Get a season and return array of ptr sort according to there points
Driver* SeasonGetDriversStandings(Season season){
    if(season == NULL){
        return NULL;
    }
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

//get season position and status.
//return the driver that we get input about the position.
Driver SeasonGetDriverByPosition(Season season, int position, SeasonStatus* status){
    if(season==NULL)
        return NULL;
    int size_array=season->number_of_drivers;
    if( position <=0 || position > size_array) {    //the position is not legal
        if(status!=NULL) {
            *status = BAD_SEASON_INFO;
        }
        return NULL;
    }else{
        if(status!=NULL) {
            *status = SEASON_OK;
        }
        Driver *new_array_drivers;
        new_array_drivers=SeasonGetDriversStandings(season);
        Driver result=new_array_drivers[position-1];
        free(new_array_drivers);
        return result;
    }
}
//* the function get id and return the driver from the season with this id
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
    for(int i=0; i<season->number_of_drivers; i++){
        season->race_result[i]=results[i];
    }
    idGetDriver(season);
    return SEASON_OK;
}


