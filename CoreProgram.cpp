#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <time.h>
#include <conio.h>
#include <math.h>
using namespace std;

//for date and time related tasks
std::string current_date();
std::string current_time();

std::string current_date()
{
    time_t now = time(NULL);
    struct tm tstruct;
    char buf[40];
    tstruct = *localtime(&now);
    //format: day DD-MM-YYYY
    strftime(buf, sizeof(buf), "%A %d/%m/%Y", &tstruct);
    return buf;
}
std::string current_time()
{
    time_t now = time(NULL);
    struct tm tstruct;
    char buf[40];
    tstruct = *localtime(&now);
    //format: HH:mm:ss
    strftime(buf, sizeof(buf), "%X", &tstruct);
    return buf;
}

//UID (User ID, TaxiID etc. ) rules

//Max prespecified Values
const int maxUserCount = 100;
const int maxVehicleCount = 30;
const int maxStaffCount = 10;
const int maxHelpCount = 200;
const int maxLocCount = 200;
const int bikeMileage = 40;
const int taxiMileage = 60;

//since we aren't going to create user Account and all, storing least data is good.
struct UserBike
{
    int UID;
    string Name;
    string password;
    string MobNo;

    int hhStart, mmStart;
    int hhEnd, mmEnd;

    int locInd1, locInd2;

    int isAllotted;
    int BikeUID;
} userBike[maxUserCount];
int userBikeCount;

struct UserTaxi
{
    int UID;
    string Name;
    string password;
    string MobNo;

    int hhStart, mmStart;
    int hhEnd, mmEnd;

    int locInd1, locInd2;

    int isAllotted;
    int TaxiUID;
} userTaxi[maxUserCount];
int userTaxiCount;

struct Bike
{
    int isAvail;
    int userIndex;

    int UID;
    string Name; //name of driver not bike
    string MobNo;
    string EmailID;
    string Date_Joining;
} bike[maxVehicleCount];
int bikeCount;

struct Taxi
{
    int isAvail;
    int userIndex;

    int UID;
    string Name;
    string MobNo;
    string EmailID;
    string Date_Joining;
} taxi[maxVehicleCount];
int taxiCount;

struct Staff
{
    int UID; //treated as UID if required
    string Name;
    string password;
    string MobNo;
} staff[maxStaffCount];
int staffCount;

struct Admin
{
    int UID; //treated as UID if required
    string Name;
    string password;
    string OrgName;
    string OrgAdrs;
    string MobNo;
} admin[1]; //Always 1
int adminCount;

struct Help
{
    int UID;
    int userMode;
    int userUID;
    string comment;
} help[maxHelpCount];
int helpCount;

struct Location
{
    string locName;
    int UID;
    long locX; //x coordinate of location
    long locY; //y coordinate of location
} location[maxLocCount];
int locCount;

//following data used for user Identification
string userModeArray[5] = {"Logged Out(Safe)", "User (Bike)", "User (Taxi)", "Staff", "Admin"};
int currentIndex = -1;
int userMode = 0;
int currentUID = 0;
/*
    indicates the mode user is in
    -1: Logged out of everything(UNSAFE)____even if not handled accessing -1 index of userModeArray will terminate the program, thereby providing security
    0: Logged out but Safe
    1: Logged in as User_Bike
    2: Logged in as User_Taxi
    3: Logged in as Staff
    4: Logged in as Admin
    */

extern "C"
{
    void import() //Completed
    {
        // memset(userBike, 0, sizeof(UserBike));
        // memset(userTaxi, 0, sizeof(UserTaxi));
        // memset(bike, 0, sizeof(Bike));
        // memset(taxi, 0, sizeof(Taxi));
        // memset(staff, 0, sizeof(Staff));
        // memset(admin, 0, sizeof(Admin));
        // memset(help, 0, sizeof(Help));
        // memset(location, 0, sizeof(Location));

        //importing from UserBike.txt
        FILE *fp = fopen("UserBike.txt", "r");
        if (fp == NULL)
        {
            printf("\nBike Users Database Not Found!");
            fp = fopen("UserBike.txt", "w");
            printf("\nNew Bike Users Database has been created.");
            fclose(fp);
        }
        userBikeCount = fread(userBike, sizeof(struct UserBike), maxUserCount, fp);
        printf("\nBike Users Database imported successfully.");
        fclose(fp);

        //importing from UserTaxi.txt
        fp = fopen("UserTaxi.txt", "r");
        if (fp == NULL)
        {
            printf("\nTaxi Users Database Not Found!");
            fp = fopen("UserTaxi.txt", "w");
            printf("\nNew Taxi Users Database has been created.");
            fclose(fp);
        }
        userTaxiCount = fread(userTaxi, sizeof(struct UserTaxi), maxUserCount, fp);
        printf("\nTaxi Users Database imported successfully.");
        fclose(fp);

        //importing from Bike Database
        fp = fopen("Bike.txt", "r");
        if (fp == NULL)
        {
            printf("\nBike Database Not Found!");
            fp = fopen("Bike.txt", "w");
            cout << "\nNew Bike Database has been created.";
            fclose(fp);
        }
        bikeCount = fread(bike, sizeof(struct Bike), maxVehicleCount, fp);
        printf("\nBike Database imported successfully.");
        fclose(fp);

        //importing from Taxi Database
        fp = fopen("Taxi.txt", "r");
        if (fp == NULL)
        {
            printf("\nTaxi Database Not Found!");
            fp = fopen("Taxi.txt", "w");
            cout << "\nNew Taxi Database has been created.";
            fclose(fp);
        }
        taxiCount = fread(taxi, sizeof(struct Taxi), maxVehicleCount, fp);
        printf("\nTaxi Database imported successfully.");
        fclose(fp);

        //importing from Staff Database
        fp = fopen("Staff.txt", "r");
        if (fp == NULL)
        {
            printf("\nStaff Database Not Found!");
            fp = fopen("Staff.txt", "w");
            cout << "\nNew Staff Database has been created.";
            fclose(fp);
        }
        staffCount = fread(staff, sizeof(struct Staff), maxStaffCount, fp);
        printf("\nStaff Database imported successfully.");
        fclose(fp);

        //importing from Admin Database
        fp = fopen("Admin.txt", "r");
        if (fp == NULL)
        {
            printf("\nAdmin Database Not Found!");
            fp = fopen("Admin.txt", "w");
            cout << "\nNew Admin Database has been created.";
            fclose(fp);
        }
        adminCount = fread(admin, sizeof(struct Admin), 1, fp);
        printf("\nAdmin Database imported successfully.");
        fclose(fp);

        //importing from Help Database
        fp = fopen("Help.txt", "r");
        if (fp == NULL)
        {
            printf("\nHelp Database Not Found!");
            fp = fopen("Help.txt", "w");
            cout << "\nNew help Database has been created.";
            fclose(fp);
        }
        helpCount = fread(help, sizeof(struct Help), 1, fp);
        printf("\nHelp Database imported successfully.");
        fclose(fp);

        //importing from Location Database
        fp = fopen("Location.txt", "r");
        if (fp == NULL)
        {
            printf("\nLocation Database Not Found!");
            fp = fopen("Location.txt", "w");
            cout << "\nNew Location Database has been created.";
            fclose(fp);
        }
        locCount = fread(location, sizeof(struct Location), maxLocCount, fp);
        printf("\nLocation Database imported successfully.");
        fclose(fp);
        //Decrypting all data
        // decryptAll();
    }
    ////////////////////////////////////////////////////////////////////////////////
    void backup()
    {
        //Encrypting all data
        // encryptAll();
        //updating UserBike.txt
        FILE *fp = fopen("UserBike.txt", "w");
        if (fp == NULL)
        {
            printf("/nBike Users Database is empty!");
            exit(1);
        }
        fwrite(userBike, sizeof(struct UserBike), userBikeCount, fp);
        printf("\nBike Users Database updated successfully.");
        fclose(fp);

        //updating UserTaxi.txt
        fp = fopen("UserTaxi.txt", "w");
        if (fp == NULL)
        {
            printf("/nTaxi Users Database is empty!");
            exit(1);
        }
        fwrite(userTaxi, sizeof(struct UserTaxi), userTaxiCount, fp);
        printf("\nTaxi Users Database updated successfully.");
        fclose(fp);

        //updating Bike.txt
        fp = fopen("Bike.txt", "w");
        if (fp == NULL)
        {
            printf("/nBike Database is empty!");
            exit(1);
        }
        fwrite(bike, sizeof(struct Bike), bikeCount, fp);
        printf("\nBike Database updated successfully.");
        fclose(fp);

        //updating Taxi.txt
        fp = fopen("Taxi.txt", "w");
        if (fp == NULL)
        {
            printf("/nTaxi Database is empty!");
            exit(1);
        }
        fwrite(taxi, sizeof(struct Taxi), taxiCount, fp);
        printf("\nTaxi Database updated successfully.");
        fclose(fp);

        //updating Staff.txt
        fp = fopen("Staff.txt", "w");
        if (fp == NULL)
        {
            printf("/nStaff Database is empty!");
            exit(1);
        }
        fwrite(staff, sizeof(struct Staff), staffCount, fp);
        printf("\nStaff Database updated successfully.");
        fclose(fp);

        //updating Admin.txt
        FILE *fp9 = fopen("Admin.txt", "w");
        if (fp9 == NULL)
        {
            printf("/nAdmin Database is empty!");
            exit(1);
        }
        fwrite(admin, sizeof(struct Admin), adminCount, fp9);
        printf("\nAdmin Database updated successfully.");
        fclose(fp9);

        //updating Help.txt
        fp = fopen("Help.txt", "w");
        if (fp == NULL)
        {
            printf("/nHelp Database is empty!");
            exit(1);
        }
        fwrite(help, sizeof(struct Help), adminCount, fp);
        printf("\nHelp Database updated successfully.");
        fclose(fp);

        //updating Location.txt
        fp = fopen("Location.txt", "w");
        if (fp == NULL)
        {
            printf("/nLocation Database is empty!");
            exit(1);
        }
        fwrite(location, sizeof(struct Location), locCount, fp);
        printf("\nLocation Database updated successfully.");
        fclose(fp);
    }
}
//Don't think much of this class below (Support), just remember the function names and what they do.
class Support
{
public:
    void wait(int noSec)
    {
        int f = 0;
        clock_t start_wait;
        clock_t end_wait;

        start_wait = clock();
        end_wait = clock() + noSec * CLK_TCK;

        // printf("\nLoading.");

        while (clock() < end_wait)
        {
            if ((clock() - start_wait) % 400 == 0)
            {
                if (f != (clock() - start_wait))
                    printf(".");
                f = (clock() - start_wait);
            }
        }
    }

