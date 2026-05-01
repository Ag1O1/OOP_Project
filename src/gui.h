#pragma once
#include "qlabel.h"
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

class GUI : public QMainWindow {
  Q_OBJECT

public:
  GUI(QWidget *parent = nullptr);

private slots:
  void showLogin();
  // void showCustomerMenu();
  // void showAdminMenu();

private:
  QVBoxLayout *mainLayout;
  QLineEdit *usernameEdit;
  QLineEdit *passwordEdit;
  QPushButton *loginButton;
  QPushButton *cancelButton;
  QLabel *errorLabel;

  void clearLayout();
  // void setupLoginScreen();
};
