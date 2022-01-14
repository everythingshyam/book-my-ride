#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

//UID (User ID, TaxiID etc. ) rules
/*
    6 char string
    First char tells what kind of data is it...
        U   User
        S   Staff
        A   Admin
        B   Bike
        L   Location
        Z   for None of the above, such as for default value

    Second char tells additional details, Z if not needed
        For example, UB**** means user of bike, UT*** means that of taxi.
    Last four char represent serial no

    Example:
    UB0030  user of bike, serial no=30
    when adding new data , UID needs to be created using no from 0 to maxCount, whatever is available
*/

//Max prespecified Values
const int maxUserCount = 100;
const int maxVehicleCount = 30;
const int maxStaffCount = 10;
const int maxLocCount = 200;

//since we aren't going to create user Account and all, storing least data is good.
struct UserBike
{
    int isActive; //0 if booking is expired, 1 if active
    string UID;
    string Name;
    string password;
    string MobNo;

    string Date_Booking;
    string Time_Booking;

    string Date_Travel;
    string Time_Start;
    string Time_End;

    int isAllotted;
    string BikeUID;
} userBike[maxUserCount];
int userBikeCount;

struct UserTaxi
{
    int isActive; //0 if booking is expired(and removed from struct), 1 if active
    int UID;
    string Name;
    string password;
    string MobNo;

    string Date_Booking;
    string Time_Booking;

    string Date_Start;
    string Time_Start;

    string Date_End;
    string Time_End;

    int isAllotted;
    string TaxiUID;
} userTaxi[maxUserCount];
int userTaxiCount;

struct Bike
{
    int isAvail;

    string UID;
    string Name; //name of driver not bike
    string MobNo;
    string EmailID;
    string Date_Birth;
    string Date_Joining;
} bike[maxVehicleCount];
int bikeCount;

struct Taxi
{
    int isAvail;
    int capacity;
    int seatsOccupied;

    string UID;
    string Name;
    string MobNo;
    string EmailID;
    string Date_Birth;
    string Date_Joining;
} taxi[maxVehicleCount];
int taxiCount;

struct Staff
{
    string UID; //treated as UID if required
    string Name;
    string passWord;
} staff[maxStaffCount];
int staffCount;

struct Admin
{
    string UID; //treated as UID if required
    string Name;
    string passWord;
} admin[1]; //Always 1
int adminCount = 1;

struct Location
{
    string locName;
    string locID; //4 lettered capital letter short name, like if name is Pimpri, ID will be PIMP, easier for user to input
    long locX;    //x coordinate of location
    long locY;
} location[maxLocCount];
int locCount;

