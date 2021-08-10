#include "../StructFiles/AdminStruct.h"
#include "../HFiles/Admin.h"
#include "../HFiles/PQueue.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

Admin::Admin(){
    root = nullptr;
    readFile();
    makeTree();
    Node<AdminUser> * temp = root;
    int op = 0;
    cout << "Welcome Admin. Please enter your 4 digit pin number" << endl;
    cin >> op;
    
    if(op == 1234)
    {
        cout << "Authorization Confirmed." << endl;
        while(op != 4)
        {
            cout << "1. Display all records" << endl; //already sorted
            cout << "2. Display about loans" << endl; //by priority
            cout << "3. Search by username" << endl;
            cout << "4. Logout" << endl;
            cin >> op;
            
            if(op == 1)
            {
                theList.mergeSort();
                displayAll();
            }
            else if(op == 2)
            {
                displayLoan(makeQueue());
            }
            else if(op == 3)
            {
                string u;
                cout << "Enter the username you want to search" << endl;
                cin >> u;
                searchInTree(temp,u);
            }
            else if(op < 1 || op > 4) 
                cout << "Incorrect input!" << endl;
            else
                cout << "GoodBye!" << endl; 
        }
        
    }
}

string readFromBankInfo(string u){
    ifstream in;
    string line;
    string str="";
    int pos;
    bool result = false;
    string user;
    
    in.open("Records/bank_info.csv");
    getline(in,line);
    
    while(getline(in,line))
    {
        pos = line.find(",");
        user = line.substr(0,pos);
        if(u == user){
            str = line;
            return str;
        }
        line.erase();
    }
    return str;
}

