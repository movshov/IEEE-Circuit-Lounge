
An electronic sign-in application for the IEEE Circuit Lounge
at Portland State University.

Author: Bar Movshovich

Description:

The purpose of this application is to allow students to sign up for help
and to allow the IEEE tutors to be able to better manage who needs help in
an orderly manner as well as get analytical data for the ECE department.

The students need only to scan their PSU access badge or
manually type in their 9-digit ODIN number into the program to sing_in.
The date of when they sign_in is automatically recorded. The
list of people who have used the program are shown in a scroll down
menu that cannot be altered.


AUTO SAVED RECORDS:
    Once the program is shut-down the program automatically records the list
    of students that signed_in and saves that list of records into a text file
    of the current month, day, and year. An example would look like so ,
        EX: "December 2, 2018.txt".
    The file can be located in the directory "SavedRecords".
    The format of the file is as follows:

    Name -> Date : Class : Sign_In_Time

    The program will automatically record the list of students to the text file daily at 4:00 PM.
    That day's records can be located in a directory called "SavedRecords". If a crash/shutdown
    has happened before the program reaches 4:00 PM because of the batter installed in the Laptop
    it should always reach 4:00 PM. In the case where the program is forcefully closed the program
    will save any students currently on the list as the current month, date, and year.txt.


Download/Build Instructions:

you can download the latest stable release at:

https://github.com/movshov/

BUILD INSTRUCTIONS:
    Some modifications will need to be made for the program to work with your own directories.

    In mainwindow.h on line 19 you will need to specify the file path for your "Access.txt" file.
        Ex: const QString ACCESS_FILE = "D:/QT5/Projects/Lab_Login/Access.txt";

    In mainwindow.h on line 20 you will need to specify the file path for your directory "SavedRecords".
        EX: const QString LOG_DIR = "D:/QT5/Projects/Lab_Login/SavedRecords/";

This application was written in C++ using the Qt5 frameworks. Make sure you have the
required libraries before building. If running on Debian or a Debian derivative,
an easy way to do this would be to use the following command:

    # apt-get install qt5-default qt5-qmake

    or if using sudo

    $ sudo apt-get install qt5-default qt5-qmake

In the top-level directory, issue the command:

    $ qmake -makefile
    $ make

And then to run the program, simple issue:

    $./Lab_Login


