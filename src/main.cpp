#include "Address.h"
#include "Person.h"
#include "main.h"
#include <cstdlib>
#include <iostream>
#include <string>


using namespace std;

int mainMenu() {
    int selection;
    cout << "Please choose an option and enter a number." << endl;
    cout << "1. View Customers" << endl;
    cout << "2. Search customers" << endl;
    cout << "3. Add a customer" << endl;
    cout << "4. Remove a customer" << endl;
    cout << "(Enter 0 to quit program)" << endl;
    cout << "Enter Selection: ";
    while (true) {
        if ((cin >> selection) && (selection >=0) && (selection <=4)){
            cin.ignore(1000, '\n');
            cout << endl;
            break;
            }
        else {
            cout << "Invalid selection: Please enter a number 0-4\n";
            cin.clear();
            cin.ignore(1000,'n');
        }}

    return selection;
}


int modificationMenu(){
    int choice;
    cout << "Select an Option\n1. Update Name\n2. Update Address\n3. Add Pet\n4. Remove Pet\n(0 to Return to Main Menu)\n";
    while (true) {
        if ((cin >> choice) && (choice >= 0 && choice <= 4)){
            cin.ignore(1000, '\n');
            cout << endl;
            break;
        }
        else {
            cout << "Invalid Selection: Please enter a number between 0-4";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;

        }
    }
    return choice;
}




int main() {
    Customers myCustomers;
    myCustomers.readCustomers();

    while (true) {
        int ch = mainMenu();

        try {
            if (ch == 1 || ch == 2) {
                Person& cust = myCustomers.selectCust(ch);
                myCustomers.displayCust(cust);
                int modChoice = modificationMenu();
                myCustomers.modifyCust(cust, modChoice);
            }
            else if (ch == 3) {
                myCustomers.addCust();
            }
            else if (ch == 4) {
                myCustomers.removeCust();
            }
            else if (ch == 0) {
                myCustomers.saveCustomers();
                exit(0);
            }
            else {
                std::cout << "Invalid selection.\n";
            }
        } catch (const char* e) {
            std::cout << "Error: " << e << std::endl;
        }
    }
}
