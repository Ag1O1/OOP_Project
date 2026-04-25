#include "Product.h"
#include <iostream>
using namespace std;

Product::Product(int p_id, string p_name, double p_price, int p_qty) {
  id = p_id;
  name = p_name;
  price = p_price;
  quantity = p_qty;
}

int Product::getId() const { return id; }
string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }

void Product::setQuantity(int qty) {
  if (qty >= 0) {
    quantity = qty;
  } else {
    cout << "Error: Quantity cannot be negative." << endl;
  }
}

void Product::updatePrice(double newPrice) {
  if (newPrice >= 0.0) {
    price = newPrice;
  } else {
    cout << "Error: Price cannot be negative." << endl;
  }
}
