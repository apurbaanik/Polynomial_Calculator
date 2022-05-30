/*
	Title: hw08: linked lists - polynomial.cpp
	Author: Anik Barua
	Version: 1.0
	Date: 05-02-2022
    
	Description: This program implements a class Polynomial for storing and manipulating polynomial 
    expressions. It has two fields, one is degree of the polynomial and other one is a Node pointer
    header. Since it uses a singly linked list to store each polynomial coeffcient, we have a struct 
    Node nested in the class. The Polynomial class contains a default constructor, a constructor that
    takes a vector, copy-control, overloaded +=, +, ==, != and output << operator. It also has a evalute 
    method that takes a value and plugs it in for x and evalutes it at a linear time using Horner's method. 
*/

//including the header files
#include "polynomial.h"
using namespace std;

// Node's constructor
Polynomial::Node::Node(int data, Node* next) : data(data), next(next) {}

// Default constructor for Polynomial
Polynomial::Polynomial() : degree(0), headPtr(new Node()) {} // initializing the degree and the headPtr 

// Constructor for Polynomial that takes a vector
Polynomial::Polynomial(const vector<int>& vec) : degree(0), headPtr(nullptr) {
    if(vec.size() > 0) { // check if the passed vector is not empty
        degree = vec.size() - 1; // degree will be 1 less than the length of the vector
        headPtr = new Node(vec[0]); // initializing the head pointer 
        Node* tmp1 = headPtr; // tmp1 is created to traverse through the list
        for(size_t i = 1; i < vec.size(); ++i) { // until we reach the vector's end
            tmp1->next = new Node(vec[i]); // create a new node, add it to tmp's next (since tmp is currently pointing to headptr)
            tmp1 = tmp1->next; // bump up the tmp to tmp's next
        }
        cleanUp(); // if there is any zero coefficeints in the front, it gets rid of it also changes the degrees
    }
}

// Destructor
Polynomial::~Polynomial(){
    Node* tmp1 = headPtr;
    while(tmp1->next != nullptr) {
        Node* tmp2 = tmp1->next; // tmp2 will hold head ptr's next
        delete tmp1; // delete tmp1
        tmp1 = tmp2; // tmp1 now holds what tmp2 is pointing to
    }
}

// Copy constructor
Polynomial::Polynomial(const Polynomial& rhs) : degree(0), headPtr(nullptr) {
    headPtr = new Node(rhs.headPtr->data); // intialize the head pointer
    Node* tmp1 = headPtr; // tmp1 is created to traverse through the list
    Node* tmp2 = rhs.headPtr->next; // tmp2 will hold the address of rhs headPtr's next
    while(tmp2 != nullptr) {
        // Copy the nodes from the tmp2 to tmp1
        listAddHead(tmp1,tmp2->data); // Add the next node in the tmp1's head
        tmp1 = tmp1->next; // bump up the tmp1 to tmp1's next
        tmp2 = tmp2->next; // bump up the tmp2 to tmp2's next
    }
    degree = rhs.degree; // change the degree to rhs.degree
}

// operator=() - assignment operator
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if(this != &rhs) {  // checking if they point to same memory location
        Node* tmp1 = headPtr;
        while(tmp1->next != nullptr) {
            Node* tmp2 = tmp1->next; // tmp2 will hold tmp  next
            delete tmp1; // delete tmp1
            tmp1 = tmp2; // tmp1 gets tmp2
        }
        headPtr = new Node(rhs.headPtr->data); // intialize the head pointer
        Node* tmp3 = headPtr; // tmp3 is now pointing to headPtr
        Node* tmp4 = rhs.headPtr->next; // tmp4 will hold the address of rhs.headPtr's next
        while(tmp4 != nullptr) { 
            //Copy the nodes from the tmp4 to tmp3
            listAddHead(tmp3,tmp4->data); // Add the next node in the tmp3's head
            tmp3 = tmp3->next; // bump up the tmp3 to tmp3's next
            tmp4 = tmp4->next; // bump up the tmp4 to tmp4's next
        }
        degree = rhs.degree; // set the degree to rhs.degree
    }
    return *this;
}

// cleanUp() method removes zeros from the front
void Polynomial::cleanUp() {
    Node* tmp1 = headPtr; // tmp1 points to the first coefficent in the list
    while(degree > 0 && tmp1 != nullptr && tmp1->data == 0) {
        Node* tmp2 = tmp1->next; // tmp2 holds tmp1's next
        delete tmp1; // deleting tmp1
        --degree; // now one degree less
        tmp1 = tmp2; // tmp1 is now holding the next
        tmp2 = tmp2->next; // bump up the tmp2 to tmp2's next
    }
    headPtr = tmp1; // now tmp1 is the new headPtr
}

