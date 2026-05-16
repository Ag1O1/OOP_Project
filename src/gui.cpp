#include "Product.h"
#include "loadFromFile.h"
#include "qicon.h"
#include "saveToFile.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <gui.h>
#include <qboxlayout.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qresource.h>

GUI::GUI(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("Login");
  setFixedSize(600, 350);
  loadFromFile::execute(inventory.getAllStock());

  QWidget *central = new QWidget(this);
  setCentralWidget(central);

  mainLayout = new QVBoxLayout(central);

  showLogin();
}

void GUI::showLogin() {
  clearLayout();

  QLabel *titleLabel = new QLabel("Inventory Management System");
  titleLabel->setAlignment(Qt::AlignCenter);
  QFont titleFont = titleLabel->font();
  titleFont.setPointSize(14);
  titleFont.setBold(true);
  titleLabel->setFont(titleFont);
  mainLayout->addWidget(titleLabel);

  mainLayout->addStretch();

  QHBoxLayout *Username_layout = new QHBoxLayout();
  QLineEdit *Username = new QLineEdit();
  Username->setPlaceholderText("Enter username");
  QLabel *Username_label = new QLabel("Username:");
  Username_layout->addWidget(Username_label);
  Username_layout->addWidget(Username);
  mainLayout->addLayout(Username_layout);

  QHBoxLayout *Password_layout = new QHBoxLayout();
  QLineEdit *Password = new QLineEdit();
  Password->setPlaceholderText("Enter password");
  QLabel *Password_label = new QLabel("Password:");
  QPushButton *Visibility = new QPushButton();
  QString iconPath =
      getThemeIcon(":/assets/hide-dark.png", ":/assets/hide-light.png");
  Visibility->setIcon(QIcon(iconPath));
  Visibility->setFixedSize(25, 25);
  Password->setEchoMode(QLineEdit::Password);

  connect(
      Visibility, &QPushButton::clicked, this, [Password, Visibility, this]() {
        if (Password->echoMode() == QLineEdit::Password) {
          Password->setEchoMode(QLineEdit::Normal);
          QString iconPath =
              getThemeIcon(":/assets/show-dark.png", ":/assets/show-light.png");
          Visibility->setIcon(QIcon(iconPath));
        } else {
          Password->setEchoMode(QLineEdit::Password);
          QString iconPath =
              getThemeIcon(":/assets/hide-dark.png", ":/assets/hide-light.png");
          Visibility->setIcon(QIcon(iconPath));
        }
      });

  Password_layout->addWidget(Password_label);
  Password_layout->addWidget(Password);
  Password_layout->addWidget(Visibility);
  mainLayout->addLayout(Password_layout);

  mainLayout->addStretch();

  QPushButton *login_button = new QPushButton("Login");
  QPushButton *register_button = new QPushButton("Register");

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(login_button);
  buttonLayout->addWidget(register_button);
  mainLayout->addLayout(buttonLayout);

  connect(login_button, &QPushButton::clicked, this,
          [this, Username, Password]() {
            std::string username = Username->text().toStdString();
            std::string password = Password->text().toStdString();

            User *user = userManager.login(username, password);
            if (user) {
              std::cout << "Getting role..." << std::endl;
              std::string role = user->getRole();
              std::cout << "Role is: " << role << std::endl;

              if (role == "admin") {
                std::cout << "Showing admin menu" << std::endl;
                showAdminMenu();
              } else {
                std::cout << "Showing user menu" << std::endl;
                showUserMenu();
              }
            } else {
              QMessageBox::warning(this, "Login Failed",
                                   "Invalid username or password");
            }

            Username->clear();
            Password->clear();
          });

  connect(register_button, &QPushButton::clicked, this,
          [this]() { showRegisterDialog(); });
}
void GUI::showRegisterDialog() {
  QDialog dialog(this);
  dialog.setWindowTitle("Register New Account");
  dialog.setMinimumSize(350, 300);
  dialog.setModal(true);

  QVBoxLayout *layout = new QVBoxLayout(&dialog);

  QLabel *titleLabel = new QLabel("Create Account");
  titleLabel->setAlignment(Qt::AlignCenter);
  QFont titleFont = titleLabel->font();
  titleFont.setPointSize(12);
  titleFont.setBold(true);
  titleLabel->setFont(titleFont);
  layout->addWidget(titleLabel);

  layout->addSpacing(20);

  QHBoxLayout *nameLayout = new QHBoxLayout();
  QLabel *nameLabel = new QLabel("Username:");
  QLineEdit *nameEdit = new QLineEdit();
  nameEdit->setPlaceholderText("Choose a username");
  nameLayout->addWidget(nameLabel);
  nameLayout->addWidget(nameEdit);
  layout->addLayout(nameLayout);

  QHBoxLayout *passLayout = new QHBoxLayout();
  QLabel *passLabel = new QLabel("Password:");
  QLineEdit *passEdit = new QLineEdit();
  passEdit->setEchoMode(QLineEdit::Password);
  passEdit->setPlaceholderText("Choose a password");
  passLayout->addWidget(passLabel);
  passLayout->addWidget(passEdit);
  layout->addLayout(passLayout);

  QHBoxLayout *confirmLayout = new QHBoxLayout();
  QLabel *confirmLabel = new QLabel("Confirm:");
  QLineEdit *confirmEdit = new QLineEdit();
  confirmEdit->setEchoMode(QLineEdit::Password);
  confirmEdit->setPlaceholderText("Confirm password");
  confirmLayout->addWidget(confirmLabel);
  confirmLayout->addWidget(confirmEdit);
  layout->addLayout(confirmLayout);

  QHBoxLayout *roleLayout = new QHBoxLayout();
  QLabel *roleLabel = new QLabel("Account Type:");
  QComboBox *roleCombo = new QComboBox();
  roleCombo->addItem("customer");
  roleCombo->addItem("admin");
  roleLayout->addWidget(roleLabel);
  roleLayout->addWidget(roleCombo);
  layout->addLayout(roleLayout);

  layout->addStretch();

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  QPushButton *registerBtn = new QPushButton("Register");
  QPushButton *cancelBtn = new QPushButton("Cancel");
  buttonLayout->addWidget(registerBtn);
  buttonLayout->addWidget(cancelBtn);
  layout->addLayout(buttonLayout);

  connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

  connect(registerBtn, &QPushButton::clicked, this,
          [this, &dialog, nameEdit, passEdit, confirmEdit, roleCombo]() {
            QString username = nameEdit->text();
            QString password = passEdit->text();
            QString confirm = confirmEdit->text();
            QString role = roleCombo->currentText();

            if (username.isEmpty() || password.isEmpty()) {
              QMessageBox::warning(&dialog, "Error",
                                   "Username and password cannot be empty");
              return;
            }

            if (password != confirm) {
              QMessageBox::warning(&dialog, "Error", "Passwords do not match");
              return;
            }

            if (password.length() < 3) {
              QMessageBox::warning(&dialog, "Error",
                                   "Password must be at least 3 characters");
              return;
            }

            if (userManager.registerUser(username.toStdString(),
                                         password.toStdString(),
                                         role.toStdString())) {
              QMessageBox::information(
                  &dialog, "Success",
                  "Account created successfully!\nYou can now login.");
              dialog.accept();
            } else {
              QMessageBox::warning(
                  &dialog, "Error",
                  "Username already exists. Please choose another.");
            }
          });

  dialog.exec();
}
void GUI::showAdminMenu() {
  clearLayout();

  QHBoxLayout *top = new QHBoxLayout();
  QHBoxLayout *toolbar = new QHBoxLayout();
  QLabel *topLabel =
      new QLabel("Welcome " + QString::fromStdString(
                                  userManager.getCurrentUser()->getUsername()));
  QPushButton *addButton = new QPushButton("Add Product");
  QPushButton *deleteButton = new QPushButton("Delete Selected");
  QPushButton *saveButton = new QPushButton("Save Changes");
  QPushButton *logoutButton = new QPushButton("Logout");

  top->addWidget(topLabel);
  top->addStretch();
  top->addWidget(logoutButton);
  mainLayout->addLayout(top);
  toolbar->addWidget(addButton);
  toolbar->addWidget(deleteButton);
  toolbar->addWidget(saveButton);
  toolbar->addStretch();

  mainLayout->addLayout(toolbar);

  table = new QTableWidget();
  table->setColumnCount(4);
  table->verticalHeader()->setVisible(false);
  table->setHorizontalHeaderLabels({"ID", "Name", "Price", "Quantity"});
  table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  table->setAlternatingRowColors(true);
  table->setSelectionBehavior(QTableWidget::SelectRows);
  table->setEditTriggers(QTableWidget::DoubleClicked |
                         QTableWidget::EditKeyPressed);

  refreshTable();

  mainLayout->addWidget(table);

  connect(addButton, &QPushButton::clicked, this, [this]() { addNewRow(); });

  connect(deleteButton, &QPushButton::clicked, this,
          [this]() { deleteSelectedRow(); });

  connect(saveButton, &QPushButton::clicked, this, [this]() {
    saveInventoryChanges();
    QMessageBox::information(this, "Success", "Inventory saved successfully!");
  });

  connect(logoutButton, &QPushButton::clicked, this, [this]() { showLogin(); });
}

