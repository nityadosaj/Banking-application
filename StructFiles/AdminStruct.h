#ifndef ADMINSTRUCT_H
#define ADMINSTRUCT_H

#include <string>
using namespace std;

struct AdminUser {
  string userName;
  string email;
  string password;
  string firstName;
  string lastName;
  string cardNum;
  string expiry;
  string cvv;
  double balance;
  string loanType;
  double loanAmount;
  int loanTime;
  double interestRate;
  int dueDate;
  int dueMonth;
  int dueYear;
  double paidLoan;
}; 


#endif