/*
Author: Peter Jin
Date: 12/3/2019
Node Class
*/

#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

//Constructor
Node::Node(char* c) {
  value = c;
  right = NULL;
  left = NULL;
  next = NULL;
}

//Get Value
char* Node::getValue() {
  return value;
}

//Get Left
Node* Node::getLeft() {
  return left;
}

//Get Right
Node* Node::getRight() {
  return right;
}

//Get Next
Node* Node::getNext() {
  return next;
}

//Set Left
void Node::setLeft(Node* n) {
  left = n;
}

//Set Right
void Node::setRight(Node* n) {
  right = n;
}

//Set Next
void Node::setNext(Node* n) {
  next = n;
}

//Destructor
Node::~Node() {
  //Nothing here for now
}
