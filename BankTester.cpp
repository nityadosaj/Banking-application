#include "HFiles/Node.h"
#include "HFiles/Login.h"
#include "HFiles/Register.h"
#include "HFiles/BankMenu.h"
#include "HFiles/Admin.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

void readFile(Node<User>**, Node<User>**, Node<Card>**, Node<Card>**);
void pushData(Node<User> ** refU, Node<Card> ** refC, User u, Card c);

int main()
{
    Node<User> *headU = nullptr;
    Node<User> *tailU = nullptr;
    Node<Card> *headC = nullptr;
    Node<Card> *tailC = nullptr;
    Login l;
    
    int lr = 0;
    
    cout << "Welcome to (set bank name). \nPlease login or register" << endl;
    while(lr != 4)
    {
        readFile(&headU, &tailU, &headC, &tailC);
        cout << "1.Login" << endl;
        cout << "2.Register" << endl; 
        cout << "3.Admin" << endl;
        cout << "4.Exit" <<endl;
        cin >> lr;
        if(lr == 1)
        {
            l = Login(headU);
        }
        else if(lr == 2)
        {
           Register r = Register();
        }
        else if(lr == 3)
        {
            Admin au = Admin();
        }
        else if(lr < 1 || lr > 4)
            cout << "Wrong input. Try Again" << endl;
        else
            cout << "Thank you for banking with us." << endl;
    }
    
}

void readFile(Node<User>** head_refU, Node<User>** tail_refU, Node<Card>** head_refC, Node<Card>** tail_refC)
{
    ifstream input;
    input.open("Records/user_input.csv");
    string line;
    int pos;
    
    getline(input,line);
    User u;
    Card c;
    
    while(getline(input,line))
    {
        u.security = new string*[3];
        for(int i=0; i<3; i++){
            u.security[i] = new string[2];
        }
        pos = line.find(",");
        u.userName = line.substr(0,pos);
        c.userName = u.userName;
        line.erase(0,pos+1);
        
        pos = line.find(",");
        u.email = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        u.password = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        u.firstName = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        u.lastName = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        u.dob = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        c.cardNum = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        c.expiry = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        c.cvv = line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        u.security[0][0] =  line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        u.security[1][0] =  line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        u.security[2][0] =  line.substr(0,pos);
        line.erase(0,pos+1);
        
        pos = line.find(",");
        u.security[0][1] =  line.substr(0,pos);
        line.erase(0,pos+1);
        pos = line.find(",");
        u.security[1][1] =  line.substr(0,pos);
        line.erase(0,pos+1);
        pos = line.find(",");
        u.security[2][1] =  line.substr(0,pos);
        
        if((*head_refC) == nullptr && (*head_refU) == nullptr)
        {
            pushData(head_refU, head_refC, u, c);
            (*tail_refU) = (*head_refU);
            (*tail_refC) = (*head_refC);
        }
        else
            pushData(tail_refU, tail_refC, u, c);
    }
    input.close();
}

void pushData(Node<User> ** refU, Node<Card> ** refC, User u, Card c)
{
    Node<User>* new_nodeU = new Node<User>(u);
    Node<Card>* new_nodeC = new Node<Card>(c);
    
    if(*refU == nullptr && *refC == nullptr )
    {
        (*refU) = new_nodeU;
        (*refC) = new_nodeC;
    }
    else{
        new_nodeU->prev = (*refU);
        (*refU)->next = new_nodeU;
        (*refU) = new_nodeU;
        
        new_nodeC->prev = (*refC);
        (*refC)->next = new_nodeC;
        (*refC) = new_nodeC;
    }
}

