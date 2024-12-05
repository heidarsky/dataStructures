#include "postfix.h"

int postfix::priority(char x){
   if(x == '+' || x == '-') 
      return 1;            // + or - is 1
   else if(x == '*' || x == '/') 
      return 2;            //* or / is 2
   else if(x == '^') 
      return 3;            //^ is 3
   else 
      return -1;
}
postfix::postfix(){
  node *temp = new node;
  top = nullptr;
}
bool postfix::isEmpty(){
  return top == nullptr;
}
char postfix::peak(){
  return top->value;
}
void postfix::push(char x){
  node *temp = new node;
  temp->value = x;
  temp->next = top;
  top = temp;
}
void postfix::pop(){
  node *temp;
  if(!isEmpty()){
    temp = top;
    top = top->next;
    delete temp;
  }
}
void postfix::print(){
  node *temp;
  if(!isEmpty()){
    temp = top; 
    while(temp != nullptr){
      cout << temp->value << " ";
      temp = temp->next;
    }
    cout << endl;
  }
}