/*
Author: Peter Jin
Date: 12/9/19
Node Class Header
*/

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstring>

class Node {

 public:

  //Constructor
  Node(char*);

  //Get Value of Node
  char* getValue();

  //Get left
  Node* getLeft();

  //Get right
  Node* getRight();

  //Destructor
  ~Node();

 private:

  char* value;
  Node* left;
  Node* right;

};

