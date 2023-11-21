# BookMyRide

### A detailed C++ program to manage Taxi and Bike Booking, with interactive interface for customers, drivers, application staff and admins. Made this as a team mini-project in the third semester of my college. (March, 2021)

## Team Members:

-   [Shyam Tiwari](https://everythingshyam.github.io/static-personal-website/)
-   [Ritik Wandale](https://github.com/Ritiksw)
-   [Hishita Thakkar](https://github.com/hishita01)
-   [Mehak Chib](https://www.linkedin.com/in/mehak-chib-336b49212/)
-   [Vanshika Dhar](https://www.linkedin.com/in/vanshika-dhar-02v/)

## Project Overview

It is a simple yet extensive Cab Booking Management System that provides users booking services for taxis as well as bikes. The application provides interface for customers, drivers, staff and administrators.

We took reference from an already existing application available on GitHub (reference code can be accessed [here](https://github.com/everythingshyam/book-my-ride/blob/master/archives/reference.cpp)) However, the whole application structure was built up from scratch, component by component. The application is divided into following major segments:

-   Util Functions
-   Admin Section
-   Staff Section
-   User Section
    -   Bike Users
    -   Taxi Users

First, there are several util functions that provide common functionalities such as changing theme of the terminal, importing and exporting data from and to text files, authenticating users, etc.

Then the functions are divided based on the user-classifications, and each function also checks for something called `userMode`, which is basically a number that represents the role of the user. Each function checks for the userMode before allowing access to the operations it contains.

## Concepts used

The menus shown in this program are made using `switch cases`. Besides, there is a lot of usage of `if-else if-else` structure and `loops`. Most of the variables used are declared globally. We used `struct` to store records of vehicles, customers, etc. Every feature is implemented as a `function`, with proper care for unexpected scenarios, even if there're not much as of now. `File handling` is used to write to/read from text files. With more than 3500 lines of code, the program has used a lot of programming concepts.

We have also taken care of consistency throughout the code through things such as:

-   Wherever there is a menu, 0 is assigned to going back/logging out.
-   And hence, to avoid any confusion, loops have been run from 1 instead of 0.
-   Also, at some places, -1 is used to represent unacceptable scenarios. Such as when user deletes himself (program needs to go back to login/signup screen)

## Backstory

After making a complete project in C, I was really motivated this semester to work on another project, this time in C++. We have made a dummy CPP Application for Taxi and Bike Booking, Book My Ride. We worked on different components at the same time. It worked out very well and the examiner really liked our project and so did our freinds. It was simple yet worth taking a look. Many of my friends were surprised by the amount of code written (for a mini-project).

This was the first real project in which we used git and GitHub extensively. That really helped us explore a lot about how open source works and was one of the initial stages that led to the extent to which I use version control now.

#
