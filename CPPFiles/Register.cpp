//registration class which will take all info and put the user in the system.
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "../HFiles/Register.h"
using namespace std;


Register::Register(){
    input();
}

User Register::getUser(){
    return tempUser;
}

Card Register::getCard(){
    return tempCard;
}

void Register::generateUserName(){
    srand(time(NULL));
    string tempUserName = tempUser.firstName[0] + tempUser.lastName + to_string(rand()%90 + 10);
    
    while(checkExistingUserName(tempUserName)){
        tempUser.userName = tempUser.firstName.at(0) + tempUser.lastName + to_string(rand()%90 + 10);
    }
    
    tempUser.userName = tempUserName;
    tempCard.userName = tempUser.userName;
}


void Register::makeQues(){
    questions = new string[6];
    questions[0] = "Where is your hometown:";
    questions[1] = "Name of your first pet:";
    questions[2] = "Your first teacher:";
    questions[3] = "Your Favourite destination:";
    questions[4] = "Favourite color:";
    questions[5] = "Best friend's name:";
}

void Register::setSecurityAns(){
    int a, b, c;
    for(int i=0; i<6; i++){
        cout<< i+1<<". "<<questions[i]<<endl;
    }
    cout<<"Enter the serial number of 3 questions you want to set up as security question: ";
    cin>>a>>b>>c;
    
    tempUser.security = new string*[3];
    for(int i=0; i <3;i++){
        tempUser.security[i] = new string[2];
    }
    tempUser.security[0][0] = questions[a-1];
    tempUser.security[1][0] = questions[b-1];
    tempUser.security[2][0] = questions[c-1];
    
    cout<< a<<". "<<tempUser.security[0][0];
    cin>>tempUser.security[0][1];
    cout<< b<<". "<<tempUser.security[1][0];
    cin>>tempUser.security[1][1];
    cout<< c<<". "<<tempUser.security[2][0];
    cin>>tempUser.security[2][1];
}

bool Register::checkExistingUserName(string s){
    fstream file;
    string line;
    file.open("Records/user_input.csv");
    getline(file, line);
    int pos;
    string tempUser="";
    while(getline(file,line) && tempUser!= s){
        pos = line.find(",");
        tempUser = line.substr(0,pos);
        if(tempUser==s){
            return true;
            break;
        }
    }
    return false;
    file.close();
}

bool Register::checkExistingEmail(string em){
    fstream file;
    string line;
    file.open("Records/user_input.csv");
    getline(file, line);
    int pos;
    while(getline(file,line) && tempUser.email!= em){
        pos = line.find(",");
        line.erase(0,pos+1);
        pos = line.find(",");
        tempUser.email = line.substr(0,pos);
        if(tempUser.email==em){
            return true;
        }
    }
    return false;
    file.close();
}

bool Register::checkExistingCardNum(string l){
    fstream file;
    string line;
    file.open("Records/user_input.csv");
    getline(file, line);
    int pos;
    string cnum;
    while(getline(file,line) && tempCard.cardNum!= l){
        pos = line.find(",");
        line.erase(0,pos+1);
        pos = line.find(",");
        line.erase(0,pos+1);
        pos = line.find(",");
        line.erase(0,pos+1);
        pos = line.find(",");
        line.erase(0,pos+1);
        pos = line.find(",");
        line.erase(0,pos+1);
        pos = line.find(",");
        line.erase(0,pos+1);
        pos = line.find(",");
        if(tempCard.cardNum==l){
            return true;
            break;
        }
    }
    return false;
    file.close();
}

