#include <iostream>
#include <string>
#include "../StructFiles/CardStruct.h"
#include "../StructFiles/UserStruct.h"
using namespace std;

class Register
{
    public:
        Register();
        
        void generateUserName();
        User getUser();
        Card getCard();
        
        void makeQues();
        void setSecurityAns();
        void input();
        void writeToFile();
        
    private:
        User tempUser;
        Card tempCard;
        string* questions;
        
        bool checkExistingEmail(string);
        bool checkExistingUserName(string);
        bool checkExistingCardNum(string);
        
        bool validateEmail(string);
        bool validateDate(string);
        bool isNum(string);
        bool isLeapYear(int);
        bool validateCardExpiry(string);
};
