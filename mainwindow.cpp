#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signinwindow.h"
#include "classwindow.h"
#include "confirmwindow.h"
#include "registerwindow.h"

/**
 * @brief Student::Student
 *      Constructor for Student Class
 * @param id
 *      The student's ODIN ID number.
 * @param name
 *      The student's name.
 * @param class
 *      The name of the class the student needs tutoring in.
 * @param timeIn
 *      The time at which the student first checks in the room.
 * @param date
 *      The date at which the student uses the program.
 */

Student::Student(QString id, QString name, QString Class, QTime timeIn, QDate date){
    this->id = id;
    this->name = name;
    this->Class = Class;
    this->date = date;
    this->signInTime = timeIn;
    this->next = nullptr;   //set next pointer to null.
    this->previous = nullptr;   //set previous pointer to null.
}

/**
 *  @brief Student::~Student
 *          Destructor for the Student node. If there is a next ptr, delete it.
 */

Student::~Student(){
    if(next != nullptr) delete next;
}

/**
 * @brief Stack::Stack
 *      Constructor for the Stack.
 */
Stack::Stack(){
    this->head = nullptr;
    this->tail = nullptr;
    setWeekOfSaveFile();    //set WeekOfSaveFile.
}

/**
 *  @brief Stack::~Stack
 *      Destructor for the class containing the list of students that have visited the room.
 */
Stack::~Stack(){
    //saverecords();  //save the stack to SavedRecords if program is shut down. Will also
    //call DeleteList() so the stack should be empty.
    if(head != nullptr){
        DeleteList();   //remove the entire DLL.
    }
}

/**
 *  @brief Stack::add
 *      Adds a student to the list of students getting help.
 *      New student's get added at the end of the DLL.
 *  @param toAdd
 *      The student node being added to the list.
 */
void Stack::add(Student * toAdd){
    if(head == nullptr){ //no list exists yet.
        head = toAdd;
        tail = head;
        return;
    }
    tail->next = toAdd; //set next pointer.
    toAdd->previous = tail; //set previous pointer.
    tail = toAdd;   //move tail over.
    return;
}


/**
* @brief Stack::DeleteList
*       Will remove everyone from the list.
*/
void Stack::DeleteList(){

    Student * current = head;

    while(current){
        Student * temp = current->next;
        current->previous = nullptr;
        current->next = nullptr;
        delete current; //delete "head"
        current = nullptr;  //set "head" to NULL.
        current = temp; //since head was already moved 1 forward.
    }
    head = nullptr;
    tail = nullptr;

}

/**
* @brief Stack::saverecords
*       Save the stack of sign in/out records to a .csv file.
* @param head
*       Is a doubly linked list of student sing in/out records.
*/
/*
void Stack::saverecords(){
    if(!head) return;
    QString fileName = LOG_DIR; //"D:/QT5/Projects/Circuit_Lounge_Login/SavedRecords/"
    fileName += WeekOfSaveFile; //get last Sunday's File Name.
    QFile data(fileName);
    if(data.open(QFile::WriteOnly | QFile::Append)){
        QTextStream out(&data); //converting everything to Text so QTextream will work.
        //Don't use QDataStream, it gets garbage symbols into .txt file.
        Student * current = head;

        //QString delimiter1 = QString::fromUtf8(" -> ");
        //QString delimiter2 = QString::fromUtf8(" : ");

        QString comma = QString::fromUtf8(",");
        while(current){
            out << current->id;   //record student's ID.
            out << comma;
            out << current->date.toString("MMMM dd yyyy");
            out << comma;
            out << current->Class;  //Class student needs help in
            out << comma;
            out << current->signInTime.toString("hh:mm a"); //record time student signed up.
            out << '\n';    //new line.
            current = current->next;
        }
        data.flush();
        data.close(); //close the opened file.
        DeleteList();   //Clean the Stack.
    }
}
*/
/**
 * @brief Stack::saveRecord
 *      Save the currently signed up student's information to the "Week of ..." file.
 *      We know that the newest student exists as Tail, so we use Tail's information.
 */
