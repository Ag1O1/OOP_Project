#pragma once
#include "Product.h"
#include <iostream>
#include <vector>
class UpdateStock {
public:
  void execute(std::vector<Product> &inventory, bool &fileSaveFlag) {
    int targetId;
    int quantityChange;
    bool productFound = false;

    std::cout << "\n--- Update Stock (Admin) ---" << std::endl;
    std::cout << "Enter Product ID to update: ";
    std::cin >> targetId;

    for (auto &item : inventory) {
      if (item.getId() == targetId) {
        productFound = true;

        std::cout << "Current stock for '" << item.getName()
                  << "' is: " << item.getQuantity() << std::endl;
        std::cout << "Enter quantity to add (use negative number to "
                     "remove/write-off): ";
        std::cin >> quantityChange;

        int newQuantity = item.getQuantity() + quantityChange;

        if (newQuantity < 0) {
          std::cout << "Error: Operation would drop stock below zero. Update "
                       "cancelled."
                    << std::endl;
        } else {
          item.setQuantity(newQuantity);
          fileSaveFlag = true;
          std::cout << "Success: Stock updated. New stock level is "
                    << item.getQuantity() << "." << std::endl;
        }
        break;
      }
    }

    if (!productFound) {
      std::cout << "Error: Product with ID " << targetId << " not found."
                << std::endl;
    }
  }
};