    void screenReset()
    {
        system("cls");
        cout << "\n---------------------------------------------------------";
        time_t mytime;
        mytime = time(NULL);
        printf(ctime(&mytime));
        cout << "\n------------------------------[ " << admin[0].OrgName << " ]--------------------------------";
        cout << "\nUSERMODE : " << userModeArray[userMode] << "\t\t\t\t";
        switch (userMode)
        {
        case 1:
            cout << "USER ID : " << userBike[currentIndex].UID;
            break;
        case 2:
            cout << "USER ID : " << userTaxi[currentIndex].UID;
            break;
        case 3:
            cout << "STAFF ID : " << staff[currentIndex].UID;
            break;
        case 4:
            cout << "ADMIN ID : " << admin[currentIndex].UID;
            break;
        default:
            cout << "NIL";
            break;
        }
        printf("\n----------------------------------------------------------------------------------");
    }

    void encrypt(string *s)
    {
        /*
		Logic for encryption
		
		to be thought yet
	*/
    }
    ////////////////////////////////////////////////////////////////////////////////
    void decrypt(string *s)
    {
    }
    ////////////////////////////////////////////////////////////////////////////////
    int encryptInt(int a)
    {
        return a;
    }
    ////////////////////////////////////////////////////////////////////////////////
    int decryptInt(int a)
    {
        return a;
    }
    ////////////////////////////////////////////////////////////////////////////////
    void encryptAll()
    {
        //encrypt all structs to be backed up...
    }
    ////////////////////////////////////////////////////////////////////////////////
    void decryptAll()
    {
        //decrypt all structs imported...
    }
    ////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////
    bool authenticate(int userModeIn)
    {
        int UIDin;
        string PWDin;
        int choice = 0, found = 0; //found used to check if user found or not
        switch (userModeIn)
        {
        case -1: //unsafe
        {
            cout << "\nUnauthorised access detected!";
        }
        break;
        case 1: //UserBike
        {
            cout << "\nUser(Bike) Log In/New User";
            cout << "\n\t1. Log In";
            cout << "\n\t2. New User";
            cout << "\n\t-1. GO BACK";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;
            switch (choice)
            {
            case -1:
            {
                cout << "\nGoing back...";
                wait(1);
            }
            break;
            case 1: //log in as user(bike)
            {
                //authenticating with the records
                if (userBikeCount > 0)
                {
                    cout << "\nUser Bike Authentication";
                    cout << "\n\tEnter UID: ";
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
                    cin >> PWDin;

                    for (int a = 0; a < userBikeCount; a++)
                    {
                        if (userBike[a].UID == UIDin && userBike[a].password == PWDin)
                        {
                            found = 1;
                            currentIndex = a;
                            int currentUID = userBike[a].UID;
                            cout << "\nAuthenticated as user(Bike).\nWelcome " << userBike[a].Name << "!";
                            wait(1);
                            return true;
                        }
                    }
                    if (found != 1)
                    {
                        cout << "\nEntered credentials do not match any of the records!";
                    }
                }
                else
                {
                    cout << "\nNo user(bike) records available to look into!";
                }
            }
            break;
            case 2: //new User
            {
                if (userBikeCount < maxUserCount)
                {
                    cout << "\nNew User for Bike Booking:";
                    cout << "\nAlright, let's get you in!";

                    cout << "\nEnter your name: ";
                    fflush(stdin);
                    getline(cin, userBike[userBikeCount].Name);

                    cout << "\nEnter new password: ";
                    fflush(stdin);
                    cin >> userBike[userBikeCount].password;

                    cout << "\nEnter your Mobile No: ";
                    fflush(stdin);
                    cin >> userBike[userBikeCount].MobNo;

                    userBike[userBikeCount].hhStart = -1;
                    userBike[userBikeCount].hhEnd = -1;
                    userBike[userBikeCount].mmStart = -1;
                    userBike[userBikeCount].mmEnd = -1;

                    userBike[userBikeCount].locInd1 = -1;
                    userBike[userBikeCount].locInd2 = -1;

                    userBike[userBikeCount].isAllotted = 0;
                    userBike[userBikeCount].BikeUID = -1;

                    //Program Snippet to allot UID to new User
                    for (int a = 0; a < maxUserCount; a++)
                    {
                        int f = 0;
                        for (int b = 0; b < userBikeCount; b++)
                        {
                            if (a != userBike[b].UID)
                            {
                                f = 1;
                                userBike[userBikeCount].UID = a;
                                break;
                            }
                        }
                        if (f == 1)
                            break;
                    }
                    userBike[userBikeCount].UID;

                    cout << "\nNew User Added";
                    userMode = 1;
                    currentIndex = userBikeCount - 1;
                    currentUID = userBike[userBikeCount].UID;
                    userBikeCount++;
                    return true;
                } //if there is still space, closed
                else
                {
                    cout << "\nSorry! User List (Bike) is already full!";
                }
            }
            break;
            default:
            {
                cout << "\nInvalid Input!";
            }
            break;
            }
        }
        break;
        case 2: //UserTaxi
        {
            cout << "\nUser(Taxi) Log In/New User";
            cout << "\n\t1. Log In";
            cout << "\n\t2. New User";
            cout << "\n\t-1. GO BACK";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;
            switch (choice)
            {
            case -1:
            {
                cout << "\nGoing back...";
                wait(1);
            }
            break;
            case 1: //log in as user(Taxi)
            {
                //authenticating with the records
                if (userTaxiCount > 0)
                {
                    cout << "\nUser Taxi Authentication";
                    cout << "\n\tEnter UID: ";
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
                    cin >> PWDin;

                    for (int a = 0; a < userTaxiCount; a++)
                    {
                        if (userTaxi[a].UID == UIDin && userTaxi[a].password == PWDin)
                        {
                            found = 1;
                            currentIndex = a;
                            int currentUID = userTaxi[a].UID;
                            cout << "\nAuthenticated as user(Taxi).\nWelcome " << userTaxi[a].Name << "!";
                            wait(1);
                            return true;
                        }
                    }
                    if (found != 1)
                    {
                        cout << "\nEntered credentials do not match any of the records!";
                    }
                }
                else
                {
                    cout << "\nNo user(Taxi) records available to look into!";
                }
            }
            break;
            case 2: //new User
            {
                if (userTaxiCount < maxUserCount)
                {
                    cout << "\nNew User for Taxi Booking:";
                    cout << "\nAlright, let's get you in!";

                    cout << "\nEnter your name: ";
                    fflush(stdin);
                    getline(cin, userTaxi[userTaxiCount].Name);

                    cout << "\nEnter new password: ";
                    fflush(stdin);
                    cin >> userTaxi[userTaxiCount].password;

                    cout << "\nEnter your Mobile No: ";
                    fflush(stdin);
                    cin >> userTaxi[userTaxiCount].MobNo;

                    userTaxi[userTaxiCount].hhStart = -1;
                    userTaxi[userTaxiCount].hhEnd = -1;
                    userTaxi[userTaxiCount].mmStart = -1;
                    userTaxi[userTaxiCount].mmEnd = -1;

                    userTaxi[userTaxiCount].locInd1 = -1;
                    userTaxi[userTaxiCount].locInd2 = -1;

                    userTaxi[userTaxiCount].isAllotted = 0;
                    userTaxi[userTaxiCount].TaxiUID = -1;

                    //Program Snippet to allot UID to new User
                    for (int a = 0; a < maxUserCount; a++)
                    {
                        int f = 0;
                        for (int b = 0; b < userTaxiCount; b++)
                        {
                            if (a != userTaxi[b].UID)
                            {
                                f = 1;
                                userTaxi[userTaxiCount].UID = a;
                                break;
                            }
                        }
                        if (f == 1)
                            break;
                    }
                    userTaxi[userTaxiCount].UID;

                    cout << "\nNew User Added";
                    userMode = 2;
                    currentIndex = userTaxiCount - 1;
                    currentUID = userTaxi[userTaxiCount].UID;
                    userTaxiCount++;
                    return true;
                } //if there is still space, closed
                else
                {
                    cout << "\nSorry! User List (Taxi) is already full!";
                }
            }
            break;
            default:
            {
                cout << "\nInvalid Input!";
            }
            break;
            }
        }
        break;
        case 3: //Staff
        {
            cout << "\nStaff Log In";
            cout << "\n\t1. Log In";
            cout << "\n\t-1. GO BACK";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;
            switch (choice)
            {
            case -1:
            {
                cout << "\nGoing back";
                wait(1);
            }
            break;
            case 1: //log in as staff
            {
                //authenticating with the records
                if (staffCount > 0)
                {
                    cout << "\nStaff Authentication:";
                    cout << "\n\tEnter UID: ";
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
                    cin >> PWDin;

                    for (int a = 0; a < staffCount; a++)
                    {
                        if (staff[a].UID == UIDin && staff[a].password == PWDin)
                        {
                            found = 1;
                            userMode = 3;
                            currentIndex = a;
                            int currentUID = staff[a].UID;
                            cout << "\nAuthenticated as staff.\nWelcome " << staff[a].Name << "!";
                            wait(1);
                            return true;
                        }
                    }
                    if (found != 1)
                    {
                        cout << "\nEntered credentials do not match any of the records!";
                    }
                }
                else
                {
                    cout << "\nNo staff records available to look into!\nContact Admin.";
                }
            }
            break;
            default:
            {
                cout << "\nInvalid Input!";
            }
            break;
            }
        }
        break;
        case 4: //Admin
        {
            cout << "\nAdmin Log In\nALERT!!! If invalid credentials are entered, Program will terminate!";
            cout << "\n\t1. Log In";
            cout << "\n\t-1. GO BACK";
            cout << "\nEnter your choice_";
            cin >> choice;
            switch (choice)
            {
            case -1:
            {
                cout << "\nGoing back";
                wait(1);
            }
            break;
            case 1: //log in as admin
            {
                //authenticating with the records
                if (adminCount > 0)
                {
                    cout << "\nadmin Authentication:";
                    cout << "\n\tEnter UID: ";
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    cin >> PWDin;

                    for (int a = 0; a < adminCount; a++)
                    {
                        if (admin[a].UID == UIDin && admin[a].password == PWDin)
                        {
                            found = 1;
                            userMode = 4;
                            currentIndex = a;
                            int currentUID = admin[a].UID;
                            cout << "\nAuthenticated as admin.\nWelcome " << admin[a].Name << "!";
                            wait(1);
                            return true;
                        }
                    }
                    if (found != 1)
                    {
                        cout << "\nEntered credentials do not match any of the records!";
                    }
                }
                else
                {
                    cout << "\nNo admin records available to look into!\nContact Admin.";
                }
            }
            break;
            default:
            {
                cout << "\nInvalid Input!";
            }
            break;
            }
        }
        break;
        default:
        {
            cout << "\nUnexpected behaviour while authentication!";
        }
        break;
        }
        //if never returned true, will return false in the end.
        return false;
    }
};