void Stack::saveRecord(){
    if(!head) return;
    QString fileName = LOG_DIR; //"D:/QT5/Projects/Circuit_Lounge_Login/SavedRecords/"
    fileName += WeekOfSaveFile; //get last Sunday's File Name.
    QFile data(fileName);
    if(data.open(QFile::WriteOnly | QFile::Append)){
        QTextStream out(&data); //converting everything to Text so QTextream will work.
        //Don't use QDataStream, it gets garbage symbols into .txt file.
        /*
        QString delimiter1 = QString::fromUtf8(" -> ");
        QString delimiter2 = QString::fromUtf8(" : ");
        */
        QString comma = QString::fromUtf8(",");

            out << tail->id;   //record student's ID.
            out << comma;
            out << tail->date.toString("MMMM dd yyyy");
            out << comma;
            out << tail->Class;  //Class student needs help in
            out << comma;
            out << tail->signInTime.toString("hh:mm a"); //record time student signed up.
            out << '\n';    //new line.

        data.flush();
        data.close(); //close the opened file.
    }
}
/**
 * @brief Stack::setWeekOfSaveFile
 *      Used to calculate what that Week's Sunday date is and create a .csv
 *      to save all of that weeks Student's that signed up for help.
 */
void Stack::setWeekOfSaveFile(){    //need to use addDays QDate function to get Sundays Date.
    QString checkDate = QDate::currentDate().toString("ddd"); //get the current date as Mon-Sun format.

    if(checkDate == "Sun") {  //it is sunday aka start of the week.
        WeekOfSaveFile = "Week of ";
        WeekOfSaveFile += QDate::currentDate().toString("MMMM dd, yyyy");
        WeekOfSaveFile += ".csv";   //append .csv
        return;
    }
    else { //if its Mon-Sat figure out what that week's Sunday is.
        WeekOfSaveFile = "Week of ";
        WeekOfSaveFile += QDate::currentDate().toString("MMMM ");   //EX: "Week of December ".
        QDate Today = QDate::currentDate(); //get Today's Date.
        QDate Sunday = Today.addDays(-Today.dayOfWeek());   //get the previous Sunday's date.
        WeekOfSaveFile += Sunday.toString("dd, ");  //Save previous Sunday's date.
        WeekOfSaveFile += QDate::currentDate().toString("yyyy");  //get the current year.
        WeekOfSaveFile += ".csv";   //append .csv
        return;
    }
}

/**
 * @brief RegInfo::RegInfo
 *      Constructor for an instance of a Registered student
 * @param id
 *      The id number of the student
 * @param name
 *      The name of the student
 */
RegInfo::RegInfo(QString id, QString name) {
  this->id = id;
  this->name = name;
  this->next = nullptr;
}

/**
 * @brief RegInfo::~RegInfo
 *      Destructor for a Registered student. Deletes the next node in the list.
 */
RegInfo::~RegInfo() {
  if (next) delete next;
}

/**
*   @brief Database::Database
*   Constructor for Register database. Reads in students from Database.txt and adds students
*   to another data structure.
*/
Database::Database(){   //Constructor.
    this->head = nullptr;   //set LLL to NULL.
    tableSize = 21;
    table = new RegInfo *[tableSize];
    QString id, name;

    for(int i=0; i< tableSize; ++i){    //set each ptr to null.
        table[i] = nullptr;
    }

    QFile data(RECORDS_FILE);    //open file containing people who have used the program before.
    if(data.open(QFile::ReadOnly)) {    //read in students from RegInfo.dat
       QTextStream inFile(&data);
        while(!inFile.atEnd()){
            QString line = inFile.readLine();
            QStringList fields = line.split(',');
            if(fields.size() == 2){
                id = fields.takeFirst();
                name = fields.takeFirst();
            }
            addStudent(id, name);
        }
    }
}

/**
*  @brief Database::~Database
*       Destructor for Database class. Writes the database to a file
*       and cleans up the hashtable.
*/
Database::~Database(){
    for(int i = 0; i < tableSize; ++i){ //traverse hash table and delete
        if(table[i]) delete table[i];   //remove info.
    }
    saveNewStudents();  //Will call DeleteList after saving.

}
/**
 * @brief Database::DeleteList
 *      Delete LLL of all data.
 */
