/*
Author: Peter Jin
Date: 12/9/19
Shunting Yard algorithm Demonstration
*/

#include <iostream>
#include <cstring>
#include <vector>
#include "Node.h"

using namespace std;

vector<char*>* getPostfix(char*);
vector<char*>* split(char*, char);
void push(Node**, char*);
void pop(Node*);
//int getPrecedence(char*);

int main() {
  cout << "Welcome to Shunting Yard demonstration" << endl;
  cout << "Enter a space-seperated infix expression. Please only use +, -, *, /, (, ), ^, and integers" << endl;

  char* expression = new char();
  cin.getline(expression, 150);
  
  vector<char*>* postfix = getPostfix(expression);
}

vector<char*>* split(char* c, char delim) {
  vector<char*>* v = new vector<char*>;
  char* build = new char[strlen(c)]();
  int ind = 0; 
  for (int i = 0; i < strlen(c); i++) {
    if (c[i] != delim) {
      build[ind++] = c[i];
    } else {
      v -> push_back(build);
      build = new char[strlen(c)]();
      ind = 0;
    }
  }
  if (build) v -> push_back(build);
  return v;
}

vector<char*>* getPostfix(char* exp) {
  vector<char*>* in = split(exp, ' ');
  vector<char*>* out = new vector<char*>;
  Node* head = NULL; 
  
  vector<char*>::iterator it = in -> begin();
  while(it != in -> end()) {
    ++it;
  }
  return out;
}

void push(Node** head, char* c) {
  if (*head == NULL) {
    Node* temp = new Node(c);
    head = &temp;
    return;
  }
  if ((*head) -> getRight() == NULL) {
    Node* newNode = new Node(c);
    (*head) -> setRight(newNode);
    return;
  }
  Node* temp = (*head) -> getRight();
  push(&temp, c);
}

void pop(Node*) {

}
  
