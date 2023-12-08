#include <iostream> //for input output
#include <fstream>  //for file handling
#include <cstdlib>  //memory allocation related
#include <string>   //for string related operations
#include <time.h>   //for time and date functions
#include <conio.h>  //for theme features
#include <math.h>   //for math operations
#include <thread>   //for wait() method
#include <chrono>   //for wait() method
using namespace std;

// defining sleep command based on platform
#if defined(_WIN32) || defined(_WIN64)
#define SLEEP_COMMAND "ping -n 2 127.0.0.1 > nul" // for Windows systems
#else
#define SLEEP_COMMAND "sleep 1" // For Unix-like systems
#endif

// Max prespecified Values
const int maxAdminCount = 1;    // max number of admins
const int maxStaffCount = 3;    // max number of staff
const int maxUserCount = 5;     // max number of users
const int maxVehicleCount = 10; // max number of vehicles
const int maxLocCount = 20;     // max number of locations
const int maxHelpCount = 10;    // max number of help requests

const int bikeMileage = 40; // mileage of bike in km per litre
const int taxiMileage = 60; // mileage of taxi in km per litre

// User(Bike) struct
struct UserBike
{
    int UID;
    string Name;
    string password;
    string MobNo;

    int locNo1, locNo2;

    int isAllotted;
    int BikeUID;
} userBike[maxUserCount];
int userBikeCount;

// User(Taxi) struct
struct UserTaxi
{
    int UID;
    string Name; // name of Driver
    string password;
    string MobNo;

    int locNo1, locNo2;

    int isAllotted;
    int TaxiUID;
} userTaxi[maxUserCount];
int userTaxiCount;

// Bike struct
struct Bike
{
    int isAvail;
    int userNo;

    int UID;
    string Name; // name of Driver
    string MobNo;
    // string EmailID;
    string Date_Joining;
} bike[maxVehicleCount];
int bikeCount;

// Taxi struct
struct Taxi
{
    int isAvail;
    int userNo;

    int UID;
    string Name;
    string MobNo;
    string Date_Joining;
} taxi[maxVehicleCount];
int taxiCount;

// Staff struct
struct Staff
{
    int UID;
    string Name;
    string password;
    string MobNo;
} staff[maxStaffCount];
int staffCount;

// Admin struct
struct Admin
{
    int UID;
    string Name;
    string password;
    string OrgName;
    string OrgAdrs;
    string MobNo;
} admin[maxAdminCount];
int adminCount;

// Help Request struct
struct Help
{
    int UID;
    int userMode;
    int userUID;
    string comment;
} help[maxHelpCount];
int helpCount;

// Location struct
struct Location
{
    string locName;
    int UID;
    long locX; // x coordinate of location
    long locY; // y coordinate of location
} location[maxLocCount];
int locCount;

// These variables are used for Identification and Authentication
string userModeNames[5] = {"Logged Out(Safe)", "User (Bike)", "User (Taxi)", "Staff", "Admin"};
int currentNo = 0;  // stores current user serial No, zero by default
int currentUID = 0; // stores UID of current user, zero by default
int userMode = 0;   // stores user mode number, zero by default, refer to list below for details:
                    /*
                        indicates the mode user is in
                       -1: Logged out (UNSAFE)
                        0: Logged out (SAFE)
                        1: Logged in (User_Bike)
                        2: Logged in (User_Taxi)
                        3: Logged in (Staff)
                        4: Logged in (Admin)
                    */

// Function to import all data from text files
void import()
{
    // importing from UserBike.txt
    ifstream file1("UserBike.txt", ios::binary);
    if (!file1)
    {
        printf("\nBike Users Database Not Found!");
        ofstream createFile("UserBike.txt");
        printf("\nNew Bike Users Database has been created.");
    }
    file1.read(reinterpret_cast<char *>(&userBike[0]), sizeof(struct UserBike) * maxUserCount);
    userBikeCount = file1.gcount() / sizeof(struct UserBike);
    printf("\nBike Users Database imported successfully.");
    file1.close();

    // importing from UserTaxi.txt
    ifstream file2("UserTaxi.txt", ios::binary);
    if (!file2)
    {
        printf("\nTaxi Users Database Not Found!");
        ofstream createFile("UserTaxi.txt");
        printf("\nNew Taxi Users Database has been created.");
    }
    file2.read(reinterpret_cast<char *>(&userTaxi[0]), sizeof(struct UserTaxi) * maxUserCount);
    userTaxiCount = file2.gcount() / sizeof(struct UserTaxi);
    printf("\nTaxi Users Database imported successfully.");
    file2.close();

    // importing from Bike Database
    ifstream file3("Bike.txt", ios::binary);
    if (!file3)
    {
        printf("\nBike Database Not Found!");
        ofstream createFile("Bike.txt");
        printf("\nNew Bike Database has been created.");
    }
    file3.read(reinterpret_cast<char *>(&bike[0]), sizeof(struct Bike) * maxVehicleCount);
    bikeCount = file3.gcount() / sizeof(struct Bike);
    printf("\nBike Database imported successfully.");
    file3.close();

    // importing from Taxi Database
    ifstream file4("Taxi.txt", ios::binary);
    if (!file4)
    {
        printf("\nTaxi Database Not Found!");
        ofstream createFile("Taxi.txt");
        printf("\nNew Taxi Database has been created.");
    }
    file4.read(reinterpret_cast<char *>(&taxi[0]), sizeof(struct Taxi) * maxVehicleCount);
    taxiCount = file4.gcount() / sizeof(struct Taxi);
    printf("\nTaxi Database imported successfully.");
    file4.close();

    // importing from Staff Database
    ifstream file5("Staff.txt", ios::binary);
    if (!file5)
    {
        printf("\nStaff Database Not Found!");
        ofstream createFile("Staff.txt");
        printf("\nNew Staff Database has been created.");
    }
    file5.read(reinterpret_cast<char *>(&staff[0]), sizeof(struct Staff) * maxStaffCount);
    staffCount = file5.gcount() / sizeof(struct Staff);
    printf("\nStaff Database imported successfully.");
    file5.close();

    // importing from Admin Database
    ifstream file6("Admin.txt", ios::binary);
    if (!file6)
    {
        printf("\nAdmin Database Not Found!");
        ofstream createFile("Admin.txt");
        printf("\nNew Admin Database has been created.");
    }
    file6.read(reinterpret_cast<char *>(&admin[0]), sizeof(struct Admin) * maxAdminCount);
    adminCount = file6.gcount() / sizeof(struct Admin);
    printf("\nAdmin Database imported successfully.");
    file6.close();

    // importing from Help Database
    ifstream file7("Help.txt", ios::binary);
    if (!file7)
    {
        printf("\nHelp Database Not Found!");
        ofstream createFile("Help.txt");
        printf("\nNew Help Database has been created.");
    }
    file7.read(reinterpret_cast<char *>(&help[0]), sizeof(struct Help) * maxHelpCount);
    helpCount = file7.gcount() / sizeof(struct Help);
    printf("\nHelp Database imported successfully.");
    file7.close();

    // importing from Location Database
    ifstream file8("Location.txt", ios::binary);
    if (!file8)
    {
        printf("\nLocation Database Not Found!");
        ofstream createFile("Location.txt");
        printf("\nNew Location Database has been created.");
    }
    file8.read(reinterpret_cast<char *>(&location[0]), sizeof(struct Location) * maxLocCount);
    locCount = file8.gcount() / sizeof(struct Location);
    printf("\nLocation Database imported successfully.");
    file8.close();
}

// Function to export all data to text files
void backup()
{
    // updating UserBike.txt
    ofstream file1("UserBike.txt", ios::binary);
    if (!file1)
    {
        printf("/nUnable to locate UserBike.txt!");
        exit(1);
    }
    file1.write(reinterpret_cast<char *>(&userBike[0]), sizeof(struct UserBike) * userBikeCount);
    printf("\nBike Users Database updated successfully.");
    file1.close();

    // updating UserTaxi.txt
    ofstream file2("UserTaxi.txt", ios::binary);
    if (!file2)
    {
        printf("/nUnable to locate UserTaxi.txt!");
        exit(1);
    }
    file2.write(reinterpret_cast<char *>(&userTaxi[0]), sizeof(struct UserTaxi) * userTaxiCount);
    printf("\nTaxi Users Database updated successfully.");
    file2.close();

    // updating Bike.txt
    ofstream file3("Bike.txt", ios::binary);
    if (!file3)
    {
        printf("/nUnable to locate Bike.txt!");
        exit(1);
    }
    file3.write(reinterpret_cast<char *>(&bike[0]), sizeof(struct Bike) * bikeCount);
    printf("\nBike Database updated successfully.");
    file3.close();

    // updating Taxi.txt
    ofstream file4("Taxi.txt", ios::binary);
    if (!file4)
    {
        printf("/nUnable to locate Taxi.txt!");
        exit(1);
    }
    file4.write(reinterpret_cast<char *>(&taxi[0]), sizeof(struct Taxi) * taxiCount);
    printf("\nTaxi Database updated successfully.");
    file4.close();

    // updating Staff.txt
    ofstream file5("Staff.txt", ios::binary);
    if (!file5)
    {
        printf("/nUnable to locate Staff.txt!");
        exit(1);
    }
    file5.write(reinterpret_cast<char *>(&staff[0]), sizeof(struct Staff) * staffCount);
    printf("\nStaff Database updated successfully.");
    file5.close();

    // updating Admin.txt
    ofstream file6("Admin.txt", ios::binary);
    if (!file6)
    {
        printf("/nUnable to locate Admin.txt!");
        exit(1);
    }
    file6.write(reinterpret_cast<char *>(&admin[0]), sizeof(struct Admin) * adminCount);
    printf("\nAdmin Database updated successfully.");
    file6.close();

    // updating Help.txt
    ofstream file7("Help.txt", ios::binary);
    if (!file7)
    {
        printf("/nUnable to locate Help.txt!");
        exit(1);
    }
    file7.write(reinterpret_cast<char *>(&help[0]), sizeof(struct Help) * helpCount);
    printf("\nHelp Database updated successfully.");
    file7.close();

    // updating Location.txt
    ofstream file8("Location.txt", ios::binary);
    if (!file8)
    {
        printf("/nUnable to locate Location.txt!");
        exit(1);
    }
    file8.write(reinterpret_cast<char *>(&location[0]), sizeof(struct Location) * locCount);
    printf("\nLocation Database updated successfully.");
    file8.close();
}

