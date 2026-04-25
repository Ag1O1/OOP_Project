#pragma once
#include "Product.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
class loadFromFile {
public:
  static void execute(std::vector<Product> &inventory) {
    std::ifstream file("products.txt");
    std::string name;
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
};
