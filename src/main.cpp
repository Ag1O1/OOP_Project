#include "UI.h"
#include "addToCart.h"
#include "loadFromFile.h"
#include "qmainwindow.h"
#include "saveToFile.h"
#include "searchProduct.h"
#include "structs.h"
#include <QApplication>
#include <QMessageBox>
#include <QStyleFactory>

#include <QMainWindow>
#include <QPushButton>
#include <gui.h>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  GUI gui;
  gui.show();

  return app.exec();

  UI ui;
  Inventory inventory;
  bool running = true;
  bool logged_in = false;
  loadFromFile::execute(inventory.getAllStock());

  while (running) {
    User user = ui.LoginMenu();
    logged_in = true;
    vector<Product> cart;

    while (logged_in) {
      if (user.getRole() == "customer") {
        int choice = ui.MainMenu();

        switch (choice) {
          // Display inventory
        case 1:
          ui.DisplayInventory(inventory);
          break;

        case 2:
          // Display cart
          ui.DisplayCart(cart);
          break;

        case 3: {
          int id, amount;
          cout << "Enter id and amount: ";
          cin >> id >> amount;
          AddToCart::execute(id, amount, inventory, cart);
          cout << "Added to cart";
          break;
        }

        case 4:
          // Print receipt
          ui.PrintReceipt(cart);
          cart.clear();
          break;

        case 5:
          // Exit
          saveToFile::execute(inventory.getAllStock());
          running = false;
          logged_in = false;
          ui.PrintMessage("Goodbye!");
          break;
        }
      } else if (user.getRole() == "admin") {
        int res;
        cout << "1. DisplayInventory 2. Add product 3. Remove product 4. "
                "logout 5. exit \n";
        cin >> res;

        switch (res) {
        case 1:
          ui.DisplayInventory(inventory);
          break;

        case 2: {
          NewProductDetails details = ui.GetProductInput();
          int newId = inventory.getAllStock().size() + 1;
          inventory.addProduct(
              Product(newId, details.name, details.price, details.quantity));
          ui.PrintMessage("Product added successfully!");
          break;
        }

        case 3: {
          unsigned removeId;
          ui.DisplayInventory(inventory);
          cout << "Enter product ID to remove: ";
          cin >> removeId;

          Product *product = inventory.getProduct(removeId);
          if (product != nullptr) {
            cout << "Removing: " << product->getName() << endl;
            inventory.removeProduct(removeId);
            ui.PrintMessage("Product removed successfully!");
          } else {
            ui.PrintMessage("Error: Product ID not found!");
          }
          break;
        }

        case 4:
          logged_in = false;
          break;

        case 5:

          saveToFile::execute(inventory.getAllStock());
          running = false;
          logged_in = false;
          ui.PrintMessage("Goodbye!");
          break;
        }
      }
    }
    /*
    if (user.userType == "cashier") {
    }
    */
  }

  return 0;
}
