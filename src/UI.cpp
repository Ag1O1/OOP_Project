#include "UI.h"
#include "Product.h"
#include "structs.h"
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int UI::MainMenu() {
  int choice;
  cout << "\n=== Supermarket Main Menu ===" << endl;
  cout << "1. View Inventory" << endl;
  cout << "2. View Cart" << endl;
  cout << "3. Add New Product" << endl;
  cout << "4. Checkout & Print Receipt" << endl;
  cout << "5. Exit" << endl;
  cout << "Enter your choice: ";
  cin >> choice;
  return choice;
}

UserLogin UI::LoginMenu() {
  UserLogin user;
  cout << "\n=== System Login ===" << endl;
  cout << "Username: ";
  cin >> user.username;
  cout << "Password: ";
  cin >> user.password;
  cout << "Account Type (admin/customer): ";
  cin >> user.userType;
  return user;
}

void UI::PrintMessage(const string &msg) {
  cout << "\n[System]: " << msg << endl;
}

void UI::DisplayInventory(const vector<Product> &inventory) {
  cout << "\n--- Current Inventory ---" << endl;
  // Using iomanip to make neat columns
  cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Price"
       << setw(10) << "Quantity" << endl;
  cout << "---------------------------------------------" << endl;

  for (const auto &item : inventory) {
    cout << left << setw(5) << item.getId() << setw(20) << item.getName() << "$"
         << setw(9) << fixed << setprecision(2) << item.getPrice() << setw(10)
         << item.getQuantity() << endl;
  }
}

void UI::DisplayCart(const vector<Product> &cart) {
  cout << "\n--- Your Shopping Cart ---" << endl;
  if (cart.empty()) {
    cout << "Your cart is currently empty." << endl;
    return;
  }

  double total = 0.0;
  for (const auto &item : cart) {
    cout << "- " << item.getName() << " | $" << fixed << setprecision(2)
         << item.getPrice() << " x " << item.getQuantity() << endl;
    total += (item.getPrice() * item.getQuantity());
  }
  cout << "--------------------------" << endl;
  cout << "Current Cart Total: $" << fixed << setprecision(2) << total << endl;
}

NewProductDetails UI::GetProductInput() {
  NewProductDetails details;
  cout << "\n--- Enter New Product Details ---" << endl;
  cout << "Product Name: ";
  cin >> details.name;
  cout << "Price: $";
  cin >> details.price;
  cout << "Initial Quantity: ";
  cin >> details.quantity;
  return details;
}

void UI::PrintReceipt(const vector<Product> &receiptData) {
  cout << "\n=====================================" << endl;
  cout << "         SUPERMARKET RECEIPT         " << endl;
  cout << "=====================================" << endl;

  double grandTotal = 0.0;
  for (const auto &item : receiptData) {
    double lineTotal = item.getPrice() * item.getQuantity();
    cout << left << setw(20) << item.getName() << "x" << setw(4)
         << item.getQuantity() << "$" << fixed << setprecision(2) << lineTotal
         << endl;
    grandTotal += lineTotal;
  }

  cout << "-------------------------------------" << endl;
  cout << "GRAND TOTAL:          $" << fixed << setprecision(2) << grandTotal
       << endl;
  cout << "   Thank you for shopping with us!   " << endl;
  cout << "=====================================" << endl;
}
