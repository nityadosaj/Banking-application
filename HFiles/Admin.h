#ifndef ADMIN_H
#define ADMIN_H

#include<string>
#include "../StructFiles/AdminStruct.h"
#include "PQueue.h"
class Admin{
    public:
        void readFile();
        //sortList();
        //searchUser();
        //void operator +=();        //displayList();
        PQueue makeQueue();
        void displayLoan(PQueue);
        void displayAll();
        
        void makeTree();
        void insertInTree(AdminUser e);
        void searchInTree(Node<AdminUser> * parent,string u);
        
        AdminUser au;
        Admin();
        
        Node<AdminUser> *root;
        LinkedList theList;
        
    private:
        
};

#endif