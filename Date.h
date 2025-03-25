/**
 * @file Date.h
 * @author Sai Krishna Karnam
 * @brief
 * @version 0.1
 * @date 2024-03-24
 *
 * @copyright Copyright (c) 2024 University of Colorado Denver - Department of Computer Science
 *
 */

#ifndef DATE_H
#define DATE_H

#include <string>
    using std::string;
    
class Date 
{ 
    private: 
        unsigned int month; // 1-12 (January-December) 
        unsigned int day; // 1-31 based on month 
        unsigned int year;//any year 
        // utility function to check if day is proper for month and year 
        unsigned int checkDay( int );
    
    public: 
        static const int monthsPerYear = 12; // months in a year
        explicit Date( int = 1, int = 1, int = 1900 ); // default constructor and parameterized constructor
        string dateString(); // print date in month/day/year format 
        ~Date(); // provided to confirm destruction order

    
}; // end class Date
        

#endif
