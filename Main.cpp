/*
Author: Peter Jin
Date: 12/9/19
Shunting Yard algorithm Demonstration
*/

#include <iostream>
#include <cstring>
#include "Node.h"
#include <vector>

using namespace std;

vector<char*>* getPostfix(vector<char*>);
vector<char*>* split(char*, char);

int main() {
  cout << "Welcome to Shunting Yard demonstration" << endl;
  cout << "Enter infix expression. Please only use +, -, *, /, (, ), ^, and integers" << endl;

  char* expression;
  cin.getline(expression, 150);
  
  vector<char*> postfix = getPostfix(split(expression, ' '))
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
