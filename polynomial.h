/*
	Title: hw08: linked lists - polynomial.h
	Author: Anik Barua
    Date: 05-02-2022

	Description: This is the header file for polynomial class. It contains the prototype of the
    polynomial class and the methods and functions are implemented in the polynomial.cpp file. 
*/

// Include guards
#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <iostream>
#include <vector>

// Polynomial class 
class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly); // friend function operator<<() for Polynomial class
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs); // friend function operator==() for Polynomial class
    // struct Node is nested in the polynomial class
    struct Node {
        Node(int data = 0, Node* next = nullptr); // Node default constructor
        int data; // stores the data
        Node* next; // Node pointer to next
    };
public:
    Polynomial(); // Default constructor
    Polynomial(const std::vector<int>& vec); // constructor that takes a vector of its coefficients in order from the highest degree term to lowest
    ~Polynomial(); // Destructor
    Polynomial(const Polynomial& rhs); // Copy constructor
    Polynomial& operator=(const Polynomial& rhs); // assignment operator
    Polynomial& operator+=(const Polynomial& rhs); // operator+=() is a method - used by the operator+() 
    int evaluate(int val) const; // evaluate() method evalutes for x value at linear time using Horner's method
    void listAddHead(Node*& head, int value); // listAddHead() method adds a new item in the head of the list
private:
    int degree; // degree of the polynomial 
    Node* headPtr; // head_ptr of singly linked list 
    void cleanUp(); // private cleanUp() method removes zeros from the front of the list
};

Polynomial operator+(const Polynomial& poly1, const Polynomial& poly2); // prototype function for operator+() and it uses the operator+=()
bool operator!=(const Polynomial& lhs, const Polynomial& rhs); // prototype function operator!=() and it uses operator==()

#endif