void GUI::showUserMenu() {
  clearLayout();

  QHBoxLayout *top = new QHBoxLayout();
  QLabel *topLabel =
      new QLabel("Welcome " + QString::fromStdString(
                                  userManager.getCurrentUser()->getUsername()));
  QPushButton *logoutButton = new QPushButton("Logout");
  top->addWidget(topLabel);
  top->addStretch();
  top->addWidget(logoutButton);
  mainLayout->addLayout(top);

  QHBoxLayout *toolbar = new QHBoxLayout();
  QPushButton *viewInventoryBtn = new QPushButton("View Inventory");
  QPushButton *viewCartBtn = new QPushButton("View Cart");
  QPushButton *checkoutBtn = new QPushButton("Checkout");
  toolbar->addWidget(viewInventoryBtn);
  toolbar->addWidget(viewCartBtn);
  toolbar->addWidget(checkoutBtn);
  toolbar->addStretch();
  mainLayout->addLayout(toolbar);

  stackedWidget = new QStackedWidget();
  mainLayout->addWidget(stackedWidget);

  createUserInventoryView();
  createCartView();

  stackedWidget->setCurrentIndex(0);

  connect(viewInventoryBtn, &QPushButton::clicked, this, [this]() {
    stackedWidget->setCurrentIndex(0);
    refreshUserInventory();
  });

  connect(viewCartBtn, &QPushButton::clicked, this, [this]() {
    stackedWidget->setCurrentIndex(1);
    refreshCartView();
  });

  connect(checkoutBtn, &QPushButton::clicked, this, [this]() { checkout(); });

  connect(logoutButton, &QPushButton::clicked, this, [this]() {
    saveToFile::execute(inventory.getAllStock());
    showLogin();
  });
}

