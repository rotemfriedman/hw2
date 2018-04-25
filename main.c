#include <stdio.h>
#include <string.h>
#include "driver.h"
#include "team.h"
#include "season.h"
#include <assert.h>

int main() {
    DriverStatus status = DRIVER_STATUS_OK;
    Driver d1=DriverCreate(&status,"avi",123);
    int check=DriverGetId(NULL);
    if(check==0)
        printf("yes");
    else
        printf("no");
    //assert(status == DRIVER_STATUS_OK);
    //assert(d1 != NULL);
    // assert(DriverGetName(d1) == "driver");

    return 0;
}