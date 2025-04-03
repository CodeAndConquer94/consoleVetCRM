#ifndef CUSTOMERS_H
#define CUSTOMERS_H
#include "Person.h"
#include "Pet.h"
#include "Address.h"
#include "Date.h"
#include <vector>


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

        void saveCustomers();
        void readCustomers();

};

#endif