void GUI::createUserInventoryView() {
  QWidget *inventoryView = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(inventoryView);

  QHBoxLayout *searchLayout = new QHBoxLayout();
  QLabel *searchLabel = new QLabel("Search:");
  QLineEdit *searchBox = new QLineEdit();
  searchBox->setPlaceholderText("Search by name or ID...");
  searchLayout->addWidget(searchLabel);
  searchLayout->addWidget(searchBox);

  layout->addLayout(searchLayout);

  userTable = new QTableWidget();
  userTable->setColumnCount(5);
  userTable->verticalHeader()->setVisible(false);
  userTable->setHorizontalHeaderLabels(
      {"ID", "Name", "Price", "Quantity", "Action"});
  userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  userTable->setAlternatingRowColors(true);
  userTable->setEditTriggers(QTableWidget::NoEditTriggers);

  layout->addWidget(userTable);

  connect(searchBox, &QLineEdit::textChanged, this, [this, searchBox]() {
    QString searchText = searchBox->text();
    const std::vector<Product> &products = inventory.getAllStock();
    userTable->setRowCount(0);

    for (int i = 0; i < (int)products.size(); i++) {
      const Product &product = products[i];
      QString idStr = QString::number(product.getId());
      QString nameStr = QString::fromStdString(product.getName());

      if (idStr.contains(searchText, Qt::CaseInsensitive) ||
          nameStr.contains(searchText, Qt::CaseInsensitive)) {
        int row = userTable->rowCount();
        userTable->insertRow(row);

        userTable->setItem(row, 0, new QTableWidgetItem(idStr));
        userTable->setItem(row, 1, new QTableWidgetItem(nameStr));

        QString priceStr = QString("$%1").arg(product.getPrice(), 0, 'f', 2);
        userTable->setItem(row, 2, new QTableWidgetItem(priceStr));
        userTable->setItem(
            row, 3,
            new QTableWidgetItem(QString::number(product.getQuantity())));

        QPushButton *addBtn = new QPushButton("Add to Cart");
        userTable->setCellWidget(row, 4, addBtn);

        int productId = product.getId();
        connect(addBtn, &QPushButton::clicked, this,
                [this, productId]() { showQuantityDialog(productId); });

        if (product.getQuantity() < 10) {
          for (int col = 0; col < 4; col++) {
            userTable->item(row, col)->setBackground(QColor(255, 255, 150));
          }
        }
      }
    }
  });

  searchBox->clear();
  stackedWidget->addWidget(inventoryView);
}

