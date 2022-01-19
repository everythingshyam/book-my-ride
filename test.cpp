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
        for (int b = 0; b < locationCount; b++)
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
            location[tempindex].UID = a;
            break;
        }
    }
}