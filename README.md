# OOP Course Project - Online Store System

## Info

- Made by me and two colluges for the OOP course project
- Online store system similar to amazon
  - Includes Customer, Admin, and Cashier user classes
  - System for storing and saving inventory data base
  - Receipt generation

### Guidelines

- Try not to use AI for writing code, if you do make sure you understand it well
  and the code follows the rest of the guidelines.
- When you write code you must make sure it works and make sure it integrates
  with the rest of the code.
- Types should also be standard and follow the types of similar variables in the
  code (for example if price uses double then any price should use the double
  type).
- DO NOT write code which is already written somewhere else, if code needs to be
  reimplemented you should replace the old code and make sure the code runs
  well.
  - For example, if part of the code needs invintory then use the invintory
    class that's already there.
- It is preferred to use Git to commit and push the code, if you can't deal with
  git then when you finish the code and it works send me the code

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
