#include "../HFiles/BankMenu.h"
#include "../HFiles/Date.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

Date BankMenu::d = Date();

BankMenu::BankMenu()
{
   
}

BankMenu::BankMenu(string u)
{
    int num = 0;
    cout << "Welcome to ABC Bank.\nSelect from the following options" << endl;
    while(num != 8)
    {
        setUserName(u);
        readFile(getUserName());
        messagePrompts();
        cout << "1. Withdraw" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Show Balance" << endl;
        cout << "4. Transfer to another account" << endl;
        cout << "5. Accept Transfers" << endl;
        cout << "6. Take Loans" << endl;
        cout << "7. Pay Loans" << endl;
        cout << "8. Logout" << endl;
        cin >> num;
        
        if(num == 1)
        {
            withdraw();
            updateFile(getUserName()); 
        }
        else if(num == 2)
        {
            input();
            updateFile(getUserName());
        }
        else if(num == 3)
        {
            cout << "Your balance : " << getBalance() << endl;
        }
        else if(num == 4)
        {
            transferToAccount();
        }
        else if(num == 5)
        {
            acceptTransfer(); 
        }
        else if(num == 6)
        {
            takeLoan();
            setDueDay(BankMenu::d.getCurrDay());
            setDueMonth(BankMenu::d.getCurrMonth());
            setDueYear(BankMenu::d.getCurrYear()+getYears());
            updateFile(getUserName());
        }
        else if(num == 7)
        {
            payLoan();
        }
        else if(num < 1 || num > 8)
            cout << "Please enter a valid input!" << endl;
        else
            cout << "GoodBye!!" << endl;
    }
}