//keep in mind follwing methods and variables as you proceed
/*
const int maxUserCount = 100;
int userBikeCount;
int userTaxiCount;
const int maxVehicleCount = 30;
int BikeCount;
int TaxiCount;
const int maxStaffCount = 10;
int staffCount;
const int maxLocCount = 200;
int locCount;

struct userBike[maxUserCount];
struct userTaxi[maxUserCount];
struct bike[maxVehicleCount];
struct taxi[maxVehicleCount];
struct staff[maxStaffCount];
struct location[maxLocCount];

*/

// class MrCalendar
// {
// public:
//     void inputDate(int *dd, int *mm, int *yy)
//     {
//         cout << "Date: ";
//         cin >> &dd;
//         cout << "Month: ";
//         cin >> &mm;
//         cout << "Year: ";
//         cin >> &yy;
//     }
//     void inputTime(int *h, int *m)
//     {
//     }
// };

//this is the class where most of us need to work
class BookMyRide : public Support
{
public:
    void authorize(int n); //storing n into userMode if user verifies the passwords and all
                           //otherwise store -1 in userMode
                           //give three chances to enter password
    //code ok
    void bookBike()
    {
        if (userMode == 1)
        {
            if (isAvailBike() != -1)
            {
                if (locCount >= 2)
                {
                    cout << "\nHere are the list of locations:";
                    showLocations();

                    int loc1, loc2; //stores first UIDs, then index nos of locations
                    int bikeIndex, dist;

                    cout << "\nFrom (Enter Serial No)_";
                    cin >> loc1;
                    cout << "\nTo (Enter Serial No)_";
                    cin >> loc2;

                    if (loc1 < locCount && loc2 < locCount)
                    {
                        userBike[currentIndex].BikeUID = bike[isAvailBike()].UID;
                        bikeIndex = isAvailBike();
                        userBike[currentIndex].locInd1 = loc1;
                        userBike[currentIndex].locInd2 = loc2;
                        dist = calculateDistance(loc1, loc2);

                        bike[bikeIndex].isAvail = 0;
                        bike[bikeIndex].userIndex = currentIndex;

                        cout << "\nBooking Details:";
                        cout << "\nFROM: " << location[loc1].locName << " (" << location[loc1].UID << ")";
                        cout << "\nTO: " << location[loc2].locName << " (" << location[loc1].UID << ")";
                        cout << "\nDistance: " << dist << " km";
                        cout << "\nExpected Time Taken: " << (float)dist / bikeMileage << " hours";
                        cout << "\n Bike UID: " << userBike[currentIndex].BikeUID;
                        cout << "\n Driver Contact: \t" << bike[bikeIndex].Name << "\t" << bike[bikeIndex].MobNo;
                    }
                    else
                    {
                        cout << "\nAtleast one of the entered location indices is invalid.";
                    }
                }
                else
                {
                    cout << "\nLocation Details are insufficient! Contact the organisation.";
                }
            }
            else
            {
                cout << "\nNo bikes available";
            }
        }
        else
        {
            cout << "\nUnauthorised Access Detected!";
            userMode = -1;
        }
    }

