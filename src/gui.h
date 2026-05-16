#pragma once

#include "inventory.h"
#include "userManager.h"
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QTableWidget>
#include <QVBoxLayout>

class GUI : public QMainWindow {
  Q_OBJECT

public:
  GUI(QWidget *parent = nullptr);

private slots:
  void showLogin();
  void showAdminMenu();
  void showUserMenu();
  void displayInventory(const std::vector<Product> &products);

private:
  struct CartItem {
    int productId;
    std::string name;
    double price;
    int quantity;
  };

  Inventory inventory;
  UserManager userManager;
  QVBoxLayout *mainLayout;
  QTableWidget *table;
  QStackedWidget *stackedWidget;
  QTableWidget *userTable;
  QTableWidget *cartTable;
  QLabel *totalLabel;
  std::vector<CartItem> cart;

  void clearLayout();
  void showRegisterDialog();
  QString getThemeIcon(const QString &lightIcon, const QString &darkIcon);

  void refreshTable();
  void saveInventoryChanges();
  void addNewRow();
  void deleteSelectedRow();

  void createUserInventoryView();
  void createCartView();
  void refreshUserInventory();
  void refreshCartView();
  void showQuantityDialog(int productId);
  void checkout();
};
