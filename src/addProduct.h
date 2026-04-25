#include "Product.h"
#include <iostream>
#include <string>
#include <vector>
class AddProduct {
public:
  void execute(std::vector<Product> &inventory, bool &fileSaveFlag) {
    int newId;
    std::string newName;
    double newPrice;
    int initialStock;

    std::cout << "\n--- Add New Product (Admin) ---" << std::endl;
    std::cout << "Enter New Product ID: ";
    std::cin >> newId;

    for (const auto &item : inventory) {
      if (item.getId() == newId) {
        std::cout << "Error: A product with ID " << newId << " already exists!"
                  << std::endl;
        return; // Exit the operation early
      }
    }

    std::cout << "Enter Product Name: ";
    std::cin >> std::ws;
    getline(std::cin, newName);
    std::cout << "Enter Price: $";
    std::cin >> newPrice;
    std::cout << "Enter Initial Stock: ";
    std::cin >> initialStock;
    fileSaveFlag = true;

    std::cout << "Success: Product '" << newName << "' added to inventory."
              << std::endl;
  }
};
