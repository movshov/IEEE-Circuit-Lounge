#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QRegExpValidator>


class SignInWindow : public QWidget {
    Q_OBJECT

public:
    QFont font, buttonFont;
    QPushButton * loginButton, * noIdButton;
    QLineEdit * loginDialog;
    QLabel * logo1, * logo2, * title, * loginText;

    SignInWindow(QWidget * parnent = 0);
    void openWindow();
    void closeWindow();
};

#endif // SIGNINWINDOW_H
