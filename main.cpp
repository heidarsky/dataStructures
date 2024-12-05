#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
#include "postfix.h"
#include <stack>
#include <string>
#include <algorithm>
#include "prioQue.h"
using namespace std;

//make string only brackets for easier bool
string strofBrac(string s) {
	string x = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(' || s[i] == ')' || s[i] == '[' || s[i] == ']' || s[i] == '{' || s[i] == '}')
			x += s[i];
	}
	return x;
}

//false expression if redundant
bool redundant(string s) {
	stack<char> st;
	for (int i = 0; i < s.size();i++) {
		if ((s[i] != ')') && (s[i] != ']') && (s[i] != '}')) { //if not closed push
			st.push(s[i]);
		}
		if ( (s[i] == ')') || (s[i] == ']') || (s[i] == '}') ) { //if closed check top
			char t = st.top(); st.pop();
			if ( (t == '(') || (t == '[') || (t == '{') ) { // if open brack false
				return false;
				break;
			}
			else {
				while(!st.empty() && (st.top() != '(') && (st.top() != '[') && (st.top() != '{')){
					st.pop();
				}
				st.pop();
			}
		}
	}
	return true;
}

//true if balanced paranthesis
bool valid(string s) {
	stack<char> st;
	s = strofBrac(s);
	cout << s << endl;
	for (int i = 0; i < s.size(); i++) {
		if (st.empty())
			st.push(s[i]);
		else if (s[i] == '{' || s[i] == '(' || s[i] == '[') {
			st.push(s[i]);
		}
		else if (s[i] == ')') {
			if (st.top() != '(') {
				return false;
				break;
			}
			st.pop();
		}
		else if (s[i] == ']') {
			if (st.top() != '[') {
				return false;
				break;
			}
			st.pop();
		}
		else if (s[i] == '}') {
			if (st.top() != '{') {
				return false;
				break;
			}
			st.pop();
		}
	}
	if(st.empty()) 
		return true;
	else 
		return false;
}

//infix to postfix
string toPostfix(string h, string result, postfix &pf1) {
	for (int i = 0; i < h.size(); i++) {
		if (isdigit(h[i]))
			result += h[i];
		else if (h[i] == '[') {
			pf1.push(h[i]);
		}
		else if (h[i] == ']') {
			while (pf1.peak() != '[') {
				result += pf1.peak();
				pf1.pop();
			}
			pf1.pop(); // remove the [
		}
		else if (h[i] == '{') {
			pf1.push(h[i]);
		}
		else if (h[i] == '}') {
			while (pf1.peak() != '{') {
				result += pf1.peak();
				pf1.pop();
			}
			pf1.pop(); // remove the {
		}
		else if (h[i] == '(') {
			pf1.push(h[i]);
		}
		else if (h[i] == ')') {
			while (pf1.peak() != '(') {
				result += pf1.peak();
				pf1.pop();
			}
			pf1.pop(); // remove the (
		}
		else {
			while (!pf1.isEmpty() && pf1.priority(h[i]) <= pf1.priority(pf1.peak())) {
				result += pf1.peak();
				pf1.pop();
			}
			pf1.push(h[i]);
		}
	}
	while (!pf1.isEmpty()) {
		result += pf1.peak();
		pf1.pop();
	}
	return result;
}

//calculate after postfix
int evalPriority(string h, stack<int> &stF) {
	int tem; // math res
	int a; int b;
	char op;

	for (int i = 0; i < h.size() ; i++) {
		if (isdigit(h[i]))
			stF.push(h[i] - '0');
		else {
			op = h[i]; //operator
			a = stF.top();
			stF.pop();

			b = stF.top();
			stF.pop();
			if (op == '/') {
				tem = b / a; // ORDER IS DIFFERENT CUS STACK!!
				stF.push(tem);
			}
			else if (op == '*') {
				tem = b * a;
				stF.push(tem);
			}
			else if (op == '+') {
				tem = b + a;
				stF.push(tem);
			}
			else if (op == '-') {
				tem = b - a;
				stF.push(tem);
			}
			//cout << a << op << b << " = " << tem << endl;
		}
	}
	return stF.top();
}

void cleanUp(string& dataType) {
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
	postfix pf1; //postfix
	string result = "";
	stack<int> stF; //evaluate priority
	int prio;
	prioQue myQ;

	if (fin.eof()){
		cout << "file empty";
		fin.close(); fout.close();
		}
	else {
		while (getline(fin, line)) {
			if (line == "")
				cout << "empty line" << endl;
			else if (valid(line) == false) {
				cout << "invalid exp " << line << endl << endl;
			}
			else if (redundant(line) == false) {
				cout << "redundant " << line << endl << endl;
			}
			else {
					cout << line << endl;
				result = toPostfix(line, result, pf1);
					cout << result << endl;
				cleanUp(result);
				prio = evalPriority(result, stF);
					cout << prio << endl << endl;
				myQ.enqueue(line, prio);
				
			}
			result = "";
		}
		if (myQ.isEmpty())
			fout << "No Valid Expression";
		else
			myQ.print(fout);
	}
	
	return 0;
}