// Add to the head of the list
void Polynomial::listAddHead(Node*& head, int value) {
    Node* tmp = new Node(value);
    // if list is empty, then we know the head is nullptr
    if(head == nullptr) {
        head = tmp; // so add the tmp to head
    } else {  // if list is not empty
        Node* hold = head->next; // hold what head's next is pointing to
        head->next = tmp; // head's next will now be the tmp
        tmp->next = hold; // now tmp's next will be what head's next was pointing to
    }
    ++degree; // increment degree
}

// overloaded operator+=() used by operator+() function
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    Node* tmp1 = headPtr; // points to the head pointer 
    Node* tmp2 = rhs.headPtr; // points to rhs's head pointer
    // Goal is to make both pointers point on the same degree so we can add them. 
    if(degree > rhs.degree){ // when lhs degree is higher
        int difference = degree - rhs.degree; // get the difference 
        for(size_t i = 0; i < difference; ++i) {
            tmp1 = tmp1->next; // until there is any difference bump up tmp1 to tmp1's next
        }
    } else if(degree < rhs.degree) { // when rhs degree is higher
        int difference = rhs.degree - degree; // get the difference 
        Node* dummy = new Node(0, headPtr); // making a dummy node who's next is the headPtr
        Node* dummy_head = dummy; // dummy_head will point to dummy
        for(size_t i = 0; i < difference; ++i) { // until there is any difference
            listAddHead(dummy, tmp2->data); // add the tmp2's data to the dummy
            dummy = dummy->next; // bump up dummy to dummy's next
            tmp2 = tmp2->next; // bump up tmp2 to tmp2's next
        }
        headPtr = dummy_head->next; // now the new head is dummy's next
        delete dummy_head; // delete the dummy headPtr
    }
    // Now both of them have the same degree, so now we can add them by position
    while(tmp1 != nullptr && tmp2 != nullptr){
        tmp1->data += tmp2->data; // add tmp2's data to tmp1
        tmp1 = tmp1->next; // go to tmp1's next 
        tmp2 = tmp2->next; // go to tmp2's next 
    }
    cleanUp(); // if there is any zero coefficeints in the front after adding, it gets rid of it also changes the degrees
    return *this;
}

// evaluate() method evalutes for x value at linear time using Horner's method
int Polynomial::evaluate(int val) const {
    int result = 0;
    Node* tmp = headPtr; // tmp points to head pointer
    for(size_t i = 0; i < degree; ++i) {
        result = (result + tmp->data) * val;
        tmp = tmp->next; // bump up tmp to tmp's next
    }
    result += tmp->data; // adds the constant in the polynomial
    return result;
}

// operator==() implemented as a friend function
bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if(lhs.degree != rhs.degree) {
        return false; // if they have different degree return false
    }
    // Since node is nested in Polynomial class we have to use the qualify operator
    Polynomial::Node* tmp1 = lhs.headPtr; // tmp1 points to lhs head pointer 
    Polynomial::Node* tmp2 = rhs.headPtr; // tmp1 points to rhs head pointer 
    // Now we have to match data at each position
    while(tmp1 != nullptr && tmp2 != nullptr){
        if(tmp1->data != tmp2->data){
            return false; // if the coefficent at the same degree is different then returns false
        }
        tmp1 = tmp1->next; // bump up tmp1 to tmp1's next
        tmp2 = tmp2->next; // bump up tmp2 to tmp1's next
    }
    return true;
}

// operator!=() implemented as a function that uses the equality operator
bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs==rhs); // uses operator==() to check if they are not equal
}

// operator+() implemented as a function that uses polynomials += operator
Polynomial operator+(const Polynomial& poly1, const Polynomial& poly2) {
    Polynomial result = poly1; // using copy constructor, result is now same as poly1
    result += poly2; // using operator+=() we add poly2 to result
    return result; 
}

// operator<<() implemented as a friend function
ostream& operator<<(ostream& os, const Polynomial& poly) {
    Polynomial::Node* tmp = poly.headPtr; // tmp is pointing to headPtr
    int countDegree = poly.degree;
    while (tmp != nullptr) {
        if (poly.degree == 0) { // only for constant at degree 0
            os << tmp->data;
        } else if (tmp->data != 0) { // when tmp data is not zero
            if(countDegree != poly.degree) { // when its not the highest degree
                os << " + "; // add the + sign since its not the end of the expression
            }
            if(tmp->data == -1) { 
                cout << "-"; // when data == -1, print only negative sign
            } else if (tmp->data != 0 && !(tmp->data == 1 && countDegree > 0)) { // when data is not 0 and 1 but degree is greater than 0
                os << tmp->data; // print the data
            }
            if(countDegree > 0) { // when degree greater than 0, print x
                cout << "x";
                if(countDegree > 1) { // when degree greater than 1 also print the exponent sign ^ with the degree
                    cout << "^" << countDegree;
                }
            }
        }
        --countDegree; // decrement degree
        tmp = tmp->next; // bump up tmp to tmp's next
    }
    return os;
}