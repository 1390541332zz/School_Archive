#ifndef PROJECT5_DATE_H
#define PROJECT5_DATE_H

#include <cstddef>
#include <iostream>
#include <sstream>
#include <iomanip>

#define DEFAULT_YEAR 2017
#define DEFAULT_MONTH 1
#define DEFAULT_DAY 1

class Date {
    private:
        size_t year  = DEFAULT_YEAR;
        size_t month = DEFAULT_MONTH;
        size_t day   = DEFAULT_DAY;
        
        bool verifyDay(/*int year, int month,*/ int day);
    public:
        Date();
        Date(int monthVal, int dayVal, int yearVal);
        size_t getYear() const;
        size_t getMonth() const;
        size_t getDay() const;
        void setYear(int value);
        void setMonth(int value);
        void setDay(int value);
        void printDate(std::ostream& os) const;
};

std::ostream& operator << (std::ostream& os, const Date& obj);
bool operator == (const Date& o1, const Date& o2);
bool operator != (const Date& o1, const Date& o2);


#endif /* PROJECT5_DATE_H */