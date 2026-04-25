#include "admin.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void Admin::loadFromFile() {
  ifstream file("products.txt");
  string name;
  double price;
  int id;
  int quantity;

  while (getline(file, name)) {
    file >> price;
    file >> id;
    file >> quantity;
    file.ignore();
    inventory.push_back(Product(id, name, price, quantity));
  }
  file.close();
}

void Admin::saveToFile() {
  ofstream file("products.txt");

  for (int i = 0; i < inventory.size(); i++) {
    file << inventory[i].getName() << endl;
    file << inventory[i].getPrice() << endl;
    file << inventory[i].getId() << endl;
    file << inventory[i].getQuantity() << endl;
  }
  file.close();
}

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
  saveToFile();

  cout << "Product added\n";
}

void Admin::deleteProduct() {
  if (inventory.empty()) {
    cout << "No products\n";
    return;
  }

  showProducts();
  int index;
  cout << "Enter number: ";
  cin >> index;

  if (index > 0 && index <= inventory.size()) {
    inventory.erase(inventory.begin() + index - 1);
    saveToFile();
    cout << "Deleted\n";
  } else {
    cout << "Invalid\n";
  }
}

void Admin::showProducts() {
  if (inventory.empty()) {
    cout << "No products\n";
    return;
  }

  for (int i = 0; i < inventory.size(); i++) {
    cout << i + 1 << "- " << inventory[i].getName() << " : "
         << inventory[i].getPrice() << endl;
  }
}

vector<Product> Admin::getProducts() { return inventory; }