    void cancelBike()
    {
    }
    //code ok
    void bookTaxi()
    {

        if (userMode == 1)
        {
            if (isAvailTaxi() != -1)
            {
                if (locCount >= 2)
                {
                    cout << "\nHere are the list of locations:";
                    showLocations();

                    int loc1, loc2; //stores first UIDs, then index nos of locations
                    int taxiIndex, dist;

                    cout << "\nFrom (Enter Serial No)_";
                    cin >> loc1;
                    cout << "\nTo (Enter Serial No)_";
                    cin >> loc2;

                    if (loc1 < locCount && loc2 < locCount)
                    {
                        userTaxi[currentIndex].TaxiUID = taxi[isAvailTaxi()].UID;
                        taxiIndex = isAvailTaxi();
                        userTaxi[currentIndex].locInd1 = loc1;
                        userTaxi[currentIndex].locInd2 = loc2;
                        dist = calculateDistance(loc1, loc2);

                        taxi[taxiIndex].isAvail = 0;
                        taxi[taxiIndex].userIndex = currentIndex;

                        cout << "\nBooking Details:";
                        cout << "\nFROM: " << location[loc1].locName << " (" << location[loc1].UID << ")";
                        cout << "\nTO: " << location[loc2].locName << " (" << location[loc1].UID << ")";
                        cout << "\nDistance: " << dist << " km";
                        cout << "\nExpected Time Taken: " << (float)dist / taxiMileage << " hours";
                        cout << "\n Taxi UID: " << userTaxi[currentIndex].TaxiUID;
                        cout << "\n Driver Contact: \t" << taxi[taxiIndex].Name << "\t" << taxi[taxiIndex].MobNo;
                    }
                    else
                    {
                        cout << "\nAtleast one of the entered location indices is invalid.";
                    }
                }
                else
                {
                    cout << "\nLocation Details are insufficient! Contact the organisation.";
                }
            }
            else
            {
                cout << "\nNo taxis available";
            }
        }
        else
        {
            cout << "\nUnauthorised Access Detected!";
            userMode = -1;
        }
    }

    void cancelTaxi()
    {
    }

    void removeBooking()
    {
    }

    void showBookings()
    {
    }

    void getHelp() //shyam
    {
    }
    //code ok
    void showLocations()
    {
        if (userMode != -1)
        {
            if (locCount > 0)
            {
                cout << "\nIndex No\tUID\tName";
                cout << "\n-------------------------------------------------------------------";
                for (int a = 0; a < locCount; a++)
                {
                    cout << "\n"
                         << a << "\t" << location[a].UID << "\t" << location[a].locName;
                }
                cout << "\n-------------------------------------------------------------------";
            }
            else
            {
                cout << "\nNo location details to print!";
            }
        }
        else
        {
            cout << "\nUnauthorised Access Detected!";
        }
    }

