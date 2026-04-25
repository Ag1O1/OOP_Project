#pragma once
#include <string>

class Product {
private:
  int id;
  std::string name;
  double price;
  int quantity;

public:
  Product(int p_id, std::string p_name, double p_price, int p_qty);

  int getId() const;
  std::string getName() const;
  double getPrice() const;
  int getQuantity() const;

  void setQuantity(int qty);

  void updatePrice(double newPrice);
};
