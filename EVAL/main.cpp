#include <iostream>
#include <vector>
#include <climits>

#include "headers.h"

using namespace std;

unordered_map<string, Variable> Vars;
unordered_map<string, int> Functions;
unordered_map<string, int> BasicMathOperations;
unordered_map<int, string> BasicMathOperationsReverse;

int main()
{
	vector<Element> Elements;
	InitializeMaps();
	string error = "";
	string input = "";
	/*InfixToElements("1+3.5123+x*sin(0.7)\\2+3", error, 0, Elements);
	for (int i = 0; i < Elements.size(); i++)
	{
		if (Elements[i].operation != 0)
			cout << BasicMathOperationsReverse[Elements[i].operation] << "\t";
		else
		{
			if (Elements[i].var.type == 3)
				printf("%f\t", Elements[i].var.value);
			else
				printf("%d\t", (int)(Elements[i].var.value));
		}
	}
	Variable result = EvaluateElements(Elements);
	cout << "=\t";
	if (result.type == 2)
		cout << (int)(result.value);
	else
		cout << result.value;*/
	while (input != "exit")
	{
		char ci[1024];
		cin.getline(ci, 1024);
		input = ci;
		error = "";
		Parse(input, error);
		cout << endl;
	}
	cin.get();
	return 0;
}