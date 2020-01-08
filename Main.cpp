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
void push(Node*&, Node*);
char* pop(Node*&, bool del = true);
char* peek(Node*);
Node* peekNode(Node*);
int getPrecedence(char*);
bool isLeftAsc(char*);
bool isnumber(char*);
Node* getTree(vector<char*>*);
void printInfix(Node*);
void printPostfix(Node*);
void printPrefix(Node*);

int main() {
  cout << "Welcome to Shunting Yard demonstration" << endl;
  cout << "Enter a space-seperated infix expression. Please only use +, -, *, /, (, ), ^, and integers" << endl;

  char* expression = new char();
  cin.getline(expression, 150);
  cout << "Getting postfix..." << endl;
  vector<char*>* postfix = getPostfix(expression);
  cout << "Done" << endl;

  /*
  vector<char*>::iterator it = postfix -> begin();
  while (it != postfix -> end()) {
    cout << *it << " ";
    ++it;
  }
  cout << endl;
  */
  
  cout << "Getting expression tree..." << endl;
  Node* expHead = getTree(postfix);
  cout << "Done" << endl;

  bool cont = true;
  while (cont) {
    cout << "Print infix(i), postfix(p), or prefix(pr)?" << endl;
    char* mode = new char();
    cin.getline(mode, 10);
    bool accept = false;
    while(!accept) {
      if (strcmp(mode, "i") == 0 || strcmp(mode, "p") == 0 || strcmp(mode, "pr") == 0) {
	accept = true;
      }
      else {
	cout << "Please enter either \"i\", \"p\", or \"pr\"." << endl;
      }
    }
    if (strcmp(mode, "i") == 0) {
      cout << "Getting infix expression..." << endl;
      printInfix(expHead);
    }
    if (strcmp(mode, "p") == 0) {
      cout << "Getting postfix expression..." << endl;
      printPostfix(expHead);
    }
    if (strcmp(mode, "pr") == 0) {
      cout << "Getting prefix expression..." << endl;
      printPrefix(expHead);
    }
    cout << endl;

    cout << "Output another expression? (y/n)" << endl;
    accept = false;
    char dec;
    while (!accept) {
      cin >> dec;
      cin.clear();
      cin.ignore();
      accept = true;
      if (dec == 'n') {
	cont = false;
      }
      else if (dec != 'y') {
	accept = false;
	cout << "Please enter either \"y\" or \"n\"" << endl;
      }
    }
  }
  cout << "Thank you for using Shunting Yard demonstration" << endl;
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
      push(head, new Node(*it));
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
      push(head, new Node(c));
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

void push(Node* &head, Node* n) {
  if (head == NULL) {
    head = n;
    return;
  }
  if (head -> getNext() == NULL) {
    head -> setNext(n);
    return;
  }
  Node* temp = head -> getNext();
  push(temp, n);
}

char* pop(Node* &head, bool del) {
  if (head == NULL) return NULL;
  if (head -> getNext() == NULL) {
    char* ret = head -> getValue();
    Node* temp = head;
    head = NULL;
    if(del) delete temp;
    return ret;
  }
  if (head -> getNext() -> getNext() == NULL) {
    char* ret = head -> getNext() -> getValue();
    if (del) delete head -> getNext();
    head -> setNext(NULL);
    return ret;
  }
  Node* temp = head -> getNext();
  return pop(temp, del);
}

char* peek(Node* head) {
  if (head == NULL) return NULL;
  if (head -> getNext() == NULL) {
    return head -> getValue();
  }
  return peek(head -> getNext());
}

Node* peekNode(Node* head) {
  if (head == NULL) return NULL;
  if (head -> getNext() == NULL) {
    return head;
  }
  return peekNode(head -> getNext());
}
  
Node* getTree(vector<char*>* v) {
  Node* head = NULL; //Stack head

  vector<char*>::iterator it = v -> begin();
  while (it != v -> end()) {
    if (isnumber(*it)) {
      push(head, new Node(*it));
    }
    else {
      Node* temp = new Node(*it);
      temp -> setRight(peekNode(head));
      pop(head, false);
      temp -> setLeft(peekNode(head));
      pop(head, false);
      push(head, temp);
    }
    ++it;
  }
  Node* ret = peekNode(head);
  pop(head, false);

  return ret;
}
 
void printInfix(Node* head) {
  if (head) {
    if (!isnumber(head -> getValue())) cout << "(";
    printInfix(head -> getLeft());
    cout << head -> getValue();
    printInfix(head -> getRight());
    if (!isnumber(head -> getValue())) cout << ")";
  }
}

void printPrefix(Node* head) {
  if (head) {
    cout << head -> getValue() << " ";
    printPrefix(head -> getLeft());
    printPrefix(head -> getRight());
  }
}

void printPostfix(Node* head) {
  if (head) {
    printPostfix(head -> getLeft());
    printPostfix(head -> getRight());
    cout << head -> getValue() << " ";
  }
}
