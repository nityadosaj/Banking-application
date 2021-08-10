#ifndef DATE_H
#define DATE_H
#include <ctime>
using namespace std;

class Date
{
    public:
        Date();
        int getCurrMonth();
        int getCurrYear();
        int getCurrDay();
        void setCurrMonth(int);
        void setCurrYear(int);
        void setCurrDay(int);
        void getCurrentDate();
        bool checkLeapYear(int);
        
    private:
        int currMonth;
        int currYear;
        int currDay;
    
};

#endif