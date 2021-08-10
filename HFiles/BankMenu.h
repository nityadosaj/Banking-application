#ifndef BANKMENU_H
#define BANKMENU_H
#include "Date.h"
#include <string>
using namespace std;

class BankMenu
{
public:
    static Date d;
    BankMenu();
    BankMenu(string);
    void input();
    void updateBalance(); //add one year interest rate
    void withdraw();
    
    string getUserName();
    double getBalance();
    string getLoanType();
    double getInterestRate();
    int getYears();
    double getTransferAmount();
    double getLoanAmount();
    int getDueDay();
    int getDueMonth();
    int getDueYear();
    double getInstallments();
    double setInstallments();
    
    void setUserName(string);
    void setBalance(double);
    void setInterestRate(double);
    void setLoanAmount(double);
    void setYear(int);
    void setLoanType(string);
    void setTransferAmount(double);
    void setDueDay(int);
    void setDueMonth(int);
    void setDueYear(int);
    void readInstallments(double);
    
    void readFile(string);
    void transferToAccount();
    void acceptTransfer();
    void takeLoan();
    void payLoan();
    void messagePrompts();
    bool checkFunds(double);
    void updateFile(string);
    void updateTransferAccount(string);
    bool readUser(string);
    void PersonalLoan();
    void Mortgage();
    void StudentLoan();
    void AutoLoan();
    int checkDueDates();
   
 private:
    
    string userName;
    double rate;
    int year;
    double loanAmount;
    string loanType;
    double transferAmount, installments;
    int dueDay, dueMonth, dueYear;
    int accountDollars; //of balance
    int accountCents; //of balance
    
    
    int dollarsPart(double amount);
    int centsPart(double amount);
    int round(double number);

    double fraction(double percent);
    //Converts a percent to a fraction. For example, fraction(50.3) returns 0.503.
};


#endif