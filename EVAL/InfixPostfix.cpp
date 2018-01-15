#include <string>
#include <vector>
#include <stack>
#include <minmax.h>

#include "Headers.h"

using namespace std;

int GetTypeOfChar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1; // Case Insensitive Letter
	if (c >= '0' && c <= '9')
		return 2; // Digit
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '\\' || c == '%')
		return 3; // Basic Arithmetic Operation
	if (c == '(' || c == ')')
		return 4; // Parenthesis
	if (c == '.')
		return 5; // Digit Separator
	return -1; // Unknown Symbol
}

bool Parse(string input, string &error)
{
	if (input.find(":=") != string::npos)
	{
		int signPosition = input.find(":=");
		if (input.find(":=", signPosition + 2) != string::npos)
		{
			error = "Expresia contine doua atribuiri!";
			return false;
		}

		string leftSide = input.substr(0, signPosition);
		vector<Element> leftSideVar;
		InfixToElements(leftSide, error, 0, leftSideVar);
		if (error != "" || Vars.count(leftSide) == 0)
		{
			error = "Operatorul din stanga atribuirii nu este o variabila!\n" + error;
			return false;
		}

		string rightSide = input.substr(signPosition + 2, input.length() - (signPosition + 2));
		vector<Element> rightSideVar;
		InfixToElements(rightSide, error, 0, rightSideVar);
		if (error != "")
		{
			error = "Operatorul din dreapta atribuirii nu este o expresie valida!\n" + error;
			return false;
		}

		Vars[leftSide] = EvaluateElements(rightSideVar, Vars[leftSide].type);
	}
}

void InfixToElements(string input, string &error, int oldPos, vector<Element> &Elements)
{
	if (input == "" || error != "")
		return;
	int charType = GetTypeOfChar(input[0]);
	int pos = 0;
	if (charType == 1) // Variable/Function Case
	{
		string currentName = "";
		while (GetTypeOfChar(input[pos]) == 1 || GetTypeOfChar(input[pos]) == 2)
		{
			currentName += input[pos];
			pos++;
		}
		if (GetTypeOfChar(input[pos]) == 3) // Variable Case
		{
			if (Vars.count(currentName) == 0)
			{
				error = "Variabila '" + currentName + "' de pe pozitia " + to_string(oldPos) + " nu are atribuita o valoare!";
				return;
			}
			Element currentElement;
			currentElement.operation = 0;
			currentElement.var = Vars[currentName];
			Elements.push_back(currentElement);

			string toAddError = "";
			InfixToElements(input.substr(pos, input.length() - pos), error, oldPos + pos, Elements);
			return;
		}
		else if (GetTypeOfChar(input[pos]) == 4) // Function Case
		{
			if (Functions.count(currentName) == 0)
			{
				error = "Functia '" + currentName + "' de pe pozitia " + to_string(oldPos) + " nu exista!";
				return;
			}
			if (input.find(')') == string::npos)
			{
				error = "Lipseste paranteza inchisa pentru paranteza de pe pozitia '" + to_string(oldPos) + "!";
				return;
			}
			if (GetTypeOfChar(input[input.find(')') + 1]) != 3)
			{
				error = "Caracter neasteptat pe pozitia " + to_string(input.find(')') + 1) + "!";
				return;
			}
			InfixToElements(input.substr(pos, input.find(')') - pos), error, oldPos + pos, Elements); // Parse content of parenthesis
			InfixToElements(input.substr(input.find(')') + 1, input.length() - (input.find(')') + 1)), error, oldPos + input.find(')') + 1, Elements); // Parse content after parenthesis
			return;
		}
		else
		{
			error = "Caracter neasteptat pe pozitia " + to_string(pos) + "!";
			return;
		}
	}
	
	if (charType == 2) // Constant Case
	{
		string currentNumber = "";
		while (GetTypeOfChar(input[pos]) == 2 || GetTypeOfChar(input[pos]) == 5)
		{
			currentNumber += input[pos];
			pos++;
		}
		if (GetTypeOfChar(input[pos] == 3)) // Constant Case
		{
			if (currentNumber.find('.') != string::npos) // Check for more than 1 decimal point
			{
				int pos1 = currentNumber.find('.') != string::npos;
				if (currentNumber.find('.', pos1 + 1) != string::npos)
				{
					error = "Caracter neasteptat pe pozitia " + to_string(oldPos + currentNumber.find('.', pos1 + 1)) + "!";
				}
			}
			Element currentElement;
			currentElement.operation = 0;
			currentElement.var.type = 2;
			if (currentNumber.find('.') != string::npos)
			{
				currentElement.var.value = stod(currentNumber);
				currentElement.var.type = 3;
			}
			else
			{
				currentElement.var.value = stoi(currentNumber);
				currentElement.var.type = 2;
			}
			Elements.push_back(currentElement);
			InfixToElements(input.substr(pos, input.length() - pos), error, oldPos + pos, Elements);
		}
		else
		{
			error = "Caracter neasteptat pe pozitia " + to_string(pos) + "!";
			return;
		}
	}

	if (charType == 3) // Basic Operation Case
	{
		pos++;
		string currentOperation = "";
		currentOperation = input[0];
		if (GetTypeOfChar(input[pos]) == 1 || GetTypeOfChar(input[pos]) == 2 || GetTypeOfChar(input[pos]) == 4)
		{
			Element currentElement;
			currentElement.operation = BasicMathOperations[currentOperation];
			Elements.push_back(currentElement);
			InfixToElements(input.substr(pos, input.length()), error, oldPos, Elements);
			return;
		}
		else
		{
			error = "Caracter neasteptat pe pozitia " + to_string(oldPos + 1) + "!";
			return;
		}
	}
	
	if (charType == 4)
	{
		if (input.find(')') == string::npos)
		{
			error = "Lipseste paranteza inchisa pentru paranteza de pe pozitia '" + to_string(oldPos) + "!";
			return;
		}
		if (GetTypeOfChar(input[input.find(')') + 1]) != 3)
		{
			error = "Caracter neasteptat pe pozitia " + to_string(input.find(')') + 1) + "!";
			return;
		}
		InfixToElements(input.substr(1, input.find(')') - 1), error, oldPos + 1, Elements); // Parse content of parenthesis
		InfixToElements(input.substr(input.find(')') + 1, input.length() - (input.find(')') + 1)), error, oldPos + input.find(')') + 1, Elements); // Parse content after parenthesis
		return;
	}
}

