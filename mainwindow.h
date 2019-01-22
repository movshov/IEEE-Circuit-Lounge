#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QLabel>
#include <QTime>
#include <QTableWidget>
#include <QHeaderView>
#include <cmath>
#include <QTimer>
#include <QDebug>
#include <QFileInfo>


using namespace std;
//"D:/QT5/Projects/Circuit_Lounge_Login/SavedRecords/";     //PC Version.
//Users/barmovshovich/Desktop/Desktop/College/CS/Open-Tech-Lab-Login-master/Access.txt";    //Mac Version.

const QString RECORDS_FILE = "/Users/barmovshovich/Desktop/Desktop/College/CS/IEEE-Circuit-Lounge-master/Database.txt";
const QString LOG_DIR = "/Users/barmovshovich/Desktop/Desktop/College/CS/IEEE-Circuit-Lounge-master/SavedRecords/";

class SignInWindow; //Window below table of current students in the room.
class ClassWindow;  //Window of available Classes to get help with.
class ConfirmWindow;    //Window to Confirm User input.

struct Student {    //struct for Student Info.
    Student(QString, QString, QString, QTime, QDate); //constructor.
    ~Student(); //destructor.

    QString id, name, Class;
    QTime signInTime;
    QDate date;
    Student * next;
    Student * previous;
};

struct Stack {
    Stack();    //constructor.
    Stack(const Stack&);    //copy constructor.
    ~Stack();   //destructor.
    void add(Student*); //add a student to the stack. 
    void DeleteList();  //remove everyone from the list.
    void saverecords();  //record the stack into a .txt file if the program is forcefully shut off.   
    void dailysave(QString);  //if one month has passed save the stack into a .txt file named "that month + year.txt"
    //EX: "December_2019.txt", "November_2019.txt"
    Student * head; //head pointer.
    Student * tail; //tail pointer.

};


struct RegInfo {
    RegInfo(QString, QString);  //constructor.
    ~RegInfo(); //destructor.
    QString id;
    QString name;
    RegInfo * next;
};

struct Database {
    Database(); //constructor.
    ~Database();    //destructor.
    void addStudent(QString, QString);
    RegInfo * getStudent(QString);

private:
    int tableSize;
    RegInfo ** table;
    int hash(QString);
};
//Resolution.
const int XRES = 1366, YRES = 768;

class MainWindow : public QMainWindow{
    Q_OBJECT

    int numberOnList;
    QString id, name, Class;
    QTime signInTime;
    QDate date;
    QLabel * errorText;
    QTableWidget * theList;
    Stack stack;
    Database database;
    SignInWindow * signInWindow;
    ClassWindow * classWindow;
    ConfirmWindow * confirmWindow;
    QTimer *timer;

    void showConfirm();
    void hideConfirm();
    void buildTable(int);   //build the table.
    void updateTable();     //update the already built table.
    //void checkmonth(Stack stack);   //check if one month has passed.


private slots:
    void signInLogInButtonPressed();

    void classECE101ButtonPressed();
    void classECE102ButtonPressed();
    void classECE103ButtonPressed();
    void classECE171ButtonPressed();
    void classECE172ButtonPressed();
    void classECE211ButtonPressed();
    void classECE212ButtonPressed();
    void classECE221ButtonPressed();
    void classECE222ButtonPressed();
    void classECE223ButtonPressed();
    void classECE241ButtonPressed();
    void classECE315ButtonPressed();
    void classECE316ButtonPressed();
    void classECE317ButtonPressed();
    void classECE321ButtonPressed();
    void classECE322ButtonPressed();
    void classECE323ButtonPressed();
    void classECE331ButtonPressed();
    void classECE332ButtonPressed();
    void classECE341ButtonPressed();
    void classECE347ButtonPressed();
    void classECE348ButtonPressed();
    void classECE351ButtonPressed();
    void classECE361ButtonPressed();
    void classECE362ButtonPressed();
    void classECE371ButtonPressed();
    void classECE372ButtonPressed();
    void classECE373ButtonPressed();
    void classECE383ButtonPressed();
    void classOtherButtonPressed(); //user has picked Other class.
    void classCancelButtonPressed();    //user has canceled signup.

    void confirmConfirmButtonPressed(); //User confirms info is correct.
    void confirmCancelButtonPressed();  //user confirms info is incorrect.

    void checktime();      //slots wrapper for checkmonth(stack).

public:
    MainWindow();

};

#endif // MAINWINDOW_H
