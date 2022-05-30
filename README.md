# Polynomial_Calculator
Polynomial using linked lists

# Description
This program implements a class Polynomial for storing and manipulating polynomial 
expressions. It has two fields, one is degree of the polynomial and other one is a Node pointer
header. Since it uses a singly linked list to store each polynomial coeffcient, we have a struct 
Node nested in the class. The Polynomial class contains a default constructor, a constructor that
takes a vector, copy-control, overloaded +=, +, ==, != and output << operator. It also has a evalute 
method that takes a value and plugs it in for x and evalutes it at a linear time using Horner's method. 
