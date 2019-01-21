#include "confirmwindow.h"

ConfirmWindow::ConfirmWindow(QWidget * parent) : QWidget (parent){
    textFont.setPointSize(24);

    buttonFont.setPointSize(24);
    buttonFont.setBold(true);

    text = new QLabel("Please confirm that the following information is correct", parent);
    text->move(100, 100);
    text->resize(1200, 300);
    text->hide();
    text->setFont(textFont);

    name = new QLabel("Name:", parent);
    name->resize(300, 50);
    name->move(300, 300);
    name->setFont(textFont);
    name->hide();

    nameOutput = new QLabel(parent);
    nameOutput->resize(1000, 50);
    nameOutput->move(500, 300);
    nameOutput->setFont(textFont);
    nameOutput->hide();

    Class = new QLabel("Class:", parent);
    Class->resize(300, 50);
    Class->move(300, 375);
    Class->setFont(textFont);
    Class->hide();

    ClassOutput = new QLabel(parent);
    ClassOutput->resize(1000, 50);
    ClassOutput->move(500, 375);
    ClassOutput->setFont(textFont);
    ClassOutput->hide();

    confirmButton = new QPushButton("Confirm", parent);
    confirmButton->resize(300, 75);
    confirmButton->move(300, 600);
    confirmButton->setFont(buttonFont);
    confirmButton->hide();

    cancelButton = new QPushButton("Start Over", parent);
    cancelButton->resize(300, 75);
    cancelButton->move(800, 600);
    cancelButton->setFont(buttonFont);
    cancelButton->hide();
  }

  void ConfirmWindow::openWindow() {
    text->show();
    name->show();
    Class->show();
    nameOutput->show();
    ClassOutput->show();
    confirmButton->show();
    cancelButton->show();
  }

  void ConfirmWindow::closeWindow() {
    text->hide();
    name->hide();
    Class->hide();
    nameOutput->hide();
    ClassOutput->hide();
    confirmButton->hide();
    cancelButton->hide();
}

