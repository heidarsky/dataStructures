#include "tree.h"
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

nodeTree* tree::insert(nodeTree* root, int v){
    //move left and right until empty node
    if (root == nullptr || root->val == 0) {
      nodeTree* r = new nodeTree;
        r->val = v;
        r->left = nullptr;
        r->right = nullptr;
      return r;
    }
    if (v < root->val){ //if smaller go left
      root->left = insert(root->left, v);
    }
    else //if bigger go right
      root->right = insert(root->right, v);
    return root;
}


// nLR (node, lefts, rights)
void tree::preorder(nodeTree* cur, string t, ofstream &fout){ //from root, left childs expand all then right childs
  if(cur!= nullptr){
    fout << "[" << t << "] " << cur->val << endl;
    preorder(cur->left, t+"l", fout);
    preorder(cur->right, t+"r", fout);
  }
}

