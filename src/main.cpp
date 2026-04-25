#include "UI.h"
#include "inventory.h" // Include this instead of Product.h directly
#include "structs.h"
#include <iostream>
using namespace std;

int main() {
  UI ui;
  Inventory inventory; // Use Inventory class
  vector<Product> cart;
  bool running = true;
  ui.LoginMenu();

  while (running) {
    int choice = ui.MainMenu();

    switch (choice) {
    case 1:
      // Display inventory using the Inventory class
      ui.DisplayInventory(inventory.getAllStock());
      break;

    case 2:
      ui.DisplayCart(cart);
      break;

    case 3: {
      // Add new product
      NewProductDetails details = ui.GetProductInput();
      // Need to generate ID automatically
      int newId = inventory.getAllStock().size() + 1;
      inventory.addProduct(
          Product(newId, details.name, details.price, details.quantity));
      ui.PrintMessage("Product added successfully!");
      break;
    }

    case 4:
      ui.PrintReceipt(cart);
      cart.clear();
      break;

    case 5:
      running = false;
      ui.PrintMessage("Goodbye!");
      break;
    }
  }

  return 0;
}
