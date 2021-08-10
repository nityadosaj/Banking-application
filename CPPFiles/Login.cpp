#include "../HFiles/Node.h"
#include "../HFiles/Login.h"
#include "../HFiles/BankMenu.h"
#include<iostream>
#include<string>
#include<ctime>
using namespace std;

Login::Login()
{}
Login::Login(Node<User> * head)
{
    input(head);
}

bool Login::checkSecurityQues(Node<User> * head, string un)
{
    srand(time(0));
    bool result = false;
    Node<User> *temp = head;
    int ques;
    string answer;
    ques = rand()%3;
    while(temp!= nullptr){
    	if(temp->getElement().userName == un){
            cout << temp->getElement().security[ques][0];
            cin >> answer;
            if(temp->getElement().security[ques][1] == answer){
                result = true;
            }
            else{
                cout << "Wrong answer" << endl;
            }
            break;
        }
        else{
            temp = temp->next;    
        }
    }
    return result;
}

bool Login::loginSuccess(Node<User> *head, string un, string pass){
    if(checkExisting(head, un, pass) ){
        //cout<<"existing working";
        if(checkSecurityQues(head,un)){
            //cout<<"security working";
            return true;
        }
    }
    else
        return false;
}

bool Login::checkExisting(Node<User> * head, string un, string pass)
{   
    bool result = false;
    Node<User>* temp = head;
    while(temp!= nullptr){
    	if(temp->getElement().userName == un){
    	    if(pass == temp->getElement().password){
    		    result = true;
    	    }
    	    else{
    		    cout << "INCORRECT PASSWORD" << endl;
    	    }
    	    break;
        }
        else{
            temp = temp->next;
        }
    }
    
    delete temp;
    return result;
}

void Login::input(Node<User> * head)
{
    string un, pass;
    cout <<"Login" << endl;
    cout << "User Name : ";
    cin >> un;
    cout << "Password : ";
    cin >> pass;
    if(loginSuccess(head, un, pass))
    {
        setUserName(un);
        setPassword(pass);
        BankMenu b = BankMenu(un);
    }
    else
    {
        cout << "Login failed" << endl;
    }
    
}

void Login::setUserName(string un){
    this->un = un;
}

void Login::setPassword(string pass){
    this->pass = pass;
}

string Login::getUserName(){
    return this->un;
}

string Login::getPassword(){
    return this->pass;
}