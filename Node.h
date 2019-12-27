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

  //Get next
  Node* getNext();
  
  //Set left
  void setLeft(Node*);

  //Set right
  void setRight(Node*);

  //Set next
  void setNext(Node*);

  //Destructor
  ~Node();

 private:

  char* value;
  Node* left;
  Node* right;
  Node* next;

};

#endif
