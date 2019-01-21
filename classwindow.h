#ifndef CLASSWINDOW_H
#define CLASSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class ClassWindow : public QWidget{
    Q_OBJECT

public:
    QPushButton * cancelButton, * ECE101, * ECE102, * ECE103,
    * ECE171, * ECE172, * ECE211, * ECE212, * ECE221, * ECE222,
    * ECE223, * ECE241, * ECE315, * ECE316, * ECE317, * ECE321,
    * ECE322, * ECE323, * ECE331, * ECE332, * ECE341, * ECE347,
    * ECE348, * ECE351, * ECE361, * ECE362, * ECE371, * ECE372,
    * ECE373, * ECE383, * other;
    QLabel * text;
    QFont textFont, buttonFont;

    ClassWindow(QWidget * parent = 0);
    void OpenWindow();
    void CloseWindow();
};

#endif // CLASSWINDOW_H
