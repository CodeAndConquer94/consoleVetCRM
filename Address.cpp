/*********************************************************
* Summary: This file includes the implementation for the Address class for PA6

*
*

*
* Author: Chris Tristan
* Created: March 18, 2025
*
********************************************************/
#include "Address.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

Address::Address() :
    street{""}, city{""}, state{""}, zipCode{00000}{}

Address::Address(const string& str, const string& cty, const string& st, const size_t& zip) {
    setStreetName(str);
    setCityName(cty);
    setStateName(st);
    setZipCode(zip);
    
}


//Setters
void Address::setStreetName(const string& str){
    street = formatString(str);
}
void Address::setCityName(const string& cty){
    city = formatString(cty);
}
void Address::setStateName(const string& st){
    state = formatString(st);
}
void Address::setZipCode(const size_t& zip){
    zipCode = zip;
}


//Getters
string Address::getStreetName() {return street;}
string Address::getCityName() {return city;}
string Address::getStateName() {return state;}
size_t Address::getZipCode() {return zipCode;}


//operators
ostream& operator<<(ostream& os, const Address& adrs) {
    os << left << setw(14) << "STREET" << ":" << setw(20) << right << adrs.street << "\n"
    << left << setw(14) << "CITY" << ":" << setw(20) << right << adrs.city << "\n"
    << left << setw(14) << "STATE" << ":" << setw(20) << right << adrs.state << "\n"
    << left << setw(14) << "ZIP CODE" << ":" << setw(20) << right << adrs.zipCode << endl;
    return os;
}

istream& operator>>(istream& is, Address& adrs) {
    string str, cty, st;

    cout << "Enter Street Name and Number: ";
    getline(is, str);
    adrs.street = Address::formatString(str);

    cout << "Enter City: ";
    getline(is, cty);
    adrs.city = Address::formatString(cty);

    cout << "Enter State: ";
    getline(is, st);
    adrs.state = Address::formatString(st);

    cout << "Enter Zip Code: ";
    is >> adrs.zipCode;
    is.ignore(1000,'\n');
    return is;
}

string Address::formatString(const string& str){
    string formatted = str;
    transform(formatted.begin(), formatted.end(), formatted.begin(), ::toupper);
    return formatted;
}

bool Address::operator==(const Address& other) const {
    return street == other.street && city == other.city &&
            state == other.state && zipCode == other.zipCode;
}