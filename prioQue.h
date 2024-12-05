#include <iostream>
using namespace std;

struct node2 {
    string element;
    int prio;
    node2* next;
};

class prioQue {
private:
    node2* front;
    node2* back;

public:
    prioQue() {
        front = nullptr;
        back = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(string val, int pr) {
        node2* temp = new node2;
        temp->element = val;
        temp->prio = pr; //priority to first 
        temp->next = nullptr;

        if (isEmpty()) {
            front = back = temp;
        }
        else {
            node2* cu = front; //store front
            node2* prev = nullptr;
            if (temp->prio < cu->prio) { //if cur has bigger priority 
                temp->next = front;
                front = temp;
            }
            else {
                while (cu != nullptr && temp->prio >= cu->prio) {
                    prev = cu;
                    cu = cu->next;
                }
                prev->next = temp;
                temp->next = cu;
                if (temp->next == nullptr)
                    back = temp;
            }
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            node2* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void print(ofstream &fout) {
        while(!isEmpty() && front->next != nullptr) {
            fout << front->element << endl;
            dequeue();
        }
        fout << front->element; //no endline at end
    }

};