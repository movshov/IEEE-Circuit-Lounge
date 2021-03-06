#include "signinwindow.h"

SignInWindow::SignInWindow(QWidget * parent) : QWidget(parent){
    font.setPointSize(30);  //set font to size 32.
    font.setBold(true); //set font to be bolded.

    buttonFont.setPointSize(20);    //set font of button to be 20.
    buttonFont.setBold(true);   //set button font to be bolded.

    loginText = new QLabel("Welcome! Please scan your PSU ID barcode or type in your ODIN ID below", parent);
    loginText->move(445, 425);
    loginText->resize(1300, 50);
    loginText->setFont(buttonFont);
    loginText->hide();

    loginButton = new QPushButton("Sign-In", parent);
    loginButton->move(900, 500);
    loginButton->resize(200, 80);
    loginButton->hide();
    loginButton->setFont(buttonFont);

    loginDialog = new QLineEdit(parent);
    loginDialog->move(670, 500);
    loginDialog->resize(200, 80);
    loginDialog->setPlaceholderText("ODIN ID");
    loginDialog->setMaxLength(9);
    loginDialog->setValidator(new QRegExpValidator(QRegExp("[0-9]{9}")));
    loginDialog->hide();

    logo1 = new QLabel("<img src='D:/QT5/Projects/Circuit_Lounge_Login/PSU_Logo.jpg' />",parent);
    logo1->resize(700,500);
    logo1->move(200,550);

    logo2 = new QLabel("<img src='D:/QT5/Projects/Circuit_Lounge_Login/IEEE.jpg' />",parent);
    logo2->resize(800,400);
    logo2->move(1200,600);

    title = new QLabel("IEEE Tutoring", parent);
    title->setFont(font);
    title->move(580, 0);
    title->resize(600, 150);
  }

void SignInWindow::openWindow(){
    logo1->show();
    logo2->show();
    loginText->show();
    loginButton->show();
    loginDialog->show();
    loginDialog->setFocus();
}

void SignInWindow::closeWindow() {
    logo1->hide();
    logo2->hide();
    loginText->hide();
    loginButton->hide();
    loginDialog->hide();
    loginDialog->clear();

}






