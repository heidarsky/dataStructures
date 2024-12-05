#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include <stack>
using namespace std;

struct node{
  string data;
  node *next;
};

class linkedList{
  private:
    node *head;
  public:
    linkedList(){
      head = nullptr;
    }

    void nextId(linkedList &bar2, stack<string> &guiltStack, stack<string>&innocStack){
      node *firstbar = head;
      firstB(firstbar, bar2, guiltStack, innocStack);
      node *tempInn = bar2.head;
      scndB(tempInn, innocStack);
    }
    
    void firstB(node* firstbar, linkedList &bar2, stack<string> &guiltStack, stack<string>&innocStack){
      string id;
      bool innoc = true;
      if(firstbar!=nullptr){
        node *scndbar = bar2.head;
        id = firstbar->data;
        firstB2(scndbar, id, guiltStack, innoc);
        if(innoc == true){
          innocStack.push(id);
        }
        else{
          innoc = true;
        }
        firstB(firstbar->next, bar2, guiltStack, innocStack);
      }
    }
    void firstB2(node* scndbar, string &id, stack<string>&guiltStack, bool &innoc){
      if(scndbar != nullptr){
          if(id == scndbar->data){
            guiltStack.push(id);
            innoc = false;
          }
          firstB2(scndbar->next, id, guiltStack, innoc);
        }
    }
    void scndB(node* tempInn, stack<string>&innocStack){
      string id;
      bool innoc2 = true;
      if(tempInn!= nullptr){
        node *tempG = head;
        id = tempInn->data;
        scndB2(tempG, id, innoc2);
        if(innoc2 == true){
          innocStack.push(id);
        }
        else{
          innoc2 = true;
        }
        scndB(tempInn->next, innocStack);
      }
    }
    void scndB2(node* tempG, string &id, bool &innoc2){
      if(tempG!=nullptr){
          if(id == tempG->data){
            innoc2 = false;
          }
          scndB2(tempG->next, id, innoc2);
        }
    }

    void insert(string _data){
      node *temp = new node;
      temp->data = _data;
      temp->next = head;
      head = temp;
    }

    void insertRec(stack<string> tempStack, linkedList temp){
      linkedList h = temp;
      if(tempStack.empty())
        return;
      insert(tempStack.top()); 
      tempStack.pop();
      insertRec(tempStack, h);
    }

    bool isEmpty(){
      return head == nullptr;
    }

    node* getHead(){
      return head;
    }

    void outPrintRec(node* cu, ofstream &fout){
      if (cu->next == nullptr){
          fout << cu->data;
          return;
      }
      fout << cu->data <<endl;
      outPrintRec(cu->next, fout);
    }

    void printRecursive(node* cu){  
      if (cu == nullptr){
          return;
      }
      cout << cu->data <<endl;
      printRecursive(cu->next);
    }

    void looP(node* cu, node* nxt, bool &isSort){
      if(cu->next != nullptr){
        string t1 = cu->data;
        string t2 = cu->next->data;
          t1 = t1.substr(t1.find_first_not_of('0'));
          t2 = t2.substr(t2.find_first_not_of('0'));
        if(t1.size() > t2.size()){
          string tempData = cu->data; //store t1
          cu->data = nxt->data;
          nxt->data = tempData;
          isSort = false;
        }
        else if(t1.size() == t2.size()){
             if(t1.compare(t2) > 0){
               string tempData = cu->data; // store t1
               cu->data = nxt->data;
               nxt->data = tempData;
               isSort = false;
              }
        }
        looP(cu->next, nxt->next, isSort);
      }
    }

    void sortR(bool isSort, node* head){
      if(head == nullptr){
        return;
      }
      else{
        if(!isSort){ //while false, list is still unsorted
          isSort = true;
          node* cu = head;
          node* nxt = cu->next;
          looP(cu, nxt, isSort);
          sortR(isSort, head);
        }
      }
    }

    /* non-recursive sorting
    void sort(){
      if(head == nullptr || head->next == nullptr){
        return;
      }
      else{
        bool isSorted = false;
        while(!isSorted){ //while false, list is still unsorted
          isSorted = true;
          node* cu = head;
          node* nxt = cu->next;
          while(cu->next != nullptr){
            string t1 = cu->data;
            string t2 = cu->next->data;
              t1 = t1.substr(t1.find_first_not_of('0'));
              t2 = t2.substr(t2.find_first_not_of('0'));
            if(t1.size() > t2.size()){
                string tempData = cu->data; //store t1
                cu->data = nxt->data;
                nxt->data = tempData;
                isSorted = false;
            }
            else if(t1.size() == t2.size()){
                    if(t1.compare(t2) > 0){
                      string tempData = cu->data; // store t1
                      cu->data = nxt->data;
                      nxt->data = tempData;
                      isSorted = false;
                    }
            }
            cu = cu->next;
            nxt = cu->next;
          }
        }
      }
    }
    */

    /* non-recursive printing 
    void print(){
      node *cu = head;
      while(cu->next != nullptr){
        cout << cu->data << endl;
        cu = cu->next;
      }
      cout << cu->data << endl;
    }
    */

    /* non-recursive file printing
    void outPrint(ofstream &fout){
      node *cu = head;
      while(cu->next != nullptr){
        fout << cu->data << endl;
        cu = cu->next;
      }
      fout << cu->data;
    }
    */
};

