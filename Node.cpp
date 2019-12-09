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

//Destructor
Node::~Node() {
  //Nothing here for now
}
