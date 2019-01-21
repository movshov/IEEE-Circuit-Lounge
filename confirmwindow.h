#ifndef CONFIRMWINDOW_H
#define CONFIRMWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class ConfirmWindow : public QWidget{
    Q_OBJECT

public:
    QPushButton * confirmButton, * cancelButton;
    QLabel * text, * name, * Class, *nameOutput, * ClassOutput;
    QFont textFont, buttonFont;

    ConfirmWindow(QWidget * parent = 0);
    void openWindow();
    void closeWindow();
};

#endif // CONFIRMWINDOW_H
