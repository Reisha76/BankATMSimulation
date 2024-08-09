# ATM Simulation Project

## Overview

This project is a simple ATM simulation written in C++. It provides basic functionalities like quick withdrawal, normal withdrawal, deposits, and balance checking. The project is designed to simulate a typical ATM system where users can log in using their account numbers and PIN codes, perform transactions, and log out.

## Project Structure

The project consists of the following files:

- **ATM.h**: Header file containing the declaration of structures, constants, and function prototypes used in the project.
- **ATMFuncDefs.cpp**: Implementation of the functions declared in `ATM.h`.
- **ATMProject.cpp**: The main entry point of the project where the execution begins.
- **Clients.txt**: A data file containing the account information of clients, including account numbers, PIN codes, names, phone numbers, and balances. This file is updated accordingly whenever a client makes a deposit or withdrawal, reflecting the new balance in their account.

## Features

- **User Authentication**: Users are required to log in with their account number and PIN code.
- **Main Menu**: After logging in, users are presented with a menu to perform various operations.
- **Quick Withdraw**: Users can quickly withdraw a predefined amount of money.
- **Normal Withdraw**: Users can withdraw any amount of money that is a multiple of 5.
- **Deposit Money**: Users can deposit money into their accounts.
- **Check Balance**: Users can check their current account balance.

## How to Build and Run

### Prerequisites

- A C++ compiler (e.g., `g++`).

### Building the Project

1. Open a terminal in the directory containing the source files.
2. Compile the project using the following command:

   ```bash
   g++ -o ATMProject ATMFuncDefs.cpp ATMProject.cpp


Running the Project
After building the project, you can run the executable with the following command:

./ATMProject.exe

OR 

ATMProject.exe

This will start the ATM simulation program.