void Database::DeleteList(){
    RegInfo * current = head;

    while(current){
        RegInfo * temp = current->next;
        current->next = nullptr;
        delete current; //delete "head"
        current = nullptr;  //set "head" to NULL.
        current = temp; //since head was already moved 1 forward.
    }
    if(head) delete head;
    head = nullptr;
}
/**
*   @brief Database::addStudent
*       Adds a student to the hashtable database.
*   @param
*       The student's ODIN ID.
*   @param
*       The student's name.
*/
void Database::addStudent(QString id, QString name){
    int key = hash(id);
    if (table[key] == nullptr) {
      table[key] = new RegInfo(id, name);
    }
    else {
      RegInfo * current = table[key];
      while (current->next) {
        current = current->next;
      }
      current->next = new RegInfo(id, name);
    }
}
/**
 * @brief Database::saveNewStudent
 * @param id
 *      The student's ODIN ID.
 * @param name
 *      The student's Name.
 */
void Database::saveNewStudent(QString id, QString name){
    if(head == nullptr){ //no list exists yet.
        head = new RegInfo(id,name);
        return;
    }
    RegInfo * temp = new RegInfo(id,name);
    temp->next = head;
    head = temp;
    return;
}


/**
 * @brief Database::getStudent
 *      Gets the registered student info from the hash table
 * @param id
 *      The id to hash
 * @return
 *      The student's registered info
 */
RegInfo * Database::getStudent(QString id) {
  int key = hash(id);   //hash id

  if (table[key] != nullptr) { //ensure list at table entry is not empty
    RegInfo * current = table[key];
    //traverse list until id is or is not found
    while (current && current->id.compare(id) != 0) {
      current = current->next;
    }
    if (current) { //if the node with the id is found
      return current; //return the node
    }
  }
  return nullptr;
}

/**
 * @brief Database::hash
 *      Hash function. Takes the value of each char and multiplies the ascii value by 7
 *      powered to the string length minus the char index minus 1. Adds that value to
 *      a sum integer and returns the value modulus the table size.
 *      i.e. Sigma from 0 to string length ( digit * |7 ^ (string length - charPos - 1)| )
 * @param id
 *      The id string to hash
 * @return
 *      The hashed value
 */
int Database::hash(QString id) {
  int sum = 0;
  int length = id.length();

  if (id.compare("") == 0)  //If the string is NULL
    return -1;              //Nothing to hash

  for (int i = 0; i < length; ++i)
    sum += id.at(i).digitValue() * abs(pow(float(7),    //sum the string char * 7 powered to string length - index - 1
           float((length - i - 1))));                   //absolute value to prevent negative numbers

  return sum % tableSize; //return the sum modulous the hash table size
}
/**
 * @brief Database::saveNewStudents
 *      Append to Database file of students that have already used the application before
 *      to allow students to get help again without needed to re-register.
 * @return
 */
void Database::saveNewStudents(){
    QString fileName = RECORDS_FILE;
    QFile data(fileName);

    if(data.open(QFile::WriteOnly | QFile::Append )){
        QTextStream out(&data); //converting everything to Text so QTextream will work.
        //Don't use QDataStream, it gets garbage symbols into .txt file.
        RegInfo * current = head;
        QString comma = QString::fromUtf8(",");
        while(current){
            out << current->id;   //record student's ID.
            out << comma;
            out << current->name;   //record student's Name.
            out << '\n';    //new line.
            current = current->next;
        }

        data.flush();
        data.close(); //close the opened file.
        DeleteList(); //delete LLL.
    }
}