void Register::input(){
    cout<<"Enter your e-mail: ";
    cin>>tempUser.email;
    if(!checkExistingEmail(tempUser.email)&&validateEmail(tempUser.email)){
        cout<<"Enter a password for your account: ";
        cin>>tempUser.password;
        cout<<"Enter your first name: ";
        cin>>tempUser.firstName;
        cout<<"Enter your last name: ";
        cin>>tempUser.lastName;
        cout<<"Enter you Date of Birth in MMDDYYYY format: ";
        cin>>tempUser.dob;
        while(!validateDate(tempUser.dob)){
            cout<<"Enter correct date in MMDDYYYY format: "<<endl;
            cin>>tempUser.dob;
        }
        cout<<"Enter your 16 digit card number: ";
        cin>>tempCard.cardNum;
        while(tempCard.cardNum.size()!=16 && isNum(tempCard.cardNum)){
            cout<<"Enter a valid 16-digit card number: ";
            cin>>tempCard.cardNum;
        }
        if(!checkExistingCardNum(tempCard.cardNum)){
            cout<<"Enter 3 digit number on back of your card: ";
            cin>>tempCard.cvv;
            while(tempCard.cvv.size()!=3 && isNum(tempCard.cvv)){
                cout<<"Enter a valid 3-digit cvv: ";
                cin>>tempCard.cvv;
            }
            cout<<"Enter the expiry date of your card in MMYY format: ";
            cin>>tempCard.expiry;
            while(!validateCardExpiry(tempCard.expiry)){
                cout<<"Enter a valid expiry of your card in MMYY format: ";    
                cin>>tempCard.expiry;
            }
            makeQues();
            setSecurityAns();
            generateUserName();
            cout<<"REGISTRATION SUCCESSFUL"<<endl;
            writeToFile();
            cout<<"Your automated username is: "<<tempUser.userName << endl;
        }
        else{
            cout<<"This card number is already registered. REGISTRATION FAILED"<<endl;
        }
    }
    else{
        if(!validateEmail(tempUser.email)){
            cout<<"Incorrect Email"<<endl;
        }
        else{
            cout<<"This email is already registered. REGISTRATION FAILED"<<endl;   
        }
    }
}

void Register::writeToFile(){
    fstream file;
    string str="";
    string s = tempUser.userName+","+tempUser.email+","+tempUser.password+","+tempUser.firstName+","+tempUser.lastName+","+tempUser.dob+","+tempCard.cardNum+","+tempCard.expiry+","+tempCard.cvv;
    for(int i=0; i<3;i++){
        s += "," +tempUser.security[i][0];
    }
    for(int i=0; i<3;i++){
        s += "," +tempUser.security[i][1];
    }
    s+="\n";
    file.open("Records/user_input.csv",ios::app);
    file<<s;
    file.close();
    
    file.open("Records/bank_info.csv", ios::app);
    str+=tempUser.userName + ",0,0,n/a,0.0,0,0,0,0,0\n";
    file << str;
    file.close();
}

bool Register::validateEmail(string s){
    if((s.find("@")!=-1)&&(s.find("@")!=0)&&(s.find(".")!=-1)&&(s.find(".")!=0)&&(s.find("@")!=s.size()-1)&&(s.find(".")!=s.size()-1)){
        int pos =  s.find("@");
        string temps = s.substr(0,pos)+s.substr(pos+1);
        if(temps.find("@")!=-1){
            return false;
        }
        temps = s.substr(pos+2);
        pos = temps.find(".");
        if(pos==-1){
            return false;
        }
        else{
            return true;    
        }
    }
    else{
        return false;
    }
}

bool Register::isLeapYear(int y){
    if(y%4 == 0){
        if(y%100 == 0){
            if(y%400 == 0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return true;
        }
        
    }
    return false;
}

bool Register::isNum(string s){
    for(int i=0; i<s.size();i++){
        if(!isdigit(s[i])){
            cout<<"Not a num";
            return false;
        }
    }
    return true;
}

bool Register::validateDate(string s){
    if(isNum(s) && s.size()==8){
        int m = stoi(s.substr(0,2));
        s.erase(0,2);
        int d = stoi(s.substr(0,2));
        s.erase(0,2);
        int y = stoi(s);
        if(m<=12 && m>=1){
            if(y<=2002 && y>= 1980){
                if(isLeapYear(y) && m == 2){
                    if(d>=1 && d<=29){
                        return true;
                    }
                    else{
                        //cout<<"Wrong in leap";
                        cout<<"Incorrect Date"<<endl;
                        return false;
                    }
                }
                else{
                    if(m == 1 || m==3 || m == 5 || m==7 || m == 8 || m==10 || m==12){
                        if(d>=1 && d<=31){
                            return true;
                        }
                        else{
                            //cout<<"Wrong in 31";
                            cout<<"Incorrect Date"<<endl;
                            return false;
                        }
                    }
                    else{
                        if(d>=1 && d<=30){
                            return true;
                        }
                        else{
                            //cout<<"Wrong in 30";
                            cout<<"Incorrect Date"<<endl;
                            return false;
                        }
                    }    
                }
            }
            else{
                //cout<<"wrong year";
                cout<<"Incorrect Date"<<endl;
                return false;
            }
        }
        else{
            cout<<"Incorrect Date"<<endl;
            return false;
        }
    }
    else{
        cout<<"Incorrect Date format"<<endl;
        return false;
    }
}

//TODO USE DATE PACKAGE
bool Register::validateCardExpiry(string s){
    if(isNum(s) && s.size()==4){
        int m = stoi(s.substr(0,2));
        int y = stoi(s.substr(2));
        if(m<=12 && m>=1){
            if(y>21){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
}
