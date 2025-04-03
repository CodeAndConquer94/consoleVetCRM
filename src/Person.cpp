/*********************************************************
* Summary: This file includes the implementation for the Person class for PA6

*
*

*
* Author: Chris Tristan
* Created: March 18, 2025
*
********************************************************/
#include "Person.h"
#include "Pet.h"
#include "Address.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

//Overloads
void operator+(vector<Pet*>& pets, Pet* newPet){
    pets.push_back(newPet);
}
void operator-(vector<Pet*>& pets, const string& petToRm){
    for (int i=0; i < pets.size(); i++){
        if (pets[i]->getPetName()== petToRm){
            delete pets[i];
            pets.erase(pets.begin()+i);
            return;
        }
    }
}

istream& operator>>(istream& is, Person& dude) {
    string first, last;

    getline(is, first);//get string, format, set first name
    first = Address::formatString(first);
    dude.fname = first;

    getline(is, last);//get string, format, set last name
    last = Address::formatString(last);
    dude.lname = last;

    is >> dude.address;//use operator overload on address object
    return is;

}

ostream& operator<<(ostream& os, const Person& dude){
    os << left << setw(14) << "FIRST NAME" << ":" << right << setw(20) << dude.fname << "\n"
    << left << setw(14) << "LAST NAME" << ":" << right << setw(20) << dude.lname << "\n\n"
    << left << setw(14) << "ADDRESS" << "\n" << dude.address << left << setw(15) << "\nPETS LIST" << "\n";
    if (dude.pets.empty()) { os << "NONE\n"; }
    else {
        for (Pet* pet: dude.pets){ os << *pet << endl; }
        }

    return os;
}


Person::Person(): fname{""}, lname{""}, address{}, pets{} {}

Person::Person(const string& first, const string& last, const Address& adrs): pets{} {
    setFirstName(first);
    setLastName(last);
    setAddress(adrs);
}

Person::Person(const string& first, const string& last): address{}, pets{} {
    setFirstName(first);
    setLastName(last);
}

//Setters
void Person::setFirstName(const string& first){ fname = Address::formatString(first); }
void Person::setLastName(const string& last){ lname = Address::formatString(last); }
void Person::setAddress(const Address& adrs){ address = adrs; }
void Person::setStreetName(const string& str){ this->address.setStreetName(str); }
void Person::setCityName(const string& cty){ this->address.setCityName(cty); }
void Person::setStateName(const string& st){ this->address.setStateName(st); }
void Person::setZipCode(const size_t& zip){ this->address.setZipCode(zip); }

//Getters
string Person::getFirstName(){ return fname; }
string Person::getLastName(){ return lname; }
Address& Person::getAddress(){ return address; }
vector<Pet*>& Person::getPets(){ return pets; }

//Utility
bool Person::searchPet(const string& petname){
    string pnm = Address::formatString(petname);
    for (Pet* pet: pets){
        if ((pet->getPetName()) == pnm){ return true; } 
    }
    return false;
}

void Person::addPet(){
    Pet* newPet = new Pet;
    cin >> *newPet;
    if (!searchPet(newPet->getPetName())){ 
        pets + newPet; }
    else {
        delete newPet;
        throw "Pet with same name already exists.";
        }
}

void Person::deletePet(){
    string pName;
    cout << "Enter name of pet to be deleted: ";
    getline(cin, pName);
    pName = Address::formatString(pName);
    if (searchPet(pName)){ pets - pName;  }
    else { throw "Pet not found.";}

}

bool Person::operator==(const Person& other) const {
    return fname == other.fname && lname == other.lname
    && address == other.address;
}

bool sortLastThenFirst(const Person* a, const Person* b) {
    if (a->lname == b->lname) {
        return a->fname < b->fname;
    }
    return a->lname < b->lname;
}

string Person::toCSVline(){
    ostringstream oss;
    oss << fname << "," << lname << "," 
        << address.getStreetName() << "," 
        << address.getCityName() << "," 
        << address.getStateName() << "," 
        << address.getZipCode();

    for (Pet* pet: pets){
        oss << "," << pet->getPetName() 
            << ","  << pet->getPetDOB().getMonth() 
            << "," << pet->getPetDOB().getDay() 
            << "," << pet->getPetDOB().getYear() 
            << "," << pet->getPetType() 
            << "," << pet->getPetBreed();
    }
    return oss.str();

}

Person* Person::fromCSVline(string line) {
    stringstream ss(line);
    string token;
    vector<string> fields;
    while (getline(ss, token, ',')) {
        fields.push_back(token);
    }

    string first = fields[0];
    string last = fields[1];
    string street = fields[2];
    string city = fields[3];
    string state = fields[4];
    size_t zip = static_cast<size_t>(stoi(fields[5]));

    Address adrs(street, city, state, zip);
    Person* newCust = new Person(first, last, adrs);

    for (int i = 6; i + 5 < fields.size(); i += 6){
        string name = fields[i];
        int mm = stoi(fields[i+1]);
        int dd = stoi(fields[i+2]);
        int yy = stoi(fields[i+3]);
        string type = fields[i+4];
        string breed = fields[i+5];
        Pet* newPet = new Pet();
        newPet->setPetName(name);
        newPet->setPetDOB(mm, dd, yy);
        newPet->setPetType(type);
        newPet->setPetBreed(breed);
        newCust->pets + newPet;
    }

    return newCust;
}