#ifndef QUEUE_H
#define QUEUE_H
#include "LinkedList.h"
#include "Date.h"
#include "../StructFiles/AdminStruct.h"
#include <stdexcept>
using namespace std;
  
class PQueue
{
  public:
    PQueue(){}
    ~PQueue(){}
    
    void enqueue(const AdminUser& element)
    {
      int priority;
      if(element.loanAmount != 0)
      {
        if(checkDueDates(element)==0){//NO LOAN
            priority = 0;
        }
        else if(checkDueDates(element)>0 &&checkDueDates(element)<=10){
            priority = 1;
        }
        else if(checkDueDates(element)>10 &&checkDueDates(element)<=20){
            priority = 2;
        }
        else{
            priority = 3;
         }
        list.insert(priority,element);
        }
    }
    
    int checkDueDates(const AdminUser& element)
    {
        Date d;
        int day,m,y, daysLeft = 0;
        day = d.getCurrDay();
        m = d.getCurrMonth();
        y = d.getCurrYear();
    
        if(day == element.dueDate && m == element.dueMonth && y == element.dueYear)
        {
            daysLeft = 0;
        }
    
        if(y <= element.dueYear)
        {
            if(d.checkLeapYear(y))
            {
                if(m == 2)
                {
                    if(element.dueDate <= 29)
                        daysLeft = element.dueDate - day;
                    else
                        daysLeft = 0;
                }
                else if(m == 4 || m == 6 || m == 9 || m == 11 )
                {
                    if(element.dueDate <= 30)
                        daysLeft = element.dueDate - day;
                    else
                        daysLeft = 0;
                }
                else
                    daysLeft = element.dueDate - day;
            }
            else
            {
                if(m == 2)
                {
                    if(element.dueDate <= 28)
                        daysLeft = element.dueDate - day;
                    else
                        daysLeft = 0;
                }
                else if(m == 4 || m == 6 || m == 9 || m == 11 )
                {
                    if(element.dueDate <= 30)
                        daysLeft = element.dueDate - day;
                    else
                        daysLeft = 0;
                }
                else
                    daysLeft = element.dueDate - day;
            }
        }
        return daysLeft;
    }
    
    AdminUser dequeue()
    {
      return list.removeFirst();
    }
    
    int getSize() const
    {
      return list.getSize();
    }
    
  private:
    LinkedList list;
};
#endif