void GUI::refreshUserInventory() {
  const std::vector<Product> &products = inventory.getAllStock();
  userTable->setRowCount(0);

  for (int i = 0; i < (int)products.size(); i++) {
    const Product &product = products[i];
    int row = userTable->rowCount();
    userTable->insertRow(row);

    userTable->setItem(row, 0,
                       new QTableWidgetItem(QString::number(product.getId())));
    userTable->setItem(
        row, 1,
        new QTableWidgetItem(QString::fromStdString(product.getName())));

    QString priceStr = QString("$%1").arg(product.getPrice(), 0, 'f', 2);
    userTable->setItem(row, 2, new QTableWidgetItem(priceStr));
    userTable->setItem(
        row, 3, new QTableWidgetItem(QString::number(product.getQuantity())));

    QPushButton *addBtn = new QPushButton("Add to Cart");
    userTable->setCellWidget(row, 4, addBtn);

    int productId = product.getId();
    connect(addBtn, &QPushButton::clicked, this,
            [this, productId]() { showQuantityDialog(productId); });

    if (product.getQuantity() < 10) {
      for (int col = 0; col < 4; col++) {
        userTable->item(row, col)->setBackground(QColor(255, 255, 150));
      }
    }
  }
}

void GUI::showQuantityDialog(int productId) {
  const Product &product = inventory.getProductRef(productId);

  if (product.getQuantity() <= 0) {
    QMessageBox::warning(this, "Out of Stock", "This product is out of stock!");
    return;
  }

  QDialog dialog(this);
  dialog.setWindowTitle("Add to Cart");
  dialog.setMinimumSize(300, 200);

  QVBoxLayout *layout = new QVBoxLayout(&dialog);

  QLabel *infoLabel =
      new QLabel(QString("Product: %1\nPrice: $%2\nAvailable: %3")
                     .arg(QString::fromStdString(product.getName()))
                     .arg(product.getPrice(), 0, 'f', 2)
                     .arg(product.getQuantity()));
  infoLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(infoLabel);

  QHBoxLayout *quantityLayout = new QHBoxLayout();
  QLabel *qtyLabel = new QLabel("Quantity:");
  QLineEdit *quantityEdit = new QLineEdit();
  quantityEdit->setPlaceholderText("Enter amount...");
  quantityLayout->addWidget(qtyLabel);
  quantityLayout->addWidget(quantityEdit);
  layout->addLayout(quantityLayout);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  QPushButton *addButton = new QPushButton("Add");
  QPushButton *cancelButton = new QPushButton("Cancel");
  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(cancelButton);
  layout->addLayout(buttonLayout);

  connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

  connect(
      addButton, &QPushButton::clicked, this,
      [this, &dialog, quantityEdit, productId, &product]() {
        if (quantityEdit->text().isEmpty()) {
          QMessageBox::warning(&dialog, "Error", "Please enter a quantity");
          return;
        }

        bool ok;
        int quantity = quantityEdit->text().toInt(&ok);

        if (!ok || quantity <= 0) {
          QMessageBox::warning(&dialog, "Error", "Please enter a valid number");
          return;
        }

        if (quantity > product.getQuantity()) {
          QMessageBox::warning(
              &dialog, "Error",
              QString("Only %1 items available").arg(product.getQuantity()));
          return;
        }

        bool found = false;
        for (int i = 0; i < (int)cart.size(); i++) {
          if (cart[i].productId == productId) {
            cart[i].quantity += quantity;
            found = true;
            break;
          }
        }

        if (!found) {
          CartItem newItem;
          newItem.productId = productId;
          newItem.name = product.getName();
          newItem.price = product.getPrice();
          newItem.quantity = quantity;
          cart.push_back(newItem);
        }

        QMessageBox::information(&dialog, "Success", "Item added to cart!");
        dialog.accept();
      });

  dialog.exec();
}

