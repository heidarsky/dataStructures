#include "avltree.h"
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

int avlTree::bFactor(node* cur) {
  if(cur == nullptr)
    return 0;
	return (height(cur->left) - height(cur->right));
}

int avlTree::height(node* cur) {
		if (cur == nullptr)
			return -1;
		else
			return cur->height;
}

/*
int avlTree::height(node* cur) {
		if (cur == nullptr)
			return -1;
		int leftH = height(cur->left);
    int rightH = height(cur->right);
    if(leftH > rightH)
      return leftH + 1;
    return rightH + 1;
}
*/

node* avlTree::insert(node* cur, int x) {
		if (cur == nullptr)
			cur = new node(x);
		else if (x < cur->val) { // go left
			cur->left = insert(cur->left, x); // add
			if (bFactor(cur) == 2) { //check balance
				if (x < cur->left->val)
					cur = singleRight(cur);
				else
					cur = leftRight(cur);
			}
		}
		else if (x > cur->val) { // go right
			cur->right = insert(cur->right, x); // add
			if (bFactor(cur) == -2) { //check balance
				if (x > cur->right->val)
					cur = singleLeft(cur);
				else
					cur = rightLeft(cur);
			}
		}
		cur->height = max(height(cur->left), height(cur->right)) + 1;
		return cur;
}

void avlTree::levelorder(node* cur){
  if(cur == nullptr){
    cout << "BST is empty" << endl;
    return;
  }
  queue<node*> q;
  q.push(cur);
    int lev = 1;
  while(!q.empty()){
    int levelsize = q.size();
    cout << "level (" << lev << "): \t";
    for(int i=0; i<levelsize; i++){
      node* c = q.front();
      q.pop();
      cout << c->val << " ";
      if(c->left != nullptr){
        q.push(c->left);
        cout << "\t";
        }
      if(c->right != nullptr)
        q.push(c->right);
    }
    lev++;
    cout << endl;
  }
}

void avlTree::treePrint(node* cur, ofstream &fout){
  if(cur == nullptr){
    cout << "BST is empty" << endl;
    return;
  }
  queue<node*> q;
  q.push(cur);
  string res = "";
  while(!q.empty()){
    int levelsize = q.size();
    for(int i=0; i<levelsize; i++){
      node* c = q.front();
      q.pop();
      //cout << c->val << " ";
      res += to_string(c->val) + " ";
      if(c->left != nullptr)
        q.push(c->left);
      if(c->right != nullptr)
        q.push(c->right);
    }
  }
  if(res[res.size()-1] == ' ')
    res = res.substr(0, res.size()-1); //remove last space
  cout << res;
  fout << res;
}

node* avlTree::leftRight(node* cur){
	cur->left = singleLeft(cur->left);
  return singleRight(cur);
}
node* avlTree::rightLeft(node* cur){
  cur->right = singleRight(cur->right);
  return singleLeft(cur);
}
node* avlTree::singleRight(node* cur){
  node* temp = cur->left;
  	cur->left = temp->right;
  	  temp->right = cur;
  cur->height = max(height(cur->left), height(cur->right)) + 1;
		temp->height = max(height(temp->left), height(temp->right)) + 1;
  return temp;
}
node* avlTree::singleLeft(node* cur){
  node* temp = cur->right;
  	cur->right = temp->left;
  	  temp->left = cur;
  cur->height = max(height(cur->left), height(cur->right)) + 1;
		temp->height = max(height(temp->left), height(temp->right)) + 1;
  return temp;
}