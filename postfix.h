#include <iostream>
using namespace std;

struct node{
  char value;
  node* next;
};

class postfix{
    private:
        node* top;
    public:    
      postfix();
      bool isEmpty();
      void push(char x);
      void pop();
      void print();
      int priority(char x);
      char peak();
};