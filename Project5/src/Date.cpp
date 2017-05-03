/*
 * Purpose for program: This class is contains the date.
 *
 * Programmer: Jacob Abel
 * Date: May 02, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include "Date.h"

// Default Constructor
Date::Date() {
}

// Constructor with parameters
Date::Date(int monthVal, int dayVal, int yearVal)
:   year((yearVal > 0) ? static_cast<size_t>(yearVal) : DEFAULT_YEAR),
    month((monthVal > 0 && monthVal <= 12) ? static_cast<size_t>(monthVal) : DEFAULT_MONTH),
    day((Date::verifyDay(/*yearVal, monthVal,*/ dayVal)) ? static_cast<size_t>(dayVal) : DEFAULT_DAY)
{}

// Verifies that the day is valid
bool Date::verifyDay(/*int year, int month, */ int day) {
    return (day > 0 && day <= 31);
    // Incorrect Assumptions are made about the day. 
    // The following would be the proper set of Assumptions
    // Issues: April, June, September, & November only have 30 days. 
    // Leap years occur on the years divisible by 4 but not 100 
    // except when divisible by 400.
    //
    //if (day <= 0 || day > 31) return false; 
    // switch (month) {
    //     case  1: //January
    //     case  3: //March
    //     case  5: //May
    //     case  7: //July
    //     case  8: //August
    //     case 10: //October
    //     case 12: //December
    //         return true;
    //     case  4: //April
    //     case  6: //June
    //     case  9: //September
    //     case 11: //November
    //         return (day <= 30);
    //     case  2: //Febuary
    //         return day <= ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28);
    //     default:
    //         return true; // If month is an illegal value, assume default # of days (31)
    // }
}

// Returns the year
size_t Date::getYear() const {
    return year;
}

// Returns the month
size_t Date::getMonth() const {
    return month;
}

// Returns the day
size_t Date::getDay() const {
    return day;
}

// Sets the year
void Date::setYear(int value) {
    if (value > 0) year = static_cast<size_t>(value);
}

// Sets the month
void Date::setMonth(int value) {
    if (value > 0 && value <= 12) month = static_cast<size_t>(value);
}

// Sets the day
void Date::setDay(int value) {
    if (Date::verifyDay(/*year, month,*/ value)) day = static_cast<size_t>(value);
}

// Prints the date in MM/DD/YYYY format
void Date::printDate(std::ostream& os) const {
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(2) << month << '/' << std::setw(2) << day << '/' << std::setw(4) << year;
    os << ss.str();
}

// Stream Insertion Operator
std::ostream& operator << (std::ostream& os, const Date& obj) {
    obj.printDate(os);
    return os;
}

// Equality Operator
bool operator == (const Date& o1, const Date& o2) {
    return ((o1.getYear()  == o2.getYear())  && \
            (o1.getMonth() == o2.getMonth()) && \
            (o1.getDay()   == o2.getDay()));
}

// Inequality Operator
bool operator != (const Date& o1, const Date& o2) {
    return !(o1 == o2); 
}