MainWindow::MainWindow(){
    signInWindow = new SignInWindow(this);
    classWindow = new ClassWindow(this);
    confirmWindow = new ConfirmWindow(this);
    registerWindow = new RegisterWindow(this);

    errorText = new QLabel(this);
    errorText->resize(400,40);
    errorText->hide();

    //This is the table of students who have signed in.
    numberOnList = 0;
    theList = new QTableWidget(0, 4, this); //QTableWidget(row,col,parent).
    buildTable(numberOnList);



    timer = new QTimer(this);
    //timer->start(86400000); //This will only run once every 24 hours.
    //timer->start(300000);     //msec in 5 minutes.
    //timer->start(60000);    //msec in 1 minute used for testing purposes.
    timer->start(30000);    //msec in 30sec used for testing purposes.

    signInWindow->openWindow();

    //setup signal and slot
    connect(timer, SIGNAL(timeout()),this, SLOT(checktime()));
    connect(signInWindow->loginButton, SIGNAL(clicked()), this, SLOT(signInLogInButtonPressed()));
    connect(signInWindow->loginDialog, SIGNAL(returnPressed()), this, SLOT(signInLogInButtonPressed()));

    connect(registerWindow->cancelButton, SIGNAL(clicked()), this, SLOT(registerCancelButtonPressed()));
    connect(registerWindow->regButton, SIGNAL(clicked()), this, SLOT(registerRegisterButtonPressed()));

    connect(classWindow->ECE101, SIGNAL(clicked()), this, SLOT(classECE101ButtonPressed()));
    connect(classWindow->ECE102, SIGNAL(clicked()), this, SLOT(classECE102ButtonPressed()));
    connect(classWindow->ECE103, SIGNAL(clicked()), this, SLOT(classECE103ButtonPressed()));
    connect(classWindow->ECE171, SIGNAL(clicked()), this, SLOT(classECE171ButtonPressed()));
    connect(classWindow->ECE172, SIGNAL(clicked()), this, SLOT(classECE172ButtonPressed()));
    connect(classWindow->ECE211, SIGNAL(clicked()), this, SLOT(classECE211ButtonPressed()));
    connect(classWindow->ECE212, SIGNAL(clicked()), this, SLOT(classECE212ButtonPressed()));
    connect(classWindow->ECE221, SIGNAL(clicked()), this, SLOT(classECE221ButtonPressed()));
    connect(classWindow->ECE222, SIGNAL(clicked()), this, SLOT(classECE222ButtonPressed()));
    connect(classWindow->ECE223, SIGNAL(clicked()), this, SLOT(classECE223ButtonPressed()));
    connect(classWindow->ECE241, SIGNAL(clicked()), this, SLOT(classECE241ButtonPressed()));
    connect(classWindow->ECE315, SIGNAL(clicked()), this, SLOT(classECE315ButtonPressed()));
    connect(classWindow->ECE316, SIGNAL(clicked()), this, SLOT(classECE316ButtonPressed()));
    connect(classWindow->ECE317, SIGNAL(clicked()), this, SLOT(classECE317ButtonPressed()));
    connect(classWindow->ECE321, SIGNAL(clicked()), this, SLOT(classECE321ButtonPressed()));
    connect(classWindow->ECE322, SIGNAL(clicked()), this, SLOT(classECE322ButtonPressed()));
    connect(classWindow->ECE323, SIGNAL(clicked()), this, SLOT(classECE323ButtonPressed()));
    connect(classWindow->ECE331, SIGNAL(clicked()), this, SLOT(classECE331ButtonPressed()));
    connect(classWindow->ECE332, SIGNAL(clicked()), this, SLOT(classECE332ButtonPressed()));
    connect(classWindow->ECE341, SIGNAL(clicked()), this, SLOT(classECE341ButtonPressed()));
    connect(classWindow->ECE347, SIGNAL(clicked()), this, SLOT(classECE347ButtonPressed()));
    connect(classWindow->ECE348, SIGNAL(clicked()), this, SLOT(classECE348ButtonPressed()));
    connect(classWindow->ECE351, SIGNAL(clicked()), this, SLOT(classECE351ButtonPressed()));
    connect(classWindow->ECE361, SIGNAL(clicked()), this, SLOT(classECE361ButtonPressed()));
    connect(classWindow->ECE362, SIGNAL(clicked()), this, SLOT(classECE362ButtonPressed()));
    connect(classWindow->ECE371, SIGNAL(clicked()), this, SLOT(classECE371ButtonPressed()));
    connect(classWindow->ECE372, SIGNAL(clicked()), this, SLOT(classECE372ButtonPressed()));
    connect(classWindow->ECE373, SIGNAL(clicked()), this, SLOT(classECE373ButtonPressed()));
    connect(classWindow->ECE383, SIGNAL(clicked()), this, SLOT(classECE383ButtonPressed()));
    connect(classWindow->other, SIGNAL(clicked()), this, SLOT(classOtherButtonPressed()));
    connect(classWindow->cancelButton, SIGNAL(clicked()), this, SLOT(classCancelButtonPressed()));

    connect(confirmWindow->confirmButton, SIGNAL(clicked()), this, SLOT(confirmConfirmButtonPressed()));
    connect(confirmWindow->cancelButton, SIGNAL(clicked()), this, SLOT(confirmCancelButtonPressed()));

    setWindowTitle("IEEE Tutoring");
    resize(XRES,YRES);  //resize to default x and y res.
    showFullScreen();   //sets to full screen mode.


}
//CheckMonth slots
/**
* @brief MainWindow::checktime
*       Used to check to see if it's past 9PM. If so, then save the stack and close the application.
*       This is mainly going to be used in case somebody forgets to shut off the Laptop.
*/

