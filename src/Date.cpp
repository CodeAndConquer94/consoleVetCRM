/**
 * @file Date.cpp
 * @author Sai Krishna Karnam
 * @brief
 * @version 0.1
 * @date 2024-03-24
 *
 * @copyright Copyright (c) 2024 University of Colorado Denver - Department of Computer Science
 *
 */

#include "Date.h"

// Fig. 9.18: Date.cpp 
// Date class member-function definitions. 
#include <array> 
    using std::array;
#include <iostream>
    using std::cout;
    using std::endl;
    using std::to_string;
#include <stdexcept>

#include "Date.h"// include Date class definition
// constructor confirms proper value for month; calls 
// utility function checkDay to confirm proper value for day
Date::Date( int mn, int dy, int yr )
{
    if ( mn > 0 && mn <= monthsPerYear) // validate the month
        month = mn;
    else
        throw std::invalid_argument( "month must be 1-12" );

    year = yr; // could validate yr
    day = checkDay( dy ); // validate the day
    cout << endl;
} // end Date constructor

string Date::dateString() 
{ 
    return to_string(month) + "/" +  to_string(day) + "/" + to_string(year);
} // end function print
// output Date object to show when its destructor is called
Date::~Date()
{

} // end ~Date destructor

// utility function to confirm proper day value based on
// month and year; handles leap years, too
unsigned int Date::checkDay( int testDay )
{
    static const array< int, monthsPerYear + 1 > daysPerMonth =
        {0, 31, 28, 31, 30,31, 30, 31, 31, 30,31,30, 31};

    // determine whether testDay isvalid for specified month
    if ( testDay> 0 && testDay <= daysPerMonth[ month ] )
        return testDay;

    // February 29 check for leap year
    if ( month == 2 && testDay ==29 && ( year % 400 == 0 ||
       ( year% 4 == 0&& year% 100 != 0 ) ) )
        return testDay;

    throw std::invalid_argument( "Invalid day for currentmonth and year");
} // end function checkDay