// Class to provides all the required utility functions
class Support
{
public:
    // Function to change theme of the Command Prompt
    void setTheme()
    {
        int choice = -1;
        cout << "\nThemes Available:";
        cout << "\n0. Default";
        cout << "\n1. Ocean";
        cout << "\n2. Forest";
        cout << "\n3. Desert";
        cout << "\nEnter your choice_";
        fflush(stdin);
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
        } // SWITCH CLOSED
    }

    // Function to wait for a given number of seconds
    void wait(int noSec)
    {
        for (int i = 0; i < noSec; ++i)
        {
            cout << ".";
            std::cout.flush();          // Ensure the dot is immediately printed
            std::system(SLEEP_COMMAND); // Sleep for 1 second, platform-specifi
        }
    }

    // Function to hold the program until user enters a character
    void holdByInput()
    {
        char holder;
        cout << "\nEnter any character to continue_";
        fflush(stdin);
        cin >> holder;
    }

    // Function to reset the screen (Header)
    void screenReset()
    {
        system("cls");
        cout << "\n---------------------------------------------------------";
        time_t mytime;
        mytime = time(NULL);
        printf(ctime(&mytime));
        cout << "\n-------------------------[ " << admin[0].OrgName << " ]---------------------------";
        cout << "\nUSERMODE : " << userModeNames[userMode] << "\t\t\t\t";
        switch (userMode)
        {
        case 1: // userBike
            cout << userBike[currentNo - 1].Name << " (" << userBike[currentNo - 1].UID << ")";
            break;
        case 2: // userTaxi
            cout << userTaxi[currentNo - 1].Name << " (" << userTaxi[currentNo - 1].UID << ")";
            break;
        case 3: // staff
            cout << staff[currentNo - 1].Name << " (" << staff[currentNo - 1].UID << ")";
            break;
        case 4: // admin
            cout << admin[currentNo - 1].Name << " (" << admin[currentNo - 1].UID << ")";
            break;
        default:
            cout << "-";
            break;
        }
        printf("\n----------------------------------------------------------------------------------");
    }

    // Function to authenticate user based on userMode
    bool authenticate(int userModeIn)
    {
        screenReset();
        int UIDin;
        string PWDin;
        int choice = -1, found = 0; // found used to check if user found or not
        switch (userModeIn)
        {
        case -1: // unsafe
        {
            cout << "\nUnauthorised access detected!";
        }
        break;
        case 1: // UserBike
        {
            cout << "\nUser(Bike) Log In/New User";
            cout << "\n\t0. GO BACK";
            cout << "\n\t1. Log In";
            cout << "\n\t2. New User";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;
            switch (choice)
            {
            case 0:
            {
                cout << "\nGoing back...";
                wait(1);
            }
            break;
            case 1: // log in as user(bike)
            {
                // authenticating with the records
                if (userBikeCount > 0)
                {
                    cout << "\nUser Bike Authentication";
                    cout << "\n\tEnter UID: ";
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
                    cin >> PWDin;

                    for (int a = 1; a <= userBikeCount; a++)
                    {
                        if (userBike[a - 1].UID == UIDin && userBike[a - 1].password == PWDin)
                        {
                            found = 1;
                            currentNo = a;
                            int currentUID = userBike[a - 1].UID;
                            cout << "\nAuthenticated as user(Bike).\nWelcome " << userBike[a - 1].Name;
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
            case 2: // new User
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

                    userBike[userBikeCount].locNo1 = 0;
                    userBike[userBikeCount].locNo2 = 0;

                    userBike[userBikeCount].isAllotted = 0;
                    userBike[userBikeCount].BikeUID = 0;

                    // Program Snippet to allot UID to new User
                    if (userBikeCount == 0)
                    {
                        userBike[userBikeCount].UID = 1;
                    }
                    else
                        for (int a = 1; a <= maxUserCount; a++)
                        {
                            bool flag = false;
                            for (int b = 0; b < userBikeCount; b++)
                            {
                                if (a != userBike[b].UID)
                                {
                                    flag = true;
                                    userBike[userBikeCount].UID = a;
                                    break;
                                }
                            }
                            if (flag)
                            {
                                break;
                            }
                        }
                    cout << "\nUID allotted: " << userBike[userBikeCount].UID;

                    cout << "\nNew User Added";
                    userBikeCount++;
                    userMode = 1;
                    currentNo = userBikeCount;
                    currentUID = userBike[userBikeCount - 1].UID;
                    holdByInput();
                    return true;
                } // if there is still space, closed
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
        case 2: // UserTaxi
        {
            cout << "\nUser(Taxi) Log In/New User";
            cout << "\n\0. GO BACK";
            cout << "\n\t1. Log In";
            cout << "\n\t2. New User";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;
            switch (choice)
            {
            case 0:
            {
                cout << "\nGoing back...";
                wait(1);
            }
            break;
            case 1: // log in as user(Taxi)
            {
                // authenticating with the records
                if (userTaxiCount > 0)
                {
                    cout << "\nUser Taxi Authentication";
                    cout << "\n\tEnter UID: ";
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
                    cin >> PWDin;

                    for (int a = 1; a <= userTaxiCount; a++)
                    {
                        if (userTaxi[a - 1].UID == UIDin && userTaxi[a - 1].password == PWDin)
                        {
                            found = 1;
                            currentNo = a;
                            int currentUID = userTaxi[a - 1].UID;
                            cout << "\nAuthenticated as user(Taxi).\nWelcome " << userTaxi[a - 1].Name << "!";
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
            case 2: // new User (Taxi)
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

                    userTaxi[userTaxiCount].locNo1 = 0;
                    userTaxi[userTaxiCount].locNo2 = 0;

                    userTaxi[userTaxiCount].isAllotted = 0;
                    userTaxi[userTaxiCount].TaxiUID = 0;

                    // Program Snippet to allot UID to new User
                    if (userTaxiCount == 0)
                    {
                        userBike[userTaxiCount].UID = 1;
                    }
                    else
                        for (int a = 1; a <= maxUserCount; a++)
                        {
                            bool flag = false;
                            for (int b = 0; b < userTaxiCount; b++)
                            {
                                if (a != userTaxi[b].UID)
                                {
                                    flag = true;
                                    userTaxi[userTaxiCount].UID = a;
                                    break;
                                }
                            }
                            if (flag)
                            {
                                break;
                            }
                        }
                    cout << "\nUID allotted: " << userTaxi[userTaxiCount].UID;

                    cout << "\nNew User Added";
                    userTaxiCount++;
                    currentUID = userTaxi[userTaxiCount - 1].UID;
                    userMode = 2;
                    currentNo = userTaxiCount;
                    holdByInput();
                    return true;
                } // if there is still space, closed
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
        case 3: // Staff
        {
            cout << "\nStaff Log In";
            cout << "\n\t0. GO BACK";
            cout << "\n\t1. Log In";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;
            switch (choice)
            {
            case 0:
            {
                cout << "\nGoing back";
                wait(1);
            }
            break;
            case 1: // log in as staff
            {
                // authenticating with the records
                if (staffCount > 0)
                {
                    cout << "\nStaff Authentication:";
                    cout << "\n\tEnter UID: ";
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
                    cin >> PWDin;

                    for (int a = 1; a <= staffCount; a++)
                    {
                        if (staff[a - 1].UID == UIDin && staff[a - 1].password == PWDin)
                        {
                            found = 1;
                            userMode = 3;
                            currentNo = a;
                            int currentUID = staff[a - 1].UID;
                            cout << "\nAuthenticated as staff.\nWelcome " << staff[a - 1].Name << "!";
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
        case 4: // Admin
        {
            cout << "\nAdmin Log In";
            cout << "\n\t0. GO BACK";
            cout << "\n\t1. Log In";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;
            switch (choice)
            {
            case 0:
            {
                cout << "\nGoing back";
                wait(1);
            }
            break;
            case 1: // log in as admin
            {
                // authenticating with the records
                if (adminCount > 0)
                {
                    cout << "\nadmin Authentication:";
                    cout << "\n\tEnter UID: ";
                    fflush(stdin);
                    cin >> UIDin;
                    cout << "\n\t Enter password: ";
                    fflush(stdin);
                    cin >> PWDin;

                    for (int a = 1; a <= adminCount; a++)
                    {
                        if (admin[a - 1].UID == UIDin && admin[a - 1].password == PWDin)
                        {
                            found = 1;
                            userMode = 4;
                            currentNo = a;
                            int currentUID = admin[a - 1].UID;
                            cout << "\nAuthenticated as admin.\nWelcome " << admin[a - 1].Name << "!";
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
        return false;
    }
};

/*

    Keep in mind follwing methods and variables as you proceed:
    int maxAdminCount;
    int adminCount;
    int maxStaffCount;
    int staffCount;
    int maxUserCount;
    int userBikeCount;
    int userTaxiCount;
    int maxVehicleCount;
    int BikeCount;
    int TaxiCount;
    const int maxLocCount;
    int locCount;
    int maxHelpCount;
    int helpCount;

    struct admin[maxAdminCount];
    struct staff[maxStaffCount];
    struct userBike[maxUserCount];
    struct userTaxi[maxUserCount];
    struct bike[maxVehicleCount];
    struct taxi[maxVehicleCount];
    struct location[maxLocCount];
    struct help[maxHelpCount];

*/

// Main Class
class BookMyRide : public Support
{
public:
    // Function to tick off (mark completed) a booking
    void tickOff()
    {
        // given three chances to enter password
        if (userMode == 3) // STAFF ACCESS
        {
            int choice = -1;
            cout << "\nWhich type of booking to tick off?";
            cout << "\n0. GO BACK";
            cout << "\n1. Bike";
            cout << "\n2. Taxi";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;
            switch (choice)
            {
            case 1: // bike
            {
                if (userBikeCount > 0)
                {
                    int UIDin, f = 0;
                    int tempNo;
                    cout << "\nEnter the UID of the user_";
                    fflush(stdin);
                    cin >> UIDin;
                    // looking for user serial no based on UID input
                    for (int a = 1; a <= userBikeCount; a++)
                    {
                        if (userBike[a - 1].UID == UIDin)
                        {
                            tempNo = a;
                            f = 1;
                            break;
                        }
                    }
                    // now, clearing the booking record of that user
                    if (f == 1)
                    {
                        if (userBike[tempNo - 1].isAllotted)
                        {
                            cout << "\nClearing the booking record...";

                            userBike[tempNo - 1].locNo1 = 0;
                            userBike[tempNo - 1].locNo2 = 0;

                            userBike[tempNo - 1].isAllotted = 0;

                            // for removing  bike booking status from  bike struct
                            for (int a = 1; a <= bikeCount; a++)
                            {
                                if (userBike[tempNo - 1].BikeUID == bike[a - 1].UID)
                                {
                                    bike[a - 1].isAvail = 1;
                                    bike[a - 1].userNo = 0;
                                    userBike[tempNo - 1].BikeUID = 0;
                                    cout << "\nBooking Removed.";
                                    wait(1);
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
            case 2: // taxi
            {
                if (userTaxiCount > 0)
                {
                    int UIDin, f = 0;
                    int tempNo;
                    cout << "\nEnter the UID of the user_";
                    fflush(stdin);
                    cin >> UIDin;
                    for (int a = 1; a <= userTaxiCount; a++)
                    {
                        if (userTaxi[a - 1].UID == UIDin)
                        {
                            tempNo = a;
                            f = 1;
                            break;
                        }
                    }
                    if (f == 1)
                    {
                        if (userTaxi[tempNo - 1].isAllotted)
                        {
                            cout << "\nClearing the booking record...";

                            userTaxi[tempNo - 1].locNo1 = 0;
                            userTaxi[tempNo - 1].locNo2 = 0;

                            userTaxi[tempNo - 1].isAllotted = 0;

                            // for removing  taxi booking status from  taxi struct
                            for (int a = 1; a <= taxiCount; a++)
                            {
                                if (userTaxi[tempNo - 1].TaxiUID == taxi[a - 1].UID)
                                {
                                    taxi[a - 1].isAvail = 1;
                                    taxi[a - 1].userNo = 0;
                                    userTaxi[tempNo - 1].TaxiUID = 0;
                                    cout << "\nBooking Removed.";
                                    wait(1);
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
            case 0:
            {
                cout << "\nGoing back.";
            }
            break;
            default:
            {
                cout << "\nInvalid choice entered!";
            }
            } // SWITCH CLOSED
        }
        else
        {
            cout << "\nUnauthorised Access Detected!";
            userMode = -1;
        }
    }

    // Function to book a bike
    void bookBike()
    {
        if (userMode == 1) // USERBIKE ACCESS
        {
            int bikeAvailNo = isAvailBike();
            if (bikeAvailNo != 0)
            {
                if (locCount >= 2)
                {
                    if (userBike[currentNo - 1].isAllotted == 0)
                    {
                        cout << "\nHere are the list of locations:";
                        showLocations();

                        int loc1, loc2; // stores first UIDs, then serial nos of locations
                        int bikeNo;
                        float dist;

                        cout << "\nFrom (Enter Serial No)_";
                        fflush(stdin);
                        cin >> loc1;
                        cout << "\nTo (Enter Serial No)_";
                        fflush(stdin);
                        cin >> loc2;

                        if (loc1 <= locCount && loc2 <= locCount)
                        {
                            userBike[currentNo - 1].BikeUID = bike[bikeAvailNo - 1].UID;
                            bikeNo = bikeAvailNo;
                            userBike[currentNo - 1].locNo1 = loc1;
                            userBike[currentNo - 1].locNo2 = loc2;
                            dist = calculateDistance(loc1, loc2);

                            bike[bikeNo - 1].isAvail = 0;
                            bike[bikeNo - 1].userNo = currentNo;

                            cout << "\nBooking Details:";
                            cout << "\nFROM: " << location[loc1 - 1].locName << " (" << location[loc1 - 1].UID << ")";
                            cout << "\nTO: " << location[loc2 - 1].locName << " (" << location[loc1 - 1].UID << ")";
                            cout << "\nDistance: " << dist << " km";
                            cout << "\nExpected Time Taken: " << dist / bikeMileage << " hours";
                            cout << "\n Bike UID: " << userBike[currentNo - 1].BikeUID;
                            cout << "\n Driver Contact: \t" << bike[bikeNo - 1].Name << "\t" << bike[bikeNo - 1].MobNo;
                            userBike[currentNo].isAllotted = 1;
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
            userMode = -1;
        }
    }

    // Function to cancel a bike booking
    void cancelBike()
    {
        if (userMode == 1) // USERBIKE ACCESS
        {
            if (userBike[currentNo - 1].isAllotted)
            {
                cout << "\nClearing the booking record...";

                userBike[currentNo - 1].locNo1 = 0;
                userBike[currentNo - 1].locNo2 = 0;

                userBike[currentNo].isAllotted = 0;

                // for removing bike booking status from bike struct
                for (int a = 1; a <= bikeCount; a++)
                {
                    if (userBike[currentNo - 1].BikeUID == bike[a - 1].UID)
                    {
                        bike[a - 1].isAvail = 1;
                        bike[a - 1].userNo = 0;
                        userBike[currentNo - 1].BikeUID = 0;
                        cout << "\nBooking Removed.";
                        wait(1);
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
            // cout << "\nYou aren't allowed to perform this change.";
            userMode = -1;
        }
    }

    // Function to book a taxi
    void bookTaxi()
    {
        if (userMode == 2) // USERTAXI ACCESS
        {
            int taxiAvailNo = isAvailTaxi();
            if (taxiAvailNo != 0)
            {
                if (locCount >= 2)
                {
                    if (userTaxi[currentNo - 1].isAllotted == 0)
                    {
                        cout << "\nHere are the list of locations:";
                        showLocations();

                        int loc1, loc2; // stores first UIDs, then serial nos of locations
                        int taxiNo;
                        float dist;

                        cout << "\nFrom (Enter Serial No)_";
                        fflush(stdin);
                        cin >> loc1;
                        cout << "\nTo (Enter Serial No)_";
                        fflush(stdin);
                        cin >> loc2;

                        if (loc1 <= locCount && loc2 <= locCount)
                        {
                            userTaxi[currentNo - 1].TaxiUID = taxi[taxiAvailNo - 1].UID;
                            taxiNo = taxiAvailNo;
                            userTaxi[currentNo - 1].locNo1 = loc1;
                            userTaxi[currentNo - 1].locNo2 = loc2;
                            dist = calculateDistance(loc1, loc2);

                            taxi[taxiNo - 1].isAvail = 0;
                            taxi[taxiNo - 1].userNo = currentNo;

                            cout << "\nBooking Details:";
                            cout << "\nFROM: " << location[loc1 - 1].locName << " (" << location[loc1 - 1].UID << ")";
                            cout << "\nTO: " << location[loc2 - 1].locName << " (" << location[loc1 - 1].UID << ")";
                            cout << "\nDistance: " << dist << " km";
                            cout << "\nExpected Time Taken: " << dist / taxiMileage << " hours";
                            cout << "\n Taxi UID: " << userTaxi[currentNo - 1].TaxiUID;
                            cout << "\n Driver Contact: \t" << taxi[taxiNo - 1].Name << "\t" << taxi[taxiNo - 1].MobNo;
                            userTaxi[currentNo].isAllotted = 1;
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
                cout << "\nNo taxis available.";
            }
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to cancel a taxi booking
    void cancelTaxi()
    {
        if (userMode == 2) // USERTAXI ACCESS
        {
            if (userTaxi[currentNo - 1].isAllotted)
            {
                cout << "\nClearing the booking record...";

                userTaxi[currentNo - 1].locNo1 = 0;
                userTaxi[currentNo - 1].locNo2 = 0;

                userTaxi[currentNo].isAllotted = 0;

                // for removing taxi booking status from taxi struct
                for (int a = 1; a <= taxiCount; a++)
                {
                    if (userTaxi[currentNo - 1].TaxiUID == taxi[a - 1].UID)
                    {
                        taxi[a - 1].isAvail = 1;
                        taxi[a - 1].userNo = 0;
                        userTaxi[currentNo - 1].TaxiUID = 0;
                        cout << "\nBooking Removed.";
                        wait(1);
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

    // Function to show the booking details of the current user
    void showMyBooking()
    {
        if (userMode == 1) // USERBIKE ACCESS
        {
            if (userBike[currentNo - 1].isAllotted == 1)
            {
                int a, f = 0;
                // checking if the bike is still available
                for (a = 1; a <= bikeCount; a++)
                {
                    if (userBike[currentNo - 1].BikeUID == bike[a - 1].UID)
                    {
                        f = 1;
                        break;
                    }
                }

                if (f == 1)
                {
                    cout << "\nBike booking details";

                    cout << "\nFrom " << location[userBike[currentNo - 1].locNo1 - 1].locName;
                    cout << "To " << location[userBike[currentNo - 1].locNo2 - 1].locName;
                    cout << "\nBike Contact: " << bike[a - 1].Name << " (" << bike[a - 1].MobNo << ")";

                    float dist = calculateDistance(userBike[currentNo - 1].locNo1, userBike[currentNo - 1].locNo2);
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
        else if (userMode == 2) // USERTAXI ACCESS
        {
            if (userTaxi[currentNo - 1].isAllotted == 1)
            {
                int a, f = 0;
                // checking if the taxi is still available
                for (a = 1; a <= taxiCount; a++)
                {
                    if (userTaxi[currentNo - 1].TaxiUID == taxi[a - 1].UID)
                    {
                        f = 1;
                        break;
                    }
                }

                if (f == 1)
                {
                    cout << "\nTaxi booking details";

                    cout << "\nFrom " << location[userTaxi[currentNo - 1].locNo1 - 1].locName;
                    cout << "To " << location[userTaxi[currentNo - 1].locNo2 - 1].locName;
                    cout << "\nTaxi Contact: " << taxi[a - 1].Name << " (" << taxi[a - 1].MobNo << ")";

                    float dist = calculateDistance(userTaxi[currentNo - 1].locNo1, userTaxi[currentNo - 1].locNo2);
                    cout << "\nDistance: " << dist << " km";
                    cout << "\nExpected Time Taken: " << dist / taxiMileage << " hours";
                    cout << "\n-------------------------------";
                }
                else
                {
                    cout << "\nTaxi not found:-(.\nKindly book again.\nExtremely Sorry for incovenience.\nProceeding to remove booking.\n";
                    wait(1);
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
            userMode = -1;
        }
    }

    // Function to show the booking list
    void showBookingList()
    {
        int counter = 0;
        if (userMode == 3 || userMode == 4) // STAFF OR ADMIN ACCESS
        {
            // for bike
            counter = 0;
            cout << "\nBike Bookings";
            cout << "\nSerial No\tBike UID\tDriver Name\tUser No\t User Name";
            for (int a = 1; a <= bikeCount; a++)
            {
                if (bike[a - 1].isAvail == 0)
                {
                    cout << "\n"
                         << ++counter << "\t\t" << bike[a - 1].UID << "\t\t" << bike[a - 1].Name << "\t\t" << bike[a - 1].userNo << "\t\t" << userBike[bike[a - 1].userNo - 1].Name;
                }
                cout << "\n---------------------------------------------";
            }
            if (counter == 0)
                cout << "\nBike booking list empty.";

            // for taxi
            counter = 0;
            cout << "\nTaxi Bookings";
            cout << "\nSerial No\tTaxi UID\tDriver Name\tUser No\t User Name";
            for (int a = 1; a <= taxiCount; a++)
            {
                if (taxi[a - 1].isAvail == 0)
                {
                    cout << "\n"
                         << ++counter << "\t\t" << taxi[a - 1].UID << "\t\t" << taxi[a - 1].Name << "\t\t" << taxi[a - 1].userNo << "\t\t" << userTaxi[taxi[a - 1].userNo - 1].Name;
                }
            }
            cout << "\n---------------------------------------------";
            if (counter == 0)
                cout << "\nTaxi booking list empty.";
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to add a help request
    void getHelp()
    {
        if (userMode == 1) // USERBIKE ACCESS
        {
            if (helpCount < maxHelpCount)
            {
                cout << "\nAdding new help request...";

                if (helpCount == 0)
                {
                    help[helpCount].UID = 1;
                    cout << "\nUID allotted : " << help[helpCount].UID;
                }
                else
                {
                    // alloting first available UID
                    for (int a = 1; a <= maxHelpCount; a++)
                    {
                        int f = 0;
                        for (int b = 1; b <= helpCount; b++)
                        {
                            if (a == help[b - 1].UID)
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
                // Help UID Allotment Done

                helpCount++;
                help[helpCount - 1].userMode = 1;
                help[helpCount - 1].userUID = userBike[currentNo - 1].UID;
                cout << "\nEnter details in short:\n";
                fflush(stdin);
                getline(cin, help[helpCount - 1].comment);
                cout << "\nWe will contact you ASAP.";
            }
            else
            {
                cout << "\nHelp List is full.";
            }
            if (adminCount > 0)
                cout << "\nBy the way, you may contact us directly IFF URGENT.\nContact: " << admin[0].MobNo;
        }

        else if (userMode == 2) // USERTAXI ACCESS
        {
            if (helpCount < maxHelpCount)
            {
                cout << "\nAdding new help request...";

                if (helpCount == 0)
                {
                    help[helpCount].UID = 1;
                    cout << "\nUID allotted : " << help[helpCount].UID;
                }
                for (int a = 1; a <= maxHelpCount; a++)
                {
                    int f = 0;
                    for (int b = 1; b <= helpCount; b++)
                    {
                        if (a == help[b - 1].UID)
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

                helpCount++;
                help[helpCount - 1].userMode = 2;
                help[helpCount - 1].userUID = userTaxi[currentNo - 1].UID;
                cout << "\nEnter details in short:\n";
                fflush(stdin);
                getline(cin, help[helpCount - 1].comment);
                cout << "\nWe will contact you ASAP.";
            }
            else
            {
                cout << "\nHelp List is full.";
            }
            if (adminCount > 0)
                cout << "\nBy the way, you may contact us directly IFF URGENT.\nContact: " << admin[0].MobNo;
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to show list of locations
    void showLocations()
    {
        if (userMode != -1)
        {
            if (locCount > 0)
            {
                cout << "\nSerial No\tUID\tName";
                cout << "\n-------------------------------------------------------------------";
                for (int a = 1; a <= locCount; a++)
                {
                    cout << "\n"
                         << a << "\t" << location[a - 1].UID << "\t" << location[a - 1].locName;
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

    // Function to add a new location
    void addLocation()
    {
        if (userMode == 3) // STAFF ACCESS
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

                // PROGRAM FOR UID ALLOTTMENT
                if (locCount == 0)
                {
                    location[locCount].UID = 1;
                    cout << "\nUID allotted : 1";
                }
                else
                {
                    for (int a = 1; a <= maxLocCount; a++)
                    {
                        int f = 0;
                        for (int b = 1; b <= locCount; b++)
                        {
                            if (a == location[b - 1].UID)
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
            userMode = -1;
        }
    }

    // Function to edit location details
    void editLocation()
    {
        if (userMode == 3) // STAFF ACCESS
        {
            if (locCount > 0)
            {
                int UIDin;
                cout << "\nEnter UID of Location to edit_";
                fflush(stdin);
                cin >> UIDin;

                int f = 0, a = 0; // a stores the serial no of required position

                for (a = 1; a <= locCount; a++)
                {
                    if (UIDin == location[a - 1].UID)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                {
                    f = 0;
                    int choice = -1;
                    while (choice != 0)
                    {
                        cout << "\nWhich parameter do you want to edit:";
                        cout << "\n0. GO BACK";
                        cout << "\n1. Location Name";
                        cout << "\n2. X-Coordinate";
                        cout << "\n3. Y-Coordinate";
                        cout << "\nEnter your choice_";
                        fflush(stdin);
                        cin >> choice;

                        switch (choice)
                        {
                        case 1: // location name
                        {
                            cout << "\nEnter new location name_";
                            fflush(stdin);
                            getline(cin, location[a - 1].locName);
                        }
                        break;
                        case 2: // x coordinate
                        {
                            cout << "\nEnter new x-coordinate_";
                            fflush(stdin);
                            cin >> location[a - 1].locX;
                        }
                        break;
                        case 3: // y coordinate
                        {
                            cout << "\nEnter new y-coordinate_";
                            fflush(stdin);
                            cin >> location[a - 1].locY;
                        }
                        break;
                        case 0: // Go back
                        {
                            cout << "\nGoing Back.";
                        }
                        break;
                        default: // invalid choice
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
            userMode = -1;
        }
    }

    // Fuction to check if the location user wants to remove is used in any booking
    bool canRemoveLocation(int no)
    {
        for (int a = 1; a <= userBikeCount; a++)
        {
            if (userBike[a - 1].isAllotted == 1)
                if (userBike[a - 1].locNo1 == no || userBike[a - 1].locNo2 == no)
                    return false;
        }
        for (int a = 1; a <= userTaxiCount; a++)
        {
            if (userTaxi[a - 1].isAllotted == 1)
                if (userTaxi[a - 1].locNo1 == no || userTaxi[a - 1].locNo2 == no)
                    return false;
        }
        return true;
    }

    // Function to remove a location from the location struct
    void removeLocation()
    {
        if (userMode = 3) // Staff Access
        {
            int UIDin;
            cout << "\nEnter UID of Location to delete_";
            fflush(stdin);
            cin >> UIDin;

            int f = 0, a = 0; // a stores the serial no of required position

            for (a = 1; a <= locCount; a++)
            {
                if (UIDin == location[a - 1].UID)
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
                    // shift all elements (just after to-be-deleted) to left
                    for (int b = a; b < locCount; b++)
                    {
                        string tempStr;
                        int tempIn;

                        tempStr = location[a - 1].locName;
                        location[a - 1].locName = location[a].locName;
                        location[a].locName = tempStr;

                        tempIn = location[a - 1].locX;
                        location[a - 1].locX = location[a].locX;
                        location[a].locX = tempIn;

                        tempIn = location[a - 1].locY;
                        location[a - 1].locY = location[a].locY;
                        location[a].locY = tempIn;
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
            userMode = -1;
        }
    }

    // Function to edit current User details (staff and users)
    void editSelf()
    {
        if (userMode == 1) // USERBIKE ACCESS
        {
            if (userBikeCount > 0)
            {
                int UIDin = userBike[currentNo - 1].UID;

                int f = 0, a = 0;
                for (a = 1; a <= userBikeCount; a++)
                {
                    if (userBike[a - 1].UID == UIDin)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                {
                    if (a != currentNo)
                    {
                        cout << "\nDiscrepancy found in userBike.";
                        currentNo = a;
                        cout << "\nResolved.";
                    }
                    f = 0;
                    int choice = -1;
                    while (choice != 0)
                    {
                        cout << "\nWhich parameter do you want to edit:";
                        cout << "\n0. GO BACK";
                        cout << "\n1. Name";
                        cout << "\n2. Password";
                        cout << "\n3. Mobile No";
                        cout << "\nEnter your choice_";
                        fflush(stdin);
                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                        {
                            cout << "\nEnter new name_";
                            fflush(stdin);
                            getline(cin, userBike[currentNo - 1].Name);
                        }
                        break;
                        case 2:
                        {
                            cout << "\nEnter new password_";
                            fflush(stdin);
                            cin >> userBike[currentNo - 1].password;
                        }
                        break;
                        case 3:
                        {
                            cout << "\nEnter new mobile No_";
                            fflush(stdin);
                            cin >> userBike[currentNo - 1].MobNo;
                        }
                        break;
                        case 0: // Go back
                        {
                            cout << "\nAlright.";
                        }
                        break;
                        default: // invalid choice
                        {
                            cout << "\nInvalid choice entered!";
                        }
                        break;
                        } // switch closed
                    }     // while closed
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
        else if (userMode == 2) // USERTAXI ACCESS
        {
            if (userTaxiCount > 0)
            {
                int UIDin = userTaxi[currentNo - 1].UID;

                int f = 0, a = 0;
                for (a = 1; a <= userTaxiCount; a++)
                {
                    if (userTaxi[a - 1].UID == userTaxi[a - 1].UID)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                {
                    if (a != currentNo)
                    {
                        cout << "\nDiscrepancy found in userTaxi.\nResolved.";
                        currentNo = a;
                    }
                    f = 0;
                    int choice = -1;
                    while (choice != 0)
                    {
                        cout << "\nWhich parameter do you want to edit:";
                        cout << "\n1. Name";
                        cout << "\n2. Password";
                        cout << "\n3. Mobile No";
                        cout << "\n0. GO BACK";
                        cout << "\nEnter your choice_";
                        fflush(stdin);
                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                        {
                            cout << "\nEnter new name_";
                            fflush(stdin);
                            getline(cin, userTaxi[currentNo - 1].Name);
                        }
                        break;
                        case 2:
                        {
                            cout << "\nEnter new password_";
                            fflush(stdin);
                            cin >> userTaxi[currentNo - 1].password;
                        }
                        break;
                        case 3:
                        {
                            cout << "\nEnter new mobile No_";
                            fflush(stdin);
                            cin >> userTaxi[currentNo - 1].MobNo;
                        }
                        break;
                        case 0: // Go back
                        {
                            cout << "\nAlright.";
                        }
                        break;
                        default: // invalid choice
                        {
                            cout << "\nInvalid choice entered!";
                        }
                        break;
                        } // switch closed
                    }     // while closed
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
        else if (userMode == 3) // STAFF ACCESS
        {
            if (staffCount > 0)
            {
                int UIDin = staff[currentNo - 1].UID;

                int f = 0, a = 0;
                for (a = 1; a <= staffCount; a++)
                {
                    if (staff[a - 1].UID == UIDin)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                {
                    if (a != currentNo)
                    {
                        cout << "\nDiscrepancy found in staff.";
                        currentNo = a;
                        cout << "\nResolved.";
                    }
                    f = 0;
                    int choice = -1;
                    while (choice != 0)
                    {
                        cout << "\nWhich parameter do you want to edit:";
                        cout << "\n0. GO BACK";
                        cout << "\n1. Name";
                        cout << "\n2. Password";
                        cout << "\n3. Mobile No";
                        cout << "\nEnter your choice_";
                        fflush(stdin);
                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                        {
                            cout << "\nEnter new name_";
                            fflush(stdin);
                            getline(cin, staff[currentNo - 1].Name);
                        }
                        break;
                        case 2:
                        {
                            cout << "\nEnter new password_";
                            fflush(stdin);
                            cin >> staff[currentNo - 1].password;
                        }
                        break;
                        case 3:
                        {
                            cout << "\nEnter new mobile No_";
                            fflush(stdin);
                            cin >> staff[currentNo - 1].MobNo;
                        }
                        break;
                        case 0: // Go back
                        {
                            cout << "\nAlright.";
                        }
                        break;
                        default: // invalid choice
                        {
                            cout << "\nInvalid choice entered!";
                        }
                        break;
                        } // switch closed
                    }     // while closed
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
            userMode = -1;
        }
    }

    // Function to check for available bike and return its serial no (0 if none available)
    int isAvailBike()
    {
        if (userMode != -1)
        {
            if (bikeCount > 0)
            {
                for (int a = 1; a <= bikeCount; a++)
                {
                    if (bike[a - 1].isAvail == 1)
                        return a;
                }
            }
        }
        else
        {
            cout << "\nUnauthorised access detected!";
        }
        return 0;
    }

    // Function to check for available taxi and return its serial no (0 if none available)
    int isAvailTaxi()
    {
        if (userMode != -1)
        {
            if (taxiCount > 0)
            {
                for (int a = 1; a <= taxiCount; a++)
                {
                    if (taxi[a - 1].isAvail == 1)
                        return a;
                }
            }
        }
        else
        {
            cout << "\nUnauthorised access detected!";
        }
        return 0;
    }

    // Function to calculate distance between two locations (given their serial nos)
    float calculateDistance(int no1, int no2)
    {
        if (no1 <= locCount && no2 <= locCount)
        {
            int x1, y1, x2, y2;

            x1 = location[no1 - 1].locX;
            y1 = location[no1 - 1].locY;

            x2 = location[no2 - 1].locX;
            y2 = location[no2 - 1].locY;

            return sqrt(pow(x2 - x1, 2) +
                        pow(y2 - y1, 2) * 1.0);
        }
        return -1;
    }

    // Function to add a vehicle
    void addVehicle()
    {
        int choice = -1, f = 0;

        if (userMode == 3 || userMode == 4) // STAFF AND ADMIN ACCESS
        {
            cout << "Which vehicle details do you want to add-";
            cout << "\0. GO BACK";
            cout << "\n1. Bike";
            cout << "\n2. Taxi";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;

            switch (choice)
            {
            case 0: // Go back
            {
                cout << "\nGoing back...";
            }
            break;
            case 1: // Add bike
            {
                if (bikeCount < maxVehicleCount)
                {
                    f = 0; // resetting the flag

                    cout << "\nEnter Name of Driver: ";
                    fflush(stdin);
                    getline(cin, bike[bikeCount].Name);
                    cout << "\nEnter Mobile no. of Driver: ";
                    fflush(stdin);
                    cin >> bike[bikeCount].MobNo;
                    cout << "\nEnter Date of Joining: ";
                    fflush(stdin);
                    cin >> bike[bikeCount].Date_Joining;

                    // Code for UID allotment
                    if (bikeCount == 0)
                    {
                        bike[bikeCount].UID = 1;
                        cout << "\nUID allotted : 1";
                    }
                    else
                    {
                        for (int a = 1; a <= maxVehicleCount; a++)
                        {
                            int f = 0;
                            for (int b = 1; b <= bikeCount; b++)
                            {
                                if (a == bike[b - 1].UID)
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
            case 2: // Add Taxi
            {
                if (taxiCount < maxVehicleCount)
                {
                    f = 0; // resetting the flag

                    cout << "\nEnter Name of Driver: ";
                    fflush(stdin);
                    getline(cin, taxi[taxiCount].Name);
                    cout << "\nEnter Mobile no. of Driver: ";
                    fflush(stdin);
                    cin >> taxi[taxiCount].MobNo;
                    cout << "\nEnter Date of Joining: ";
                    fflush(stdin);
                    cin >> taxi[taxiCount].Date_Joining;

                    // Code for UID allotment
                    if (taxiCount < 1)
                    {
                        taxi[taxiCount].UID = 1;
                        cout << "\nUID allotted : 1";
                    }
                    else
                    {
                        for (int a = 1; a <= maxVehicleCount; a++)
                        {
                            int f = 0;
                            for (int b = 1; b <= taxiCount; b++)
                            {
                                if (a == taxi[b - 1].UID)
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

    // Function to edit a vehicle's details
    void editVehicle()
    {
        int choice = -1, choice2 = -1; // choice2 for inner switch case
        int tempNo = 0;                // for loops,to store serial no of bike/taxi which is to be edited
        int UIDinput;
        string dataInput;
        int f = 0;                          // flag to check if entered UID is found or not
        if (userMode == 3 || userMode == 4) // STAFF OR ADMIN ACCESS
        {
            cout << "Which vehicle do you want to edit-";
            cout << "\n0. GO BACK";
            cout << "\n1. Bike";
            cout << "\n2. Taxi";
            cout << "\nEnter your choice_";
            fflush(stdin);
            fflush(stdin);
            cin >> choice;

            switch (choice)
            {
            case 0: // Go back
            {
                cout << "\nGoing back...";
            }
            break;
            case 1: // Edit bike
            {
                if (bikeCount > 0)
                {
                    f = 0; // resetting the flag
                    cout << "\nEnter UID of Bike to edit_";
                    fflush(stdin);
                    cin >> UIDinput;
                    for (tempNo = 1; tempNo <= bikeCount; tempNo++)
                    {
                        if (bike[tempNo - 1].UID == UIDinput)
                        {
                            f = 1; // flag if entered UID is found
                            break;
                        }
                    }
                    if (f == 1)
                    {
                        while (choice2 != 0) // loop because user may want to edit several things at a time
                        {
                            cout << "\nWhat do you want to edit?";
                            cout << "\n0. GO BACK";
                            cout << "\n1. Name"; // name of driver not bike
                            cout << "\n2. Mobile No";
                            cout << "\n3. Date_Joining";
                            cout << "\nEnter your choice";
                            fflush(stdin);
                            cin >> choice2;
                            switch (choice2)
                            {
                            case 0: // Go back
                            {
                                cout << "\nGoing back...";
                            }
                            break;
                            case 1: // change name
                            {
                                cout << "\nCurrent Name:" << bike[tempNo - 1].Name;
                                cout << "\nEnter new Name_";
                                fflush(stdin);
                                cin >> dataInput;
                                bike[tempNo - 1].Name = dataInput;
                                cout << "\nName of UID " << UIDinput << " changed.";
                            }
                            break;
                            case 2: // change MobNo
                            {
                                cout << "\nCurrent Mobile No:" << bike[tempNo - 1].MobNo;
                                cout << "\nEnter new Mobile No_";
                                fflush(stdin);
                                cin >> dataInput;
                                bike[tempNo - 1].MobNo = dataInput;
                                cout << "\nMobile No of UID " << UIDinput << " changed.";
                            }
                            break;
                            case 3: // change Date_joining
                            {
                                cout << "\nCurrent Date_Joining:" << bike[tempNo - 1].Date_Joining;
                                cout << "\nEnter new Date_Joining_";
                                fflush(stdin);
                                cin >> dataInput;
                                bike[tempNo - 1].Date_Joining = dataInput;
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
            case 2: // Edit Taxi
            {
                if (taxiCount > 0)
                {
                    f = 0; // resetting the flag
                    cout << "\nEnter UID of taxi to edit_";
                    fflush(stdin);
                    cin >> UIDinput;
                    for (tempNo = 1; tempNo <= taxiCount; tempNo++)
                    {
                        if (taxi[tempNo - 1].UID == UIDinput)
                        {
                            f = 1; // flag if entered UID is found
                            break;
                        }
                    }
                    if (f == 1)
                    {
                        while (choice2 != 0) // loop because user may want to edit several things at a time
                        {
                            cout << "\nWhat do you want to edit?";
                            cout << "\n0. GO BACK";
                            cout << "\n1. Name"; // name of driver not taxi
                            cout << "\n2. Mobile No";
                            cout << "\n3. Date_Joining";
                            cout << "\nEnter your choice";
                            fflush(stdin);
                            cin >> choice2;
                            switch (choice2)
                            {
                            case 0: // Go back
                            {
                                cout << "\nGoing back...";
                            }
                            break;
                            case 1: // change name
                            {
                                cout << "\nCurrent Name:" << taxi[tempNo - 1].Name;
                                cout << "\nEnter new Name_";
                                fflush(stdin);
                                cin >> dataInput;
                                taxi[tempNo - 1].Name = dataInput;
                                cout << "\nName of UID " << UIDinput << " changed.";
                            }
                            break;
                            case 2: // change MobNo
                            {
                                cout << "\nCurrent Mobile No:" << taxi[tempNo - 1].MobNo;
                                cout << "\nEnter new Mobile No_";
                                fflush(stdin);
                                cin >> dataInput;
                                taxi[tempNo - 1].MobNo = dataInput;
                                cout << "\nMobNo of UID " << UIDinput << " changed.";
                            }
                            break;
                            case 3: // change Date_joining
                            {
                                cout << "\nCurrent Date_Joining:" << taxi[tempNo - 1].Date_Joining;
                                cout << "\nEnter new Date_Joining_";
                                fflush(stdin);
                                cin >> dataInput;
                                taxi[tempNo - 1].Date_Joining = dataInput;
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
            userMode = -1;
        }
    }

    // Function to check if the bike, which user wants to remove, is used in any booking
    bool canRemoveBike(int no)
    {
        for (int a = 1; a <= userBikeCount; a++)
        {
            if (userBike[a - 1].isAllotted = 1)
                if (userBike[a - 1].BikeUID == bike[no - 1].UID)
                    return false;
        }
        return true;
    }

    // Function to check if the taxi, which user wants to remove, is used in any booking
    bool canRemoveTaxi(int no)
    {
        for (int a = 1; a <= userTaxiCount; a++)
        {
            if (userTaxi[a - 1].isAllotted = 1)
                if (userTaxi[a - 1].TaxiUID == taxi[no - 1].UID)
                    return false;
        }
        return true;
    }

    // Function to remove a vehicle
    void removeVehicle()
    {
        int choice = -1;

        if (userMode == 3 || userMode == 4) // STAFF OR ADMIN ACCESS
        {
            cout << "Which vehicle details do you want to remove-";
            cout << "\n0. GO BACK";
            cout << "\n1. Bike";
            cout << "\n2. Taxi";
            cout << "\nEnter your choice_";
            fflush(stdin);
            cin >> choice;

            switch (choice)
            {
            case 0: // Go back
            {
                cout << "\nGoing back...";
            }
            break;
            case 1: // remove bike
            {

                if (bikeCount == 0)
                {
                    cout << "Bike list is empty ! Nothing to Delete !" << endl;
                }
                else
                {
                    cout << "Enter the UID of bike you want to Delete: ";
                    int tempUID, flag = 0;
                    fflush(stdin);
                    cin >> tempUID;

                    for (int i = 1; i <= bikeCount; bikeCount++)
                    {
                        if (tempUID == bike[i - 1].UID)
                        {
                            flag = i;
                            break;
                        }
                    }
                    if (flag == 0)
                    {
                        cout << "Entered UID not found !";
                    }
                    else
                    {
                        if (canRemoveBike(flag))
                        {
                            string temp;
                            int tempN;
                            for (int i = flag; i < bikeCount; i++)
                            {
                                tempN = bike[i - 1].UID;
                                bike[i - 1].UID = bike[i].UID;
                                bike[i].UID = tempN;

                                temp = bike[i - 1].Name;
                                bike[i - 1].Name = bike[i].Name;
                                bike[i].Name = temp;

                                temp = bike[i - 1].MobNo;
                                bike[i - 1].MobNo = bike[i].MobNo;
                                bike[i].MobNo = temp;

                                temp = bike[i - 1].Date_Joining;
                                bike[i - 1].Date_Joining = bike[i].Date_Joining;
                                bike[i].Date_Joining = temp;
                            }
                            bikeCount--;
                        }
                        else
                        {
                            cout << "\nCannot Delete! The Bike is currently booked.";
                        }
                    }
                }
            }

            break;
            case 2: // remove taxi
            {
                if (taxiCount == 0)
                {
                    cout << "Taxi list is empty ! Nothing to Delete !" << endl;
                }
                else
                {
                    cout << "Enter the UID of Taxi you want to Delete: ";
                    int tempUID, flag = -1;
                    fflush(stdin);
                    cin >> tempUID;

                    for (int i = 1; i <= taxiCount; taxiCount++)
                    {
                        if (tempUID == taxi[i - 1].UID)
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
                            string temp;
                            int tempN;
                            for (int i = flag; i < taxiCount; i++)
                            {
                                tempN = taxi[i - 1].UID;
                                taxi[i - 1].UID = taxi[i].UID;
                                taxi[i].UID = tempN;

                                temp = taxi[i - 1].Name;
                                taxi[i - 1].Name = taxi[i].Name;
                                taxi[i].Name = temp;

                                temp = taxi[i - 1].MobNo;
                                taxi[i - 1].MobNo = taxi[i].MobNo;
                                taxi[i].MobNo = temp;

                                temp = taxi[i - 1].Date_Joining;
                                taxi[i - 1].Date_Joining = taxi[i].Date_Joining;
                                taxi[i].Date_Joining = temp;
                            }
                            taxiCount--;
                        }
                        else
                        {
                            cout << "\nCannot Delete! The Taxi is currently booked.";
                        }
                    }
                }
            } // REMOVE TAXI SECTION CLOSED

            } // SWITCH CLOSED
        }
        else
        {
            cout << "Access not allowed !";

            userMode = -1;
        }
    }

    // Function to view list of Help Requests
    void viewHelpList()
    {
        if (userMode == 3) // STAFF ACCESS
        {
            if (helpCount > 0)
            {
                cout << "\n-------------------------------------------------------------------";
                cout << "\nHelp UID\tUser Type\tUser UID";
                for (int a = 1; a <= helpCount; a++)
                {

                    cout << "\n\n"
                         << help[a - 1].UID << "\t" << help[a - 1].userMode << "\t\t";

                    if (help[a - 1].userMode = 0)
                        for (int b = 1; b <= userBikeCount; b++)
                        {
                            if (help[a - 1].userUID == userBike[b - 1].UID)
                            {
                                cout << userBike[b - 1].MobNo;
                                break;
                            }
                        }
                    else
                        for (int b = 1; b <= userTaxiCount; b++)
                        {
                            if (help[a - 1].userUID == userTaxi[b - 1].UID)
                            {
                                cout << userTaxi[b - 1].MobNo;
                                break;
                            }
                        }

                    cout << "\nComment:" << help[a - 1].comment;
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
            userMode = -1;
        }
    }

    // View List of Vehicles
    void showVehicles()
    {
        int tempNo = 0;
        if (userMode == 3 || userMode == 4) // STAFF OR ADMIN ACCESS
        {
            int choice = -1;
            while (choice != 0)
            {
                screenReset();
                cout << "\nDisplay Vehicle Details Menu:";
                cout << "\n0. GO BACK";
                cout << "\n1. Bike List";
                cout << "\n2. Taxi List";
                cout << "\nEnter your choice_";
                fflush(stdin);
                cin >> choice;
                switch (choice)
                {
                case 1: // View Bike List
                {
                    if (bikeCount > 0)
                    {
                        cout << "\nSr.No\tUID\tDriver\tContact";
                        for (int a = 1; a <= bikeCount; a++)
                        {
                            cout << "\n"
                                 << a << "\t" << bike[a - 1].UID << "\t" << bike[a - 1].Name << "\t" << bike[a - 1].MobNo;
                        }
                    }
                    else
                    {
                        cout << "\nBike List is empty!";
                    }
                    holdByInput();
                }
                break;
                case 2: // View Taxi List
                {
                    if (taxiCount > 0)
                    {
                        cout << "\nSr.No\tUID\tDriver\tContact";
                        for (int a = 1; a <= taxiCount; a++)
                        {
                            cout << "\n"
                                 << a << "\t" << taxi[a - 1].UID << "\t" << taxi[a - 1].Name << "\t" << taxi[a - 1].MobNo;
                        }
                    }
                    else
                    {
                        cout << "\nTaxi List is empty!";
                    }
                    holdByInput();
                }
                break;
                case 0:
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
                } // SWITCH CLOSED
            }
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to mark a Help Request as Resolved
    void resolveHelp()
    {
        if (userMode == 3) // STAFF ACCESS
        {
            if (helpCount > 0)
            {
                int UIDin = -1;
                while (UIDin != 0)
                {
                    viewHelpList();
                    cout << "\nEnter Help UID to resolve(0 to GO BACK)_";
                    fflush(stdin);
                    cin >> UIDin;
                    if (UIDin == 0)
                        break;

                    int f = -1;
                    for (int a = 1; a <= helpCount; a++)
                    {
                        if (UIDin == help[a - 1].UID)
                        {
                            f = a;
                            break;
                        }
                    }
                    if (f > 0)
                    {
                        cout << "\nHelp UID\tUser Type\tUser Contact)\n";
                        cout << help[f - 1].UID << "\t" << help[f - 1].userMode << "\t\t";

                        if (help[f].userMode = 1) // userBike
                            for (int a = 1; a <= userBikeCount; a++)
                            {
                                if (help[f - 1].userUID == userBike[a - 1].UID)
                                {
                                    cout << userBike[a - 1].MobNo;
                                    break;
                                }
                            }
                        else // userTaxi
                            for (int a = 1; a <= userTaxiCount; a++)
                            {
                                if (help[f - 1].userUID == userTaxi[a - 1].UID)
                                {
                                    cout << userTaxi[a - 1].MobNo;
                                    break;
                                }
                            }

                        cout << "\nComment:" << help[f - 1].comment;

                        int choice2 = -1;
                        cout << "\nPress 1 to confirm, 0 to CANCEL_";
                        fflush(stdin);
                        cin >> choice2;
                        if (choice2 == 1) // delete the help record (confirmed)
                        {
                            for (int b = f; b < helpCount; b++)
                            {
                                string tempStr;
                                int tempInt;

                                tempInt = help[b - 1].UID;
                                help[b - 1].UID = help[b].UID;
                                help[b].UID = tempInt;

                                tempInt = help[b - 1].userMode;
                                help[b - 1].userMode = help[b].userMode;
                                help[b].userMode = tempInt;

                                tempInt = help[b - 1].userUID;
                                help[b - 1].userUID = help[b].userUID;
                                help[b].userUID = tempInt;

                                tempStr = help[b - 1].comment;
                                help[b - 1].comment = help[b].comment;
                                help[b].comment = tempStr;
                            }
                            helpCount--;
                            cout << "\nRecord Deleted.";
                            if (helpCount == 0)
                                UIDin = -1;
                            wait(2);
                        }
                        else
                        {
                            cout << "\nCancelled. Going back.";
                            wait(1);
                        }
                    } // if f>0
                    else
                    {
                        cout << "\nEntered help UID not found";
                    }
                } // WHILE UIDin!=-1 CLOSED
            }
            else
            {
                cout << "\nThere are no help requests.";
            }
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to view current user details (LOGGED IN)
    void showMyDetails()
    {
        if (userMode != -1)
        {
            if (userMode == 1) // USERBIKE ACCESS
            {
                cout << "\nYour Login Status: User (Bike)";
                cout << "\n------------------------------------------";
                cout << "\nName: " << userBike[currentNo - 1].Name;
                cout << "\nUID: " << userBike[currentNo - 1].UID;
                cout << "\nMobile No: " << userBike[currentNo - 1].MobNo;

                cout << "\nBooking Status: " << (userBike[currentNo - 1].isAllotted == 1) ? "Booked" : "Not Booked";
                cout << "\n------------------------------------------";
            }
            else if (userMode == 2) // USERTAXI ACCESS
            {
                cout << "\nYour Login Status: User (Taxi)";
                cout << "\n------------------------------------------";
                cout << "\nName: " << userTaxi[currentNo - 1].Name;
                cout << "\nUID: " << userTaxi[currentNo - 1].UID;
                cout << "\nMobile No: " << userTaxi[currentNo - 1].MobNo;

                cout << "\nBooking Status: " << (userTaxi[currentNo - 1].isAllotted == 1) ? "Booked" : "Not BookTaxi";
                cout << "\n------------------------------------------";
            }
            else if (userMode == 3) // STAFF ACCESS
            {
                cout << "\nYour Login Status: Staff";
                cout << "\n------------------------------------------";
                cout << "\nName: " << staff[currentNo - 1].Name;
                cout << "\nUID: " << staff[currentNo - 1].UID;
                cout << "\nMobile No: " << staff[currentNo - 1].MobNo;
                cout << "\n------------------------------------------";
            }
            else if (userMode == 4) // ADMIN ACCESS
            {
                cout << "\nYour Login Status: Admin";
                cout << "\n------------------------------------------";
                viewAdminDetails();
                cout << "\n------------------------------------------";
            }
            else
            {
                cout << "\nUSERMODE INVALID!";
            }
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to add a new staff
    void addStaff()
    {

        if (userMode == 4) // ADMIN ACCESS
        {
            if (staffCount < maxStaffCount)
            {
                int tempNo = staffCount;

                cout << "Enter your name : ";
                fflush(stdin);
                getline(cin, staff[tempNo].Name);

                cout << "Enter your password : ";
                fflush(stdin);
                cin >> staff[tempNo].password;

                cout << "Enter your mobile no : ";
                fflush(stdin);
                cin >> staff[tempNo].MobNo;

                // PROGRAM FOR UID ALLOTTMENT
                if (staffCount == 0)
                {
                    staff[staffCount].UID = 1;
                    cout << "\nUID allotted : 1";
                }
                else
                {
                    for (int a = 1; a <= maxStaffCount; a++)
                    {
                        int f = 0;
                        for (int b = 1; b <= staffCount; b++)
                        {
                            if (a == staff[b - 1].UID)
                            {
                                f = 1;
                                break;
                            }
                        }
                        if (f != 1)
                        {
                            cout << "\nUID allotted : " << a;
                            staff[tempNo - 1].UID = a;
                            break;
                        }
                    }
                }
                staffCount++;
            }
            else
            {
                cout << "Staff List is already full !" << endl;
            }
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to edit Staff Details
    void editStaff()
    {
        if (userMode == 4) // ADMIN ACCESS
        {

            if (staffCount == 0)
            {
                cout << "Staff List is empty !" << endl;
            }
            else
            {
                cout << "Enter the UID of staff you want to edit: ";
                int tempUID, flag = 0;
                fflush(stdin);
                cin >> tempUID;

                for (int i = 1; i <= staffCount; staffCount++)
                {
                    if (tempUID == staff[i - 1].UID)
                    {
                        flag = i;
                        break;
                    }
                }
                if (flag == 0)
                {
                    cout << "Entered UID not found !";
                }
                else
                {
                    string temp;

                    cout << "\nWhat do you want to change?:";
                    cout << "\n1. Change Name \n2.Change password";
                    cout << "\nEnter your choice_";
                    int choice = -1;
                    fflush(stdin);
                    cin >> choice;
                    if (choice == 1)
                    {
                        cout << "Enter new Name: \n";
                        fflush(stdin);
                        getline(cin, temp);
                        staff[flag - 1].Name = temp;
                    }
                    else if (choice == 2)
                    {
                        cout << "Enter new password: ";
                        fflush(stdin);
                        cin >> temp;
                        staff[flag - 1].password = temp;
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
            userMode = -1;
        }
    }

    // Funtion to remove a Staff
    void removeStaff()
    {
        if (userMode == 4) // ADMIN ACCESS
        {

            if (staffCount == 0)
            {
                cout << "Staff List is already empty!" << endl;
            }
            else
            {
                cout << "Enter the UID you want to Delete: ";
                int tempUID, flag = 0;
                fflush(stdin);
                cin >> tempUID;

                for (int i = 1; i <= staffCount; staffCount++)
                {
                    if (tempUID == staff[i - 1].UID)
                    {
                        flag = i;
                        break;
                    }
                }
                if (flag == 0)
                {
                    cout << "Entered UID not found !";
                }
                else
                {
                    string temp;
                    int tempN;
                    for (int i = flag; i < staffCount; i++)
                    {
                        tempN = staff[i - 1].UID;
                        staff[i - 1].UID = staff[i].UID;
                        staff[i].UID = tempN;

                        temp = staff[i - 1].Name;
                        staff[i - 1].Name = staff[i].Name;
                        staff[i].Name = temp;

                        temp = staff[i - 1].password;
                        staff[i - 1].password = staff[i].password;
                        staff[i].password = temp;
                    }
                    staffCount--;
                }
            }
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to view list of Staff members
    void viewStaff()
    {
        int tempNo = -1;   // to run loops and store serial no to operate on
        if (userMode == 4) // ADMIN ACCESS
        {
            if (staffCount > 0)
            {
                cout << "\nSr. No\tUID\tName";
                for (int tempNo = 1; tempNo <= staffCount; tempNo++)
                {
                    cout << "\n"
                         << tempNo
                         << "\t"
                         << staff[tempNo - 1].UID
                         << "\t"
                         << staff[tempNo - 1].Name;
                }
            }
            else
            {
                cout << "\nStaff List is empty!";
            }
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to View current Admin Details
    void viewAdminDetails()
    {
        if (userMode != -1)
        {
            cout << "Admin Details" << endl;
            if (adminCount > 0)
            {
                cout << "Name: " << admin[currentNo - 1].OrgName << endl;
                cout << "Address: " << admin[currentNo - 1].OrgAdrs << "\n";
                cout << "Mobile Number: " << admin[currentNo - 1].MobNo << "\n";
                cout << "Administrator: " << admin[currentNo - 1].Name;
                cout << "\n****************************************" << endl;
            }
            else
            {
                cout << "No Admin details Found!" << endl;
            }
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to edit current Admin Details
    void editAdminDetails()
    {
        if (userMode == 4) // ADMIN ACCESS
        {
            int choice = -1;
            string temp;
            while (choice != 0)
            {
                screenReset();
                cout << "What Do You Want To Change?\n";
                cout << "0. GO BACK\n";
                cout << "1. Name\n";
                cout << "2. password \n";
                cout << "3. OrgName\n";
                cout << "4. OrgAdrs\n";
                cout << "5. MobNo" << endl;

                cout << "Enter Your Choice_";
                fflush(stdin);
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    cout << "Enter New Admin Name\n";
                    fflush(stdin);
                    getline(cin, temp);
                    admin[currentNo - 1].Name = temp;
                }
                break;
                case 2:
                {
                    cout << "Enter New password" << endl;
                    fflush(stdin);
                    cin >> admin[currentNo - 1].password;
                }
                break;
                case 3:
                {
                    cout << "Enter New Organization Name\n";
                    fflush(stdin);
                    getline(cin, temp);
                    admin[currentNo - 1].OrgName = temp;
                }
                break;
                case 4:
                {
                    cout << "Enter New Organization Address\n";
                    fflush(stdin);
                    getline(cin, temp);
                    admin[currentNo - 1].OrgAdrs = temp;
                }
                break;
                case 5:
                {
                    cout << "Enter New Organization Name\n";
                    fflush(stdin);
                    cin >> temp;
                    admin[currentNo - 1].MobNo = temp;
                }
                break;
                case 0:
                {
                    cout << "Going Back..." << endl;
                }
                break;
                }
            }
        }
        else
        {
            userMode = -1;
        }
    }

    // Function to add new Admin
    void addAdminDetails()
    {
        string temp;
        if (userMode == 4) // ADMIN ACCESS
        {
            if (adminCount < maxAdminCount)
            {
                // UID Allotment
                if (adminCount == 0)
                {
                    admin[0].UID = 1;
                    cout << "\nUID allotted: 1";
                }
                else
                {
                    for (int a = 1; a <= maxAdminCount; a++)
                    {
                        int f = 0;
                        for (int b = 1; b <= adminCount; b++)
                        {
                            if (a == admin[b - 1].UID)
                            {
                                f = 1;
                                break;
                            }
                        }
                        if (f != 1)
                        {
                            cout << "\nUID allotted: " << a;
                            admin[adminCount].UID = a;
                            break;
                        }
                    }
                }

                cout << "\nEnter New Admin Name_";
                fflush(stdin);
                getline(cin, temp);
                admin[adminCount].Name = temp;

                cout << "\nEnter New password_";
                fflush(stdin);
                cin >> temp;
                admin[adminCount].password = temp;

                cout << "\nEnter Organization Name_";
                fflush(stdin);
                getline(cin, temp);
                admin[adminCount].OrgName = temp;

                cout << "\nEnter Organization Address_";
                fflush(stdin);
                getline(cin, temp);
                admin[adminCount].OrgAdrs = temp;

                cout << "\nEnter New Contact No_";
                fflush(stdin);
                cin >> temp;
                admin[adminCount].MobNo = temp;

                adminCount++;
                cout << "Going Back." << endl;
                wait(1);
            }
            else
            {
                cout << "Admin List is already full!" << endl;
            }
        }

        else
        {
            userMode = -1;
        }
    }
};

///////////////////////////////////////////////////////////////////////////////////////////

// MAIN FUNCTION
int main()
{

    /*
    Use value of variables
        -userMode
        -userModeNames[5]
        -currentNo
        -currentUID
    as and when needed
    */

    BookMyRide BMR;

    // cout << "Testing wait.";
    // BMR.wait(5);
    // exit(0);

    int choice = -1;
    BMR.setTheme();
    import();
    BMR.wait(1);
    BMR.screenReset();

    // Below code to ensure atleast one Admin is present, If not, then add one
    cout << "\nAdmin count=" << adminCount;
    if (adminCount == 0)
    {
        cout << "\nAdmin Details Not Present.\nDirecting to add Admin Details.";
        BMR.wait(1);
        userMode = 4;
        BMR.addAdminDetails();
        userMode = 0; // resetting userMode after adding admin as user isn't logged in yet
    }

    while (choice != 0)
    {

        BMR.screenReset();
        cout << "\nMain Menu";
        cout << "\n0. QUIT PROGRAM!";
        cout << "\n1. Use for Bike booking & related";
        cout << "\n2. Use for Taxi booking & related";
        cout << "\n3. Login as Staff";
        cout << "\n4. Login as Admin";
        cout << "\nEnter your Choice_";
        fflush(stdin);
        cin >> choice;
        switch (choice)
        {
        case 0: // EXIT
        {
            cout << "\nHappy to help:-)";
        }
        break;
        case 1: // UserBike Section
        {
            userMode = 1;
            if (BMR.authenticate(userMode))
            {
                int choice2 = -1;
                while (choice2 != 0)
                {
                    BMR.screenReset();
                    cout << "\n0. LOG OUT";
                    cout << "\nUser(Bike) Menu";
                    cout << "\n1. Make Booking";
                    cout << "\n2. Show Booking Details";
                    cout << "\n3. Remove Booking";
                    cout << "\n4. Ask for help";

                    cout << "\nEnter your choice_";
                    fflush(stdin);
                    cin >> choice2;
                    switch (choice2)
                    {
                    case 1: // new booking
                    {
                        BMR.bookBike();
                    }
                    break;
                    case 2: // show booking
                    {
                        BMR.showMyBooking();
                    }
                    break;
                    case 3: // remove booking
                    {
                        BMR.cancelBike();
                    }
                    break;
                    case 4: // help
                    {
                        BMR.getHelp();
                    }
                    break;
                    case 0: // LOG OUT
                    {
                        cout << "\nLogging out";
                    }
                    break;
                    default: // Default
                    {
                        cout << "\nInvalid choice entered!";
                    }
                    break;
                    }
                    BMR.holdByInput();
                } // SWITCH CLOSED

                if (userMode == -1) // SAFETY CHECK
                {
                    break;
                }
            } // IF AUTHENTICATE CLOSED
            else
            {
                cout << "\nUnable to Authenticate for Bike booking section!";
            }
        }
        break;
        case 2: // UserTaxi Section
        {
            userMode = 2;
            if (BMR.authenticate(userMode))
            {

                int choice2 = -1;
                while (choice2 != 0)
                {
                    BMR.screenReset();
                    cout << "\nUser(Taxi) Menu";
                    cout << "\n0. LOG OUT";
                    cout << "\n1. New Booking";
                    cout << "\n2. Show Booking Details";
                    cout << "\n3. Remove Booking";
                    cout << "\n4. Ask for help";

                    cout << "\nEnter your choice_";
                    fflush(stdin);
                    cin >> choice2;
                    switch (choice2)
                    {
                    case 1: // new booking
                    {
                        BMR.bookTaxi();
                    }
                    break;
                    case 2: // show booking
                    {
                        BMR.showMyBooking();
                    }
                    break;
                    case 3: // remove booking
                    {
                        BMR.cancelTaxi();
                    }
                    break;
                    case 4: // help
                    {
                        BMR.getHelp();
                    }
                    break;
                    case 0: // LOG OUT
                    {
                        cout << "\nLogging out";
                    }
                    break;
                    default: // Default
                    {
                        cout << "\nInvalid choice entered!";
                    }
                    break;
                    }
                    BMR.holdByInput();
                } // WHILE LOOP CLOSED

                if (userMode == -1) // SAFETY CHECK
                {
                    break;
                }
            }
            else
            {
                cout << "\nUnable to Authenticate for Taxi booking section!";
            }
        }
        break;
        case 3: // Staff Section
        {
            userMode = 3;
            int choice2 = -1, choice3 = -1;
            if (BMR.authenticate(userMode))
            {
                // Show your creativity here
                while (choice2 != 0)
                {

                    BMR.screenReset();

                    cout << "\nSTAFF MENU:";
                    cout << "\n0. LOG OUT";
                    cout << "\n1. Vehicle Menu";
                    cout << "\n2. Location Menu";
                    cout << "\n3. User Management";
                    cout << "\n4. Self Menu";
                    cout << "\nEnter your choice_";
                    fflush(stdin);
                    cin >> choice2;

                    switch (choice2)
                    {
                    case 1: // Vehicle Menu
                    {
                        choice3 = -1;
                        while (choice3 != 0)
                        {
                            BMR.screenReset();
                            cout << "\nVehicle Menu";
                            cout << "\n0. GO BACK";
                            cout << "\n1. Add Vehicle";
                            cout << "\n2. Edit Vehicle";
                            cout << "\n3. Remove Vehicle";
                            cout << "\n4. View Vehicles";
                            cout << "\nEnter your choice_";
                            fflush(stdin);
                            cin >> choice3;

                            switch (choice3)
                            {
                            case 1:
                            {
                                BMR.addVehicle();
                            } // Add Vehicle
                            break;
                            case 2:
                            {
                                BMR.editVehicle();
                            } // Edit Vehicle
                            break;
                            case 3:
                            {
                                BMR.removeVehicle();
                            } // Remove Vehicle
                            break;
                            case 4:
                            {
                                BMR.showVehicles();
                            } // View Vehicles
                            break;
                            case 0:
                            {
                                cout << "\nGoing back.";
                            } // Log Out
                            break;
                            default:
                            {
                                cout << "\nInvalid choice entered!";
                            }
                            } // SWITCH CLOSED
                            BMR.holdByInput();
                            if (userMode == -1) // SAFETY CHECK
                            {
                                break;
                            }
                        } // WHILE LOOP CLOSED
                    }
                    break;
                    case 2: // Location Menu
                    {
                        choice3 = -1;
                        while (choice3 != 0)
                        {
                            BMR.screenReset();
                            cout << "\nLocation Menu";
                            cout << "\n0. GO BACK";
                            cout << "\n1. Add Location";
                            cout << "\n2. Edit Location";
                            cout << "\n3. Remove Location";
                            cout << "\n4. View Locations";
                            cout << "\nEnter your choice_";
                            fflush(stdin);
                            cin >> choice3;

                            switch (choice3)
                            {
                            case 1:
                            {
                                BMR.addLocation();
                            } // Add Location
                            break;
                            case 2:
                            {
                                BMR.editLocation();
                            } // Edit Location
                            break;
                            case 3:
                            {
                                BMR.removeLocation();
                            } // Remove Location
                            break;
                            case 4:
                            {
                                BMR.showLocations();
                            } // View Location
                            break;
                            case 0:
                            {
                                cout << "\nGoing back.";
                            } // Log Out
                            break;
                            default:
                            {
                                cout << "\nInvalid choice entered!";
                            }
                            } // SWITCH CLOSED
                            BMR.holdByInput();
                            if (userMode == -1) // SAFETY CHECK
                            {
                                break;
                            }
                        }
                    }
                    break;
                    case 3: // User Management Menu
                    {
                        choice3 = -1;
                        while (choice3 != 0)
                        {
                            BMR.screenReset();
                            cout << "\nUser Management";
                            cout << "\n0. GO BACK";
                            cout << "\n1. Tick Off Booking";
                            cout << "\n2. Resolve help";
                            cout << "\n3. View Booking List";
                            cout << "\nEnter your choice_";
                            fflush(stdin);
                            cin >> choice3;

                            switch (choice3)
                            {
                            case 1:
                            {
                                BMR.tickOff();
                            }
                            break;
                            case 2:
                            {
                                BMR.resolveHelp();
                            }
                            break;
                            case 3:
                            {
                                BMR.showBookingList();
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
                            } // SWITCH CLOSED
                            BMR.holdByInput();
                            if (userMode == -1) // SAFETY CHECK
                            {
                                break;
                            }
                        }
                    }
                    break;
                    case 4: // Self Menu
                    {
                        choice3 = -1;
                        while (choice3 != 0)
                        {
                            BMR.screenReset();
                            cout << "\nSelf Menu";
                            cout << "\n0. Go Back";
                            cout << "\n1. View My Details";
                            cout << "\n2. Edit My Details";
                            cout << "\nEnter your choice_";
                            fflush(stdin);
                            cin >> choice3;

                            switch (choice3)
                            {
                            case 1:
                            {
                                BMR.showMyDetails();
                            } // View My Details
                            break;
                            case 2:
                            {
                                BMR.editSelf();
                            } // Edit My Details
                            break;
                            case 0:
                            {
                                cout << "\nGoing back.";
                            } // Log Out
                            break;
                            default:
                            {
                                cout << "\nInvalid choice entered!";
                            }
                            } // SWITCH CLOSED
                            BMR.holdByInput();
                            if (userMode == -1) // SAFETY CHECK
                            {
                                break;
                            }
                        }
                    }
                    break;
                    case 0:
                    {
                        cout << "\nLogged Out.";
                    }
                    break;
                    default:
                    {
                        cout << "\nInvalid Choice Entered!";
                    }
                    } // SWITCH CLOSED
                    BMR.holdByInput();
                    if (userMode == -1) // SAFETY CHECK
                    {
                        break;
                    }
                } // OUTER WHILE CLOSED
            }     // IF AUTHENTICATION CLOSED
        }
        break;
        case 4: // Admin Section
        {
            userMode = 4;
            int choice2 = -1;
            if (BMR.authenticate(userMode))
            {
                // Show your creativity here
                while (choice2 != 0)
                {
                    BMR.screenReset();
                    cout << "\nAdmin Menu:";
                    cout << "\n0. LOG OUT";
                    cout << "\n1. Add Staff";
                    cout << "\n2. Edit Staff";
                    cout << "\n3. Remove Staff";
                    cout << "\n4. View Staff";
                    cout << "\n5. View Org Details";
                    cout << "\n6. Edit Org Details";
                    cout << "\nEnter your choice_";
                    fflush(stdin);
                    cin >> choice2;

                    switch (choice2)
                    {
                    case 1: // add staff
                    {
                        BMR.addStaff();
                    }
                    break;
                    case 2: // edit staff
                    {
                        BMR.editStaff();
                    }
                    break;
                    case 3: // remove staff
                    {
                        BMR.removeStaff();
                    }
                    break;
                    case 4: // view staff
                    {
                        BMR.viewStaff();
                    }
                    break;
                    case 5: // view org details
                    {
                        BMR.viewAdminDetails();
                    }
                    break;
                    case 6: // edit org details
                    {
                        BMR.editAdminDetails();
                    }
                    break;
                    case 0:
                    {
                        cout << "\nLogging out.";
                    }
                    break;
                    default:
                    {
                        cout << "\nInvalid choice entered!";
                    }
                    break;
                    } // SWITCH CLOSED

                    BMR.holdByInput();

                    if (userMode == -1) // SAFETY CHECK
                    {
                        break;
                    }
                } // WHILE LOOP CLOSED
            }     // IF AUTHENTICATE CLOSED
            else
            {
                cout << "\nUnable to Authenticate as Admin!";
                userMode = -1; // extra layer of security
            }
        }
        break;
        default:
        {
            cout << "\nINVALID CHOICE ENTERED";
        }
        break;
        }                   // SWITCH CLOSED
        if (userMode == -1) // SAFETY CHECK
        {
            cout << "\nSecurity issue(s) detected!\nExiting the program.";
            BMR.wait(2);
            break;
        } // extra layer of security

        // resetting authentication and identification variables
        userMode = 0;
        currentNo = 0;
        currentUID = 0;
    } // MAIN WHILE LOOP CLOSED
    backup();
    BMR.wait(1);
    cout << "\nEND OF PROGRAM.";
    BMR.wait(1);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
