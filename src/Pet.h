/*********************************************************
* Summary: This file includes the declaration for the Pet class for PA6

*
*

*
* Author: Chris Tristan
* Created: March 18, 2025
*
********************************************************/
#ifndef PET_H
#define PET_H
#include "Date.h"
#include <string>

using namespace std;

class Pet {

    friend ostream& operator<<(ostream& output, Pet& pet);
    friend istream& operator>>(istream& input, Pet& pet);

    private:
        string name;
        Date DOB;
        string type;
        string breed;

    public:
        Pet();
        Pet(const string& nm, const Date& dob, const int& tp, const string& breed);
    
    //Setters
        void setPetName(const string& nm);
        void setPetDOB(const int& mm, const int& dd, const int& yyyy);
        void setPetType(const int& tp = 0);
        void setPetType(string tp);
        void setPetBreed(const string& brd);
    
    //Getters
        string getPetName();
        Date getPetDOB();
        string getPetType();
        string getPetBreed();
    
    //Utility
        static string formatString(const string& str);
        static void passType(Pet& pet, const int& tp = 0); //need static member function to call non-static member function
};
string trim(string str);





#endif