void MainWindow::checktime(){
    QString checkTime = QTime::currentTime().toString("hh"); //get the current time (00 to 23).
    if (checkTime < 21) { //it is not 9PM.
        return;
    }
    //stack.saverecords();  //save the stack to the weekly save file.
    numberOnList = 0;   //after saving reset list #.
    updateTable();  //Table should be empty at this point.
    QCoreApplication::quit();   //quit the application.
    return; //will never get hit but just in case.
}
/*
 * Sign-in Window SLOTS
 */
void MainWindow::signInLogInButtonPressed() {
    if (signInWindow->loginDialog->cursorPosition() < 9) {
       signInWindow->closeWindow();
       signInWindow->openWindow();
       errorText->move(1080, 525);
       errorText->setText("Please enter a valid\n9-digit ODIN ID");
       errorText->show();
       return;
     }

     errorText->hide();
     id = signInWindow->loginDialog->text();

     signInTime = QTime::currentTime();    //get the current time.
     date = QDate::currentDate();  //get the current date.

     RegInfo * student = database.getStudent(id);

     if (!student) { //if id is not in the database
         theList->hide();
         signInWindow->closeWindow();
         updateTable();
         registerWindow->openWindow(); //add new student to database.
     }
     else{
         name = student->name;
         id = student->id;
         theList->hide();  //hide the stack.
         signInWindow->closeWindow();  //close sign in window.
         updateTable();
         classWindow->OpenWindow();    //opne class window.
     }
}

/*
 * Register Window SLOTS
 */
void MainWindow::registerRegisterButtonPressed(){
    if(registerWindow->nameDialog->cursorPosition() < 3){
        registerWindow->nameDialog->clear();
        registerWindow->nameDialog->setFocus();
        errorText->move(910,525);
        errorText->setText("Please enter a name with at leaast 3 characters");
        errorText->show();
        return;
    }
    name = registerWindow->nameDialog->text();
    database.addStudent(id,name);   //add to Hash Table.
    database.saveNewStudent(id,name);   //add to LLL to be recorded for future use.
    errorText->hide();
    registerWindow->closeWindow();
    classWindow->OpenWindow();
}

void MainWindow::registerCancelButtonPressed(){
    errorText->hide();
    registerWindow->closeWindow();
    theList->show();
    signInWindow->openWindow();
}

void MainWindow::registerIDDialogEntered(){
    registerWindow->nameDialog->setFocus();
}

/*
 * Class Window SLOTS
 */
