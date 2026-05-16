#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

// 1. Define roles for clarity
enum class Role { Customer, Staff };

// 2. The User Model
struct User {
    std::string name;
    std::string email;
    Role role;
    int loyaltyPoints;

    // Helper to turn the Enum into a readable string
    std::string getRoleString() const {
        return (role == Role::Customer) ? "Customer" : "Staff";
    }
};

// 3. The Management System
class SupermarketSystem {
private:
    std::unordered_map<std::string, User> users; // Storage: ID -> User
    std::unordered_set<std::string> registeredEmails; // For O(1) duplicate checking
    int nextId = 1001;

public:
    void registerUser(std::string name, std::string email, Role role) {
        // Validation: Check if email exists in our set
        if (registeredEmails.find(email) != registeredEmails.end()) {
            std::cout << "[-] Registration Failed: Email " << email << " is already taken.\n";
            return;
        }

        // Generate ID (Prefix + Counter)
        std::string prefix = (role == Role::Customer) ? "CUST" : "STAF";
        std::string newId = prefix + std::to_string(nextId++);

        // Create and Store User
        int startingPoints = (role == Role::Customer) ? 0 : -1; // -1 indicates N/A for staff
        User newUser{ name, email, role, startingPoints };

        users[newId] = newUser;
        registeredEmails.insert(email); // Track the email so it can't be used again

        std::cout << "[+] Success: " << name << " registered with ID: " << newId << "\n";
    }

    void displayAllUsers() {
        std::cout << "\n--- Supermarket Database ---\n";
        std::cout << std::left << std::setw(10) << "ID" << std::setw(20) << "Name"
            << std::setw(15) << "Role" << "Email" << "\n";
        std::cout << "------------------------------------------------------------\n";
        for (const auto& [id, user] : users) {
            std::cout << std::left << std::setw(10) << id
                << std::setw(20) << user.name
                << std::setw(15) << user.getRoleString()
                << user.email << "\n";
        }
    }
};

/*
// 4. Execution Logic
int main() {
    SupermarketSystem market;

    // Adding some initial data
    market.registerUser("Alice Smith", "alice@gmail.com", Role::Customer);
    market.registerUser("Bob Manager", "bob@supermarket.com", Role::Staff);
    market.registerUser("Charlie Day", "charlie@gmail.com", Role::Customer);

    // Testing the duplicate email check
    market.registerUser("Imposter Alice", "alice@gmail.com", Role::Customer);

    // Final Output
    market.displayAllUsers();

    return 0;
}
*/