void Admin::readFile(){
    AdminUser au;
    fstream file;
    string line;
    int pos;
    file.open("Records/user_input.csv");
    getline(file,line);
    while(getline(file,line)){
        pos = line.find(",");
        au.userName = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        au.email = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        au.password = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        au.firstName = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        au.lastName = line.substr(0,pos);
        line.erase(0,pos+1);
        
        //dob
        pos = line.find(",");
        line.erase(0,pos+1);
        
        pos = line.find(",");
        au.cardNum = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        au.expiry = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        au.cvv = line.substr(0,pos);
        line.erase(0,pos+1);
        
        string line = readFromBankInfo(au.userName);
        if(line!=""){
            pos = line.find(",");
            line.erase(0,pos+1);
            
            pos = line.find(",");
            au.balance = stod(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            line.erase(0,pos+1);
            
            pos = line.find(",");
            au.loanType = line.substr(0,pos);
            line.erase(0,pos+1);
            
            pos = line.find(",");
            au.loanAmount = stod(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            au.loanTime = stoi(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            au.interestRate = stod(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            au.dueDate = stoi(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            au.dueMonth = stoi(line.substr(0,pos));
            line.erase(0,pos+1);
            
            pos = line.find(",");
            au.dueYear = stoi(line.substr(0,pos));
            
            au.paidLoan = stod(line.substr(pos+1));
        }
        theList.addFirst(au);
    }
}

PQueue Admin::makeQueue(){
    PQueue myQueue;
    for(int i=0; i<theList.getSize();i++){
        myQueue.enqueue(theList.get(i));
    }
    return myQueue;
}

void Admin::displayLoan(PQueue myQueue){
    AdminUser temp;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << setw(10) << "User Name" << setw(15) << "Loan type" << setw(15) << "Loan Amount" << setw(12) << "Loan Time" << setw(15) << "Interest Rate" << setw(12) << "Due Date" << setw(10) << "Loan Paid" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    for(int i=0; i<myQueue.getSize();i++){
        temp = myQueue.dequeue();
        cout << setw(10) << temp.userName << setw(15) << temp.loanType << setw(10) << temp.loanAmount << setw(12) << temp.loanTime << setw(15) << temp.interestRate << setw(10) << temp.dueDate << "/" << temp.dueMonth << "/" << temp.dueYear << setw(10) << temp.paidLoan << endl;
        i--;
    }
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

//PREV IS LEFT 
//NEXT IS RIGHT
void Admin::insertInTree(AdminUser e){
    Node<AdminUser>* newNode = new Node<AdminUser>(e);
    if(root == nullptr){
        root = newNode;
    }
    else{
        Node<AdminUser>* temp = root;
        Node<AdminUser>* parent;
        while(temp!=nullptr){
            if(e.userName < temp->getElement().userName){
                parent = temp;
                temp = temp->prev;
            } 
            else{
                parent = temp;
                temp = temp->next;
            }
        }
        if(parent->getElement().userName>e.userName){
            parent->prev = newNode;
        }
        else{
            parent->next = newNode;
        }    
    }
}

void Admin::makeTree(){
    for(int i=0; i<theList.getSize();i++){
        insertInTree(theList.get(i));
    }
}

void Admin::searchInTree(Node<AdminUser>* parent, string u){
    if(parent == nullptr)
    {
        cout << "User not found" << endl;
        return;
    }
    else if(parent->getElement().userName == u)
    {
        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << setw(10) << "User name" << setw(20) << "Email" << setw(18) << "Password" << setw(12) << "First Name" << setw(12) << "Last Name" << setw(14) << "Card Num" << setw(12) << "Expiry" << setw(5) << "CVV" << setw(10) << "Balance" << setw(10) << "Loan Type" << setw(13) << "Loan Amount" << setw(11) << "Loan Time" << setw(16) << "Interest rate" << setw(10) << "Due date" << setw(12) << "Loan Paid" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setw(10) << parent->getElement().userName << setw(25) << parent->getElement().email << setw(13) << parent->getElement().password << setw(12) << parent->getElement().firstName << setw(12) << parent->getElement().lastName << setw(18) << parent->getElement().cardNum << setw(7) << parent->getElement().expiry << setw(6) << parent->getElement().cvv << setw(10) << parent->getElement().balance << setw(10) << parent->getElement().loanType << setw(10) << parent->getElement().loanAmount << setw(10) << parent->getElement().loanTime << setw(12) << parent->getElement().interestRate << setw(11) << parent->getElement().dueDate << "/" << parent->getElement().dueMonth << "/" << parent->getElement().dueYear << setw(10) << parent->getElement().paidLoan << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        
    }else if(u < parent->getElement().userName)
        return searchInTree(parent->prev, u);
    else
        return searchInTree(parent->next,u);
}

void Admin::displayAll()
{
    AdminUser temp;
    double tsum = 0, lsum = 0, leftAmount = 0;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << setw(10) << "User name" << setw(20) << "Email" << setw(18) << "Password" << setw(12) << "First Name" << setw(12) << "Last Name" << setw(14) << "Card Num" << setw(12) << "Expiry" << setw(5) << "CVV" << setw(10) << "Balance" << setw(10) << "Loan Type" << setw(13) << "Loan Amount" << setw(11) << "Loan Time" << setw(16) << "Interest rate" << setw(10) << "Due date" << setw(12) << "Loan Paid" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for(int i=0; i<theList.getSize();i++){
        temp = theList.get(i);
        cout << setw(10) << temp.userName << setw(25) << temp.email << setw(13) << temp.password << setw(12) << temp.firstName << setw(12) << temp.lastName << setw(18) << temp.cardNum << setw(7) << temp.expiry << setw(6) << temp.cvv << setw(10) << temp.balance << setw(10) << temp.loanType << setw(10) << temp.loanAmount << setw(10) << temp.loanTime << setw(12) << temp.interestRate << setw(11) << temp.dueDate << "/" << temp.dueMonth << "/" << temp.dueYear << setw(10) << temp.paidLoan << endl;
        tsum += temp.balance+temp.paidLoan;
        lsum += temp.loanAmount;
        leftAmount += temp.loanAmount - temp.paidLoan;
    }
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    cout << "The total money the bank has is $" << tsum << endl;
    cout << "Total money lent in loans : $" << lsum << endl;
    cout << "Total money left to pay for loans : $" << leftAmount << endl;
}