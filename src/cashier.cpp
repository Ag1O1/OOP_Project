#include "cashier.h"
#include <iostream>
using namespace std;
void Cashier::startTransaction() {
  cart.clear();
  cout << "Transaction started\n";
}

void Cashier::addToCart(vector<Product> products) {
  int choice;

  do {
    cout << "Select product (0 to finish): ";
    cin >> choice;

    if (choice > 0 && choice <= products.size()) {
      cart.push_back(products[choice - 1]);
      cout << "Added: " << products[choice - 1].getName() << endl;
    }

  } while (choice != 0);
}

void Cashier::finalizePayment() {
  if (cart.empty()) {
    cout << "Cart is empty\n";
    return;
  }

  double total = 0;

  cout << "\n--- Cart ---\n";
  for (int i = 0; i < cart.size(); i++) {
    cout << cart[i].getName() << " : " << cart[i].getPrice() << endl;
    total += cart[i].getPrice();
  }

  double discount = 0;
  if (total >= 1000) {
    discount = total * 0.10;
  }

  cout << "Total = " << total << endl;
  cout << "Discount = " << discount << endl;
  cout << "Final = " << total - discount << endl;
  cout << "Payment done\n";
}
