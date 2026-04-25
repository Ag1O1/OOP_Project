#include "admin.h"
#include "loadFromFile.h"
#include "saveToFile.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void Admin::addProduct() {
  int id;
  string name;
  double price;
  int quantity;

  cin.ignore();
  cout << "Enter id: ";
  cin >> id;

  cout << "Enter product name: ";
  getline(cin, name);

  cout << "Enter price: ";
  cin >> price;

  cout << "Enter quantity: ";
  cin >> quantity;

  inventory.push_back(Product(id, name, price, quantity));
  saveToFile::execute(inventory);

  cout << "Product added\n";
}

void Admin::deleteProduct() {
  if (inventory.empty()) {
    cout << "No products\n";
    return;
  }
}

void Admin::showProducts() {
  int index;
  cout << "Enter number: ";
  cin >> index;

  if (index > 0 && index <= inventory.size()) {
    inventory.erase(inventory.begin() + index - 1);
    saveToFile::execute(inventory);
    cout << "Deleted\n";
  } else {
    cout << "Invalid\n";
  }
}

vector<Product> Admin::getProducts() { return inventory; }