void GUI::createCartView() {
  QWidget *cartView = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(cartView);

  cartTable = new QTableWidget();
  cartTable->setColumnCount(5);
  cartTable->verticalHeader()->setVisible(false);
  cartTable->setHorizontalHeaderLabels(
      {"ID", "Name", "Price", "Quantity", "Subtotal"});
  cartTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  cartTable->setAlternatingRowColors(true);
  cartTable->setEditTriggers(QTableWidget::NoEditTriggers);

  layout->addWidget(cartTable);

  QHBoxLayout *bottomLayout = new QHBoxLayout();
  totalLabel = new QLabel("Total: $0.00");
  totalLabel->setAlignment(Qt::AlignRight);
  QPushButton *clearCartBtn = new QPushButton("Clear Cart");
  bottomLayout->addWidget(clearCartBtn);
  bottomLayout->addStretch();
  bottomLayout->addWidget(totalLabel);

  layout->addLayout(bottomLayout);

  connect(clearCartBtn, &QPushButton::clicked, this, [this]() {
    cart.clear();
    refreshCartView();
  });

  stackedWidget->addWidget(cartView);
}

void GUI::refreshCartView() {
  cartTable->setRowCount(cart.size());
  double total = 0;

  for (int i = 0; i < (int)cart.size(); i++) {
    const CartItem &item = cart[i];
    double subtotal = item.price * item.quantity;
    total += subtotal;

    cartTable->setItem(i, 0,
                       new QTableWidgetItem(QString::number(item.productId)));
    cartTable->setItem(i, 1,
                       new QTableWidgetItem(QString::fromStdString(item.name)));
    cartTable->setItem(
        i, 2, new QTableWidgetItem(QString("$%1").arg(item.price, 0, 'f', 2)));
    cartTable->setItem(i, 3,
                       new QTableWidgetItem(QString::number(item.quantity)));
    cartTable->setItem(
        i, 4, new QTableWidgetItem(QString("$%1").arg(subtotal, 0, 'f', 2)));
  }

  totalLabel->setText(QString("Total: $%1").arg(total, 0, 'f', 2));
}

