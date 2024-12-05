#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

bool BFS(int **graph, int start, int end, int size){
  // BFS uses queue
  queue<int> myQ;
  bool *visited = new bool[size]; // check if vertex visisted
  for(int i=0; i<size; i++)
    visited[i] = false;
  myQ.push(start);
  int v =0;
  while(!myQ.empty()){
    v = myQ.front();
    myQ.pop();
    if(v == end){
      delete [] visited;
      return true; 
    }
    else if(!visited[v]){
      visited[v] = true;
    }
    for(int i=0; i<size; i++)
      if(graph[v][i] != 0 && !visited[i])
        myQ.push(i);
  }
  delete[] visited;
  return false;
}

void cleanUp(string &dataType){
  dataType.erase(remove(dataType.begin(), dataType.end(), '\n'), dataType.end());
  dataType.erase(remove(dataType.begin(), dataType.end(), '\r'), dataType.end());
  dataType.erase(remove(dataType.begin(), dataType.end(), ' '), dataType.end());
}

int main(int argc, char* argv[]) {
  ArgumentManager argMan(argc, argv);
	ifstream fin(argMan.get("input"));
	ofstream fout(argMan.get("output"));
  //ifstream fin("input3.txt");
	//ofstream fout("output3.txt");

  string line;

	if (fin.peek() == EOF) {
		cout << "file is empty" << endl;
		fin.close();
		fout.close();
	}
  else{

    int start; int end; int n=0;
    fin >> n;
    fin >> start; 
    fin >> end;

    int **graph = new int*[n]; 
    for(int i=0; i<n; i++)
      graph[i] = new int[n];
    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
        graph[i][j] = 0;
    
    while(getline(fin, line)){
      cleanUp(line);
      if(line.size() == 0){
        cout << ">empty line" << endl;
        continue;
        }
      else{
        int i = line[0] - '0';
        int j = line[1] - '0';
        graph[i][j] = 1; 
        graph[j][i] = 1;
        cout << i << " " << j << endl;
      }
    }
    if(BFS(graph, start, end, n)){
      fout << "true";
      cout << "true";
    }
    else{
      fout << "false";
      cout << "false";
    }
  }
        
}
