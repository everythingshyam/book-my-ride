-   Add CLOSED comment besides closing curly braces if it doesn't have a sibling braces on next line.

-   Fix redundancy in userMode=-1; (if any)

-   Program is unnecessarily finding serial no from UID (which is obtained from serial no (currentNo) itself). Fix that redundancy

-   Add access permission comment on each if (userMode) line

-   make choice variable global

-   in place of if(userMode), use blank returns

-   get util class in another file, import from there

-   fflush before each input (maybe make a dedicated function)

-   convert C Code to C++

-   reduce wait time

-   set 'back' as 0, indexing from 1 (indexing remaining)
