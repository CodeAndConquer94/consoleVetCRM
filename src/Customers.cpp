#include "Customers.h"
#include "Person.h"
#include "Address.h"
#include "Date.h"
#include "Pet.h"
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


bool Customers::custExists(const string& first, const string& last) {
    for (Person* cust : customers) {
    if (cust->getLastName() == last && cust->getFirstName() == first) return true;
    }
    return false;
}

void Customers::resort(){
    sort(customers.begin(),customers.end(), sortLastThenFirst);
}

void Customers::addCust(){
    string first, last;
    cout << "Enter First and Last name of customer you would like to add.\n";
    cout << "First Name: ";
    getline(cin, first);
    cout << endl;
    first = Address::formatString(first);

    cout << "Last Name: ";
    getline(cin, last);
    cout << endl;
    last = Address::formatString(last);

    if (custExists(first, last)) { throw "Customer already exists.";}

    Person* newCust = new Person(first, last);

    Address custAddress;
    cout << "Enter Address\n";
    cin >> custAddress;
    newCust->setAddress(custAddress);
    
    int choice;
    while (true) {
        cout << "Enter pets now?\n1.Yes\n2.No\nEnter Selection: ";
        if (cin >> choice && (choice == 1 || choice ==2)){
            cin.ignore(1000, '\n');
            break;
    }
        else {
            cout << "Invalid input, please enter a 1 or a 2.\n";
            cin.clear();
            cin.ignore(1000,'\n');
    }
    }

    if (choice == 1) {
        newCust->addPet();
    }
    customers.push_back(newCust);
    if (customers.size() > 1) { resort(); }
    return;

}

void Customers::removeCust() {
    string first, last;
    cout << "Enter First and Last name of customer you would like to remove.\n";
    cout << "First Name: ";
    getline(cin, first);
    first = Address::formatString(first);
    cout << endl;

    cout << "Last Name: ";
    getline(cin, last);
    last = Address::formatString(last);
    cout << endl;

    if (!custExists(first, last)) { throw "Customer not found.";}

    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i]->getFirstName() == first && customers[i]->getLastName() == last){
            removeFromCSV(*customers[i]);
            delete customers[i];
            customers.erase(customers.begin() + i);
            break;
            }
    }
    return;
}

Customers Customers::searchCusts(){
    Customers results;
    string first, last;

    while (true){
        cout << "Enter Customer Last Name: ";
        getline(cin, last);
        if (last.empty()){ 
            cout << "Invalid: Must have a value for customer last name.";
        }
        else break;
    }
    last = Address::formatString(last);
    cout << "\nEnter Customer First Name (Press Enter to skip:)\nFirst Name: ";
    getline(cin, first);
    if (first.empty()){
        for (size_t i=0; i < customers.size(); i++ ){
            if (customers[i]->getLastName() == last){
                results.customers.push_back(customers[i]);
            }
        }
        return results;
    }
    else { first = Address::formatString(first);
    for (size_t i=0; i< customers.size(); i++){
        if ((customers[i]->getFirstName() == first) && (customers[i]->getLastName() == last)){
            results.customers.push_back(customers[i]);
        }
    }
    return results;
}
}

void Customers::displayCustList(){
    cout << "Results:\n" << setw(30) <<setfill('-') << '-' << endl;
    cout << left << setw(6) << setfill(' ')<< "Number" << setw(12) << right << "Last Name" << setw(12) << "First Name" << endl;
    cout << setw(30) << setfill('-') << '-' << endl;
    cout << setfill(' ');

    for (size_t i=0; i< customers.size(); i++){
        cout << i+1 << ':' << setw(14) << right << customers[i]->getLastName() << setw(14) << customers[i]->getFirstName() << endl; 
    }
    cout << endl;
}

Person& Customers::selectCust(int x){
    unsigned int selection;
    if (x == 1){
        displayCustList();
        while (true) {
            cout << "Enter Customer Number 1-" << customers.size() << "(Enter 0 to return to Main Menu): ";
            if ((cin >> selection) && (selection >= 1 && selection <= customers.size())){
                cin.ignore(1000, '\n');
                return *customers[selection-1];
            }
            else if (selection == 0) { throw "Aborted"; }            
            else {
                cout << "Invalid Input: please enter a valid number\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
        }

    }
    if (x == 2) {
        Customers results = searchCusts();

        results.displayCustList();
        while (true) {
            cout << "Enter Customer Number 1-" << results.customers.size() << "(Enter 0 to return to Main Menu): ";
            if ((cin >> selection) && (selection >= 1 && selection <= results.customers.size())){
                cin.ignore(1000, '\n');
                Person selected = *results.customers[selection-1];
                for (Person* cust : customers){
                    if (*cust == selected){ return *cust; }
                    else {throw "Selected customer not found";}
            }
            if (selection == 0) { throw "Aborted"; }
            }
            else {
                cout << "Invalid Input: please enter a valid number\n";
                cin.clear();
                cin.ignore(1000,'\n');
            }
        }
        }
    else { throw "Invalid Argument";}
}

void Customers::modifyCust(Person& cust, int x){

    switch (x) {
        case 1: {
            removeFromCSV(cust);
            string first, last;
            cout << "Enter first name: ";
            getline(cin, first);
            cout << "\nEnter last name: ";
            getline(cin, last);
            first = Address::formatString(first);
            last = Address::formatString(last);
            cust.setFirstName(first);
            cust.setLastName(last);
            resort();
            saveCustomers();
            break;
            }
        case 2: {
            removeFromCSV(cust);
            Address newAdd;
            cin >> newAdd;
            cust.setAddress(newAdd);
            saveCustomers();
            break;
            }
        case 3: {
            removeFromCSV(cust);
            cust.addPet();
            saveCustomers();
            break;
            }
        case 4: {
            removeFromCSV(cust);
            cust.deletePet();
            saveCustomers();
            break;
            }
        case 0: {throw "";} 
    }
}

void Customers::displayCust(const Person& selected){
    cout << selected << endl;
}

vector<string> Customers::readCSVlines() {
    ifstream custFile("data/customers.csv", ios::in);
    vector<string> lines;
    string line;
    if (!custFile.is_open()) {
        throw runtime_error("Could not open file: customers.csv");
    }
    while (getline(custFile, line)){
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    custFile.close();
    return lines;
}

void Customers::saveCustomers() {
    vector<string> lines = readCSVlines();
    ofstream custFile{"data/customers.csv", ios::app};
    if (!custFile.is_open()) {
        throw runtime_error("Could not open file: customers.csv");
    }
    for (Person* cust : customers) {
        string target = cust->toCSVline();

        bool alreadyExists = (find(lines.begin(), lines.end(), target) != lines.end());

        if (!alreadyExists) {
                custFile << target;
        }
    }
    custFile.close();

}

void Customers::readCustomers() {
    vector<string> lines = readCSVlines();
    for (string line : lines) {
        customers.push_back(Person::fromCSVline(line));
    }
}

void Customers::removeFromCSV(Person& cust) {
    string target = cust.toCSVline();
    vector<string> lines = readCSVlines();

    ofstream custFile("data/customers.csv", ios::out | ios::trunc);

    if (!custFile.is_open()) {
        throw runtime_error("Could not open file: customers.csv");
    }
    for (const string line : lines) {
        if (line != target) {
            custFile << line;
        }
    }
    custFile.close();

}