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
	InfixToElements("1+3+x*(60-3*4)\\2", error, 0, Elements);
	for (int i = 0; i < Elements.size(); i++)
	{
		if (Elements[i].operation != 0)
			cout << BasicMathOperationsReverse[Elements[i].operation] << "\n";
		else
		{
			if (Elements[i].var.type == 1)
			{
				if (Elements[i].var.value == 1)
					cout << "True\n";
				else
					cout << "False\n";
			}
			else if (Elements[i].var.type == 3)
				printf("%f\n", Elements[i].var.value);
			else
				printf("%d\n", (int)(Elements[i].var.value));
		}
	}
	/*Parse("a:=2*3", error);
	InfixToElements("1+3+5", error, 0, Elements);
	for (int i = 0; i < Elements.size(); i++)
	{
		if (Elements[i].operation != 0)
			cout << BasicMathOperationsReverse[Elements[i].operation] << "\n";
		else
		{
			if (Elements[i].var.type == 1)
			{
				if (Elements[i].var.value == 1)
					cout << "True\n";
				else
					cout << "False\n";
			}
			else if (Elements[i].var.type == 3)
				printf("%f\n", Elements[i].var.value);
			else
				printf("%d\n", (int)(Elements[i].var.value));
		}
	}*/
	cin.get();
	return 0;
}