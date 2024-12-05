#include <fstream>
using namespace std;

struct node {
	int val;
	node* left;
	node* right;
	int height;
	node(int d) {
		val = d;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
};

class avlTree {
private:
  node* root;
public:
  avlTree(){ root = nullptr; }
  void add(int data) { root = insert(root, data); }
  node* getRoot() { return root; }
  int max(int a, int b) {
	  if (a > b)
  		return a;
  	else
  		return b;
  }
  node* insert(node* t, int x);

  node* leftRight(node* );
	node* rightLeft(node* );
  node* singleRight(node* );
	node* singleLeft(node* );

  int height(node* cu);
	int bFactor(node* cu);
  void levelorder(node* cur);
  void treePrint(node* cur, ofstream &fout);
};