void GUI::checkout() {
  if (cart.empty()) {
    QMessageBox::warning(this, "Cart Empty", "Your cart is empty!");
    return;
  }

  QDialog dialog(this);
  dialog.setWindowTitle("Receipt");
  dialog.setMinimumSize(500, 400);

  QVBoxLayout *layout = new QVBoxLayout(&dialog);

  QLabel *titleLabel = new QLabel("=== RECEIPT ===");
  titleLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(titleLabel);

  QTableWidget *receiptTable = new QTableWidget();
  receiptTable->setColumnCount(4);
  receiptTable->verticalHeader()->setVisible(false);
  receiptTable->setHorizontalHeaderLabels(
      {"Name", "Price", "Quantity", "Subtotal"});
  receiptTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  receiptTable->setEditTriggers(QTableWidget::NoEditTriggers);

  double total = 0;
  receiptTable->setRowCount(cart.size());

  for (int i = 0; i < (int)cart.size(); i++) {
    const CartItem &item = cart[i];
    double subtotal = item.price * item.quantity;
    total += subtotal;

    receiptTable->setItem(
        i, 0, new QTableWidgetItem(QString::fromStdString(item.name)));
    receiptTable->setItem(
        i, 1, new QTableWidgetItem(QString("$%1").arg(item.price, 0, 'f', 2)));
    receiptTable->setItem(i, 2,
                          new QTableWidgetItem(QString::number(item.quantity)));
    receiptTable->setItem(
        i, 3, new QTableWidgetItem(QString("$%1").arg(subtotal, 0, 'f', 2)));
  }

  layout->addWidget(receiptTable);

  QLabel *totalLabelReceipt =
      new QLabel(QString("TOTAL: $%1").arg(total, 0, 'f', 2));
  totalLabelReceipt->setAlignment(Qt::AlignCenter);
  layout->addWidget(totalLabelReceipt);

  for (int i = 0; i < (int)cart.size(); i++) {
    const CartItem &item = cart[i];
    int newQuantity =
        inventory.getProductRef(item.productId).getQuantity() - item.quantity;
    inventory.updateProduct(item.productId, item.name, item.price, newQuantity);
  }

  cart.clear();

  QPushButton *okButton = new QPushButton("OK");
  connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
  layout->addWidget(okButton);

  dialog.exec();

  refreshUserInventory();
  refreshCartView();

  QMessageBox::information(this, "Thank You", "Thank you for your purchase!");
}

void GUI::refreshTable() {
  const std::vector<Product> &products = inventory.getAllStock();
  table->setRowCount(products.size());

  for (int i = 0; i < (int)products.size(); i++) {
    const Product &product = products[i];

    QTableWidgetItem *idItem =
        new QTableWidgetItem(QString::number(product.getId()));
    idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
    table->setItem(i, 0, idItem);

    table->setItem(
        i, 1, new QTableWidgetItem(QString::fromStdString(product.getName())));

    QTableWidgetItem *priceItem =
        new QTableWidgetItem(QString::number(product.getPrice(), 'f', 2));
    table->setItem(i, 2, priceItem);

    QTableWidgetItem *qtyItem =
        new QTableWidgetItem(QString::number(product.getQuantity()));
    table->setItem(i, 3, qtyItem);

    if (inventory.checkLowStock(product.getId(), 10)) {
      for (int col = 0; col < 4; col++) {
        if (table->item(i, col)) {
          table->item(i, col)->setBackground(
              palette().color(QPalette::Highlight).darker(130));
          table->item(i, col)->setForeground(
              palette().color(QPalette::HighlightedText));
        }
      }
    }
  }
}

void GUI::saveInventoryChanges() {
  for (int row = 0; row < table->rowCount(); row++) {
    QTableWidgetItem *idItem = table->item(row, 0);
    QTableWidgetItem *nameItem = table->item(row, 1);
    QTableWidgetItem *priceItem = table->item(row, 2);
    QTableWidgetItem *qtyItem = table->item(row, 3);

    if (!idItem || !nameItem || !priceItem || !qtyItem) {
      continue;
    }

    int id = idItem->text().toInt();
    QString name = nameItem->text();
    double price = priceItem->text().toDouble();
    int quantity = qtyItem->text().toInt();

    if (name.isEmpty() || price < 0 || quantity < 0) {
      continue;
    }

    try {
      inventory.updateProduct(id, name.toStdString(), price, quantity);
    } catch (const std::string &msg) {
      continue;
    }
  }
}