//following data used for user Identification
string userModeArray[5] = {"Logged Out(Safe)", "User (Bike)", "User (Taxi)", "Staff", "Admin"};
int userIndex = -1;
int userMode = 0;
string currentUID = "ZZ0000";
/*
    indicates the mode user is in
    -1: Logged out of everything(UNSAFE)____even if not handled accessing -1 index of userModeArray will terminate the program, thereby providing security
    0: Logged out but Safe
    1: Logged in as User_Bike
    2: Logged in as User_Taxi
    3: Logged in as Staff
    4: Logged in as Admin
    */

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

        printf("\nLoading.");

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
        cout << "\n------------------------------[ BOOK MY RIDE ]--------------------------------";
        cout << "\nUSERMODE : " << userModeArray[userMode] << "\t\t\t\t";
        switch (userMode)
        {
        case 1:
            cout << "USER ID : " << userBike[userIndex].UID;
            break;
        case 2:
            cout << "USER ID : " << userTaxi[userIndex].UID;
            break;
        case 3:
            cout << "STAFF ID : " << staff[userIndex].UID;
            break;
        case 4:
            cout << "ADMIN ID : " << admin[userIndex].UID;
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
    void import() //Completed
    {
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
        adminCount = fread(admin, sizeof(struct Admin), adminCount, fp);
        printf("\nAdmin Database imported successfully.");
        fclose(fp);

        //importing from Vehicle Database
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
        decryptAll();
    }
    ////////////////////////////////////////////////////////////////////////////////
    void backup()
    {
        //Encrypting all data
        encryptAll();
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
        fp = fopen("Admin.txt", "w");
        if (fp == NULL)
        {
            printf("/nAdmin Database is empty!");
            exit(1);
        }
        fwrite(admin, sizeof(struct Admin), adminCount, fp);
        printf("\nAdmin Database updated successfully.");
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
    ////////////////////////////////////////////////////////////////////////////////
    bool authenticate(int userModeIn)
    {
        //not designed yet...so, returning true.
        return true;
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

//this is the class where most of us need to work
class BookMyRide : public Support
{
public:
    void authorize(int n); //storing n into userMode if user verifies the passwords and all
                           //otherwise store -1 in userMode
                           //give three chances to enter password

    void bookTaxi();
    void cancelTaxi();
    void bookBike();
    void cancelBike();
    void showBookings();
    void help();

    void addVehicle();
    void editVehicle();
    void removeVehicle(); //hishita

    void showVehicles();
    void resolveHelp();
    void showMyDetails(); //vanshika

    void addStaff();
    void editStaff();
    void removeStaff(); //ritik

    void viewStaff();
    void viewOrgDetails();
    void editOrgDetails(); //mehak
};

void BookMyRide::editVehicle()
{
    int choice = 0, choice2 = 0; //choice2 for inner switch case
    int indexTemp = 0;           //for loops,to store index no of bike/taxi
    string UIDinput, dataInput;
    int f = 0;                          //flag to check if entered UID is found or not
    if (userMode == 3 || userMode == 4) //if user is staff or admin, then only allowed to edit
    {
        cout << "Which vehicle do you want to edit-";
        cout << "\n1. Bike";
        cout << "\n2. Car";
        cout << "\n-1. GO BACK";
        cout << "\nEnter your choice_";
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
                        cout << "\n2. MobNo";
                        cout << "\n3. EmailID";
                        cout << "\n4. Date_Birth";
                        cout << "\n5. Date_Joining";
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
                            cin >> dataInput;
                            bike[indexTemp].Name = dataInput;
                            cout << "\nName of UID " << UIDinput << " changed.";
                        }
                        break;
                        case 2: //change MobNo
                        {
                            cout << "\nCurrent MobNo:" << bike[indexTemp].MobNo;
                            cout << "\nEnter new MobNo_";
                            fflush(stdin);
                            cin >> dataInput;
                            bike[indexTemp].MobNo = dataInput;
                            cout << "\nMobNo of UID " << UIDinput << " changed.";
                        }
                        break;
                        case 3: //change EmailID
                        {
                            cout << "\nCurrent EmailID:" << bike[indexTemp].EmailID;
                            cout << "\nEnter new EmailID_";
                            fflush(stdin);
                            cin >> dataInput;
                            bike[indexTemp].EmailID = dataInput;
                            cout << "\nEmailID of UID " << UIDinput << " changed.";
                        }
                        break;
                        case 4: //change Date_Birth
                        {
                            cout << "\nCurrent Date_Birth:" << bike[indexTemp].Date_Birth;
                            cout << "\nEnter new Date_Birth_";
                            fflush(stdin);
                            cin >> dataInput;
                            bike[indexTemp].Date_Birth = dataInput;
                            cout << "\nDate_Birth of UID " << UIDinput << " changed.";
                        }
                        break;
                        case 5: //change Date_joining
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
                        cout << "\n2. MobNo";
                        cout << "\n3. EmailID";
                        cout << "\n4. Date_Birth";
                        cout << "\n5. Date_Joining";
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
                            cin >> dataInput;
                            taxi[indexTemp].Name = dataInput;
                            cout << "\nName of UID " << UIDinput << " changed.";
                        }
                        break;
                        case 2: //change MobNo
                        {
                            cout << "\nCurrent MobNo:" << taxi[indexTemp].MobNo;
                            cout << "\nEnter new MobNo_";
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
                            cin >> dataInput;
                            taxi[indexTemp].EmailID = dataInput;
                            cout << "\nEmailID of UID " << UIDinput << " changed.";
                        }
                        break;
                        case 4: //change Date_Birth
                        {
                            cout << "\nCurrent Date_Birth:" << taxi[indexTemp].Date_Birth;
                            cout << "\nEnter new Date_Birth_";
                            fflush(stdin);
                            cin >> dataInput;
                            taxi[indexTemp].Date_Birth = dataInput;
                            cout << "\nDate_Birth of UID " << UIDinput << " changed.";
                        }
                        break;
                        case 5: //change Date_joining
                        {
                            cout << "\nCurrent Date_Joining:" << taxi[indexTemp].Date_Joining;
                            cout << "\nEnter new Date_Joining_";
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

void BookMyRide::viewStaff()
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
int main()
{
    // currentUID, UserMode, UserIndex and ARRAY userIndexArray available if needed

    BookMyRide BMRobj;
    BMRobj.screenReset();
    BMRobj.import();
    int choice = 0;
    while (choice != -1)
    {
        cout << "\nMain Menu";
        cout << "\n1.  Use for Bike booking & related";
        cout << "\n2.  Use for Taxi booking & related";
        cout << "\n3.  Login as Staff";
        cout << "\n4.  Login as Admin";
        cout << "\n-1. QUIT PROGRAM!";
        cout << "\nEnter your Choice_";
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
                //Show your creativity here
            }
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
            if (BMRobj.authenticate(userMode))
            {
                //Show your creativity here
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
            if (BMRobj.authenticate(userMode))
            {
                //Show your creativity here
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
    BMRobj.backup();
    cout << "\n\\END OF PROGRAM.";
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
