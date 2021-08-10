#include "../HFiles/LinkedList.h"
#include "../StructFiles/AdminStruct.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0 ;
}

LinkedList::~LinkedList() {
    clear(); 
}

void LinkedList::addFirst(AdminUser e) {
    Node<AdminUser> *temp = new Node<AdminUser>(e);
    temp->next = head;
    temp->prev = nullptr;
    if(head != nullptr)  
      head->prev = temp;
    head = temp;
    size++;
    
    if (tail == nullptr)
        tail = head;
}


int LinkedList::getSize() const{
  return size;
}

void LinkedList::clear(){
  while (head != nullptr){
    Node<AdminUser>* temp = head;
    head = head->next;
    delete temp;
    size--;
  }

  tail = nullptr;
  size = 0;
}


AdminUser LinkedList::get(int index) const {
  if (index < 0 || index > size - 1)
    throw "Out of range"; 

  Node<AdminUser>* current = head;
  int i=0;
  while(current!=nullptr && i!= index){
    current = current->next;
    i++;
  }
  if(i==index){
    return current->getElement();
  }
}

AdminUser LinkedList::removeFirst()
{
  if (size == 0)
    throw "No elements in the list";
  else{
    Node<AdminUser>* temp = head;
    head = head->next;
    if (head == nullptr) 
        tail = nullptr;
    size--;
    AdminUser element = temp->getElement();
    delete temp;
    return element;
  }
}

void LinkedList::insert(int priority, const AdminUser& e)
  {
    Node<AdminUser> *temp, *q;
    temp = new Node<AdminUser>(e);
 
    temp->priority = priority;
    if (size == 0 || priority < head->priority)
    {
      temp->next = head;
      if(head!=nullptr)
        head->prev = temp;
      head = temp;
    }
    else
    {
      q = head;
      while (q->next != NULL && q->next->priority <= priority)
        q = q->next;
      temp->next = q->next;
      temp->prev = q;
      q->next = temp;
    }
    size++;
}

Node<AdminUser>* partition(Node<AdminUser>* t_head){
    Node<AdminUser>* mid = t_head;
    Node<AdminUser>* end = t_head;
    
    while(end->next!=nullptr){
      end = end->next;
      if(end->next!=nullptr){
        end = end->next;
        mid = mid->next;  
      }
    }
    Node<AdminUser>* tempMid = mid->next;
    mid->next = nullptr;
    return tempMid;
}


Node<AdminUser>* merge(Node<AdminUser>* l, Node<AdminUser>* r){
  if(l == nullptr){
    return r;
  }
  else if(r == nullptr){
    return l;
  }
  
  if(l->getElement().userName <= r->getElement().userName){
    l->next = merge(l->next,r);
    l->next->prev = l;
    l->prev = nullptr;
    return l;
  }
  else{
    r->next = merge(l,r->next);
    r->next->prev = r;
    r->prev = nullptr;
    return r;
  }
}

Node<AdminUser>* LinkedList::mergeSort(Node<AdminUser>* t_head){
  if(t_head == nullptr || t_head->next == nullptr){
    return t_head;
  }
  Node<AdminUser>* mid = partition(t_head);
  t_head = mergeSort(t_head);
  mid = mergeSort(mid);
  return merge(t_head,mid);
}

void LinkedList::mergeSort(){
  head = mergeSort(head);
}

void LinkedList::displayList(){
  Node<AdminUser> * temp = head;
  while(temp!=nullptr){
    cout<<temp->getElement().userName<<endl;
    temp = temp->next;
  }
}