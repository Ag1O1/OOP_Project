#pragma once
#include "Product.h"
#include <fstream>
#include <iostream>
#include <vector>
class saveToFile {
public:
  static void execute(std::vector<Product> &inventory) {
    std::cout << "Saving...\n";
    std::ofstream file("products.txt");

    for (long unsigned int i = 0; i < inventory.size(); i++) {
      file << inventory[i].getName() << std::endl;
      file << inventory[i].getPrice() << std::endl;
      file << inventory[i].getId() << std::endl;
      file << inventory[i].getQuantity() << std::endl;
    }
    file.close();
  }
};
