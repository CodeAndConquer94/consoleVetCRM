/*********************************************************
* Summary: This file includes the implementation for the Pet class for PA6

*
*

*
* Author: Chris Tristan
* Created: March 18, 2025
*
********************************************************/
#include "Date.h"
#include "Pet.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

//utility function to process mm dd and yyyy input.
string trim(string str){
    str.erase(remove(str.begin(),str.end(), ' '), str.end());
    for (int i=0; i < str.size(); i++){
        if (str[i] != '0'){
            return str.substr(i);
        }
    }
    return str;
    }

Pet::Pet() : name{""}, DOB{}, type{}, breed{} {}

Pet::Pet(const string& nm, const Date& dob, const int& tp, const string& brd) {
    setPetName(nm);
    DOB = dob;
    setPetType(tp);
    setPetBreed(brd);
}

//Setters

void Pet::setPetName(const string& nm) {name = formatString(nm);}
void Pet::setPetDOB(const int& mm, const int& dd, const int& yyyy) { 
    DOB = Date(mm, dd, yyyy);
     }

void Pet::setPetType(const int& tp) {
    switch (tp){
        case 1: type = "DOG"; break;
        case 2: type = "CAT"; break;
        case 3: type = "BIRD"; break;
        case 4: type = "SNAKE"; break;
        default:
            string userInput;
            cout << "Enter pet type: ";
            getline(cin, userInput);
            type = formatString(userInput);
            cout << endl;
            break;
    }
}
void Pet::setPetBreed(const string& brd) {breed = formatString(brd);}

//Getters
string Pet::getPetName() {return name;}
Date Pet::getPetDOB() {return DOB;}
string Pet::getPetType() {return type;}
string Pet::getPetBreed() {return breed;}

//Utility
string Pet::formatString(const string& str){
    string formatted = str;
    transform(formatted.begin(), formatted.end(), formatted.begin(), ::toupper);
    return formatted;
    }

void Pet::passType(Pet& pet, const int& tp) { pet.setPetType(tp); }

//Operators

ostream& operator<<(ostream& out, Pet& pet) {
    out << left << setw(14) << "NAME" << ":" << right << setw(20) << pet.name << "\n"
    << left << setw(14) << "DOB" << ":" << right << setw(20) << pet.DOB.dateString() << "\n"
    << left << setw(14) << "TYPE" << ":" << right << setw(20) << pet.type << "\n"
    << left << setw(14) << "BREED" << ":" << right << setw(20) << pet.breed << endl;
    return out;
}

istream& operator>>(istream& in, Pet& pet) {
    string nm, brd, mm, dd, yyyy, tp;

    cout << "Enter Pet Name: ";
    getline(in, nm);//get name
    pet.name = Pet::formatString(nm);//format and assign

    cout << "Enter Pet Date of Birth.\n";
    cout << "Month: ";
    getline(in,mm);
    cout << "Day: ";
    getline(in, dd);
    cout << "Year: ";
    getline(in, yyyy);


    if (mm.empty() && dd.empty() && yyyy.empty()){
        pet.DOB = Date();
    }
    
    else{
        try {
            mm = trim(mm);
            dd = trim(dd);
            yyyy = trim(yyyy);
            pet.DOB = Date(stoi(mm), stoi(dd), stoi(yyyy));//convert to int and assign
        }
        catch(invalid_argument& e){
            pet.DOB = Date();
        }
    }
    cout << "Enter Pet Type\n1. DOG\n2. CAT\n3. BIRD\n4. SNAKE\n(Enter 0 to input manually)\nEnter Selection: ";
    getline(in, tp);
    if (tp.empty()) {
        Pet::passType(pet);
    }
    else{
        Pet::passType(pet, stoi(tp));
    }
    cout << "Enter Pet Breed: ";
    getline(in, brd);
    pet.breed = Pet::formatString(brd);
    return in;


}


