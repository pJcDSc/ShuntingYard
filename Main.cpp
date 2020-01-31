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

Node* getPostfix(char*);
void enqueue(Node*&, char*);
char* dequeue(Node*&);
vector<char*>* split(char*, char);
void push(Node*&, Node*);
char* pop(Node*&, bool del = true);
char* peek(Node*);
Node* peekNode(Node*);
int getPrecedence(char*);
bool isLeftAsc(char*);
bool isnumber(char*);
Node* getTree(Node*);
void printInfix(Node*);
void printPostfix(Node*);
void printPrefix(Node*);

int main() {
  cout << "Welcome to Shunting Yard demonstration" << endl;
  cout << "Enter a space-seperated infix expression. Please only use +, -, *, /, (, ), ^, and integers" << endl;

  //Read in infix expression
  char* expression = new char();
  cin.getline(expression, 150);
  
  //Get postfix and store in char* vector
  cout << "Getting postfix..." << endl;
  Node* postfix = getPostfix(expression);
  cout << "Done" << endl;

  //Get expression tree and store head node
  cout << "Getting expression tree..." << endl;
  Node* expHead = getTree(postfix);
  cout << "Done" << endl;

  //While they haven't quit yet
  bool cont = true;
  while (cont) {
    //Prompt to print infix, postfix, or prefix
    cout << "Print infix(i), postfix(p), or prefix(pr)?" << endl;
    char* mode = new char();
    bool accept = false;
    //If they don't type in one of the accepted characters don't accept the input
    while(!accept) {
      cin.get(mode, 10);
      cin.clear();
      cin.ignore(999, '\n');
      if (strcmp(mode, "i") == 0 || strcmp(mode, "p") == 0 || strcmp(mode, "pr") == 0) {
	accept = true;
      }
      else {
	cout << "Please enter either \"i\", \"p\", or \"pr\"." << endl;
      }
    }
    //Print based on user input
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

    //Prompt for quit or no
    cout << "Output another expression? (y/n)" << endl;
    accept = false;
    char dec;
    //Don't accept other than y and n
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

/* split function takes char* c and char delim to split c by delim
 * >>> split ("Hello World", ' ') -> {"Hello", "World"}
 */ 
vector<char*>* split(char* c, char delim) {
  //Output vector
  vector<char*>* v = new vector<char*>;
  //Temporary cstring to store next word that will be added to output vector
  char* build = new char[strlen(c)]();
  int ind = 0;
  //loop through c, if delim push build to v, otherwise add to build
  for (int i = 0; i < strlen(c); i++) {
    if (c[i] != delim) {
      build[ind++] = c[i];
    } else {
      v -> push_back(build);
      build = new char[strlen(c)]();
      ind = 0;
    }
  }
  //If anything is left in build string, push to vector also
  if (build) v -> push_back(build);
  return v;
}

/* takes in char* exp as infix space-separated expression, return postfix in form of vector<char*>
 * >>> getPostfix("1 + 2 * 3") -> {"1", "2", "3", "*", "+"}
 *
 * Uses Dijkstra's Shunting Yard algorithm to parse infix, cannot handle unary operators
 * Accepted operators: +, -, *, /, ^, (, )
 */
Node* getPostfix(char* exp) {
  vector<char*>* in = split(exp, ' ');
  //Ouptut vector
  Node* out = NULL;
  //Stack head
  Node* head = NULL; 
  
  //Loop through vector
  vector<char*>::iterator it = in -> begin();
  while(it != in -> end()) {
    char* c = *it;
    //If c is a number just push to output
    if (isnumber(c)) enqueue(out, c);
    //If c is a left paren push it to stack
    else if (strcmp(c, "(") == 0) {
      push(head, new Node(*it));
    }
    //If c is right paren pop from stack onto output until left paren is found
    else if (strcmp(c, ")") == 0) {
      char* op = pop(head);
      while (strcmp(op, "(") != 0) {
	enqueue(out, op);
	op = pop(head);
      }
    }
    //If c is other operator pop and push to output until there's nothing left or left paren or (next greater precedence than prec or
    //next has equal precedence to next and next is left associative) then push c
    else {
      int prec = getPrecedence(c);
      char* next = peek(head);
      while (next && strcmp(next, "(") != 0 && (getPrecedence(next) > prec || getPrecedence(next) == prec && isLeftAsc(next))) {
	enqueue(out, pop(head));
	next = peek(head);
      }
      push(head, new Node(c));
    }
    ++it;
  }
  //Push the rest of the stack into output in order
  while (peek(head) != NULL) {
    enqueue(out, pop(head));
  }
  return out;
}

//Returns precedence of operator, return -1 if not recognized
int getPrecedence(char* c) {
  if (strcmp(c, "^") == 0) return 4;
  if (strcmp(c, "*") == 0 || strcmp(c, "/") == 0) return 3;
  if (strcmp(c, "+") == 0 || strcmp(c, "-") == 0) return 2;
  return -1;
}

//Returns whether or not an operator is left associative
bool isLeftAsc(char* c) {
  if (strcmp(c, "^") == 0) return false;
  return true;
}

//Checks each digit to make sure it is a number
bool isnumber(char* c) {
  for (int i = 0; i < strlen(c); i++) {
    if (!isdigit(c[i])) return false;
  }
  return true;
}

//Enqueue function for shunting yard
void enqueue(Node* &head, char* c) {
  //Empty List
  if (head == NULL) {
    head = new Node(c);
    return;
  }
  //Last node
  if (head -> getNext() == NULL) {
    head -> setNext(new Node(c));
    return;
  }
  //Recurse on next node
  Node* temp = head -> getNext();
  enqueue(temp, c);
}

//Dequeue function for queue
char* dequeue(Node* &head) {
  //Empty List
  if (head == NULL) {
    return NULL;
  }
  //Otherwise, get temp, return value of temp, set head to next
  Node* temp = head;
  head = head -> getNext();
  char* value = temp -> getValue();
  delete temp;
  return value;
}

//recursive Push function for push into stack
void push(Node* &head, Node* n) {
  //If stack empty just make head
  if (head == NULL) {
    head = n;
    return;
  }
  //If last node then setnext to n
  if (head -> getNext() == NULL) {
    head -> setNext(n);
    return;
  }
  //try pushing again with next node in stack
  Node* temp = head -> getNext();
  push(temp, n);
}

//Recursive Pop function, include del as mode to choose whether or not deleting node
char* pop(Node* &head, bool del) {
  //If empty don't do anything
  if (head == NULL) return NULL;
  //If only one node in stack delete it carefully
  if (head -> getNext() == NULL) {
    char* ret = head -> getValue();
    Node* temp = head;
    head = NULL;
    if(del) delete temp;
    return ret;
  }
  //If two after node is end, then set current nodenext to null, and delete next node, return next node value
  if (head -> getNext() -> getNext() == NULL) {
    char* ret = head -> getNext() -> getValue();
    if (del) delete head -> getNext();
    head -> setNext(NULL);
    return ret;
  }
  //try again with next node
  Node* temp = head -> getNext();
  //MAKE SURE TO RETURN RECURSION VALUE
  return pop(temp, del);
}

//Recursive peek function for stack
char* peek(Node* head) {
  //If empty return null
  if (head == NULL) return NULL;
  //if next is empty return this
  if (head -> getNext() == NULL) {
    return head -> getValue();
  }
  //try again with next node
  return peek(head -> getNext());
}

//Recursive peek function for stack, but returns node
Node* peekNode(Node* head) {
  //if empty return null
  if (head == NULL) return NULL;
  //if next is empty return this node
  if (head -> getNext() == NULL) {
    return head;
  }
  //try again with next node
  return peekNode(head -> getNext());
}

//Returns exptree given a postfix vector<char*>
Node* getTree(Node* post) {
  //Stack head
  Node* head = NULL;

  //loop through v
  char* next = dequeue(post);
  while (next) {
    //if number push to stack
    if (isnumber(next)) {
      push(head, new Node(next));
    }
    //otherwise (operator) make new node, pop twice, set first to right and second to left, push
    else {
      Node* temp = new Node(next);
      temp -> setRight(peekNode(head));
      pop(head, false);
      temp -> setLeft(peekNode(head));
      pop(head, false);
      push(head, temp);
    }
    next = dequeue(post);
  }
  //Final node in stack is head node
  Node* ret = peekNode(head);
  pop(head, false);

  return ret;
}

//Recursive infix print
void printInfix(Node* head) {
  if (head) {
    //If it's an operator we need paren
    if (!isnumber(head -> getValue())) cout << "(";
    //Recurse on left node
    printInfix(head -> getLeft());
    //Print this node
    cout << head -> getValue();
    //Recurse on right node
    printInfix(head -> getRight());
    //If it's an operator we need the other paren
    if (!isnumber(head -> getValue())) cout << ")";
  }
}

//Recursive prefix print
void printPrefix(Node* head) {
  if (head) {
    //Print this node
    cout << head -> getValue() << " ";
    //Recurse on left node
    printPrefix(head -> getLeft());
    //Recurse on right node
    printPrefix(head -> getRight());
  }
}

//Recursive postfix print
void printPostfix(Node* head) {
  if (head) {
    //Recurse on left node
    printPostfix(head -> getLeft());
    //Recurse on right node
    printPostfix(head -> getRight());
    //Print this node 
    cout << head -> getValue() << " ";
  }
}
