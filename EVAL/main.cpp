#include <iostream>
#include <vector>
#include <climits>

#include "headers.h"

using namespace std;

unordered_map<string, Variable> Vars;
unordered_map<string, int> Functions;
unordered_map<string, int> BasicMathOperations;
unordered_map<int, string> BasicMathOperationsReverse;
unordered_map<int, int> OperatorPrecedence;

int main()
{
	vector<Element> Elements;
	InitializeMaps();
	string error = "";
	string input = "";
	while (input != "exit")
	{
		char ci[1024];
		cin.getline(ci, 1024);
		input = ci;
		error = "";
		if(input != "")
			Parse(input, error);
		cout << endl;
	}
	cin.get();
	return 0;
}