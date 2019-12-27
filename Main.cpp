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
void push(Node*&, char*);
char* pop(Node*&);
char* peek(Node*);
int getPrecedence(char*);
bool isLeftAsc(char*);
bool isnumber(char*);
Node* getTree(vector<char*>*);

int main() {
  cout << "Welcome to Shunting Yard demonstration" << endl;
  cout << "Enter a space-seperated infix expression. Please only use +, -, *, /, (, ), ^, and integers" << endl;

  char* expression = new char();
  cin.getline(expression, 150);
  vector<char*>* postfix = getPostfix(expression);
  vector<char*>::iterator it = postfix -> begin();
  /*while (it != postfix -> end()) {
    cout << *it << " ";
    ++it;
  }
  cout << endl;*/
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
    char* c = *it;
    if (isnumber(c)) out -> push_back(c);
    else if (strcmp(c, "(") == 0) {
      push(head, *it);
    } else if (strcmp(c, ")") == 0) {
      char* op = pop(head);
      while (strcmp(op, "(") != 0) {
	out -> push_back(op);
	op = pop(head);
      }
    } else {
      int prec = getPrecedence(c);
      char* next = peek(head);
      while (next && strcmp(next, "(") != 0 && (getPrecedence(next) > prec || getPrecedence(next) == prec && isLeftAsc(next))) {
	out -> push_back(pop(head));
	next = peek(head);
      }
      push(head, c);
    }
    ++it;
  }
  while (peek(head) != NULL) {
    out -> push_back(pop(head));
  }
  return out;
}

int getPrecedence(char* c) {
  if (strcmp(c, "^") == 0) return 4;
  if (strcmp(c, "*") == 0 || strcmp(c, "/") == 0) return 3;
  if (strcmp(c, "+") == 0 || strcmp(c, "-") == 0) return 2;
  return -1;
}

bool isLeftAsc(char* c) {
  if (strcmp(c, "^") == 0) return false;
  return true;
}

bool isnumber(char* c) {
  for (int i = 0; i < strlen(c); i++) {
    if (!isdigit(c[i])) return false;
  }
  return true;
}

void push(Node* &head, char* c) {
  if (head == NULL) {
    Node* temp = new Node(c);
    head = temp;
    return;
  }
  if (head -> getRight() == NULL) {
    Node* newNode = new Node(c);
    head -> setRight(newNode);
    return;
  }
  Node* temp = head -> getRight();
  push(temp, c);
}

char* pop(Node* &head) {
  if (head == NULL) return NULL;
  if (head -> getRight() == NULL) {
    char* ret = head -> getValue();
    Node* temp = head;
    head = NULL;
    delete temp;
    return ret;
  }
  if (head -> getRight() -> getRight() == NULL) {
    char* ret = head -> getRight() -> getValue();
    delete head -> getRight();
    head -> setRight(NULL);
    return ret;
  }
  Node* temp = head -> getRight();
  return pop(temp);
}

char* peek(Node* head) {
  if (head == NULL) return NULL;
  if (head -> getRight() == NULL) {
    char* ret = head -> getValue();
    return ret;
  }
  return peek(head -> getRight());
}

Node* getTree(vector<char*>* v) {
  Node* head = NULL; //Stack head

  vector<char*>::iterator it = v -> begin();
  while (it != v -> end()) {
    if (isnumber(*it)) {
      
    
    ++it;
  }
}