    void addLocation()
    {
    }
    //code ok
    int isAvailBike()
    {
        if (userMode != -1)
        {
            if (bikeCount > 0)
            {
                for (int a = 0; a < bikeCount; a++)
                {
                    if (bike[a].isAvail == 1)
                        return a;
                }
            }
        }
        else
        {
            cout << "\nUnauthorised access detected!";
        }
        return -1;
    }
    //code ok
    int isAvailTaxi()
    {
        if (userMode != -1)
        {
            if (taxiCount > 0)
            {
                for (int a = 0; a < taxiCount; a++)
                {
                    if (taxi[a].isAvail == 1)
                        return a;
                }
            }
        }
        else
        {
            cout << "\nUnauthorised access detected!";
        }
        return -1;
    }
    //code ok
    int calculateDistance(int index1, int index2)
    {
        if (index1 < locCount && index2 < locCount)
        {
            int x1, y1, x2, y2, dist;

            x1 = location[index1].locX;
            y1 = location[index1].locY;

            x2 = location[index2].locX;
            y2 = location[index2].locY;

            dist = sqrt((double)(x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        }
        return -1;
    }
    //code ok
    void addVehicle()
    {
        int choice = 0, f = 0;

        if (userMode == 3 || userMode == 4) //if user is staff or admin, then only allowed to edit
        {
            cout << "Which vehicle details do you want to add-";
            cout << "\n1. Bike";
            cout << "\n2. Car";
            cout << "\n-1. GO BACK";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;

            switch (choice)
            {
            case -1: //Go back
            {
                cout << "\nGoing back...";
            }
            break;
            case 1: //Add bike
            {
                if (bikeCount < maxVehicleCount) //if  bike count is less that maxvehiclecount, then only we can add
                {
                    f = 0; //resetting the flag

                    cin >> bike[bikeCount].UID;
                    cout << "\nEnter Name of Driver: ";
                    fflush(stdin);
                    getline(cin, bike[bikeCount].Name);
                    cout << "\nEnter Mobile no. of Driver: ";
                    fflush(stdin);
                    cin >> bike[bikeCount].MobNo;
                    cout << "\nEnter Email id: ";
                    fflush(stdin);
                    cin >> bike[bikeCount].EmailID;
                    cout << "\nEnter Date of Joining: ";
                    fflush(stdin);
                    cin >> bike[bikeCount].Date_Joining;

                    //PROGRAM FOR UID ALLOTTMENT
                    if (bikeCount < 1)
                    {
                        bike[bikeCount].UID = 0;
                        cout << "\nUID allotted : 0";
                    }
                    else
                    {
                        for (int a = 0; a < maxVehicleCount; a++)
                        {
                            int f = 0;
                            for (int b = 0; b < bikeCount; b++)
                            {
                                if (a == bike[b].UID)
                                {
                                    f = 1;
                                    break;
                                }
                            }
                            if (f != 1)
                            {
                                cout << "\nUID allotted : " << a;
                                bike[bikeCount].UID = a;
                                break;
                            }
                        }
                    }
                    ///////////////////////////////

                    bikeCount++;
                }
                else
                {
                    cout << "\nCannot add more bikes! Database is full!";
                }
            }
            break;
            case 2: //Add Taxi
            {
                if (taxiCount < maxVehicleCount) //if  taxi count is less that maxvehiclecount, then only we can add
                {
                    f = 0; //resetting the flag

                    cout << "\nEnter Name of Driver: ";
                    fflush(stdin);
                    getline(cin, taxi[taxiCount].Name);
                    cout << "\nEnter Mobile no. of Driver: ";
                    fflush(stdin);
                    cin >> taxi[taxiCount].MobNo;
                    cout << "\nEnter Email id: ";
                    fflush(stdin);
                    cin >> taxi[taxiCount].EmailID;
                    cout << "\nEnter Date of Joining: ";
                    fflush(stdin);
                    cin >> taxi[taxiCount].Date_Joining;

                    //PROGRAM FOR UID ALLOTTMENT
                    if (taxiCount < 1)
                    {
                        taxi[taxiCount].UID = 0;
                        cout << "\nUID allotted : 0";
                    }
                    else
                    {
                        for (int a = 0; a < maxVehicleCount; a++)
                        {
                            int f = 0;
                            for (int b = 0; b < taxiCount; b++)
                            {
                                if (a == taxi[b].UID)
                                {
                                    f = 1;
                                    break;
                                }
                            }
                            if (f != 1)
                            {
                                cout << "\nUID allotted : " << a;
                                staff[taxiCount].UID = a;
                                break;
                            }
                        }
                    }
                    taxiCount++;
                }
                else
                {
                    cout << "\nCannot add more taxis! Database is full ";
                }
            }
            break;

            default:
            {
                cout << "\nInvalid choice entered!";
            }
            }
        }
    }
    //code ok
    void editVehicle()
    {
        int choice = 0, choice2 = 0; //choice2 for inner switch case
        int indexTemp = 0;           //for loops,to store index no of bike/taxi
        int UIDinput;
        string dataInput;
        int f = 0;                          //flag to check if entered UID is found or not
        if (userMode == 3 || userMode == 4) //if user is staff or admin, then only allowed to edit
        {
            cout << "Which vehicle do you want to edit-";
            cout << "\n1. Bike";
            cout << "\n2. Car";
            cout << "\n-1. GO BACK";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;

            switch (choice)
            {
            case -1: //Go back
            {
                cout << "\nGoing back...";
            }
            break;
            case 1: //Edit bike
            {
                if (bikeCount > 0) //if there is any bike, then only editing is possible
                {
                    f = 0; //resetting the flag
                    cout << "\nEnter UID of Bike to edit_";
                    fflush(stdin);
                    cin >> UIDinput;
                    for (indexTemp = 0; indexTemp < bikeCount; indexTemp++)
                    {
                        if (bike[indexTemp].UID == UIDinput)
                        {
                            f = 1; //flag if entered UID is found
                            break;
                        }
                    }
                    if (f == 1)
                    {
                        while (choice2 != -1) //loop because user may want to edit several things at a time
                        {
                            cout << "\nWhat do you want to edit?";
                            cout << "\n1. Name"; //name of driver not bike
                            cout << "\n2. Mobile No";
                            cout << "\n3. Email ID";
                            cout << "\n4. Date_Joining";
                            cout << "\n-1 GO BACK";

                            switch (choice2)
                            {
                            case -1: //Go back
                            {
                                cout << "\nGoing back...";
                            }
                            break;
                            case 1: //change name
                            {
                                cout << "\nCurrent Name:" << bike[indexTemp].Name;
                                cout << "\nEnter new Name_";
                                fflush(stdin);
                                fflush(stdin);
                                cin >> dataInput;
                                bike[indexTemp].Name = dataInput;
                                cout << "\nName of UID " << UIDinput << " changed.";
                            }
                            break;
                            case 2: //change MobNo
                            {
                                cout << "\nCurrent Mobile No:" << bike[indexTemp].MobNo;
                                cout << "\nEnter new Mobile No_";
                                fflush(stdin);
                                fflush(stdin);
                                cin >> dataInput;
                                bike[indexTemp].MobNo = dataInput;
                                cout << "\nMobile No of UID " << UIDinput << " changed.";
                            }
                            break;
                            case 3: //change EmailID
                            {
                                cout << "\nCurrent Email ID:" << bike[indexTemp].EmailID;
                                cout << "\nEnter new Email ID_";
                                fflush(stdin);
                                fflush(stdin);
                                cin >> dataInput;
                                bike[indexTemp].EmailID = dataInput;
                                cout << "\nEmailID of UID " << UIDinput << " changed.";
                            }
                            break;
                            case 4: //change Date_joining
                            {
                                cout << "\nCurrent Date_Joining:" << bike[indexTemp].Date_Joining;
                                cout << "\nEnter new Date_Joining_";
                                fflush(stdin);
                                fflush(stdin);
                                cin >> dataInput;
                                bike[indexTemp].Date_Joining = dataInput;
                                cout << "\nDate_Joining of UID " << UIDinput << " changed.";
                            }
                            break;
                            default:
                            {
                                cout << "\nInvalid choice entered!";
                            }
                            break;
                            }
                        }
                    }
                    else
                    {
                        cout << "\nEntered UID is not found!";
                    }
                }
                else
                {
                    cout << "\nNo bike records to look into!";
                }
            }
            break;
            case 2: //Edit Car
            {
                if (taxiCount > 0) //if there is any taxi, then only editing is possible
                {
                    f = 0; //resetting the flag
                    cout << "\nEnter UID of taxi to edit_";
                    fflush(stdin);
                    fflush(stdin);
                    cin >> UIDinput;
                    for (indexTemp = 0; indexTemp < taxiCount; indexTemp++)
                    {
                        if (taxi[indexTemp].UID == UIDinput)
                        {
                            f = 1; //flag if entered UID is found
                            break;
                        }
                    }
                    if (f == 1)
                    {
                        while (choice2 != -1) //loop because user may want to edit several things at a time
                        {
                            cout << "\nWhat do you want to edit?";
                            cout << "\n1. Name"; //name of driver not taxi
                            cout << "\n2. Mobile No";
                            cout << "\n3. Email ID";
                            cout << "\n4. Date_Joining";
                            cout << "\n-1 GO BACK";

                            switch (choice2)
                            {
                            case -1: //Go back
                            {
                                cout << "\nGoing back...";
                            }
                            break;
                            case 1: //change name
                            {
                                cout << "\nCurrent Name:" << taxi[indexTemp].Name;
                                cout << "\nEnter new Name_";
                                fflush(stdin);
                                fflush(stdin);
                                cin >> dataInput;
                                taxi[indexTemp].Name = dataInput;
                                cout << "\nName of UID " << UIDinput << " changed.";
                            }
                            break;
                            case 2: //change MobNo
                            {
                                cout << "\nCurrent Mobile No:" << taxi[indexTemp].MobNo;
                                cout << "\nEnter new Mobile No_";
                                fflush(stdin);
                                fflush(stdin);
                                cin >> dataInput;
                                taxi[indexTemp].MobNo = dataInput;
                                cout << "\nMobNo of UID " << UIDinput << " changed.";
                            }
                            break;
                            case 3: //change EmailID
                            {
                                cout << "\nCurrent EmailID:" << taxi[indexTemp].EmailID;
                                cout << "\nEnter new EmailID_";
                                fflush(stdin);
                                fflush(stdin);
                                cin >> dataInput;
                                taxi[indexTemp].EmailID = dataInput;
                                cout << "\nEmailID of UID " << UIDinput << " changed.";
                            }
                            break;
                            case 4: //change Date_joining
                            {
                                cout << "\nCurrent Date_Joining:" << taxi[indexTemp].Date_Joining;
                                cout << "\nEnter new Date_Joining_";
                                fflush(stdin);
                                fflush(stdin);
                                cin >> dataInput;
                                taxi[indexTemp].Date_Joining = dataInput;
                                cout << "\nDate_Joining of UID " << UIDinput << " changed.";
                            }
                            break;
                            default:
                            {
                                cout << "\nInvalid choice entered!";
                            }
                            break;
                            }
                        }
                    }
                    else
                    {
                        cout << "\nEntered UID is not found!";
                    }
                }
                else
                {
                    cout << "\nNo taxi records to look into!";
                }
            }
            break;
            default:
            {
                cout << "\nInvalid Vehicle type entered!";
            }
            }
        }
    }
    //code ok
    void removeVehicle() //hishita
    {
        int choice = 0;

        if (userMode == 3 || userMode == 4) //if user is staff or admin, then only allowed to edit
        {
            cout << "Which vehicle details do you want to remove-";
            cout << "\n1. Bike";
            cout << "\n2. Car";
            cout << "\n-1. GO BACK";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;

            switch (choice)
            {
            case -1: //Go back
            {
                cout << "\nGoing back...";
            }
            break;
            case 1: //remove bike
            {

                if (bikeCount == 0)
                {
                    cout << "Bike list is empty ! Nothing to Delete !" << endl;
                }
                else
                {
                    cout << "Enter the UID of bike you want to Delete: ";
                    int tempUID, flag = -1;
                    fflush(stdin);
                    cin >> tempUID;

                    for (int i = 0; i < bikeCount; bikeCount++)
                    {
                        if (tempUID == bike[i].UID)
                        {
                            flag = i;
                            break;
                        }
                    }
                    if (flag == -1)
                    {
                        cout << "Entered UID not found !";
                    }
                    else
                    {
                        if (flag == bikeCount - 1)
                        {
                            bikeCount--;
                        }
                        else
                        {
                            string tempnp;
                            int tempU;
                            for (int i = flag; i < bikeCount - 1; i++)
                            {
                                tempU = bike[i].UID;
                                bike[i].UID = bike[i + 1].UID;
                                bike[i + 1].UID = tempU;

                                tempnp = bike[i].Name;
                                bike[i].Name = bike[i + 1].Name;
                                bike[i + 1].Name = tempnp;

                                tempnp = bike[i].MobNo;
                                bike[i].MobNo = bike[i + 1].MobNo;
                                bike[i + 1].MobNo = tempnp;

                                tempnp = bike[i].EmailID;
                                bike[i].EmailID = bike[i + 1].EmailID;
                                bike[i + 1].EmailID = tempnp;

                                tempnp = bike[i].Date_Joining;
                                bike[i].Date_Joining = bike[i + 1].Date_Joining;
                                bike[i + 1].Date_Joining = tempnp;
                            }
                            bikeCount--;
                        }
                    }
                }
            }

            break;
            case 2: //remove taxi
            {
                if (taxiCount == 0)
                {
                    cout << "Taxilist is empty ! Nothing to Delete !" << endl;
                }
                else
                {
                    cout << "Enter the UID of Taxi you want to Delete: ";
                    int tempUID, flag = -1;
                    fflush(stdin);
                    cin >> tempUID;

                    for (int i = 0; i < taxiCount; taxiCount++)
                    {
                        if (tempUID == taxi[i].UID)
                        {
                            flag = i;
                            break;
                        }
                    }
                    if (flag == -1)
                    {
                        cout << "Entered UID not found !";
                    }
                    else
                    {
                        if (flag == taxiCount - 1)
                        {
                            taxiCount--;
                        }
                        else
                        {
                            string tempnp;
                            int tempU;
                            for (int i = flag; i < taxiCount - 1; i++)
                            {
                                tempU = taxi[i].UID;
                                taxi[i].UID = taxi[i + 1].UID;
                                taxi[i + 1].UID = tempU;

                                tempnp = taxi[i].Name;
                                taxi[i].Name = taxi[i + 1].Name;
                                taxi[i + 1].Name = tempnp;

                                tempnp = taxi[i].MobNo;
                                taxi[i].MobNo = taxi[i + 1].MobNo;
                                taxi[i + 1].MobNo = tempnp;

                                tempnp = taxi[i].EmailID;
                                taxi[i].EmailID = taxi[i + 1].EmailID;
                                taxi[i + 1].EmailID = tempnp;

                                tempnp = taxi[i].Date_Joining;
                                taxi[i].Date_Joining = taxi[i + 1].Date_Joining;
                                taxi[i + 1].Date_Joining = tempnp;
                            }
                            taxiCount--;
                        }
                    }
                }
            }

            } //switch
        }     //userMode Check
        else
        {
            cout << "Access not allowed !";

            userMode = -1;
        }
    }
    //code ok
    void viewHelpList()
    {
        if (userMode == 3)
        {
            if (helpCount > 0)
            {
                cout << "\n-------------------------------------------------------------------";
                cout << "\nHelp UID\tUser Type\tUser UID";
                for (int a = 0; a < helpCount; a++)
                {

                    cout << "\n\n"
                         << help[a].UID << "\t" << help[a].userMode << "\t" << help[a].userUID
                         << "\nComment:" << help[a].comment;
                }
                cout << "\n-------------------------------------------------------------------";
            }
            else
            {
                cout << "\nThere are no help requests.";
            }
        }
        else
        {
            cout << "\nUnauthorised Access Detected!";
            userMode = -1;
        }
    }
    //code ok
    void showVehicles()
    {
        int indexTemp = -1;
        if (userMode == 3 || userMode == 4)
        {
            int choice = 0;
            while (choice != -1)
            {
                cout << "\nDisplay Vehicle Details Menu:";
                cout << "\n1. Bike List";
                cout << "\n2. Taxi List";
                cout << "\n-1 GO BACK";
                cout << "\nEnter your choice_";
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    if (bikeCount > 0)
                    {
                        cout << "\nSr.No\tUID\tDriver\tContact";
                        for (int a = 0; a < bikeCount; a++)
                        {
                            cout << "\n"
                                 << a + 1 << "\t" << bike[a].UID << "\t" << bike[a].Name << "\t" << bike[a].MobNo;
                        }
                    }
                    else
                    {
                        cout << "\nBike List is empty!";
                    }
                }
                break;
                case 2:
                {
                    if (taxiCount > 0)
                    {
                        cout << "\nSr.No\tUID\tDriver\tContact";
                        for (int a = 0; a < taxiCount; a++)
                        {
                            cout << "\n"
                                 << a + 1 << "\t" << taxi[a].UID << "\t" << taxi[a].Name << "\t" << taxi[a].MobNo;
                        }
                    }
                    else
                    {
                        cout << "\nTaxi List is empty!";
                    }
                }
                break;
                case -1:
                {
                    cout << "\nGoing back";
                    wait(2);
                }
                break;
                default:
                {
                    cout << "\nInvalid Choice entered";
                }
                break;
                }
            }
        }
        else
        {
            cout << "\nUnauthorised access detected!";
            userMode = -1;
        }
    }
    //code ok
    void resolveHelp()
    {
        if (userMode == 3)
        {
            if (helpCount > 0)
            {
                int UIDin = 0;
                while (UIDin != -1)
                {
                    viewHelpList();
                    cout << "\nEnter Help UID to resolve_";
                    cin >> UIDin;

                    int f = -1;
                    for (int a = 0; a < helpCount; a++)
                    {
                        if (UIDin == help[a].UID)
                        {
                            f = a;
                            break;
                        }
                    }
                    if (f >= 0)
                    {
                        cout << "\nHelp UID\tUser Type\tUser UID";
                        cout << help[f].UID << "\t" << help[f].userMode << "\t" << help[f].userUID
                             << "\nComment:" << help[f].comment;

                        int choice2 = 0;
                        cout << "\nPress 1 to confirm, 0 to cancel_";
                        cin >> choice2;
                        if (choice2 == 1) //delete that record
                        {
                            for (int b = f; b < helpCount - 1; b++)
                            {
                                string tempStr;
                                int tempInt;

                                tempInt = help[b].UID;
                                help[b].UID = help[b + 1].UID;
                                help[b + 1].UID = tempInt;

                                tempInt = help[b].userMode;
                                help[b].userMode = help[b + 1].userMode;
                                help[b + 1].userMode = tempInt;

                                tempInt = help[b].userUID;
                                help[b].userUID = help[b + 1].userUID;
                                help[b + 1].userUID = tempInt;

                                tempStr = help[b].comment;
                                help[b].comment = help[b + 1].comment;
                                help[b + 1].comment = tempStr;
                            }
                            helpCount--;
                            cout << "\nRecord Deleted.";
                            wait(2);
                        }
                        else
                        {
                            cout << "\nCancelled. Going back";
                            wait(2);
                        }
                    } //if f>0
                    else
                    {
                        cout << "\nEntered help UID not found";
                    }
                } //while UIDin!=-1
            }
            else
            {
                cout << "\nThere are no help requests.";
            }
        }
        else
        {
            cout << "\nUnauthorised access detected!";
            userMode = -1;
        }
    }
    //code ok
    void showMyDetails() //vanshika
    {
        if (userMode != -1)
        {
            if (userMode == 1)
            {
                cout << "\nYour Login Status: User (Bike)";
                cout << "\n------------------------------------------";
                cout << "\nName: " << userBike[currentIndex].Name;
                cout << "\nUID: " << userBike[currentIndex].UID;
                cout << "\nMobile No: " << userBike[currentIndex].MobNo;

                cout << "\nBooking Status: " << (userBike[currentIndex].isAllotted == 1) ? "Booked" : "Not Booked";
                cout << "\n------------------------------------------";
            }
            else if (userMode == 2)
            {
                cout << "\nYour Login Status: User (Taxi)";
                cout << "\n------------------------------------------";
                cout << "\nName: " << userTaxi[currentIndex].Name;
                cout << "\nUID: " << userTaxi[currentIndex].UID;
                cout << "\nMobile No: " << userTaxi[currentIndex].MobNo;

                cout << "\nBooking Status: " << (userTaxi[currentIndex].isAllotted == 1) ? "Booked" : "Not BookTaxi";
                cout << "\n------------------------------------------";
            }
            else if (userMode == 3)
            {
                cout << "\nYour Login Status: Staff";
                cout << "\n------------------------------------------";
                cout << "\nName: " << staff[currentIndex].Name;
                cout << "\nUID: " << staff[currentIndex].UID;
                cout << "\nMobile No: " << staff[currentIndex].MobNo;
                cout << "\n------------------------------------------";
            }
            else if (userMode == 4)
            {
                cout << "\nYour Login Status: Admin";
                cout << "\n------------------------------------------";
                viewOrgDetails();
                cout << "\n------------------------------------------";
            }
            else
            {
                cout << "\nOops! Something Unexpected occured!";
            }
        }
        else
        {
            cout << "\nUnauthorised access detected!";
            userMode = -1;
        }
    }
    //code ok
    void addStaff()
    {

        if (userMode == 4)
        {

            if (staffCount < maxStaffCount)
            {
                int tempindex = staffCount++;

                cout << "Enter your name : ";
                fflush(stdin);
                getline(cin, staff[tempindex].Name);
                cout << "Enter your password : ";

                fflush(stdin);
                cin >> staff[tempindex].password;

                //PROGRAM FOR UID ALLOTTMENT
                if (staffCount < 1)
                {
                    staff[staffCount].UID = 0;
                    cout << "\nUID allotted : 0";
                }
                else
                {
                    for (int a = 0; a < maxStaffCount; a++)
                    {
                        int f = 0;
                        for (int b = 0; b < staffCount; b++)
                        {
                            if (a == staff[b].UID)
                            {
                                f = 1;
                                break;
                            }
                        }
                        if (f != 1)
                        {
                            cout << "\nUID allotted : " << a;
                            staff[tempindex].UID = a;
                            break;
                        }
                    }
                }
            }
            else
            {
                cout << "Stafflist is full ! Can not add more staff." << endl;
            }
        }
        else
        {
            cout << "Access not allowed !";

            userMode = -1;
        }
    }
    //code ok
    void editStaff()
    {
        if (userMode == 4)
        {

            if (staffCount == 0)
            {
                cout << "Stafflist is empty ! Nothing to edit !" << endl;
            }
            else
            {
                cout << "Enter the UID you want to edit: ";
                int tempUID, flag = -1;
                fflush(stdin);
                cin >> tempUID;

                for (int i = 0; i < staffCount; staffCount++)
                {
                    if (tempUID == staff[i].UID)
                    {
                        flag = i;
                        break;
                    }
                }
                if (flag == -1)
                {
                    cout << "Entered UID not found !";
                }
                else
                {
                    cout << "Enter your choice";
                    cout << "1. Change Name \n2.Change password:" << endl;
                    int choice;
                    string temp;

                    fflush(stdin);
                    cin >> choice;
                    if (choice == 1)
                    {
                        cout << "Enter new Name: \n";
                        fflush(stdin);
                        fflush(stdin);
                        getline(cin, temp);
                        staff[flag].Name = temp;
                    }
                    else if (choice == 2)
                    {
                        cout << "Enter new password: ";
                        fflush(stdin);
                        cin >> temp;
                        staff[flag].password = temp;
                    }
                    else
                    {
                        cout << "Enter a valid Input: ";
                    }
                }
            }
        }
        else
        {
            cout << "Access not allowed !";

            userMode = -1;
        }
    }
    //code ok
    void removeStaff() //ritik
    {
        if (userMode == 4)
        {

            if (staffCount == 0)
            {
                cout << "Stafflist is empty ! Nothing to Delete !" << endl;
            }
            else
            {
                cout << "Enter the UID you want to Delete: ";
                int tempUID, flag = -1;
                fflush(stdin);
                cin >> tempUID;

                for (int i = 0; i < staffCount; staffCount++)
                {
                    if (tempUID == staff[i].UID)
                    {
                        flag = i;
                        break;
                    }
                }
                if (flag == -1)
                {
                    cout << "Entered UID not found !";
                }
                else
                {
                    if (flag == staffCount - 1)
                    {
                        staffCount--;
                    }
                    else
                    {
                        string tempnp;
                        int tempU;
                        for (int i = flag; i < staffCount - 1; i++)
                        {
                            tempU = staff[i].UID;
                            staff[i].UID = staff[i + 1].UID;
                            staff[i + 1].UID = tempU;

                            tempnp = staff[i].Name;
                            staff[i].Name = staff[i + 1].Name;
                            staff[i + 1].Name = tempnp;

                            tempnp = staff[i].password;
                            staff[i].password = staff[i + 1].password;
                            staff[i + 1].password = tempnp;
                        }
                        staffCount--;
                    }
                }
            }
        }
        else
        {
            cout << "Access not allowed !";

            userMode = -1;
        }
    }
    //code ok
    void viewStaff()
    {
        int indexTemp = -1; //to run loops and store index no to operate on
        if (userMode == 4)  //only admin is allowed to view staff list
        {
            if (staffCount > 0) //if there is atleast one staff, then only we can print
            {
                cout << "\nSr. No\tUID\tName";
                for (int indexTemp = 0; indexTemp < staffCount; indexTemp++)
                {
                    cout << "\n"
                         << indexTemp + 1
                         << "\t"
                         << staff[indexTemp].UID
                         << "\t";
                    //  << staff[indexTemp];
                }
            }
            else
            {
                cout << "\nStaff list is empty!";
            }
        }
        else
        {
            cout << "\nYou aren't allowed to view staff list!\nUnauthorised access detected!";
            //because if he isn't allowed, how did he get to that option!!! security!!!
            userMode = -1;
            //above line to exit program, to mark that unauthorise access is detected
        }
    }
    //code ok
    void viewOrgDetails()
    {
        if (userMode != -1)
        {
            cout << "Organization Details" << endl;
            if (adminCount == 1) //details are available
            {
                cout << "Name " << admin[0].OrgName << endl;
                cout << "Address " << admin[0].OrgAdrs << "\n";
                cout << "Mobile Number " << admin[0].MobNo << "\n";
                cout << "****************************************" << endl;
                cout << "Administrator" << admin[0].Name;
            }
            else
            {
                cout << "No Admin details Found" << endl;
            }
        }
        else
        {
            cout << "\nYou aren't allowed to view Organization Details!\nUnauthorised access detected!";
            //because if he isn't allowed, how did he get to that option!!! security!!!
            userMode = -1;
            //above line to exit program, to mark that unauthorise access is detected
        }
    }
    //code ok
    void editOrgDetails() //mehak
    {
        if (userMode == 4)
        {
            int choice = 1;
            string temp;
            while (choice != -1)
            {
                cout << "What Do You Want To Change\n";
                cout << "1. Name\n";
                cout << "2. password \n";
                cout << "3. OrgName\n";
                cout << "4. OrgAdrs\n";
                cout << "5. MobNo\n";
                cout << "-1 To Go Back" << endl;

                cout << "Enter Your Choice" << endl;
                fflush(stdin);
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    cout << "Enter New Admin Name\n";
                    fflush(stdin);
                    getline(cin, temp);
                    admin[0].Name = temp;
                }
                break;
                case 2:
                {
                    cout << "Enter New password" << endl;
                    fflush(stdin);
                    cin >> admin[0].password;
                }
                break;
                case 3:
                {
                    cout << "Enter New Organization Name\n";
                    fflush(stdin);
                    getline(cin, temp);
                    admin[0].OrgName = temp;
                }
                break;
                case 4:
                {
                    cout << "Enter New Organization Address\n";
                    fflush(stdin);
                    getline(cin, temp);
                    admin[0].OrgAdrs = temp;
                }
                break;
                case 5:
                {
                    cout << "Enter New Organization Name\n";
                    fflush(stdin);
                    cin >> temp;
                    admin[0].MobNo = temp;
                }
                break;
                case -1:
                {
                    cout << "Going Back..." << endl;
                    wait(2);
                }
                break;
                }
            }
        }
        else
        {
            cout << "\nYou aren't allowed to  Edit Organization Details!\nUnauthorised access detected!";
            //because if he isn't allowed, how did he get to that option!!! security!!!
            userMode = -1;
            //above line to exit program, to mark that unauthorise access is detected
        }
    }
    //code ok
    void addOrgDetails()
    {
        string temp = "NIL";
        if (userMode == 4)
        {
            cout << "\nEnter New Admin Name_";
            fflush(stdin);
            getline(cin, temp);
            admin[0].Name = temp;

            cout << "\nEnter New password_" << endl;
            fflush(stdin);
            cin >> temp;
            admin[0].password = temp;

            cout << "\nEnter Organization Name_";
            fflush(stdin);
            getline(cin, temp);
            admin[0].OrgName = temp;

            cout << "\nEnter Organization Address_";
            fflush(stdin);
            getline(cin, temp);
            admin[0].OrgAdrs = temp;

            cout << "\nEnter New Contact No_";
            fflush(stdin);
            cin >> temp;
            admin[0].MobNo = temp;

            admin[0].UID = 1;
            adminCount = 1;
            cout << "Going Back..._" << endl;
            wait(2);
        }

        else
        {
            cout << "\nYou aren't allowed to add Organization Details!\nUnauthorised access detected!";
            //because if he isn't allowed, how did he get to that option!!! security!!!
            userMode = -1;
            //above line to exit program, to mark that unauthorise access is detected
        }
    }
};

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int choice = 0;
    //changing theme of the prompt
    cout << "\nThemes Available:";
    cout << "\n0. Default";
    cout << "\n1. Ocean";
    cout << "\n2. Forest";
    cout << "\n3. Desert";
    cout << "\nEnter your choice_";
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        system("color 10");
    }
    break;
    case 2:
    {
        system("color 20");
    }
    break;
    case 3:
    {
        system("color 60");
    }
    break;
    default:
    {
        system("color 07");
    }
    break;
    } //switch

    // currentUID, UserMode, currentIndex and ARRAY currentIndexArray available if needed

    BookMyRide BMRobj;
    import();
    BMRobj.wait(3);
    BMRobj.screenReset();
    choice = 0;
    cout << "\nAdmin count=" << adminCount;
    //atleast admin details is mandatory to be present. If not, function call to Add Admin Details
    if (adminCount != 1)
    {
        cout << "\nAdmin Details Not Present.\nDirecting to add Admin Details";
        BMRobj.wait(2);
        userMode = 4;
        BMRobj.addOrgDetails();
        userMode = 0; //resetting userMode after important work is done
    }

    while (choice != -1)
    {
        BMRobj.screenReset();
        cout << "\nMain Menu";
        cout << "\n1.  Use for Bike booking & related";
        cout << "\n2.  Use for Taxi booking & related";
        cout << "\n3.  Login as Staff";
        cout << "\n4.  Login as Admin";
        cout << "\n-1. QUIT PROGRAM!";
        cout << "\nEnter your Choice_";
        fflush(stdin);
        cin >> choice;
        switch (choice)
        {
        case -1: //EXIT
        {
            cout << "\nHappy to help:-)";
        }
        break;
        case 1: //UserBike Section
        {
            userMode = 1;
            if (BMRobj.authenticate(userMode))
            {
                int choice2 = 0;
                while (choice2 != -1)
                {
                    cout << "\nUser(Bike) Menu";
                    cout << "\n1. New Booking";
                    cout << "\n2. Show Booking Details";
                    cout << "\n3. Remove Booking";
                    cout << "\n4. Ask for help";
                    cout << "\n-1. LOG OUT";

                    cout << "\nEnter your choice_";
                    fflush(stdin);
                    cin >> choice2;
                    switch (choice2)
                    {
                    case 1: //new booking
                    {
                        BMRobj.bookBike();
                    }
                    break;
                    case 2: //show booking
                    {
                        BMRobj.showBookings();
                    }
                    break;
                    case 3: //remove booking
                    {
                        BMRobj.removeBooking();
                    }
                    break;
                    case 4: //help
                    {
                        BMRobj.getHelp();
                    }
                    break;
                    case -1: //LOG OUT
                    {
                        cout << "\nLogging out";
                        BMRobj.wait(2);
                    }
                    break;
                    default: //Default
                    {
                        cout << "\nInvalid choice entered!";
                    }
                    break;
                    }
                    //Show your creativity here
                } //switch closed
                if (userMode == -1)
                {
                    cout << "\nUnauthorised Access Detected!";
                    break; //takes out of while loop
                }
            } //if closed
            else
            {
                cout << "\nUnable to Authenticate for Bike booking section!";
            }
        }
        break;
        case 2: //UserTaxi Section
        {
            userMode = 2;
            if (BMRobj.authenticate(userMode))
            {

                int choice2 = 0;
                while (choice2 != -1)
                {
                    cout << "\nUser(Taxi) Menu";
                    cout << "\n1. New Booking";
                    cout << "\n2. Show Booking Details";
                    cout << "\n3. Remove Booking";
                    cout << "\n4. Ask for help";
                    cout << "\n-1. LOG OUT";

                    cout << "\nEnter your choice_";
                    fflush(stdin);
                    cin >> choice2;
                    switch (choice2)
                    {
                    case 1: //new booking
                    {
                        BMRobj.bookTaxi();
                    }
                    break;
                    case 2: //show booking
                    {
                        BMRobj.showBookings();
                    }
                    break;
                    case 3: //remove booking
                    {
                        BMRobj.removeBooking();
                    }
                    break;
                    case 4: //help
                    {
                        BMRobj.getHelp();
                    }
                    break;
                    case -1: //LOG OUT
                    {
                        cout << "\nLogging out";
                        BMRobj.wait(2);
                    }
                    break;
                    default: //Default
                    {
                        cout << "\nInvalid choice entered!";
                    }
                    break;
                    }
                    //Show your creativity here
                } //switch closed
                if (userMode == -1)
                {
                    cout << "\nUnauthorised Access Detected!";
                    break; //takes out of while loop
                }
                //Show your creativity here
            }
            else
            {
                cout << "\nUnable to Authenticate for Taxi booking section";
            }
        }
        break;
        case 3: //Staff Section
        {
            userMode = 3;
            int choice2 = 0;
            if (BMRobj.authenticate(userMode))
            {
                //Show your creativity here
                while (choice2 != -1)
                {
                    BMRobj.screenReset();
                    cout << "\nAdmin Menu:";
                    cout << "\n1. Add Vehicle";
                    cout << "\n2. Edit Vehicle";
                    cout << "\n3. Remove Vehicle";
                    cout << "\n4. View Vehicles";
                    cout << "\n\n5. Add Location";
                    cout << "\n6. Edit Location";
                    cout << "\n7. Remove Location";
                    cout << "\n8. View Locations";
                    cout << "\n9. View My Details";
                    cout << "\n10. Edit My Details";
                    cout << "\n-1 LOG OUT";
                    cout << "\nEnter your choice_";
                    cin >> choice2;
                }
            }
            else
            {
                cout << "\nUnable to Authenticate as staff!";
            }
        }
        break;
        case 4: //Admin Section
        {

            userMode = 4;
            int choice2 = 0;
            if (BMRobj.authenticate(userMode))
            {
                //Show your creativity here
                while (choice2 != -1)
                {
                    BMRobj.screenReset();
                    cout << "\nAdmin Menu:";
                    cout << "\n1. Add Staff";
                    cout << "\n2. Edit Staff";
                    cout << "\n3. Remove Staff";
                    cout << "\n4. View Staff";
                    cout << "\n5. View Org Details";
                    cout << "\n6. Edit Org Details";
                    cout << "\n-1 LOG OUT";
                    cout << "\nEnter your choice_";
                    cin >> choice2;

                    switch (choice2)
                    {
                    case 1: //add staff
                    {
                        BMRobj.addStaff();
                    }
                    break;
                    case 2: //edit staff
                    {
                        BMRobj.editStaff();
                    }
                    break;
                    case 3: //remove staff
                    {
                        BMRobj.removeStaff();
                    }
                    break;
                    case 4: //view staff
                    {
                        BMRobj.viewStaff();
                    }
                    break;
                    case 5: //view org details
                    {
                        BMRobj.viewOrgDetails();
                    }
                    break;
                    case 6: //edit org details
                    {
                        BMRobj.editOrgDetails();
                    }
                    break;
                    case -1:
                    {
                        cout << "\nGoing back";
                        BMRobj.wait(2);
                    }
                    break;
                    default:
                    {
                        cout << "\nInvalid choice entered!";
                    }
                    break;
                    }
                }
            }
            else
            {
                cout << "\nUnable to Authenticate as Admin!";
                userMode = -1; //if unable to authenticate as admin, it will be considered as someone tried to breach the program!
            }
        }
        break;
        default: //Invalid Choice
        {
            cout << "\nINVALID CHOICE ENTERED";
        }
        break;
        } //switch closed
        if (userMode == -1)
        {
            cout << "\nSecurity issue detected!\nExiting the program...";
            break; //takes out of while loop
        }
        //resetting userMode and other things here
        userMode = 0;
    } //while closed
    backup();
    cout << "\n\\END OF PROGRAM.";
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