void BankMenu::readFile(string u)
{
    ifstream in;
    string line;
    int pos;
    double balance;
    string user;
    in.open("Records/bank_info.csv");
    getline(in,line);
    
    while(getline(in,line))
    {
        pos = line.find(",");
        user = line.substr(0,pos);
        line.erase(0,pos+1);
        
        if(user == u)
        {
            pos = line.find(",");
            balance = stod(line.substr(0,pos));
            line.erase(0,pos+1);
           
            pos = line.find(",");
            transferAmount = stod(line.substr(0,pos));
            line.erase(0,pos+1);
        
            pos = line.find(",");
            loanType = line.substr(0,pos);
            line.erase(0,pos+1);
            
            pos = line.find(",");
            loanAmount = stod(line.substr(0,pos));
            line.erase(0,pos+1);
        
            pos = line.find(",");
            year = stoi(line.substr(0,pos));
            line.erase(0,pos+1);
        
            pos = line.find(",");
            rate = stod(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            dueDay = stoi(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            dueMonth = stoi(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            dueYear = stoi(line.substr(0,pos));
            
            installments = stod(line.substr(pos+1));
            
            setBalance(balance);
            setTransferAmount(transferAmount);
            setLoanType(loanType);
            setLoanAmount(loanAmount);
            setYear(year);
            setInterestRate(rate);
            setDueDay(dueDay);
            setDueMonth(dueMonth);
            setDueYear(dueYear);
            readInstallments(installments);
            setInstallments();
        }
    }
}

void BankMenu::input()
{
    double balance;
    
    cout << "Enter account balance $";
    cin >> balance;
    
    setBalance(balance+getBalance());
    
    setInterestRate(1);
}

void BankMenu::setBalance(double balance)
{
    accountDollars = dollarsPart(balance);
    accountCents = centsPart(balance);
}

void BankMenu::updateBalance() //at logout
{
    double balance = getBalance();
    balance += fraction(1) * balance;
    accountDollars = dollarsPart(balance);
    accountCents = centsPart(balance);
}

void BankMenu::withdraw()
{
    double w;
    cout << "Enter an amount $";
    cin >> w;
    
    double balance = getBalance();
    
    if(checkFunds(w))
    {
        balance -= w;
        setBalance(balance);
    }
    else
        cout << "Insufficient funds!!" << endl;
}

double BankMenu::getBalance()
{
    return (accountDollars + accountCents*0.01);
}

void BankMenu::transferToAccount()
{
    double amount;
    string u;
    cout << "Enter the username of the person you want to transfer money to:" << endl;
    cin >> u;
    
    if(readUser(u))
    {
        cout << "Enter amount to transfer $";
        cin >> amount;
        
        if(checkFunds(amount))
        {
            setBalance(getBalance() - amount);
            setTransferAmount(amount);
            updateTransferAccount(u);
            updateFile(getUserName());
            
        }
        else
            cout << "Insufficient funds!!" << endl;
    }
    else
        cout << "User not found!" << endl;
}

void BankMenu::updateFile(string u)
{
    ifstream in;
    ofstream out, app;
    string line;
    string temp;
    double b = 0;
    in.open("Records/bank_info.csv");
    out.open("Records/temp.csv", ios::out);
    
    getline(in,line);
    out << line << endl;
    
    while(getline(in,line))
    {
        int pos = line.find(",");
        temp = line.substr(0,pos);
        if(u != temp)
            out << line << endl;
        
        line.erase();
    }
    out.close();
    in.close();
    
    remove("Records/bank_info.csv");
    rename("Records/temp.csv" , "Records/bank_info.csv");
    
    app.open("Records/bank_info.csv", ios::app);
    app << u << "," << getBalance() << ",0," << getLoanType() << "," << getLoanAmount() << "," << getYears() << "," << getInterestRate() << "," << getDueDay() << "," << getDueMonth() << "," << getDueYear() << "," << getInstallments() << endl ;
    app.close();
}

void BankMenu::updateTransferAccount(string u)
{
    ifstream in;
    ofstream out, app;
    string line;
    string temp;
    double b,de,am,r,ins;
    int day,m,y,ti;
    string ltype;
    in.open("Records/bank_info.csv");
    out.open("Records/temp.csv", ios::out);
    
    getline(in,line);
    out << line << endl;
    
    while(getline(in,line))
    {
        int pos = line.find(",");
        temp = line.substr(0,pos);
        if(u != temp)
            out << line << endl;
        else
        {
            line.erase(0,pos+1);
            
            pos = line.find(",");
            b = stod(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            de = stod(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            ltype = line.substr(0,pos);
            line.erase(0,pos+1);
            
            pos = line.find(",");
            am = stod(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            ti = stoi(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            r = stod(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            day = stoi(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            m = stoi(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            y = stoi(line.substr(0,pos));
            
            ins = stod(line.substr(pos+1));
        }
        
        line.erase();
    }
    out.close();
    in.close();
    
    remove("Records/bank_info.csv");
    rename("Records/temp.csv" , "Records/bank_info.csv");
    
    app.open("Records/bank_info.csv", ios::app);
    app << u << "," << b << ","<< de+getTransferAmount() << "," << ltype << "," << am << "," << ti << "," << r << "," << day << "," << m << "," << y << "," << ins <<endl ;
    app.close();
}

bool BankMenu::readUser(string u)
{
    ifstream in;
    string line;
    int pos;
    bool result = false;
    string user;
    
    in.open("Records/bank_info.csv");
    getline(in,line);
    
    while(getline(in,line))
    {
        pos = line.find(",");
        user = line.substr(0,pos);
        if(u == user)
            result = true;
        line.erase();
    }
    
    return result;
}

bool BankMenu::checkFunds(double w)
{
    if(w < getBalance())
        return true;
    else
        return false;
}

void BankMenu::acceptTransfer()
{
    if(getTransferAmount() > 0)
    {
        setBalance(getBalance()+getTransferAmount());
        setTransferAmount(0);
        cout << "Transfer accepted" << endl;
    }
    else
        cout << "You do not have any transfers to accept" << endl;
        
    updateFile(getUserName());
}

void BankMenu::takeLoan()
{
    int num;
    cout << "Select which loan you want to take:" << endl;
    cout << "1. Personal Loan" << endl;
    cout << "2. Mortgage" << endl;
    cout << "3. Student Loan" << endl;
    cout << "4. Auto Loan" << endl;
    cout << "5. Go back" << endl;
    cin >> num;
    
    if( num == 1)
    {
        setLoanType("personal");
        PersonalLoan();
    }
    else if(num == 2)
    {
        setLoanType("mortgage");
        Mortgage();
    }
    else if(num == 3)
    {
        setLoanType("student");
        StudentLoan();
    }
    else if(num == 4)
    {
        setLoanType("auto");
        AutoLoan();
    }
    else if(num > 5 || num < 1)
    {
        cout <<"Not a valid option" << endl;
    }
}

void BankMenu::PersonalLoan()
{
    double am;
    double rate;
    int years;
    cout << "Enter an amount you need $";
    cin >> am;
    
    if(am >= 30000 && am < 50000)
    {
        rate = 3;
        years = 2;
        setLoanAmount(am);
        setInterestRate(rate);
        setYear(years);
        readInstallments(setInstallments());
    }
    else if(am >= 50000 && am < 65000)
    {
        rate = 5;
        years = 4;
        setLoanAmount(am);
        setInterestRate(rate);
        setYear(years);
        readInstallments(setInstallments());
        
    }
    else if(am >= 65000)
    {
        rate = 7;
        years = 6;
        setLoanAmount(am);
        setInterestRate(rate);
        setYear(years);
        readInstallments(setInstallments());
    }
    else if(am <30000)
    {
        cout << "Our loan amount starts from $30000. Please enter an amount after it" << endl;
    }
}

void BankMenu::Mortgage()
{
    double am;
    double rate;
    int years;
    cout << "Enter an amount you need $";
    cin >> am;
    
    if(am >= 500000 && am < 1000000)
    {
        rate = 7;
        years = 5;
        setLoanAmount(am);
        setInterestRate(rate);
        setYear(years);
        readInstallments(setInstallments());
    }
    else if(am >= 1000000 && am < 1500000)
    {
        rate = 10;
        years = 10;
        setLoanAmount(am);
        setInterestRate(rate);
        setYear(years);
        readInstallments(setInstallments());
    }
    else if(am >= 1500000)
    {
        rate = 12;
        years = 15;
        setLoanAmount(am);
        setInterestRate(rate);
        setYear(years);
        readInstallments(setInstallments());
    }
    else if(am <500000)
    {
        cout << "Our loan amount starts from $500000. Please enter an amount after it" << endl;
    }
        
}

void BankMenu::StudentLoan()
{
    double am;
    double rate;
    int years;
    cout << "Enter an amount you need $";
    cin >> am;
    
    if(am >= 15000 && am <= 20000)
    {
        rate = 2.5;
        years = 4;
        setLoanAmount(am);
        setInterestRate(rate);
        setYear(years);
        readInstallments(setInstallments());
    }
    else if(am < 15000)
    {
        cout << "Our loan amount starts from $15000. Please enter an amount after it" << endl;
    }
}

void BankMenu::AutoLoan()
{
    double am;
    double rate;
    int years;
    cout << "Enter an amount you need $";
    cin >> am;
    
    if(am >= 30000 && am < 40000)
    {
        rate = 5;
        years = 6;
        setLoanAmount(am);
        setInterestRate(rate);
        setYear(years);
        readInstallments(setInstallments());
    }
    else if(am >= 40000 && am < 50000)
    {
        rate = 6;
        years = 7;
        setLoanAmount(am);
        setInterestRate(rate);
        setYear(years);
        setInstallments();
    }
    else if(am >= 50000)
    {
        rate = 7;
        years = 8;
        setLoanAmount(am);
        setInterestRate(rate);
        setYear(years);
        readInstallments(setInstallments());
    }
    else if(am < 30000)
    {
        cout << "Our loan amount starts from $30000. Please enter an amount after it" << endl;
    }
}

void BankMenu::payLoan()
{
    char option;
    cout << "You took a " << getLoanType() << " loan. The due date is " << getDueDay() << "/" << getDueMonth() << "/" << getDueYear() << endl;
    cout << "Your monthly installments are of $" << setInstallments() << endl;
    
    while(option != 'n')
    {
        cout <<"Enter (y) to pay your installment or (n) to go back:" << endl;
        cin >> option;
        if(option == 'y')
        {
            if(checkFunds(setInstallments()))
            {
                setBalance(getBalance() - setInstallments());
                readInstallments(getInstallments() + setInstallments());
                updateFile(getUserName());
                cout << "Transaction Successful" << endl;
            }
            else
                cout << "Insufficient funds!";
        }
        else if(option != 'y' || option != 'n')
            cout << "Enter a character between (y) or (n)" << endl;
        else if(option == 'n')
        {
            if(getLoanAmount() == getInstallments())
                cout << "You have successfully paid your loan" << endl;
            else
                cout << "You still have to pay $" << getLoanAmount() - getInstallments() << endl;
        }
    }
}

int BankMenu::checkDueDates()
{
    int day,m,y, daysLeft = 0;
    day = BankMenu::d.getCurrDay();
    m = BankMenu::d.getCurrMonth();
    y = BankMenu::d.getCurrYear();
    
    if(day == getDueDay() && m == getDueMonth() && y == getDueYear())
    {
        setDueDay(0);
        setDueMonth(0);
        setDueYear(0);
    }
    
    if(y <= getDueYear())
    {
        if(BankMenu::d.checkLeapYear(y))
        {
            if(m == 2)
            {
                if(getDueDay() <= 29)
                    daysLeft = getDueDay() - day;
                else
                    daysLeft = 0;
            }
            else if(m == 4 || m == 6 || m == 9 || m == 11 )
            {
                if(getDueDay() <= 30)
                    daysLeft = getDueDay() - day;
                else
                    daysLeft = 0;
            }
            else
                daysLeft = getDueDay() - day;
        }
        else
        {
            if(m == 2)
            {
                if(getDueDay() <= 28)
                    daysLeft = getDueDay() - day;
                else
                    daysLeft = 0;
            }
            else if(m == 4 || m == 6 || m == 9 || m == 11 )
            {
                if(getDueDay() <= 30)
                    daysLeft = getDueDay() - day;
                else
                    daysLeft = 0;
            }
            else
                daysLeft = getDueDay() - day;
        }
    }
    return daysLeft;
}

void BankMenu::messagePrompts()
{
    if(getTransferAmount() > 0)
    {
        cout << "You have a transfer to accept" << endl;
    }
    
    if(getLoanAmount() > 0)
    {
        cout << "You have " << checkDueDates() << " day(s) left to pay your loan." << endl;
    }
}

int BankMenu::dollarsPart(double amount)
{
    return static_cast<int>(amount);
}
int BankMenu::centsPart(double amount)
{
    double dc = amount*100;
    int intCents = (round(fabs(dc)))%100;
    
    if(amount < 0)
        intCents = -intCents;
    
    return intCents;
}

int BankMenu::round(double number)
{
    return static_cast<int>(floor(number+0.5));
}

double BankMenu::fraction(double percent)
{
    return (percent/100.0);
}

void BankMenu::setUserName(string u)
{
    userName = u;
}
    
void BankMenu::setInterestRate(double newRate)
{
    if (newRate >= 0.0)
        rate = newRate;
    else
    {
        cout << "Cannot have a negative interest rate." << endl;
        exit(1);
    }
}

void BankMenu::setLoanAmount(double am)
{
    loanAmount = am;
}
void BankMenu::setYear(int y)
{
    year = y;
}
void BankMenu::setLoanType(string s)
{
    loanType = s;
}
void BankMenu::setTransferAmount(double a)
{
    transferAmount = a;
}
void BankMenu::setDueDay(int d)
{
    dueDay = d;
}    
void BankMenu::setDueMonth(int m)
{
    dueMonth = m;
}
void BankMenu::setDueYear(int y)
{
    dueYear = y;
}

double BankMenu::setInstallments()
{
    double r = fraction(getInterestRate())/12;
    r += 1;
    double n = getYears() * 12;
    double product = pow(r,n);
    r -= 1;
    double ins = (product-1)/(r*product);
    return getLoanAmount()/ins;
}

void BankMenu::readInstallments(double i)
{
    installments = i;
}
string BankMenu::getLoanType()
{
    return loanType;
}
double BankMenu::getInterestRate()
{
    return rate;
}
int BankMenu::getYears()
{
    return year;
}
string BankMenu::getUserName()
{
    return userName;
}
double BankMenu::getTransferAmount()
{
    return transferAmount;
}
double BankMenu::getLoanAmount()
{
    return loanAmount;
}
int BankMenu::getDueDay()
{
    return dueDay;
}
int BankMenu::getDueMonth()
{
    return dueMonth;
}
int BankMenu::getDueYear()
{
    return dueYear;
}

double BankMenu::getInstallments()
{
    return installments;
}