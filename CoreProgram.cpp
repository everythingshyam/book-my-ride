#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

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

struct UserBike
{
    int isActive; //0 if booking is expired, 1 if active
    string Name;
    string password;
    string MobNo;
    string Email;

    string Date_Booking;
    string Time_Booking;

    string Date_Travel;
    string Time_Start;
    string Time_End;

    int isAllotted;
    string BikeCode;
} userBike[maxUserCount];

struct UserTaxi
{
    int isActive; //0 if booking is expired, 1 if active
    string Name;
    string password;
    string MobNo;
    string Email;

    string Date_Booking;
    string Time_Booking;

    string Date_Start;
    string Time_Start;

    string Date_End;
    string Time_End;

    int isAllotted;
    string TaxiCode;
} userTaxi[maxUserCount];

struct Bike
{
    int isAvail;

    string BikeCode;
    string Name;
    string MobNo;
    string EmailID;
    string Date_Birth;
    string Date_Joining;
} bike[maxVehicleCount];

struct Taxi
{
    int isAvail;
    int capacity;
    int seatsOccupied;

    string TaxiCode;
    string Name;
    string MobNo;
    string EmailID;
    string Date_Birth;
    string Date_Joining;
} taxi[maxVehicleCount];

struct Staff
{
    string StaffCode;
    string Name;
    string passWord;
} staff[maxStaffCount];

struct Admin
{
    string AdminCode;
    string Name;
    string passWord;
} admin[1]; //Always 1

struct Location
{
    string locName;
    string locID; //4 lettered capital letter short name, like if name is Pimpri, ID will be PIMP, easier for user to input
    long locX;    //x coordinate of location
    long locY;
} location[maxLocCount];

//Don't think much of this class below, just remember the function names and what they do.
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
        printf("\n--------------------------------------------------------");
        time_t mytime;
        mytime = time(NULL);
        printf(ctime(&mytime));
        printf("\n\t\t\t***Welcome to %s Hospital***\n");

        printf("\n--------------------------------------------------------------------------------");
    }

    void encrypt(char *S)
    {
        /*
		Logic for encryption
		
		Basic rules applied, but effective enough

		FOR STRING
		if alphabet, first, case is changed then, considering the alphabets forming a circle, the opposite letter is chosen
		if digit, again, opposite digit is chosen, for ex, 0 replaced by 9, 1 replaced by 8
		Other symbols kept as it is
		For Decryption, just reverse the processes
	*/
        int l = strlen(S);
        for (int i = 0; i < l; i++)
        {
            if (S[i] >= 65 && S[i] <= 90) //UPPER CASE LETTERS
            {
                S[i] += 32;
                S[i] = 122 - (S[i] - 97);
            }
            else if (S[i] >= 97 && S[i] <= 122) //LOWER CASE LETTERS
            {
                S[i] -= 32;
                S[i] = 90 - (S[i] - 65);
            }
            else if (S[i] >= 48 && S[i] <= 57) //DIGITS
            {
                S[i] = 57 - (S[i] - 48);
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////
    void decrypt(char *S)
    {
        int l = strlen(S);
        for (int i = 0; i < l; i++)
        {
            if (S[i] >= 65 && S[i] <= 90) //UPPER CASE LETTERS
            {
                S[i] += 32;
                S[i] = 122 - (S[i] - 97);
            }
            else if (S[i] >= 97 && S[i] <= 122) //LOWER CASE LETTERS
            {
                S[i] -= 32;
                S[i] = 90 - (S[i] - 65);
            }
            else if (S[i] >= 48 && S[i] <= 57) //DIGITS
            {
                S[i] = 57 - (S[i] - 48);
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////////////
    int encryptInt(int a)
    {
        int b = 0;

        while (a != 0)
        {
            b = b * 10 + (9 - a % 10);
            a /= 10;
        }

        a = 0; //for confirmation

        while (b != 0)
        {
            a = a * 10 + b % 10;
            b /= 10;
        }

        return a;
    }
    ////////////////////////////////////////////////////////////////////////////////
    int decryptInt(int a)
    {
        int b = 0;

        while (a != 0)
        {
            b = b * 10 + (9 - a % 10);
            a /= 10;
        }

        a = 0; //for confirmation

        while (b != 0)
        {
            a = a * 10 + b % 10;
            b /= 10;
        }

        return a;
    }

    void import()
    {
        int dataCount; //temp line
        //importing from PatientRecords1024.txt
        FILE *fp = fopen("FileName.txt", "r");
        if (fp == NULL)
        {
            printf("\nFile Not Found!");
            fp = fopen("FileName.txt", "w");
            printf("\nNew File has been created.");
            fclose(fp);
        }
        dataCount = fread(userTaxi, sizeof(struct UserTaxi), 100, fp);
        printf("\nFile imported successfully.");
        fclose(fp);

        //Decrypting all data

        //DECRYPTION COMPLETED
    }
    void backup()
    {
        int dataCount; //temp line
        //Encrypting all data

        //ENCRYPTION COMPLETED

        //updating FileName.txt
        FILE *fp = fopen("FileName.txt", "w");
        if (fp == NULL)
        {
            printf("/nBackup File is empty!");
            exit(1);
        }
        fwrite(userTaxi, sizeof(struct UserTaxi), dataCount, fp);
        printf("\nBackup File updated successfully.");
        fclose(fp);
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
    int userMode = 0;
    /*
    indicates the mode user is in
    -1: Logged out of everything(UNSAFE)
    0: Logged out but Safe
    1: Logged in as User
    2: Logged in as Staff
    3: Logged in as Admin
    */
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
    void removeVehicle();
    void showVehicles();
    void resolveHelp();
    void showMyDetails();

    void addStaff();
    void editStaff();
    void removeStaff();
    void viewStaff();
    void viewOrgDetails();
    void editOrgDetails();
};

int main()
{
    //Main Menu here first, will be like switch inside switch
    cout << "hello there...";
    Support S;
    S.wait(5);
    cout << "\nHello again";
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
