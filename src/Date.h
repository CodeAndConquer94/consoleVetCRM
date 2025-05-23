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
        int getMonth();
        int getDay();
        int getYear();


    
}; // end class Date
        

#endif
