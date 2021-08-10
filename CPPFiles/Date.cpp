#include "../HFiles/Date.h"

Date::Date()
{
    getCurrentDate();
}

int Date::getCurrDay()
{
    return currDay;
}

int Date::getCurrMonth()
{
    return currMonth;
}

int Date::getCurrYear()
{
    return currYear;
}

void Date::setCurrMonth(int m)
{
    currMonth = m;
}

void Date::setCurrYear(int y)
{
    currYear = y;
}

void Date::setCurrDay(int d)
{
    currDay = d;
}

void Date::getCurrentDate()
{
    time_t now = time(0);
    tm *date = localtime(&now);
    setCurrMonth(1+date->tm_mon);
    setCurrYear(1900+date->tm_year);
    setCurrDay((date->tm_mday));
}

bool Date::checkLeapYear(int y)
{
    bool result = false;
    
    if((y%4 == 0) && (y%100 != 0))
        result = true;
    else if(y%400 == 0)
        result = false;
    else
        result = false;
        
    return result;
}