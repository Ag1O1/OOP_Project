# OOP Course Project - Online Store System

## Info

- Made by me and two colluges for the OOP course project
- Online store system similar to amazon
  - Includes Customer, Admin, and Cashier user classes
  - System for storing and saving inventory data base
  - Receipt generation

> [!Note] Please avoid using any AI generated content. If you do, make sure to
> understand all the code properly. I will post guidelines soon

## Running

- Run `make run` in the terminal

## TODO

- [ ] Make user manager class
  - private variables: `Vector<User> users, User current_user` (getter for
    current_user only)
  - Should have functions for registeration, logging in.
  - Register will make a new account and put it in a txt or json file (whichever
    you prefer), rewrite loadFromFile/saveToFile if needed.
  - Then there should be saving and loading of the user data, it's easier to do
    this using json in my opinion. They should be saved and loaded as Vector
    called users.
    - The loading should run in the constructor of the class, so when the class
      initializes it loads the data automatically
  - Login will take username and password as input and return User. Then iterate
    over the users vector and compare the name of every entry in it to the
    username until it finds the user, if it doesn't find anything say that the
    user doesn't exist. If it does find the user use the
    user.checkPassword(password) function to compare the password the user
    entered to the one in the database. Finally return the user if the password
    is correct user class if needed.

- [ ] Add proper error handling in all functions which need it
  - As to make errors verbose instead of silently fail

- [ ] Properly use user classes instead of struct
- [ ] Cleanup
  - Remove repeated code, replace with it's proper functions
  - Remove unessisary/unused code
- [ ] Create cashier UI
  - Or concider removing the cashier class altogether if its redundant
- [ ] Polish UI
  - Low priority since we'll make a GUI anyway
- [ ] Ensure that types are consistent
- [ ] Make GUI
  - using QT
- [x] Properly implement/fix saving and loading

### IDEAS

- Cashier
  - For now, the cashier will not be implemented. IF there is time after making
    the GUI and finishing the project we will add the cashier ui as one in-store
    cashier checkout.
  - [ ] Add QR code scanning for cashier to scan products
