//JUST backup file
//nothing much to do

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;
class FileManager
{
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
};
