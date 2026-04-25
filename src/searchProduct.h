#pragma once
#include "Product.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
class SearchProduct {
public:
  static void execute(const std::vector<Product> &inventory) {
    std::string searchQuery;
    std::cout << "\n--- Search Products ---" << std::endl;
    std::cout << "Enter product name or ID to search: ";
    std::cin >> std::ws;
    getline(std::cin, searchQuery);

    bool foundAny = false;
    std::cout << "\nSearch Results:" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    for (const auto &item : inventory) {
      if (std::to_string(item.getId()) == searchQuery ||
          item.getName().find(searchQuery) != std::string::npos) {

        std::cout << std::left << "ID: " << std::setw(5) << item.getId()
                  << " | Name: " << std::setw(20) << item.getName()
                  << " | Stock: " << item.getQuantity() << " | Price: $"
                  << std::fixed << std::setprecision(2) << item.getPrice()
                  << std::endl;

        foundAny = true;
      }
    }

    if (!foundAny) {
      std::cout << "Error: No products found matching '" << searchQuery << "'."
                << std::endl;
    }
    std::cout << "---------------------------------------------" << std::endl;
  }
};