void GUI::addNewRow() {
  int newId = 1;
  const std::vector<Product> &stock = inventory.getAllStock();
  for (int i = 0; i < (int)stock.size(); i++) {
    if (stock[i].getId() >= newId) {
      newId = stock[i].getId() + 1;
    }
  }

  int newRow = table->rowCount();
  table->insertRow(newRow);

  QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(newId));
  idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
  table->setItem(newRow, 0, idItem);

  table->setItem(newRow, 1, new QTableWidgetItem("New Product"));
  table->setItem(newRow, 2, new QTableWidgetItem("0.00"));
  table->setItem(newRow, 3, new QTableWidgetItem("0"));

  inventory.addProduct(Product(newId, "New Product", 0.00, 0));
}

void GUI::deleteSelectedRow() {
  int currentRow = table->currentRow();
  if (currentRow < 0) {
    QMessageBox::warning(this, "No Selection", "Please select a row to delete");
    return;
  }

  QTableWidgetItem *idItem = table->item(currentRow, 0);
  if (!idItem) {
    return;
  }

  int id = idItem->text().toInt();

  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Confirm Delete",
                                "Are you sure you want to delete this product?",
                                QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    try {
      inventory.removeProduct(id);
      table->removeRow(currentRow);
    } catch (const std::string &msg) {
      QMessageBox::warning(this, "Error", QString::fromStdString(msg));
    }
  }
}

void GUI::displayInventory(const std::vector<Product> &products) {
  QDialog dialog(this);
  dialog.setWindowTitle("Current Inventory");
  dialog.setMinimumSize(600, 400);

  QVBoxLayout *layout = new QVBoxLayout(&dialog);

  QTableWidget *viewTable = new QTableWidget(&dialog);
  viewTable->setColumnCount(4);
  viewTable->verticalHeader()->setVisible(false);
  viewTable->setHorizontalHeaderLabels({"ID", "Name", "Price", "Quantity"});

  viewTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  viewTable->setAlternatingRowColors(true);
  viewTable->setEditTriggers(QTableWidget::NoEditTriggers);
  viewTable->setSelectionBehavior(QTableWidget::SelectRows);

  viewTable->setRowCount(products.size());
  for (int i = 0; i < (int)products.size(); i++) {
    const Product &product = products[i];

    viewTable->setItem(i, 0,
                       new QTableWidgetItem(QString::number(product.getId())));

    viewTable->setItem(
        i, 1, new QTableWidgetItem(QString::fromStdString(product.getName())));

    QString priceStr = QString("$%1").arg(product.getPrice(), 0, 'f', 2);
    viewTable->setItem(i, 2, new QTableWidgetItem(priceStr));

    int qty = product.getQuantity();
    viewTable->setItem(i, 3, new QTableWidgetItem(QString::number(qty)));

    if (inventory.checkLowStock(product.getId(), 10)) {
      for (int col = 0; col < 4; col++) {
        viewTable->item(i, col)->setBackground(
            palette().color(QPalette::Highlight).darker(130));
        viewTable->item(i, col)->setForeground(
            palette().color(QPalette::HighlightedText));
      }
    } else if (qty < 10) {
      for (int col = 0; col < 4; col++) {
        viewTable->item(i, col)->setBackground(QColor(255, 255, 150));
      }
    }
  }

  layout->addWidget(viewTable);

  QPushButton *okButton = new QPushButton("OK", &dialog);
  connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
  layout->addWidget(okButton);

  dialog.exec();
}

QString GUI::getThemeIcon(const QString &lightIcon, const QString &darkIcon) {
  QColor bgColor = palette().color(QPalette::Window);
  int brightness =
      bgColor.red() * 0.299 + bgColor.green() * 0.587 + bgColor.blue() * 0.114;

  if (brightness > 128) {
    return lightIcon; // Light background, use dark icon
  } else {
    return darkIcon; // Dark background, use light icon
  }
}

void GUI::clearLayout() {
  QWidget *newCentral = new QWidget(this);
  setCentralWidget(newCentral);
  delete mainLayout;
  mainLayout = new QVBoxLayout(newCentral);
  stackedWidget = nullptr;
}
