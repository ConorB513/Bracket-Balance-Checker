
/*
Name: Conor Benson
*/


#ifndef _DLLSTACK_HPP_
#define _DLLSTACK_HPP_

#include "DoublyLinkedListADT.hpp"
#include <ostream>
using namespace std;

//Exception class if stack is empty 
class StackEmpty : public exception {
    public:
        virtual const char* what() const noexcept {
            return "Exception: stack is empty";
    }
};

template <class E>
class DLLStack {
    private:
        DoublyLinkedList<E>* S;
    public:
        //Default constructor, stack is implemented using a doubly linked list
        DLLStack() {
            S = new DoublyLinkedList<E>;
        }
        //Getter of size
        int size() const {
            return S->getSize();
        }
        //Method returns bool relating to "emptiness" of stack
        bool empty() const {
            return S->getSize() == 0;
        }
        //Method returns value of top node
        const E top() const {
            if (empty()){
                 throw StackEmpty();
            }
            E toReturn = S->peekHead();
            return toReturn;
        }
        //Adds node to top of stack
        void push(const E& e) {
            S->addToHead(e);
        }
        //Removes value from top of stack
        void pop() {
            if (empty()) throw StackEmpty();
            S->removeFromHead();
        }
        //Method prints contents of stack
        void printContent(ostream &os) {
            os << (*S) << endl;
        } 
        //Destructor of stack
        ~DLLStack() {
            delete S;
        }
};

#endif