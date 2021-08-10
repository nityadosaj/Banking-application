#ifndef LINKLIST_H
#define LINKLIST_H

#include "../StructFiles/AdminStruct.h"
#include "Node.h"

class LinkedList {
    public:
        LinkedList();
        ~LinkedList();
        void addFirst(AdminUser e);
        int getSize() const;
        void clear();
        AdminUser get(int index) const;
        
        AdminUser removeFirst();
    
        bool contains(int element) const; // returns true if it contains the element
        
        void mergeSort();
        Node<AdminUser>* mergeSort(Node<AdminUser>* t_head);
        void displayList();
        
        void insert(int priority, const AdminUser&e);
    private:
        Node<AdminUser> * head;
        Node<AdminUser> * tail;
        int size;
        
};

#endif