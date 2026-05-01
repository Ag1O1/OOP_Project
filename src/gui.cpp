#include "qboxlayout.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <gui.h>
#include <qresource.h>

GUI::GUI(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("Login");
  setFixedSize(300, 200);

  QWidget *central = new QWidget(this);
  setCentralWidget(central);

  mainLayout = new QVBoxLayout(central);

  showLogin();
}

void GUI::showLogin() {
  QLabel *label = new QLabel("Login menu");
  label->setAlignment(Qt::AlignCenter);
  mainLayout->addWidget(label);

  QHBoxLayout *Username_layout = new QHBoxLayout();
  QLineEdit *Username = new QLineEdit();
  QLabel *Username_label = new QLabel("Username");
  Username_layout->addWidget(Username_label);
  Username_layout->addWidget(Username);
  mainLayout->addLayout(Username_layout);

  QHBoxLayout *Password_layout = new QHBoxLayout();
  QLabel *Password_label = new QLabel("Password");
  QLineEdit *Password = new QLineEdit();
  QPushButton *Visibility = new QPushButton();
  Visibility->setIcon(QIcon(":/assets/show.png"));
  QIcon icon(":/assets/show.png");

  Password->setEchoMode(QLineEdit::Password);

  connect(Visibility, &QPushButton::clicked, this, [Password, Visibility]() {
    if (Password->echoMode() == QLineEdit::Password) {

      Password->setEchoMode(QLineEdit::Normal);
      Visibility->setIcon(QIcon(":/assets/hide.png"));
    } else if (Password->echoMode() == QLineEdit::Normal) {

      Password->setEchoMode(QLineEdit::Password);
      Visibility->setIcon(QIcon(":/assets/show.png"));
    }
  });

  Password_layout->addWidget(Password_label);
  Password_layout->addWidget(Password);
  Password_layout->addWidget(Visibility);

  mainLayout->addLayout(Password_layout);

  QPushButton *login_button = new QPushButton("Login");
  mainLayout->addWidget(login_button);

  QPushButton *register_button = new QPushButton("Register");
  mainLayout->addWidget(register_button);

  //  connect(register_button, &QPushButton::clicked, this,
  //        [label, Username]() { label->setText("Name: " + Username->text());
  //        });
}

void GUI::clearLayout() {
  QLayoutItem *item;
  while ((item = mainLayout->takeAt(0)) != nullptr) {
    delete item->widget();
    delete item;
  }
}
