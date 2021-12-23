//This is to test github
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

struct UserBike
{
    int isActive; //0 if booking is expired, 1 if active
    string Name;
    string MobNo;
    string Email;

    string Date_Booking;
    string Time_Booking;

    string Date_Start;
    string Time_Start;

    string Date_End;
    string Time_End;

    int isAllotted;
    string BikeCode;
};
