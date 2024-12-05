#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include "ArgumentManager.h"
#include "linkedList.h"
#include <stack>
#include <queue>
using namespace std;

void cleanString(string lineStr){
  lineStr.erase(remove(lineStr.begin(), lineStr.end(), '\n'), lineStr.end());
  lineStr.erase(remove(lineStr.begin(), lineStr.end(), '\r'), lineStr.end());
}
 
bool invalidOr(string test){
  for(int i=0; i<test.size(); i++){
    if(!isdigit(test.at(i))){
      if(test.at(i) == '(' || test.at(i) == ')')
        continue;
      else{
        cout << test.at(i) << " << invalid" << endl;
        return true; // if true invalid ID
        }
    }
  }
  return false;
}

void strSearch(string sr, int &num){ // count braces in string
  string temp = sr;
  int bracIndex = temp.find('(');
  string test;
  
  while(bracIndex < temp.size()-1){
    if(temp[bracIndex] == '('){
      num++;
      //cout << temp << endl;
      }
    temp = temp.substr(bracIndex+1);
  }
}

void rev(string &results, int &parStack, stack<char> &res, queue<char> &resQ, string &idTemp){
  
    for(int i = 0; i < results.length(); i++){
      if(parStack == 0 && isdigit(results[i])){
        idTemp += results[i]; //add num to string
      }
        else if(results[i] == '('){ 
          res.push(results[i]);
          parStack++;
        }
        else if(parStack > 0 && isdigit(results[i])){ 
          res.push(results[i]); 
          //cout << "pushing inside: " << results[i] << endl; 
        }
        else if(parStack == 1 && results[i] == ')'){     
          while(res.top() != '('){
            idTemp += res.top();
            res.pop();
          }
          res.pop();
          parStack--; //brace closed
        }
        else if( parStack > 1 && results[i] == ')'){
          while(res.top() != '('){
            //cout << "to que>: " << res.top() << endl;
            resQ.push(res.top());
            res.pop();
          }
          res.pop(); // delete (
          
          while(!resQ.empty()){
            //cout << "to stack>: " << resQ.front() << endl;
            res.push(resQ.front());
            resQ.pop();
          }
          parStack--; //brace closed
        }
    else{
      while (!res.empty()) {
            idTemp += res.top();
            res.pop();
      }
    }
  }
}

int main(int argc, char *argv[]){

  ArgumentManager argMan(argc, argv);
  ifstream input(argMan.get("input"));
  ofstream output(argMan.get("output"));
  //ifstream input("input11.txt");
  //ofstream output("output11.txt"); 

  linkedList bar1;
  linkedList bar2;
  bool idInvalid;
  string lineStr, whichBar;
  int maxHundred = 0;

  stack<char> res; //result stack
  queue<char> resQ; //queue to hold
  string results;
  int parStack = 0;
  string idTemp = "";
  //results = "(4(23)1)";
  int numBrac = 0;

// FILE PROCESSING 
  while(getline(input, lineStr) && maxHundred <= 100){ // max 100 IDs
    cleanString(lineStr);
    if(lineStr == "") // skip blank lines
      continue;
      if(lineStr == "Bar1")
        whichBar = lineStr; // to know where to add IDs
      if(lineStr == "Bar2")
        whichBar = lineStr; // to know where to add IDs

    // if Bar 1
    if(whichBar == "Bar1" && lineStr != "Bar1"){
      // only num and parantheses otherwise invalid
      idInvalid = invalidOr(lineStr);
      if(idInvalid == true)
        cout << "can't use this ID :" << lineStr << endl;
      else{
        // m characters >=1 && <=100 for each ID
        if(lineStr.size() >= 1 && lineStr.size() <= 100){
          //cout << lineStr << " >>>>>> in Bar 1" << endl; //ID to bar#
          maxHundred ++;
          
          strSearch(results, numBrac);
          //cout << "num of bracket-pairs : " << numBrac << endl;
          rev(lineStr, parStack, res, resQ, idTemp); //reverse
          cout << "Reverse ID: " << idTemp << endl;
          string results = idTemp;
          idTemp = "";
          bar1.insert(results);
        }
        else{
          cout << lineStr.size() << " : can't be less than 1 or more than 100" << endl;
        }
      }
    }
    
    // if Bar 2
    else if(whichBar == "Bar2" && lineStr != "Bar2"){
      // only num and parantheses otherwise invalid
      idInvalid = invalidOr(lineStr);
      if(idInvalid == true)
        cout << "can't use this ID :" << lineStr << endl;
      else{
        // m characters >=1 && <=100 for each ID
        if(lineStr.size() >= 1 && lineStr.size() <= 100){ 
          //cout << lineStr << " >>>>>> in Bar 2" << endl; // ID to bar#
          maxHundred ++;
          
          strSearch(results, numBrac);
          //cout << "num of bracket-pairs : " << numBrac << endl;
          rev(lineStr, parStack, res, resQ, idTemp); //reverse
          cout << "Reverse ID: " << idTemp << endl;
          string results = idTemp;
          idTemp = "";
          bar2.insert(results);
        }
        else{
          cout << lineStr.size() << " : can't be less than 1 or more than 100" << endl;
        }
      }
    }
    else
      cout << lineStr << endl; // print Bar1 or Bar2 lines
  }
  
  // Input max 100
  //cout << "number of IDs in file: " << maxHundred << endl; 
  //cout << endl;

 
// GUILT CHECK
  stack<string> guiltStack; 
  stack<string> innocStack;
  bar1.nextId(bar2, guiltStack, innocStack); 

  linkedList guilt;
  linkedList innoc;
  bool isSort = false;
  cout << endl;
  
// PRINTING GUILTY
  if(!guiltStack.empty()){ //skip print if empty
    cout << "Guilty: " << endl;
    output << "Guilty: " << endl; 
    }
  guilt.insertRec(guiltStack, guilt); //stack to linkedlist recursive

  guilt.sortR(isSort ,guilt.getHead()); //sort recursive
  if(!guilt.isEmpty()){ //skip print if empty
    guilt.printRecursive(guilt.getHead()); 
    guilt.outPrintRec(guilt.getHead(), output); 
    if(!innocStack.empty()) //skip printing new line if empty
      output << endl;    
  }      

// PRINTING INNOCENT
  isSort = false;   
  if(!innocStack.empty()){                
    cout << "Innocent: " << endl;        
    output << "Innocent: " << endl;               
    }               
  innoc.insertRec(innocStack, innoc);       
  innoc.sortR(isSort, innoc.getHead());     
  if(!innoc.isEmpty()){ 
    innoc.printRecursive(innoc.getHead());
    innoc.outPrintRec(innoc.getHead() ,output);   
  }
    
  return 0; 
}
