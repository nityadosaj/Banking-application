#include "../HFiles/Node.h"
#include "../StructFiles/CardStruct.h"
#include "../StructFiles/UserStruct.h"
#include "../HFiles/BankMenu.h"

class Login
{
    public:
        Login();
        Login(Node<User> *head);
        //~Login();
        bool loginSuccess(Node<User> *head, string un, string pass);
        void input(Node<User> * head);
        void setUserName(string);
        void setPassword(string);
        string getUserName();
        string getPassword();
        
    private:
        string un;
        string pass;
        bool checkExisting(Node<User> * head, string un, string pass);
        bool checkSecurityQues(Node<User> * head,string un);
};