void MainWindow::classECE101ButtonPressed(){
    Class = "ECE 101";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE102ButtonPressed(){
    Class = "ECE 102";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE103ButtonPressed(){
    Class = "ECE 103";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE171ButtonPressed(){
    Class = "ECE 171";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE172ButtonPressed(){
    Class = "ECE 172";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE211ButtonPressed(){
    Class = "ECE 211";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE212ButtonPressed(){
    Class = "ECE 212";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE221ButtonPressed(){
    Class = "ECE 221";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE222ButtonPressed(){
    Class = "ECE 222";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE223ButtonPressed(){
    Class = "ECE 223";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE241ButtonPressed(){
    Class = "ECE 241";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE315ButtonPressed(){
    Class = "ECE 315";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE316ButtonPressed(){
    Class = "ECE 316";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE317ButtonPressed(){
    Class = "ECE 317";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE321ButtonPressed(){
    Class = "ECE 321";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE322ButtonPressed(){
    Class = "ECE 322";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE323ButtonPressed(){
    Class = "ECE 323";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE331ButtonPressed(){
    Class = "ECE 331";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE332ButtonPressed(){
    Class = "ECE 332";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE341ButtonPressed(){
    Class = "ECE 341";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE347ButtonPressed(){
    Class = "ECE 347";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE348ButtonPressed(){
    Class = "ECE 348";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE351ButtonPressed(){
    Class = "ECE 351";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE361ButtonPressed(){
    Class = "ECE 361";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE362ButtonPressed(){
    Class = "ECE 362";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE371ButtonPressed(){
    Class = "ECE 371";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE372ButtonPressed(){
    Class = "ECE 372";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE373ButtonPressed(){
    Class = "ECE 373";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classECE383ButtonPressed(){
    Class = "ECE 383";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classOtherButtonPressed(){
    Class = "Other";
    classWindow->CloseWindow();
    confirmWindow->openWindow();
    showConfirm();
}

void MainWindow::classCancelButtonPressed(){
    classWindow->CloseWindow();
    theList->show();
    signInWindow->openWindow();
}

/*
 * Confirm Window SLOTS
 */
void MainWindow::confirmConfirmButtonPressed(){
     stack.add(new Student(id, name, Class, signInTime, date));  //add to the stack.
     ++numberOnList;
     updateTable();
     stack.setWeekOfSaveFile(); //Will make sure we are still on the same week.
     stack.saveRecord();    //save the newly added Sign-in to the csv file.
     confirmWindow->closeWindow();
     hideConfirm();
     theList->show();
     signInWindow->openWindow();
     theList->scrollToBottom();
}

void MainWindow::confirmCancelButtonPressed(){
    confirmWindow->closeWindow();
    hideConfirm();
    theList->show();
    signInWindow->openWindow();
}

void MainWindow::showConfirm(){
    confirmWindow->nameOutput->setText(name);
    confirmWindow->ClassOutput->setText(Class);
}

void MainWindow::hideConfirm(){
    confirmWindow->nameOutput->setText("");
    confirmWindow->ClassOutput->setText("");
}

void MainWindow::buildTable(int rows) {
  theList->removeRow(rows);
  theList->insertRow(rows);
  theList->move(450, 100);
  theList->resize(970,300);
  theList->setHorizontalHeaderLabels(QStringList() << "Name" << "Date" << "Class" << "Sign-in Time");
  theList->setEditTriggers(QAbstractItemView::NoEditTriggers);
  theList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  theList->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  theList->setColumnWidth(0, 250);
  theList->setColumnWidth(1, 250);
  theList->setColumnWidth(2, 250);
  theList->setColumnWidth(3, 203);
}

void MainWindow::updateTable() {
  theList->clearContents();
  buildTable(numberOnList);
  Student * current = stack.head;
  int row = 0;
  while (current != nullptr) {
    theList->setItem(row, 0, new QTableWidgetItem(current->name));
    theList->setItem(row, 1, new QTableWidgetItem(current->date.toString("MMMM dd, yyyy")));
    theList->setItem(row, 2, new QTableWidgetItem(current->Class));
    theList->setItem(row, 3, new QTableWidgetItem(current->signInTime.toString("hh:mm a")));
    current = current->next;
    ++row;
  }
}















