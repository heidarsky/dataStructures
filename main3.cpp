#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
#include "tree.h"
using namespace std;

int main(int argc, char* argv[]) {
  ArgumentManager argMan(argc, argv);
	ifstream fin(argMan.get("input"));
	ofstream fout(argMan.get("output"));
  //ifstream fin("input1.txt");
  //ofstream fout("output1.txt");
  string line;
  int num;

  tree myTree;
  nodeTree* ga3 = new nodeTree;
  
  if (fin.peek() == EOF) {
    fout << "";
		cout << "file is empty" << endl;
		fin.close();
		fout.close();
	}
  else{
    while(getline(fin, line)){
      if(line.size() == 0)
        cout << ">empty line" << endl;
      else{
        istringstream st(line);
        while(st >> num){
          ga3 = myTree.insert(ga3, num);
        }
      }
    }
    string t = "x";
    myTree.preorder(ga3, t, fout);
  }

  
}
