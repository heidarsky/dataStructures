#include <string>
#include <fstream>
using namespace std;

struct nodeTree{
  nodeTree* left;
  int val;
  nodeTree* right;
};

class tree{
  private:
    nodeTree* root;
  public:
    tree(){
      int val = 0;
      nodeTree* left = nullptr;
      nodeTree* right = nullptr;
    }
    nodeTree* insert(nodeTree* root, int v);
    void preorder(nodeTree* , string t, ofstream &fout);

};