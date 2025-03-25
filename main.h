#ifndef MAIN_H
#define MAIN_H
#include "Address.h"
#include "Person.h"
#include "Pet.h"
#include <vector>

using namespace std;

int mainMenu(); //displays main menu and returns an integer of customer input

int modificationMenu();



class Customers {
    private:
        vector<Person*> customers;

        void resort();

    public:
        bool custExists(const string& fname, const string& lname);
        void addCust();
        void removeCust();
        void modifyCust(Person& cust, int x);
        Customers searchCusts();
        void displayCustList();
        void displayCust(const Person& cust);
        Person& selectCust(int x);

};






#endif

