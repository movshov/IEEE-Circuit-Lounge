#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QRegExpValidator>

class RegisterWindow : public QWidget{
    Q_OBJECT

    static const int startXPos = 300;
    static const int startYPos = 100;

public:
    QPushButton * regButton, * cancelButton;
    QLineEdit * nameDialog;
    QLabel * nameLabel, * text;
    QFont font;

    RegisterWindow(QWidget * parent = 0);
    void openWindow();
    void closeWindow();
};

#endif // REGISTERWINDOW_H
