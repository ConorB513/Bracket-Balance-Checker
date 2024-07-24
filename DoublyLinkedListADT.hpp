
/*
Name: Conor Benson
External Help:
1. Purpose of inline(appeared automatically when implementing methods)
-> https://www.geeksforgeeks.org/inline-functions-cpp/
2. Code beautify used to format code nicely 
-> https://codebeautify.org/cpp-formatter-beautifier
*/

#ifndef _DOUBLYLINKEDLIST_HPP_
#define _DOUBLYLINKEDLIST_HPP_

#include <exception>
#include <ostream>
using namespace std;

template <class T>
class DLLNode {
    private:
        T data;
        DLLNode* next;
        DLLNode* prev;
    public:
        //parameterized constructor
        //this forces the user to create a node with a value
        DLLNode (T value){
            setNext(nullptr);
            setPrev(nullptr);
            setData(value);
        }
        //getter of address of the next node
        DLLNode* getNext(){
            return next;
        }
        //getter of address of the previous node
        DLLNode* getPrev(){
            return prev;
        }
        //setter of address of the next node
        void setNext(DLLNode* next){
            this->next = next;
        }
        //setter of address of the previous node
        void setPrev(DLLNode* prev){
            this->prev = prev;
        }
        //getter of data
        T getData(){
            return data;
        }
        //setter of data
        void setData(T value){
            data = value;
        }
};

// Exception thrown on accessing head from an empty list
class DoublyLinkedListEmpty : public exception {
    public:
        virtual const char* what() const noexcept {
            return "Exception: list is empty";
    }
};

template <class T>
class DoublyLinkedList {
    private:
        DLLNode<T>* head;
        DLLNode<T>* tail;
        int size;
    public:
        //default constructor
        DoublyLinkedList(){
            head = nullptr;
            tail = nullptr;
            size = 0;
        }
        //copy constructor, creates a list of nodes from the reference
        DoublyLinkedList(const DoublyLinkedList<T> &other){
            head = nullptr;
            tail = nullptr;
            size = 0;

            DLLNode < T > * currentNode = other.tail;
            //Sets the first node added to copy as the last node in the original stack

            while (currentNode != nullptr) {
                addToHead(currentNode -> getData()); //
                currentNode = currentNode -> getPrev();
            }
        }
        //adds a new element to the head of the list storing a copy of value
        void addToHead(T value){

            DLLNode < T > * newNode = new DLLNode < T > (value);
            //New node created with given value stored as nodes data

            //If the list is empty, newNode becomes both the head and tail of list 
            if (head == nullptr) {
                head = newNode;
                tail = newNode;

                //If list isn't empty, newNode becomes the new head, but pushes old head down list
            }   
            else {
                newNode -> setNext(head);
                head -> setPrev(newNode);
                head = newNode;
            }
            size++; //Since a node has been added, size of list increases by one 
        }

        // Method removes("pops") the current head from the list 
        //turning the next node in the list into the new head
        void removeFromHead(){
            //If the list is empty, throws an exception stating the list is already empty
            if (size == 0) {
                throw DoublyLinkedListEmpty();
            }
            DLLNode < T > * toRemove = head; //Creates a pointer to the node to be remove (the head)
            head = head -> getNext(); //Assigns head to the next node in the list
            //If the list is now empty, tail shouldn't point to anything 
            if (head == nullptr) {
                tail = nullptr;
            }
            //If the list isn't empty, the new head node shouldn't point to a previous node 
            else {
                head -> setPrev(nullptr);
            }

            delete(toRemove);
            size--;
        }

        //adds a new element to the tail of the list storing a copy of value
        void addToTail(T value){
            DLLNode < T > * newNode = new DLLNode < T > (value);

            //If tail does not exist i.e. list is empty, newNode becomes both tail and head
            if (tail == nullptr) {
                tail = newNode;
                head = newNode;
            }
            //If the list isn't empty, newNode becomes the tail and pushes previous tail forward in the list
            
            else {
                newNode -> setPrev(tail);
                tail -> setNext(newNode);
                tail = newNode;
                }
            size++;
        }

        //Method removes the tail node from the list, if there is a tail node 
        void removeFromTail(){
            //Throw an exception if theres nothing to remove
            if (size == 0) {
                throw DoublyLinkedListEmpty();
            }

            DLLNode < T > * toRemove = tail; //Creates a pointer to the node to be remove (the tail)
            tail = tail -> getPrev(); //Set the tail to the previous node in the list
            //If the list is now empty, head shouldn't point anything 
            if (tail == nullptr) {
                head = nullptr;
            }
            //If the list isn't empty, tail shouldn't point to a next node
            else {
                tail -> setNext(nullptr);
            }
            delete(toRemove);
            size--;
        }

        //getter of head 
        T peekHead(){
            //If the user tries to access the head of an empty list, throw a DLL empty exception 
            if (head == nullptr) {
                throw DoublyLinkedListEmpty();
            }   
            else {
                return head -> getData();
            }
        }

        //getter of tail
        T peekTail(){
            //If the user tries to access the tail of an empty list, throw a DLL empty exception
            if (tail == nullptr) {
                throw DoublyLinkedListEmpty();
            }   
            else {
            return tail -> getData();
            }
        }

        //returns the size of the list
        int getSize(){
            return size;
        }
        //print the content backwards (from tail to head) to an ostream object
        // using the prev pointers
        //if the list is empty, print "The list is empty"
        void printBackwards(ostream &os){
            //Nothing to print if list is empty 
            if (size == 0) {
                os << "The list is empty" << endl;
            }
            //Starting with the tail node, print print the data of the node
            DLLNode < T > * currentNode = tail;
            while (currentNode != nullptr) {
                os << currentNode -> getData();
                //While there exist a next node, print -> 
                if (currentNode -> getPrev() != nullptr) {
                    os << " -> ";
                }
                //Move up the list 
                currentNode = currentNode -> getPrev();
            }
        }
        //destructor
        ~DoublyLinkedList(){
            while (size != 0) {
                removeFromHead();
            }
        }

        //used for printing using << operator
        friend ostream& operator<<(ostream &os, const DoublyLinkedList<T> &lst) {
            DLLNode<T>* current = lst.head;
            while (current != nullptr) {
                os << current->getData();
                if (current->getNext() != nullptr) os << " -> ";
                current = current->getNext();
            }
            return os;
        }
};

#endif