Variable EvaluateElements(vector<Element> expression, uint8_t &returnType)
{
	stack<Element> opStack;
	vector<Element> postFix;
	for (int i = 0; i < expression.size(); i++)
	{
		if (expression[i].operation == 0)
		{
			postFix.push_back(expression[i]);
		}
		else
		{
			if (expression[i].operation == 1 || expression[i].operation == 2)
			{
				while (opStack.size() > 0)
				{
					postFix.push_back(opStack.top());
					opStack.pop();
				}
				opStack.push(expression[i]);
			}
			else
			{
				opStack.push(expression[i]);
			}
		}
	}
	while (opStack.size() > 0)
	{
		postFix.push_back(opStack.top());
		opStack.pop();
	}
	int pos = 0;
	while (postFix.size() > 1)
	{
		if (postFix[pos + 2].operation != 0)
		{
			postFix[pos].var = ApplyBasicOperation(postFix[pos].var, postFix[pos + 1].var, postFix[pos + 2].operation);
			postFix.erase(postFix.begin() + pos + 1, postFix.begin() + pos + 2);
			pos--;
		}
		else
			pos++;
	}
	return postFix[0].var;
}

Variable ApplyBasicOperation(Variable var1, Variable var2, uint8_t op)
{
	Variable var;
	if (op == 1)
	{
		var.type = max(var1.type, var2.type);
		var.value = var1.value + var2.value;
		return var; // +
	}
	if (op == 2)
	{
		var.type = max(var1.type, var2.type);
		var.value = var1.value - var2.value;
		return var; // -
	}
	if (op == 3)
	{
		var.type = max(var1.type, var2.type);
		var.value = var1.value * var2.value;
		return var; // *
	}
	if (op == 4)
	{
		var.type = 3;
		var.value = var1.value / var2.value;
		return var; // /
	}
	if (op == 5)
	{
		var.type = 2;
		var.value = ((int)(var1.value)) / ((int)(var2.value));
		return var; // \\ 
	}
	if (op == 6)
	{
		var.type = 2;
		var.value = ((int)(var1.value)) % ((int)(var2.value));
		return var; // %
	}
	return var;
}