/*********************************************************
* Summary: This file includes the declaration for the Person class for PA6

*
*

*
* Author: Chris Tristan
* Created: March 18, 2025
*
********************************************************/
#ifndef PERSON_H
#define PERSON_H
#include "Pet.h"
#include "Address.h"
#include <string>
#include <vector>

using namespace std;

bool sortLastThenFirst(const class Person*, const class Person*);

class Person {

    friend ostream& operator<<(ostream& os, const Person& dude);
    friend istream& operator>>(istream& is, Person& dude);
    friend void operator+(vector<Pet*>& pets, Pet* newPet);
    friend void operator-(vector<Pet*>& pts, const string& petToRm);
    friend bool sortLastThenFirst(const Person* a, const Person* b);

    private:
        string fname;
        string lname;
        Address address;
        vector<Pet*> pets;
    
    public:
        Person();
        Person(const string& first, const string& last, const Address& adrs);
        Person(const string& first, const string& last);

    //Setters
        void setFirstName(const string& first);
        void setLastName(const string& last);
        void setAddress(const Address& adrs);
        void setStreetName(const string& str);
        void setCityName(const string& cty);
        void setStateName(const string& st);
        void setZipCode(const size_t& zip);

    //Getters
        string getFirstName();
        string getLastName();
        Address& getAddress();
        vector<Pet*>& getPets();

    //Utility
        bool searchPet(const string& petname);
        void addPet();
        void deletePet();
        bool operator==(const Person& other) const;

    //Utility
        string toCSVline();
        static Person* fromCSVline(string line);
        






};





#endif
