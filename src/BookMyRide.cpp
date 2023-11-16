#include <iostream> //for input output
#include <stdio.h>  //for iput output
#include <stdlib.h> //memory allocation related
#include <string>
#include <cstring> //for string related operations
#include <time.h>  //for printing time
#include <conio.h> //for changing theme
#include <math.h>  //for math operations, sqrt,pow
using namespace std;

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
    void setTheme()
    {
        int choice = 0;
        //changing theme of the prompt
        cout << "\nThemes Available:";
        cout << "\n0. Default";
        cout << "\n1. Ocean";
        cout << "\n2. Forest";
        cout << "\n3. Desert";
        cout << "\nEnter your choice_";
        fflush(stdin);
        cin >> choice; //will be uncommented once program is finalised
        // choice = 3;
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
    }
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

    void holdByInput()
    {
        char holder;
        cout << "\nEnter any character to continue_";
        fflush(stdin);
        cin >> holder;
    }

    void screenReset()
    {
        system("cls");
        cout << "\n---------------------------------------------------------";
        time_t mytime;
        mytime = time(NULL);
        printf(ctime(&mytime));
        cout << "\n-------------------------[ " << admin[0].OrgName << " ]---------------------------";
        cout << "\nUSERMODE : " << userModeArray[userMode] << "\t\t\t\t";
        switch (userMode)
        {
        case 1:
            cout << userBike[currentIndex].Name << " (" << userBike[currentIndex].UID << ")";
            break;
        case 2:
            cout << userTaxi[currentIndex].Name << " (" << userTaxi[currentIndex].UID << ")";
            break;
        case 3:
            cout << staff[currentIndex].Name << " (" << staff[currentIndex].UID << ")";
            break;
        case 4:
            cout << admin[currentIndex].Name << " (" << admin[currentIndex].UID << ")";
            break;
        default:
            cout << "NIL";
            break;
        }
        printf("\n----------------------------------------------------------------------------------");
    }

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
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
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
                holdByInput();
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
                    fflush(stdin);
                    getline(cin, userBike[userBikeCount].Name);

                    cout << "\nEnter new password: ";
                    fflush(stdin);
                    fflush(stdin);
                    cin >> userBike[userBikeCount].password;

                    cout << "\nEnter your Mobile No: ";
                    fflush(stdin);
                    fflush(stdin);
                    cin >> userBike[userBikeCount].MobNo;

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
                    cout << "\nUID allotted: " << userBike[userBikeCount].UID;

                    cout << "\nNew User Added";
                    userMode = 1;
                    currentIndex = userBikeCount;
                    currentUID = userBike[userBikeCount].UID;
                    userBikeCount++;
                    holdByInput();
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
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
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
                    fflush(stdin);
                    getline(cin, userTaxi[userTaxiCount].Name);

                    cout << "\nEnter new password: ";
                    fflush(stdin);
                    cin >> userTaxi[userTaxiCount].password;

                    cout << "\nEnter your Mobile No: ";
                    fflush(stdin);
                    cin >> userTaxi[userTaxiCount].MobNo;

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
                    cout << "\nUID allotted: " << userTaxi[userTaxiCount].UID;

                    cout << "\nNew User Added";
                    currentUID = userTaxi[userTaxiCount].UID;
                    userMode = 2;
                    currentIndex = userTaxiCount;
                    userTaxiCount++;
                    holdByInput();
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
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
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
            case 1: //log in as admin
            {
                //authenticating with the records
                if (adminCount > 0)
                {
                    cout << "\nadmin Authentication:";
                    cout << "\n\tEnter UID: ";
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
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
//         fflush(stdin);cin>> &dd;
//         cout << "Month: ";
//         fflush(stdin);cin>> &mm;
//         cout << "Year: ";
//         fflush(stdin);cin>> &yy;
//     }
//     void inputTime(int *h, int *m)
//     {
//     }
// };

//this is the class where most of us need to work
class BookMyRide : public Support
{
public:
    // void authorize(int n); //storing n into userMode if user verifies the passwords and all
    //otherwise store -1 in userMode
    //give three chances to enter password
    //code done
    void tickOff()
    {
        if (userMode == 3)
        {
            int choice = 0;
            cout << "\nWhich type of booking to tick off?";
            cout << "\n1. Bike";
            cout << "\n2. Taxi";
            cout << "\n-1 GO BACK";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;
            switch (choice)
            {
            case 1: //bike
            {
                if (userBikeCount > 0)
                {
                    int UIDin, f = 0;
                    int tempIndex;
                    cout << "\nEnter the UID of the user_";
                    fflush(stdin);
                    cin >> UIDin;
                    for (int a = 0; a < userBikeCount; a++)
                    {
                        if (userBike[a].UID == UIDin)
                        {
                            tempIndex = a;
                            f = 1;
                            break;
                        }
                    }
                    if (f == 1)
                    {
                        if (userBike[tempIndex].isAllotted)
                        {
                            cout << "\nClearing the booking record...";

                            userBike[tempIndex].locInd1 = -1;
                            userBike[tempIndex].locInd2 = -1;

                            userBike[tempIndex].isAllotted = 0;

                            //for removing  bike booking status from  bike struct
                            for (int a = 0; a < bikeCount; a++)
                            {
                                if (bike[a].UID == userBike[tempIndex].BikeUID)
                                {
                                    bike[a].isAvail = 1;
                                    bike[a].userIndex = -1;
                                    userBike[tempIndex].BikeUID = -1;
                                    cout << "\nBooking Removed.";
                                    wait(2);
                                    break;
                                }
                            }
                        }
                        else
                        {
                            cout << "\nNo booking found with this UID!";
                        }
                    }
                    else
                    {
                        cout << "\nEntered UID not found!";
                    }
                }
                else
                {
                    cout << "\nThere are no users of Bike Booking right now.";
                }
            }
            break;
            case 2: //taxi
            {
                if (userTaxiCount > 0)
                {
                    int UIDin, f = 0;
                    int tempIndex;
                    cout << "\nEnter the UID of the user_";
                    fflush(stdin);
                    cin >> UIDin;
                    for (int a = 0; a < userTaxiCount; a++)
                    {
                        if (userTaxi[a].UID == UIDin)
                        {
                            tempIndex = a;
                            f = 1;
                            break;
                        }
                    }
                    if (f == 1)
                    {
                        if (userTaxi[tempIndex].isAllotted)
                        {
                            cout << "\nClearing the booking record...";

                            userTaxi[tempIndex].locInd1 = -1;
                            userTaxi[tempIndex].locInd2 = -1;

                            userTaxi[tempIndex].isAllotted = 0;

                            //for removing  taxi booking status from  taxi struct
                            for (int a = 0; a < taxiCount; a++)
                            {
                                if (taxi[a].UID == userTaxi[tempIndex].TaxiUID)
                                {
                                    taxi[a].isAvail = 1;
                                    taxi[a].userIndex = -1;
                                    userTaxi[tempIndex].TaxiUID = -1;
                                    cout << "\nBooking Removed.";
                                    wait(2);
                                    break;
                                }
                            }
                        }
                        else
                        {
                            cout << "\nNo booking found with this UID!";
                        }
                    }
                    else
                    {
                        cout << "\nEntered UID not found!";
                    }
                }
                else
                {
                    cout << "\nThere are no users of Taxi Booking right now.";
                }
            }
            break;
            case -1:
            {
                cout << "\nGoing back.";
            }
            break;
            default:
            {
                cout << "\nInvalid choice entered!";
            }
            } //switch case closed
        }
        else
        {
            cout << "\nUnauthorised Access Detected!";
            userMode = -1;
        }
    }
    //code done
    void bookBike()
    {
        if (userMode == 1)
        {
            if (isAvailBike() != -1)
            {
                if (locCount >= 2)
                {
                    if (userBike[currentIndex].isAllotted == 0)
                    {
                        cout << "\nHere are the list of locations:";
                        showLocations();

                        int loc1, loc2; //stores first UIDs, then index nos of locations
                        int bikeIndex;
                        float dist;

                        cout << "\nFrom (Enter Serial No)_";
                        fflush(stdin);
                        cin >> loc1;
                        cout << "\nTo (Enter Serial No)_";
                        fflush(stdin);
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
                            cout << "\nExpected Time Taken: " << dist / bikeMileage << " hours";
                            cout << "\n Bike UID: " << userBike[currentIndex].BikeUID;
                            cout << "\n Driver Contact: \t" << bike[bikeIndex].Name << "\t" << bike[bikeIndex].MobNo;
                            userBike[currentIndex].isAllotted = 1;
                        }
                        else
                        {
                            cout << "\nAtleast one of the entered location indices is invalid.";
                        }
                    }
                    else
                    {
                        cout << "\nYou already have a booking";
                    }
                }
                else
                {
                    cout << "\nLocation Details are insufficient! Contact the organisation.";
                }
            }
            else
            {
                cout << "\nNo bikes available.";
            }
        }
        else
        {
            cout << "\nUnauthorised Access Detected!";
            userMode = -1;
        }
    }
    //code done
    void cancelBike()
    {
        if (userMode == 1)
        {
            if (userBike[currentIndex].isAllotted)
            {
                cout << "\nClearing the booking record...";

                userBike[currentIndex].locInd1 = -1;
                userBike[currentIndex].locInd2 = -1;

                userBike[currentIndex].isAllotted = 0;

                //for removing bike booking status from bike struct
                for (int a = 0; a < bikeCount; a++)
                {
                    if (bike[a].UID == userBike[currentIndex].BikeUID)
                    {
                        bike[a].isAvail = 1;
                        bike[a].userIndex = -1;
                        userBike[currentIndex].BikeUID = -1;
                        cout << "\nBooking Removed.";
                        wait(2);
                        break;
                    }
                }
            }
            else
            {
                cout << "\nYou haven't booked any travel yet";
            }
        }
        else
        {
            cout << "\nYou aren't allowed to perform this change.";
        }
    }
    //code done
    void bookTaxi()
    {

        if (userMode == 2)
        {
            if (isAvailTaxi() != -1)
            {
                if (locCount >= 2)
                {
                    if (userTaxi[currentIndex].isAllotted == 0)
                    {
                        cout << "\nHere are the list of locations:";
                        showLocations();

                        int loc1, loc2; //stores first UIDs, then index nos of locations
                        int taxiIndex;
                        float dist;

                        cout << "\nFrom (Enter Serial No)_";
                        fflush(stdin);
                        cin >> loc1;
                        cout << "\nTo (Enter Serial No)_";
                        fflush(stdin);
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
                            cout << "\n Taxi UID: " << userTaxi[currentIndex].TaxiUID;
                            cout << "\n Driver Contact: \t" << taxi[taxiIndex].Name << "\t" << taxi[taxiIndex].MobNo;
                            cout << "\nDistance: " << dist << " km";
                            cout << "\nExpected Time Taken: " << dist / taxiMileage << " hours";
                            userTaxi[currentIndex].isAllotted = 1;
                        }
                        else
                        {
                            cout << "\nAtleast one of the entered location indices is invalid.";
                        }
                    }
                    else
                    {
                        cout << "\nYou already have a booking";
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
    //code done
    void cancelTaxi()
    {
        if (userMode == 2)
        {
            if (userTaxi[currentIndex].isAllotted)
            {
                cout << "\nClearing the booking record...";

                userTaxi[currentIndex].locInd1 = -1;
                userTaxi[currentIndex].locInd2 = -1;

                userTaxi[currentIndex].isAllotted = 0;

                //for removing taxi booking status from taxi struct
                for (int a = 0; a < taxiCount; a++)
                {
                    if (taxi[a].UID == userTaxi[currentIndex].TaxiUID)
                    {
                        taxi[a].isAvail = 1;
                        taxi[a].userIndex = -1;
                        userTaxi[currentIndex].TaxiUID = -1;
                        cout << "\nBooking Removed.";
                        wait(2);
                        break;
                    }
                }
            }
            else
            {
                cout << "\nYou haven't booked any travel yet";
            }
        }
        else
        {
            cout << "\nYou aren't allowed to perform this change.";
        }
    }
    //code done
    void showMyBooking()
    {
        if (userMode == 1)
        {
            if (userBike[currentIndex].isAllotted == 1)
            {
                int a, f = 0;
                for (a = 0; a < bikeCount; a++)
                {
                    if (userBike[currentIndex].BikeUID == bike[a].UID)
                    {
                        f = 1;
                        break;
                    }
                }

                if (f == 1)
                {
                    cout << "\nBike booking details";

                    cout << "\nFrom " << location[userBike[currentIndex].locInd1].locName;
                    cout << "To " << location[userBike[currentIndex].locInd2].locName;
                    cout << "\nBike Contact: " << bike[a].Name << " (" << bike[a].MobNo << ")";

                    float dist = calculateDistance(userBike[currentIndex].locInd1, userBike[currentIndex].locInd2);
                    cout << "\nDistance: " << dist << " km";
                    cout << "\nExpected Time Taken: " << dist / bikeMileage << " hours";
                    cout << "\n-------------------------------";
                }
                else
                {
                    cout << "\nBike not found:-(.\nKindly book again.\nExtremely Sorry for incovenience.\nProceeding to remove booking.\n";
                    cancelBike();
                }
            }
            else
            {
                cout << "\nYou haven't booked any travel yet.";
            }
        }
        else if (userMode == 2)
        {
            if (userTaxi[currentIndex].isAllotted == 1)
            {
                int a, f = 0;
                for (a = 0; a < taxiCount; a++)
                {
                    if (userTaxi[currentIndex].TaxiUID == taxi[a].UID)
                    {
                        f = 1;
                        break;
                    }
                }

                if (f == 1)
                {
                    cout << "\nTaxi booking details";

                    cout << "\nFrom " << location[userTaxi[currentIndex].locInd1].locName;
                    cout << "To " << location[userTaxi[currentIndex].locInd2].locName;
                    cout << "\nTaxi Contact: " << taxi[a].Name << " (" << taxi[a].MobNo << ")";

                    float dist = calculateDistance(userTaxi[currentIndex].locInd1, userTaxi[currentIndex].locInd2);
                    cout << "\nDistance: " << dist << " km";
                    cout << "\nExpected Time Taken: " << dist / taxiMileage << " hours";
                    cout << "\n-------------------------------";
                }
                else
                {
                    cout << "\nTaxi not found:-(.\nKindly book again.\nExtremely Sorry for incovenience.\nProceeding to remove booking.\n";
                    cancelTaxi();
                }
            }
            else
            {
                cout << "\nYou haven't booked any travel yet.";
            }
        }
        else
        {
            cout << "\nUnauthorised Access Detected!";
            userMode = -1;
        }
    }
    //code done
    void showBookingList()
    {
        int counter = 0;
        if (userMode == 3 || userMode == 4)
        {
            //for bike
            counter = 0;
            cout << "\nBike Bookings";
            cout << "\nIndex No\tBike UID\tUser Index\t Name";
            for (int a = 0; a < bikeCount; a++)
            {
                if (bike[a].isAvail == 0)
                {
                    cout << "\n"
                         << counter++ << "\t\t" << bike[a].UID << "\t\t" << bike[a].userIndex << "\t\t" << userBike[bike[a].userIndex].Name;
                }
            }
            cout << "\n---------------------------------------------";
            if (counter == 0)
                cout << "\nBike booking list empty.";

            //for taxi
            counter = 0;
            cout << "\nTaxi Bookings";
            cout << "\nIndex No\tTaxi UID\tUser Index\t Name";
            for (int a = 0; a < taxiCount; a++)
            {
                if (taxi[a].isAvail == 0)
                {
                    cout << "\n"
                         << counter++ << "\t\t" << taxi[a].UID << "\t\t" << taxi[a].userIndex << "\t\t" << userTaxi[taxi[a].userIndex].Name;
                }
            }
            cout << "\n---------------------------------------------";
            if (counter == 0)
                cout << "\nTaxi booking list empty.";
        }
        else
        {
            cout << "\nUnauthorised access detected!";
            userMode = -1;
        }
    }
    //code done
    void getHelp() //shyam
    {
        if (userMode == 1)
        {
            if (helpCount < maxHelpCount)
            {
                cout << "\nAdding new help request...";

                if (helpCount == 0)
                {
                    help[helpCount].UID = 0;
                    cout << "\nUID allotted : " << help[helpCount].UID;
                }
                else
                {
                    for (int a = 0; a < maxHelpCount; a++)
                    {
                        int f = 0;
                        for (int b = 0; b < helpCount; b++)
                        {
                            if (a == help[b].UID)
                            {
                                f = 1;
                                break;
                            }
                        }
                        if (f != 1)
                        {
                            cout << "\nUID allotted : " << a;
                            help[helpCount].UID = a;
                            break;
                        }
                    }
                }

                help[helpCount].userMode = 1;
                help[helpCount].userUID = userBike[currentIndex].UID;
                cout << "\nEnter details in short:\n";
                fflush(stdin);
                fflush(stdin);
                getline(cin, help[helpCount].comment);
                cout << "\nWe will contact you ASAP.";
                helpCount++;
            }
            else
            {
                cout << "\nHelp List is full.";
            }
            cout << "\nBy the way, you may contact us directly IFF URGENT.\nContact: " << admin[0].MobNo;
        }

        else if (userMode == 2)
        {
            if (helpCount < maxHelpCount)
            {
                cout << "\nAdding new help request...";

                if (helpCount == 0)
                {
                    help[helpCount].UID = 0;
                    cout << "\nUID allotted : " << help[helpCount].UID;
                }
                for (int a = 0; a < maxHelpCount; a++)
                {
                    int f = 0;
                    for (int b = 0; b < helpCount; b++)
                    {
                        if (a == help[b].UID)
                        {
                            f = 1;
                            break;
                        }
                    }
                    if (f != 1)
                    {
                        cout << "\nUID allotted : " << a;
                        help[helpCount].UID = a;
                        break;
                    }
                }

                help[helpCount].userMode = 2;
                help[helpCount].userUID = userTaxi[currentIndex].UID;
                cout << "\nEnter details in short:\n";
                fflush(stdin);
                fflush(stdin);
                getline(cin, help[helpCount].comment);
                cout << "\nWe will contact you ASAP.";
            }
            else
            {
                cout << "\nHelp List is full.";
            }
            cout << "\nBy the way, you may contact us directly IFF URGENT.\nContact: " << admin[0].MobNo;
        }
        else
        {
            cout << "\nUnauthorised access detected!";
            userMode = -1; //if not already
        }
    }
    //code done
    void showLocations()
    {
        if (userMode != -1)
        {
            if (locCount > 0)
            {
                cout << "\nIndex\tUID\tName";
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
    //code done
    void addLocation()
    {
        if (userMode == 3)
        {
            if (locCount < maxLocCount)
            {

                cout << "Add New Location:";
                cout << "\nName: ";
                fflush(stdin);
                cin >> location[locCount].locName;
                cout << "\nCoordinates: ";
                cout << "\nX: ";
                fflush(stdin);
                cin >> location[locCount].locX;
                cout << "\nY: ";
                fflush(stdin);
                cin >> location[locCount].locY;

                //PROGRAM FOR UID ALLOTTMENT
                if (locCount == 0)
                {
                    location[locCount].UID = 0;
                    cout << "\nUID allotted : 0";
                }
                else
                {
                    for (int a = 0; a < maxLocCount; a++)
                    {
                        int f = 0;
                        for (int b = 0; b < locCount; b++)
                        {
                            if (a == location[b].UID)
                            {
                                f = 1;
                                break;
                            }
                        }
                        if (f != 1)
                        {
                            cout << "\nUID allotted : " << a;
                            location[locCount].UID = a;
                            break;
                        }
                    }
                }
                locCount++;
            }
            else
            {
                cout << "\nLocation List is already full!";
            }
        }
        else
        {
            cout << "\nUnauthorised Access Detected!";
            userMode = -1;
        }
    }
    //code done
    void editLocation()
    {
        if (userMode == 3)
        {
            if (locCount > 0)
            {
                int UIDin;
                cout << "\nEnter UID of Location to edit_";
                fflush(stdin);
                cin >> UIDin;

                int f = 0, a = 0; //a stores the index no of required position

                for (a = 0; a < locCount; a++)
                {
                    if (UIDin == location[a].UID)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                {
                    f = 0;
                    int choice = 0;
                    while (choice != -1)
                    {
                        cout << "\nWhich parameter do you want to edit:";
                        cout << "\n1. Location Name";
                        cout << "\n2. X-Coordinate";
                        cout << "\n3. Y-Coordinate";
                        cout << "\n-1 Go Back";
                        cout << "\nEnter your choice_";
                        fflush(stdin);
                        cin >> choice;

                        switch (choice)
                        {
                        case 1: //location name
                        {
                            cout << "\nEnter new location name_";
                            fflush(stdin);
                            getline(cin, location[a].locName);
                        }
                        break;
                        case 2: //x coordinate
                        {
                            cout << "\nEnter new x-coordinate_";
                            fflush(stdin);
                            cin >> location[a].locX;
                        }
                        break;
                        case 3: //y coordinate
                        {
                            cout << "\nEnter new y-coordinate_";
                            fflush(stdin);
                            cin >> location[a].locY;
                        }
                        break;
                        case -1: //Go back
                        {
                            cout << "\nAlright.";
                        }
                        break;
                        default: //invalid choice
                        {
                            cout << "\nInvalid choice entered!";
                        }
                        break;
                        }
                    }
                }
                else
                {
                    cout << "\nEntered UID isn't present in the records!";
                }
            }
            else
            {
                cout << "\nLocation Database is empty!";
            }
        }
        else
        {
            cout << "\nUnauthorised Access Detected!";
            userMode = -1;
        }
    }
    //code done
    bool canRemoveLocation(int index)
    {
        for (int a = 0; a < userBikeCount; a++)
        {
            if (userBike[a].isAllotted == 1)
                if (userBike[a].locInd1 == index || userBike[a].locInd2 == index)
                    return false;
        }
        for (int a = 0; a < userTaxiCount; a++)
        {
            if (userTaxi[a].isAllotted == 1)
                if (userTaxi[a].locInd1 == index || userTaxi[a].locInd2 == index)
                    return false;
        }
        return true;
    }
    //code done
    void removeLocation()
    {
        if (userMode = 3)
        {
            int UIDin;
            cout << "\nEnter UID of Location to delete_";
            fflush(stdin);
            cin >> UIDin;

            int f = 0, a = 0; //a stores the index no of required position

            for (a = 0; a < locCount; a++)
            {
                if (UIDin == location[a].UID)
                {
                    f = 1;
                    break;
                }
            }
            if (f == 1)
            {
                if (canRemoveLocation(a))
                {

                    f = 0;
                    if (a < locCount - 1)
                    {
                        for (int b = a; b < locCount - 1; b++)
                        {
                            string tempStr;
                            int tempIn;

                            tempStr = location[a].locName;
                            location[a].locName = location[a + 1].locName;
                            location[a + 1].locName = tempStr;

                            tempIn = location[a].locX;
                            location[a].locX = location[a + 1].locX;
                            location[a + 1].locX = tempIn;

                            tempIn = location[a].locY;
                            location[a].locY = location[a + 1].locY;
                            location[a + 1].locY = tempIn;
                        }
                    }
                    locCount--;
                }
                else
                {
                    cout << "\nCannot Delete Vehicle!\nIt can be deleted only when it has no bookings";
                }
            }
            else
            {
                cout << "\nEntered UID isn't present in the records!";
            }
        }
        else
        {
            cout << "\nUnauthorised access detected!";
            userMode = -1;
        }
    }
    //code done
    void editSelf() //for staff and users
    {
        if (userMode == 1)
        {
            if (userBikeCount > 0)
            {
                int UIDin = userBike[currentIndex].UID;

                int f = 0, a = 0;
                for (a = 0; a < userBikeCount; a++)
                {
                    if (userBike[a].UID == userBike[a].UID)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                {
                    if (a != currentIndex)
                    {
                        cout << "\nDiscrepancy found in userBike.\nResolved.";
                        currentIndex = a;
                    }
                    f = 0;
                    int choice = 0;
                    while (choice != -1)
                    {
                        cout << "\nWhich parameter do you want to edit:";
                        cout << "\n1. Name";
                        cout << "\n2. Password";
                        cout << "\n3. Mobile No";
                        cout << "\n-1 Go Back";
                        cout << "\nEnter your choice_";
                        fflush(stdin);
                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                        {
                            cout << "\nEnter new name_";
                            fflush(stdin);
                            getline(cin, userBike[currentIndex].Name);
                        }
                        break;
                        case 2:
                        {
                            cout << "\nEnter new password_";
                            fflush(stdin);
                            cin >> userBike[currentIndex].password;
                        }
                        break;
                        case 3:
                        {
                            cout << "\nEnter new mobile No_";
                            fflush(stdin);
                            cin >> userBike[currentIndex].MobNo;
                        }
                        break;
                        case -1: //Go back
                        {
                            cout << "\nAlright.";
                        }
                        break;
                        default: //invalid choice
                        {
                            cout << "\nInvalid choice entered!";
                        }
                        break;
                        } //switch closed
                    }     //while closed
                }
                else
                {
                    userMode = -1;
                }
            }
            else
            {
                userMode = -1;
            }
        }
        else if (userMode == 2)
        {
            if (userTaxiCount > 0)
            {
                int UIDin = userTaxi[currentIndex].UID;

                int f = 0, a = 0;
                for (a = 0; a < userTaxiCount; a++)
                {
                    if (userTaxi[a].UID == userTaxi[a].UID)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                {
                    if (a != currentIndex)
                    {
                        cout << "\nDiscrepancy found in userTaxi.\nResolved.";
                        currentIndex = a;
                    }
                    f = 0;
                    int choice = 0;
                    while (choice != -1)
                    {
                        cout << "\nWhich parameter do you want to edit:";
                        cout << "\n1. Name";
                        cout << "\n2. Password";
                        cout << "\n3. Mobile No";
                        cout << "\n-1 Go Back";
                        cout << "\nEnter your choice_";
                        fflush(stdin);
                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                        {
                            cout << "\nEnter new name_";
                            fflush(stdin);
                            getline(cin, userTaxi[currentIndex].Name);
                        }
                        break;
                        case 2:
                        {
                            cout << "\nEnter new password_";
                            fflush(stdin);
                            cin >> userTaxi[currentIndex].password;
                        }
                        break;
                        case 3:
                        {
                            cout << "\nEnter new mobile No_";
                            fflush(stdin);
                            cin >> userTaxi[currentIndex].MobNo;
                        }
                        break;
                        case -1: //Go back
                        {
                            cout << "\nAlright.";
                        }
                        break;
                        default: //invalid choice
                        {
                            cout << "\nInvalid choice entered!";
                        }
                        break;
                        } //switch closed
                    }     //while closed
                }
                else
                {
                    userMode = -1;
                }
            }
            else
            {
                userMode = -1;
            }
        }
        else if (userMode == 3)
        {
            if (staffCount > 0)
            {
                int UIDin = staff[currentIndex].UID;

                int f = 0, a = 0;
                for (a = 0; a < staffCount; a++)
                {
                    if (staff[a].UID == staff[a].UID)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                {
                    if (a != currentIndex)
                    {
                        cout << "\nDiscrepancy found in staff.\nResolved temporarily.";
                        currentIndex = a;
                    }
                    f = 0;
                    int choice = 0;
                    while (choice != -1)
                    {
                        cout << "\nWhich parameter do you want to edit:";
                        cout << "\n1. Name";
                        cout << "\n2. Password";
                        cout << "\n3. Mobile No";
                        cout << "\n-1 Go Back";
                        cout << "\nEnter your choice_";
                        fflush(stdin);
                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                        {
                            cout << "\nEnter new name_";
                            fflush(stdin);
                            getline(cin, staff[currentIndex].Name);
                        }
                        break;
                        case 2:
                        {
                            cout << "\nEnter new password_";
                            fflush(stdin);
                            cin >> staff[currentIndex].password;
                        }
                        break;
                        case 3:
                        {
                            cout << "\nEnter new mobile No_";
                            fflush(stdin);
                            cin >> staff[currentIndex].MobNo;
                        }
                        break;
                        case -1: //Go back
                        {
                            cout << "\nAlright.";
                        }
                        break;
                        default: //invalid choice
                        {
                            cout << "\nInvalid choice entered!";
                        }
                        break;
                        } //switch closed
                    }     //while closed
                }
                else
                {
                    userMode = -1;
                }
            }
            else
            {
                userMode = -1;
            }
        }
        else
        {
            cout << "\nUnauthorised access detected!";
            userMode = -1;
        }
    }
    //code done
    int isAvailBike()
    {
        if (userMode != -1)
        {
            // cout << "\nbikeCount= " << bikeCount; //testing
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
    //code done
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
    //code done
    float calculateDistance(int index1, int index2)
    {
        if (index1 < locCount && index2 < locCount)
        {
            int x1, y1, x2, y2;

            x1 = location[index1].locX;
            y1 = location[index1].locY;

            x2 = location[index2].locX;
            y2 = location[index2].locY;

            return sqrt(pow(x2 - x1, 2) +
                        pow(y2 - y1, 2) * 1.0);
            // cout << "\nCalculating Distance";
            // int l1 = (x2 - x1) * (x2 - x1);
            // int l2 = (y2 - y1) * (y2 - y1);
            // cout << "\t" << l1 << "\t" << l2;
            // dist = sqrtf(l1 + l2);
            // dist = 0;
        }
        return -1;
    }
    //code done

    //HISHITA
    void addVehicle()
    {
        int choice = 0, f = 0;

        if (userMode == 3 || userMode == 4) //if user is staff or admin, then only allowed to edit
        {
            cout << "Which vehicle details do you want to add-";
            cout << "\n1. Bike";
            cout << "\n2. Taxi";
            cout << "\n-1. GO BACK";
            cout << "\nEnter your choice_";
            fflush(stdin);
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

                    // //PROGRAM FOR UID ALLOTTMENT
                    // if (bikeCount == 0)
                    // {
                    //     bike[bikeCount].UID = 0;
                    //     cout << "\nUID allotted : 0";
                    // }
                    // else
                    // {
                    //     for (int a = 0; a < maxVehicleCount; a++)
                    //     {
                    //         int f = 0;
                    //         for (int b = 0; b < bikeCount; b++)
                    //         {
                    //             if (a == bike[b].UID)
                    //             {
                    //                 f = 1;
                    //                 break;
                    //             }
                    //         }
                    //         if (f != 1)
                    //         {
                    //             cout << "\nUID allotted : " << a;
                    //             staff[bikeCount].UID = a;
                    //             break;
                    //         }
                    //     }
                    // }

                    cout << "\nEnter Name of Driver: ";
                    fflush(stdin);
                    getline(cin, bike[bikeCount].Name);
                    cout << "\nEnter Mobile no. of Driver: ";
                    fflush(stdin);
                    fflush(stdin);
                    cin >> bike[bikeCount].MobNo;
                    cout << "\nEnter Email id: ";
                    fflush(stdin);
                    fflush(stdin);
                    cin >> bike[bikeCount].EmailID;
                    cout << "\nEnter Date of Joining: ";
                    fflush(stdin);
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
                    bike[bikeCount].isAvail = 1;
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
                    fflush(stdin);
                    cin >> taxi[taxiCount].MobNo;
                    cout << "\nEnter Email id: ";
                    fflush(stdin);
                    fflush(stdin);
                    cin >> taxi[taxiCount].EmailID;
                    cout << "\nEnter Date of Joining: ";
                    fflush(stdin);
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
                    taxi[taxiCount].isAvail = 1;
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
    //code done
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
                            cout << "\nEnter your choice";
                            fflush(stdin);
                            cin >> choice2;
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
                            cout << "\nEnter your choice";
                            fflush(stdin);
                            cin >> choice2;
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
        else
        {
            cout << "\nUnauthorised access detected!";
            userMode = -1;
        }
    }
    //code done
    bool canRemoveBike(int index)
    {
        for (int a = 0; a < userBikeCount; a++)
        {
            if (userBike[a].isAllotted = 1)
                if (userBike[a].BikeUID == bike[index].UID)
                    return false;
        }
        return true;
    }
    //code done
    bool canRemoveTaxi(int index)
    {
        for (int a = 0; a < userTaxiCount; a++)
        {
            if (userTaxi[a].isAllotted = 1)
                if (userTaxi[a].TaxiUID == taxi[index].UID)
                    return false;
        }
        return true;
    }
    //code done
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
                        if (canRemoveBike(flag))
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
                        else
                        {
                            cout << "\nCannot Delete! It can be deleted only when it hasn't been booked.";
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
                        if (canRemoveTaxi(flag))
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
                        else
                        {
                            cout << "\nCannot Delete! It can be deleted only when it hasn't been booked.";
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
    //HISHITA
    //
    void viewHelpList()
    {
        if (userMode == 3)
        {
            if (helpCount > 0)
            {
                cout << "\n-------------------------------------------------------------------";
                cout << "\nHelpUID\tUser Type\tUser UID";
                for (int a = 0; a < helpCount; a++)
                {

                    cout << "\n\n"
                         << help[a].UID << "\t" << help[a].userMode << "\t\t";

                    if (help[a].userMode = 0)
                        for (int b = 0; b < userBikeCount; b++)
                        {
                            if (help[a].userUID == userBike[b].UID)
                            {
                                cout << userBike[b].MobNo;
                                break;
                            }
                        }
                    else
                        for (int b = 0; b < userTaxiCount; b++)
                        {
                            if (help[a].userUID == userTaxi[b].UID)
                            {
                                cout << userTaxi[b].MobNo;
                                break;
                            }
                        }

                    cout << "\nComment:" << help[a].comment;
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
    //code done
    //VANSHIKA
    void showVehicles()
    {
        int indexTemp = -1;
        if (userMode == 3 || userMode == 4)
        {
            int choice = 0;
            while (choice != -1)
            {
                screenReset();
                cout << "\nDisplay Vehicle Details Menu:";
                cout << "\n1. Bike List";
                cout << "\n2. Taxi List";
                cout << "\n-1 GO BACK";
                cout << "\nEnter your choice_";
                fflush(stdin);
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
                    holdByInput();
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
                    holdByInput();
                }
                break;
                case -1:
                {
                    cout << "\nGoing back";
                }
                break;
                default:
                {
                    cout << "\nInvalid Choice entered";
                    holdByInput();
                }
                break;
                } //switch closed
            }
        }
        else
        {
            cout << "\nUnauthorised access detected!";
            userMode = -1;
        }
    }
    //code done
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
                    cout << "\nEnter Help UID to resolve(-1 to go back)_";
                    fflush(stdin);
                    cin >> UIDin;
                    if (UIDin == -1)
                        break;

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
                        cout << "\nHelp UID\tUser Type\tUser Contact)\n";
                        cout << help[f].UID << "\t" << help[f].userMode << "\t\t";

                        if (help[f].userMode = 1)
                            for (int a = 0; a < userBikeCount; a++)
                            {
                                if (help[f].userUID == userBike[a].UID)
                                {
                                    cout << userBike[a].MobNo;
                                    break;
                                }
                            }
                        else
                            for (int a = 0; a < userTaxiCount; a++)
                            {
                                if (help[f].userUID == userTaxi[a].UID)
                                {
                                    cout << userTaxi[a].MobNo;
                                    break;
                                }
                            }

                        cout << "\nComment:" << help[f].comment;

                        int choice2 = 0;
                        cout << "\nPress 1 to confirm, 0 to cancel_";
                        fflush(stdin);
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
                            if (helpCount == 0)
                                UIDin = -1;
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
    //code done
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
    //VANSHIKA

    //RITIK
    void addStaff()
    {

        if (userMode == 4)
        {

            // cout << "\nstaff count=" << staffCount; //testing
            if (staffCount < maxStaffCount)
            {
                int tempindex = staffCount;

                cout << "Enter your name : ";
                fflush(stdin);
                getline(cin, staff[tempindex].Name);
                // cout << "\nEntered Data: " << staff[tempindex].Name; //testing

                cout << "Enter your password : ";
                fflush(stdin);
                cin >> staff[tempindex].password;

                cout << "Enter your mobile no : ";
                fflush(stdin);
                cin >> staff[tempindex].MobNo;

                //PROGRAM FOR UID ALLOTTMENT
                if (staffCount == 0)
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
                staffCount++;
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
    //code done
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
                    fflush(stdin);
                    cin >> choice;
                    if (choice == 1)
                    {
                        cout << "Enter new Name: \n";
                        fflush(stdin);
                        fflush(stdin);
                        fflush(stdin);
                        getline(cin, temp);
                        staff[flag].Name = temp;
                    }
                    else if (choice == 2)
                    {
                        cout << "Enter new password: ";
                        fflush(stdin);
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
    //code done
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
    //RITIK

    //MEHAK
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
                         << "\t"
                         << staff[indexTemp].Name;
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
    //code done
    void viewOrgDetails()
    {
        if (userMode != -1)
        {
            cout << "Organization Details" << endl;
            if (adminCount == 1) //details are available
            {
                cout << "Name: " << admin[0].OrgName << endl;
                cout << "Address: " << admin[0].OrgAdrs << "\n";
                cout << "Mobile Number: " << admin[0].MobNo << "\n";
                cout << "Administrator: " << admin[0].Name;
                cout << "\n****************************************" << endl;
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
    //code done
    void editOrgDetails() //mehak
    {
        if (userMode == 4)
        {
            int choice = 1;
            string temp;
            while (choice != -1)
            {
                screenReset();
                cout << "What Do You Want To Change\n";
                cout << "1. Name\n";
                cout << "2. password \n";
                cout << "3. OrgName\n";
                cout << "4. OrgAdrs\n";
                cout << "5. MobNo\n";
                cout << "-1 To Go Back" << endl;

                cout << "Enter Your Choice_";
                fflush(stdin);
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    cout << "Enter New Admin Name\n";
                    fflush(stdin);
                    fflush(stdin);
                    getline(cin, temp);
                    admin[0].Name = temp;
                }
                break;
                case 2:
                {
                    cout << "Enter New password" << endl;
                    fflush(stdin);
                    fflush(stdin);
                    cin >> admin[0].password;
                }
                break;
                case 3:
                {
                    cout << "Enter New Organization Name\n";
                    fflush(stdin);
                    fflush(stdin);
                    getline(cin, temp);
                    admin[0].OrgName = temp;
                }
                break;
                case 4:
                {
                    cout << "Enter New Organization Address\n";
                    fflush(stdin);
                    fflush(stdin);
                    getline(cin, temp);
                    admin[0].OrgAdrs = temp;
                }
                break;
                case 5:
                {
                    cout << "Enter New Organization Name\n";
                    fflush(stdin);
                    fflush(stdin);
                    cin >> temp;
                    admin[0].MobNo = temp;
                }
                break;
                case -1:
                {
                    cout << "Going Back..." << endl;
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
    //MEHAK

    void addOrgDetails()
    {
        string temp = "NIL";
        if (userMode == 4)
        {
            cout << "\nUID allotted: 0";

            cout << "\nEnter New Admin Name_";
            fflush(stdin);
            getline(cin, temp);
            admin[0].Name = temp;

            cout << "\nEnter New password_";
            fflush(stdin);
            fflush(stdin);
            cin >> temp;
            admin[0].password = temp;

            cout << "\nEnter Organization Name_";
            fflush(stdin);
            fflush(stdin);
            getline(cin, temp);
            admin[0].OrgName = temp;

            cout << "\nEnter Organization Address_";
            fflush(stdin);
            fflush(stdin);
            getline(cin, temp);
            admin[0].OrgAdrs = temp;

            cout << "\nEnter New Contact No_";
            fflush(stdin);
            fflush(stdin);
            cin >> temp;
            admin[0].MobNo = temp;

            admin[0].UID = 0;
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

    // currentUID, UserMode, currentIndex and ARRAY currentIndexArray available if needed

    BookMyRide BMRobj;
    BMRobj.setTheme();
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
                    BMRobj.screenReset();
                    cout << "\nUser(Bike) Menu";
                    cout << "\n1. Make Booking";
                    cout << "\n2. Show Booking Details";
                    cout << "\n3. Remove Booking";
                    cout << "\n4. Ask for help";
                    cout << "\n-1. LOG OUT";

                    cout << "\nEnter your choice_";
                    fflush(stdin);
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
                        BMRobj.showMyBooking();
                    }
                    break;
                    case 3: //remove booking
                    {
                        BMRobj.cancelBike();
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
                    }
                    break;
                    default: //Default
                    {
                        cout << "\nInvalid choice entered!";
                    }
                    break;
                    }
                    //Show your creativity here
                    BMRobj.holdByInput();
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
                    BMRobj.screenReset();
                    cout << "\nUser(Taxi) Menu";
                    cout << "\n1. New Booking";
                    cout << "\n2. Show Booking Details";
                    cout << "\n3. Remove Booking";
                    cout << "\n4. Ask for help";
                    cout << "\n-1. LOG OUT";

                    cout << "\nEnter your choice_";
                    fflush(stdin);
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
                        BMRobj.showMyBooking();
                    }
                    break;
                    case 3: //remove booking
                    {
                        BMRobj.cancelTaxi();
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
                    }
                    break;
                    default: //Default
                    {
                        cout << "\nInvalid choice entered!";
                    }
                    break;
                    }
                    //Show your creativity here
                    BMRobj.holdByInput();
                } //while closed

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
            int choice2 = 0, choice3 = 0;
            if (BMRobj.authenticate(userMode))
            {
                //Show your creativity here
                while (choice2 != -1)
                {

                    BMRobj.screenReset();

                    cout << "\nSTAFF MENU:";
                    cout << "\n1. Vehicle Menu";
                    cout << "\n2. Location Menu";
                    cout << "\n3. User Management";
                    cout << "\n4. Self Menu";
                    cout << "\n-1 LOG OUT";
                    cout << "\nEnter your choice_";
                    cin >> choice2;

                    switch (choice2)
                    {
                    case 1: //vehicle related
                    {
                        choice3 = 0;
                        while (choice3 != -1)
                        {
                            BMRobj.screenReset();
                            cout << "\nVehicle Menu";
                            cout << "\n1. Add Vehicle";
                            cout << "\n2. Edit Vehicle";
                            cout << "\n3. Remove Vehicle";
                            cout << "\n4. View Vehicles";
                            cout << "\n-1 Go Back";
                            cout << "\nEnter your choice_";
                            fflush(stdin);
                            cin >> choice3;

                            switch (choice3)
                            {
                            case 1:
                            {
                                BMRobj.addVehicle();
                            } //Add Vehicle
                            break;
                            case 2:
                            {
                                BMRobj.editVehicle();
                            } //Edit Vehicle
                            break;
                            case 3:
                            {
                                BMRobj.removeVehicle();
                            } //Remove Vehicle
                            break;
                            case 4:
                            {
                                BMRobj.showVehicles();
                            } //View Vehicles
                            break;
                            case -1:
                            {
                                cout << "\nGoing back.";
                            } //Log Out
                            break;
                            default:
                            {
                                cout << "\nInvalid choice entered!";
                            } //deafult
                            } //switch closed
                            BMRobj.holdByInput();
                            if (userMode == -1)
                            {
                                cout << "\nUnauthorised Access Detected!";
                                break; //takes out of while loop
                            }
                        } //while loop
                    }
                    break;
                    case 2: //location related
                    {
                        choice3 = 0;
                        while (choice3 != -1)
                        {
                            BMRobj.screenReset();
                            cout << "\nLocation Menu";
                            cout << "\n1. Add Location";
                            cout << "\n2. Edit Location";
                            cout << "\n3. Remove Location";
                            cout << "\n4. View Locations";
                            cout << "\n-1 Go Back";
                            cout << "\nEnter your choice_";
                            fflush(stdin);
                            cin >> choice3;

                            switch (choice3)
                            {
                            case 1:
                            {
                                BMRobj.addLocation();
                            } //Add Location
                            break;
                            case 2:
                            {
                                BMRobj.editLocation();
                            } //Edit Location
                            break;
                            case 3:
                            {
                                BMRobj.removeLocation();
                            } //Remove Location
                            break;
                            case 4:
                            {
                                BMRobj.showLocations();
                            } //View Location
                            break;
                            case -1:
                            {
                                cout << "\nGoing back.";
                            } //Log Out
                            break;
                            default:
                            {
                                cout << "\nInvalid choice entered!";
                            } //deafult
                            }
                            BMRobj.holdByInput();
                            if (userMode == -1)
                            {
                                cout << "\nUnauthorised Access Detected!";
                                break; //takes out of while loop
                            }
                        }
                    }
                    break;
                    case 3: // user related
                    {
                        choice3 = 0;
                        while (choice3 != -1)
                        {
                            BMRobj.screenReset();
                            cout << "\nUser Management";
                            cout << "\n1. Tick Off Booking";
                            cout << "\n2. Resolve help";
                            cout << "\n3. View Booking List";
                            cout << "\n-1 GO BACK";
                            cout << "\nEnter your choice_";
                            fflush(stdin);
                            cin >> choice3;

                            switch (choice3)
                            {
                            case 1:
                            {
                                BMRobj.tickOff();
                            }
                            break;
                            case 2:
                            {
                                BMRobj.resolveHelp();
                            }
                            break;
                            case 3:
                            {
                                BMRobj.showBookingList();
                            }
                            break;
                            case -1:
                            {
                                cout << "\nGoing back.";
                            } //Log Out
                            break;
                            default:
                            {
                                cout << "\nInvalid choice entered!";
                            } //deafult
                            }
                            BMRobj.holdByInput();
                            if (userMode == -1)
                            {
                                cout << "\nUnauthorised Access Detected!";
                                break; //takes out of while loop
                            }
                        }
                    }
                    break;
                    case 4: //self related
                    {
                        choice3 = 0;
                        while (choice3 != -1)
                        {
                            BMRobj.screenReset();
                            cout << "\nSelf Menu";
                            cout << "\n1. View My Details";
                            cout << "\n2. Edit My Details";
                            cout << "\n-1 Go Back";
                            cout << "\nEnter your choice_";
                            fflush(stdin);
                            cin >> choice3;

                            switch (choice3)
                            {
                            case 1:
                            {
                                BMRobj.showMyDetails();
                            } //View My Details
                            break;
                            case 2:
                            {
                                BMRobj.editSelf();
                            } //Edit My Details
                            break;
                            case -1:
                            {
                                cout << "\nGoing back.";
                            } //Log Out
                            break;
                            default:
                            {
                                cout << "\nInvalid choice entered!";
                            } //deafult
                            }
                            BMRobj.holdByInput();
                            if (userMode == -1)
                            {
                                cout << "\nUnauthorised Access Detected!";
                                break; //takes out of while loop
                            }
                        }
                    }
                    break;
                    case -1: //Go back
                    {
                        cout << "\nLogged Out.";
                    }
                    break;
                    default: //invalid choice
                    {
                        cout << "\nInvalid Choice Entered!";
                    }
                    }
                    BMRobj.holdByInput();
                    if (userMode == -1)
                    {
                        cout << "\nUnauthorised Access Detected!";
                        break; //takes out of while loop
                    }
                } // outer while closed
            }     //if authenticated closed
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
                    fflush(stdin);
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
                        cout << "\nGoing back.";
                    }
                    break;
                    default:
                    {
                        cout << "\nInvalid choice entered!";
                    }
                    break;
                    } //switch closed

                    BMRobj.holdByInput();

                    if (userMode == -1)
                    {
                        cout << "\nUnauthorised Access Detected!";
                        break; //takes out of while loop
                    }
                } //while closed
            }     //if(authentication) closed
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
    BMRobj.wait(3);
    cout << "\n\\END OF PROGRAM.";
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
