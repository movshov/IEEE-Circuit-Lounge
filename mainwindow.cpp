#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signinwindow.h"
#include "classwindow.h"
#include "confirmwindow.h"

/**
 * @brief Student::Student
 *      Constructor for Student Class
 * @param id
 *      The student's ODIN ID number.
 * @param name
 *      The student's name.
 * @param timeIn
 *      The time at which the student first checks in the room.
 * @param timeOut
 *      The time at which the student checks out of the room.
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
}

/**
 *  @brief Stack::~Stack
 *      Destructor for the class containing the list of students that have visited the room.
 */
Stack::~Stack(){
    saverecords();  //save the stack to SavedRecords if program is shut down.
    if(head != nullptr) delete head;
}

/**
 *  @brief Stack::add
 *      Adds a student to the list of students that have checked in/out of the room.
 *  @param toAdd
 *      The student node being added to the list.
 */
//FUNCTION: Inserts new node at the head of the stack always.
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
        delete current;
        current = temp; //since head was already moved 1 forward.
    }
    head = nullptr;
    tail = nullptr;

}
/**
* @brief Stack::saverecords
*       Save the stack of sign in/out records to a .txt file.
* @param head
*       Is a doubly linked list of student sing in/out records.
*/
void Stack::saverecords(){
    if(!head) return;
    QString fileName = LOG_DIR; //"D:/QT5/Projects/Circuit_Lounge_Login/SavedRecords/"
    fileName += QDateTime::currentDateTime().toString("MMMM dd, yyyy"); //gets month and year.
    fileName += ".csv"; //append .csv file extension to name
    QFile data(fileName);
    if(data.open(QFile::WriteOnly | QFile::Append)){
        QTextStream out(&data); //converting everything to Text so QTextream will work.
        //Don't use QDataStream, it gets garbage symbols into .txt file.
        Student * current = head;
        /*
        QString delimiter1 = QString::fromUtf8(" -> ");
        QString delimiter2 = QString::fromUtf8(" : ");
        */
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
    }
}

/**
* @brief Stack::dailysave
*       Saves the stack into a .txt file if it is past 4PM.
* @param head
*       Is a doubly linked list of sign In/Out records.
*/
void Stack::dailysave(QString SaveFileName){
    QString fileName = LOG_DIR; //"D:/QT5/Projects/Lab_Login/SavedRecords/"
    fileName += SaveFileName;   //given from monthlysave in MainWindow class.
    fileName += ".csv"; //append .csv file extension to name
    QFile data(fileName);

    if(data.open(QFile::WriteOnly | QFile::Append )){
        QTextStream out(&data); //converting everything to Text so QTextream will work.
        //Don't use QDataStream, it gets garbage symbols into .txt file.
        Student * current = head;
       /*
        QString empty = QString::fromUtf8(" ____ ");
        QString delimiter1 = QString::fromUtf8(" -> ");
        QString delimiter2 = QString::fromUtf8(" : ");
        */
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

/**
 * @brief RegInfo::RegInfo
 *      Constructor for an instance of a Registered student/tutor
 * @param id
 *      The id number of the student/tutor
 * @param name
 *      The name of the student/tutor
 */
RegInfo::RegInfo(QString id, QString name) {
  this->id = id;
  this->name = name;
  this->next = nullptr;
}

/**
 * @brief RegInfo::~RegInfo
 *      Destructor for a Registered student/tutor. Deletes the next node in the list.
 */
RegInfo::~RegInfo() {
  if (next) delete next;
}

/**
*   @brief Database::Database
*   Constructor for Register database. Reads in students from RegInfo.dat and adds students
*   to another data structure.
*/
Database::Database(){   //Constructor.
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


MainWindow::MainWindow(){
    signInWindow = new SignInWindow(this);
    classWindow = new ClassWindow(this);
    confirmWindow = new ConfirmWindow(this);

    errorText = new QLabel(this);
    errorText->resize(400,40);
    errorText->hide();

    //This is the table of students who have signed in.
    numberOnList = 0;
    theList = new QTableWidget(0, 3, this); //QTableWidget(row,col,parent).
    buildTable(numberOnList);

    signInWindow->openWindow();

    timer = new QTimer(this);
    //timer->start(86400000); //This will only run once every 24 hours.
    //timer->start(300000);     //msec in 5 minutes.
    //timer->start(60000);    //msec in 1 minute used for testing purposes.
    timer->start(30000);    //msec in 30sec used for testing purposes.

    //setup signal and slot
    connect(timer, SIGNAL(timeout()),this, SLOT(checktime()));
    connect(signInWindow->loginButton, SIGNAL(clicked()), this, SLOT(signInLogInButtonPressed()));
    connect(signInWindow->loginDialog, SIGNAL(returnPressed()), this, SLOT(signInLogInButtonPressed()));

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
  //  showFullScreen();   //Full Screen mode for Windows.
    QTimer::singleShot(300, this, SLOT(showFullScreen())); //Full Screen mode for MAC.


}
//CheckMonth slots
/**
* @brief MainWindow::checktime
*       Used to check to see if it's past 4PM. If so, then save the stack and close the application.
*/

void MainWindow::checktime(){
    if(!stack.head) return; //if there is no list.
    QString checkTime = QTime::currentTime().toString("hh"); //get the current time (00 to 23).
    if (checkTime != "00") { //it is not 4PM.
        return;
    }
    QString SaveFileName = QDate::currentDate().toString("MMMM dd, yyyy"); //get the current Month.
    stack.dailysave(SaveFileName);
    numberOnList = 0;   //after saveing reset list #.
    updateTable();
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

    RegInfo * student = database.getStudent(id);
    if (!student) { //if id is not in the database
      signInWindow->closeWindow();
      signInWindow->openWindow();
      errorText->move(1080, 525);
      errorText->setText("You do not have access to be in this room");
      errorText->show();
      return;
    }  
      name = student->name;
      id = student->id;
      signInTime = QTime::currentTime();    //get the current time.
      date = QDate::currentDate();  //get the current date.
      theList->hide();  //hide the stack.
      signInWindow->closeWindow();  //close sign in window.
      classWindow->OpenWindow();    //opne class window.

}

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

void MainWindow::confirmConfirmButtonPressed(){
     stack.add(new Student(id, name, Class, signInTime, date));  //add to the stack.
     ++numberOnList;
     updateTable();
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
  theList->move(265, 100);
  theList->resize(900, 300);
  theList->setHorizontalHeaderLabels(QStringList() << "Name" << "Class" << "Sign-in Time");
  theList->setEditTriggers(QAbstractItemView::NoEditTriggers);
  theList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  theList->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  theList->setColumnWidth(0, 300);
  theList->setColumnWidth(1, 300);
  theList->setColumnWidth(2, 300);
}

void MainWindow::updateTable() {
  theList->clearContents();
  buildTable(numberOnList);
  Student * current = stack.head;
  int row = 0;
  while (current != nullptr) {
    theList->setItem(row, 0, new QTableWidgetItem(current->name));
    theList->setItem(row, 1, new QTableWidgetItem(current->Class));
    theList->setItem(row, 2, new QTableWidgetItem(current->signInTime.toString("hh:mm a")));
    current = current->next;
    ++row;
  }
}















