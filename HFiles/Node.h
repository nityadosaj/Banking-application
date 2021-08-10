#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {

    public: 
        int priority;
        Node *next;
        Node *prev;
        
        Node() {
            next = nullptr;
            prev = nullptr;
            priority = 0;
        }
        
        Node(T element) {
            this->element = element;
            next = nullptr;
            prev = nullptr;
            priority = 0;
        }
        
        T getElement() const {
            return element;
        }
        
    private:
        T element;
};

#endif