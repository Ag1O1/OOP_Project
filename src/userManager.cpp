#include "userManager.h"
#include <fstream>
#include <iostream>

UserManager::UserManager() {
  currentUser = nullptr;
  loadFromFile();
}

UserManager::~UserManager() {
  for (int i = 0; i < (int)users.size(); i++) {
    delete users[i];
  }
}

void UserManager::loadFromFile() {
  std::ifstream file("users.txt");
  if (!file.is_open()) {
    return;
  }

  std::string username, password, role;

  while (file >> username >> password >> role) {
    std::cout << "Loading: " << username << ", " << role << std::endl;

    if (role == "admin") {
      users.push_back(new Admin(username, password));
    } else if (role == "customer") {
      users.push_back(new User(username, password));
    } else {
      std::cout << "Unknown role: " << role << std::endl;
    }
  }
  file.close();
}

void UserManager::saveToFile() const {
  std::ofstream file("users.txt");
  if (!file.is_open())
    return;

  for (int i = 0; i < (int)users.size(); i++) {
    file << users[i]->getUsername() << std::endl;
    file << users[i]->getPassword() << std::endl;
    file << users[i]->getRole() << std::endl;
  }
  file.close();
}

bool UserManager::registerUser(const std::string &username,
                               const std::string &password,
                               const std::string &role) {
  for (int i = 0; i < (int)users.size(); i++) {
    if (users[i]->getUsername() == username) {
      return false;
    }
  }

  if (role == "admin") {
    users.push_back(new Admin(username, password));
  } else {
    users.push_back(new User(username, password));
  }

  saveToFile();
  return true;
}

User *UserManager::login(const std::string &username,
                         const std::string &password) {
  for (int i = 0; i < (int)users.size(); i++) {
    if (users[i]->getUsername() == username &&
        users[i]->checkPassword(password)) {
      currentUser = users[i];
      return currentUser;
    }
  }
  return nullptr;
}

User *UserManager::getCurrentUser() const { return currentUser; }

void UserManager::logout() { currentUser = nullptr; }
