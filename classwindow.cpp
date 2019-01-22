#include "classwindow.h"

ClassWindow::ClassWindow(QWidget * parent) : QWidget (parent){
    textFont.setPointSize(24);

    buttonFont.setPointSize(24);
    buttonFont.setBold(true);

    text = new QLabel("Please select one of the supported classes below\n", parent);

    text->move(100, 100);
    text->resize(1200, 300);
    text->hide();
    text->setFont(textFont);

    ECE101 = new QPushButton("ECE 101", parent);
    ECE101->move(50, 400);
    ECE101->resize(200, 75);
    ECE101->setFont(buttonFont);
    ECE101->hide();

    ECE102 = new QPushButton("ECE 102", parent);
    ECE102->move(50, 500);
    ECE102->resize(200, 75);
    ECE102->setFont(buttonFont);
    ECE102->hide();

    ECE103 = new QPushButton("ECE 103", parent);
    ECE103->move(50, 600);
    ECE103->resize(200, 75);
    ECE103->setFont(buttonFont);
    ECE103->hide();

    ECE171 = new QPushButton("ECE 171", parent);
    ECE171->move(50, 700);
    ECE171->resize(200, 75);
    ECE171->setFont(buttonFont);
    ECE171->hide();

    ECE172 = new QPushButton("ECE 172", parent);
    ECE172->move(50, 800);
    ECE172->resize(200, 75);
    ECE172->setFont(buttonFont);
    ECE172->hide();

    ECE211 = new QPushButton("ECE 211", parent);
    ECE211->move(275, 400);
    ECE211->resize(200, 75);
    ECE211->setFont(buttonFont);
    ECE211->hide();

    ECE212 = new QPushButton("ECE 212", parent);
    ECE212->move(275, 500);
    ECE212->resize(200, 75);
    ECE212->setFont(buttonFont);
    ECE212->hide();

    ECE221 = new QPushButton("ECE 221", parent);
    ECE221->move(275, 600);
    ECE221->resize(200, 75);
    ECE221->setFont(buttonFont);
    ECE221->hide();

    ECE222 = new QPushButton("ECE 222", parent);
    ECE222->move(275, 700);
    ECE222->resize(200, 75);
    ECE222->setFont(buttonFont);
    ECE222->hide();

    ECE223 = new QPushButton("ECE 223", parent);
    ECE223->move(275, 800);
    ECE223->resize(200, 75);
    ECE223->setFont(buttonFont);
    ECE223->hide();

    ECE241 = new QPushButton("ECE 241", parent);
    ECE241->move(500, 400);
    ECE241->resize(200, 75);
    ECE241->setFont(buttonFont);
    ECE241->hide();

    ECE315 = new QPushButton("ECE 315", parent);
    ECE315->move(500, 500);
    ECE315->resize(200, 75);
    ECE315->setFont(buttonFont);
    ECE315->hide();

    ECE316 = new QPushButton("ECE 316", parent);
    ECE316->move(500, 600);
    ECE316->resize(200, 75);
    ECE316->setFont(buttonFont);
    ECE316->hide();

    ECE317 = new QPushButton("ECE 317", parent);
    ECE317->move(500, 700);
    ECE317->resize(200, 75);
    ECE317->setFont(buttonFont);
    ECE317->hide();

    ECE321 = new QPushButton("ECE 321", parent);
    ECE321->move(500, 800);
    ECE321->resize(200, 75);
    ECE321->setFont(buttonFont);
    ECE321->hide();

    ECE322 = new QPushButton("ECE 322", parent);
    ECE322->move(725, 400);
    ECE322->resize(200, 75);
    ECE322->setFont(buttonFont);
    ECE322->hide();

    ECE323 = new QPushButton("ECE 323", parent);
    ECE323->move(725, 500);
    ECE323->resize(200, 75);
    ECE323->setFont(buttonFont);
    ECE323->hide();

    ECE331 = new QPushButton("ECE 331", parent);
    ECE331->move(725, 600);
    ECE331->resize(200, 75);
    ECE331->setFont(buttonFont);
    ECE331->hide();

    ECE332 = new QPushButton("ECE 332", parent);
    ECE332->move(725, 700);
    ECE332->resize(200, 75);
    ECE332->setFont(buttonFont);
    ECE332->hide();

    ECE341 = new QPushButton("ECE 341", parent);
    ECE341->move(725, 800);
    ECE341->resize(200, 75);
    ECE341->setFont(buttonFont);
    ECE341->hide();

    ECE347 = new QPushButton("ECE 347", parent);
    ECE347->move(950, 400);
    ECE347->resize(200, 75);
    ECE347->setFont(buttonFont);
    ECE347->hide();

    ECE348 = new QPushButton("ECE 348", parent);
    ECE348->move(950, 500);
    ECE348->resize(200, 75);
    ECE348->setFont(buttonFont);
    ECE348->hide();

    ECE351 = new QPushButton("ECE 351", parent);
    ECE351->move(950, 600);
    ECE351->resize(200, 75);
    ECE351->setFont(buttonFont);
    ECE351->hide();

    ECE361 = new QPushButton("ECE 361", parent);
    ECE361->move(950, 700);
    ECE361->resize(200, 75);
    ECE361->setFont(buttonFont);
    ECE361->hide();

    ECE362 = new QPushButton("ECE 362", parent);
    ECE362->move(950, 800);
    ECE362->resize(200, 75);
    ECE362->setFont(buttonFont);
    ECE362->hide();

    ECE371 = new QPushButton("ECE 371", parent);
    ECE371->move(1175, 400);
    ECE371->resize(200, 75);
    ECE371->setFont(buttonFont);
    ECE371->hide();

    ECE372 = new QPushButton("ECE 372", parent);
    ECE372->move(1175, 500);
    ECE372->resize(200, 75);
    ECE372->setFont(buttonFont);
    ECE372->hide();

    ECE373 = new QPushButton("ECE 373", parent);
    ECE373->move(1175, 600);
    ECE373->resize(200, 75);
    ECE373->setFont(buttonFont);
    ECE373->hide();

    ECE383 = new QPushButton("ECE 383", parent);
    ECE383->move(1175, 700);
    ECE383->resize(200, 75);
    ECE383->setFont(buttonFont);
    ECE383->hide();

    other = new QPushButton("Other", parent);
    other->move(1175, 800);
    other->resize(200, 75);
    other->setFont(buttonFont);
    other->hide();

    cancelButton = new QPushButton("Start Over", parent);
    cancelButton->move(1375, 900);
    cancelButton->resize(200, 75);
    cancelButton->setFont(buttonFont);
    cancelButton->hide();
  }

  void ClassWindow::OpenWindow() {
    text->show();
    ECE101->show();
    ECE102->show();
    ECE103->show();
    ECE171->show();
    ECE172->show();
    ECE211->show();
    ECE212->show();
    ECE221->show();
    ECE222->show();
    ECE223->show();
    ECE241->show();
    ECE315->show();
    ECE316->show();
    ECE317->show();
    ECE321->show();
    ECE322->show();
    ECE323->show();
    ECE331->show();
    ECE332->show();
    ECE341->show();
    ECE347->show();
    ECE348->show();
    ECE351->show();
    ECE361->show();
    ECE362->show();
    ECE371->show();
    ECE372->show();
    ECE373->show();
    ECE383->show();
    other->show();
    cancelButton->show();
  }

  void ClassWindow::CloseWindow() {
    text->hide();
    ECE101->hide();
    ECE102->hide();
    ECE103->hide();
    ECE171->hide();
    ECE172->hide();
    ECE211->hide();
    ECE212->hide();
    ECE221->hide();
    ECE222->hide();
    ECE223->hide();
    ECE241->hide();
    ECE315->hide();
    ECE316->hide();
    ECE317->hide();
    ECE321->hide();
    ECE322->hide();
    ECE323->hide();
    ECE331->hide();
    ECE332->hide();
    ECE341->hide();
    ECE347->hide();
    ECE348->hide();
    ECE351->hide();
    ECE361->hide();
    ECE362->hide();
    ECE371->hide();
    ECE372->hide();
    ECE373->hide();
    ECE383->hide();
    other->hide();
    cancelButton->hide();
}
