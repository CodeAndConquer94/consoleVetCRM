/*********************************************************
* Summary: This file includes the declaration for the Address class for PA6

*
*

*
* Author: Chris Tristan
* Created: March 18, 2025
*
********************************************************/
#ifndef ADDRESS_H
#define ADDRESS_H
#include <string>
#include <iostream>



using namespace std;

class Address {
    friend ostream& operator<<(ostream& os, const Address& adrs);
    friend istream& operator>>(istream& is, Address& adrs);

    private:
        string street;
        string city;
        string state;
        size_t zipCode;
    public:
        Address();
        Address(const string& street, const string& cty, const string& state, const size_t& zip);
    //Setters
        void setStreetName(const string& str);
        void setCityName(const string& cty);
        void setStateName(const string& st);
        void setZipCode(const size_t& zip);
    //Getters
        string getStreetName();
        string getCityName();
        string getStateName();
        size_t getZipCode();

    //Utility
        static string formatString(const string& str); // must be static so that friend functions can access
        bool operator==(const Address& other) const;

    


};
    






#endif
