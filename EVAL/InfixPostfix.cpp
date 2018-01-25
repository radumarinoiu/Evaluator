#include <string>
#include <vector>
#include <stack>
#include <minmax.h>
#include <iostream>

#include "Headers.h"

using namespace std;

int GetTypeOfChar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1; // Case Insensitive Letter
	if (c >= '0' && c <= '9')
		return 2; // Digit
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '\\' || c == '%' || c == '\0')
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
			error = "Expresia contine doua atribuiri!\n";
			cout << error;
			return false;
		}

		bool errorOccured = false;
		string leftSide = input.substr(0, signPosition);
		vector<Element> leftSideVar;
		InfixToElements(leftSide, error, 0, leftSideVar);
		string specError = " nu are atribuita o valoare";
		if (!(error == "" ||  error.find(specError) != string::npos))
		{
			error = "Operatorul din stanga atribuirii nu este o variabila!\n" + error;
			cout << error;
			errorOccured = true;
		}
		error = "";

		string rightSide = input.substr(signPosition + 2, input.length() - (signPosition + 2));
		vector<Element> rightSideVar;
		InfixToElements(rightSide, error, signPosition + 2, rightSideVar);
		if (error != "")
		{
			error = "Operatorul din dreapta atribuirii nu este o expresie valida!\n" + error;
			cout << error;
			errorOccured = true;
		}
		if(errorOccured)
			return false;

		Vars[leftSide] = EvaluateElements(rightSideVar);
		return true;
	}
	else
	{
		Variable result;
		vector<Element> expression;
		InfixToElements(input, error, 0, expression);
		if (error != "")
		{
			cout << error;
			return false;
		}
		result = EvaluateElements(expression);
		if (result.type == 2)
		{
			cout << (int)(result.value) << endl;
			return true;
		}
		else
		{
			cout << result.value << endl;
			return true;
		}
	}
	return false;
}

void InfixToElements(string input, string &error, int oldPos, vector<Element> &Elements)
{
	input = input + "\0";
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
				error = "Variabila '" + currentName + "' de pe pozitia " + to_string(oldPos) + " nu are atribuita o valoare!\n";
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
				error = "Caracter neasteptat pe pozitia " + to_string(input.find(')') + 1) + "!\n";
				return;
			}
			string contentString[2] = { "", input.substr(pos + 1, input.find(')') - (pos + 1)) };
			if (contentString[1].find(",") != string::npos)
			{
				if (contentString[1].find(",", contentString[1].find(",") + 1) != string::npos)
				{
					error = "Caracter neasteptat pe pozitia " + to_string(contentString[1].find(",", contentString[1].find(",")) + oldPos) + "!\n";
					return;
				}
				contentString[0] = contentString[1].substr(0, contentString[1].find(","));
				contentString[1] = contentString[1].substr(contentString[1].find(",") + 1, contentString[1].length() - contentString[1].find(",") - 1);
			}
			vector<Element> parameter1;
			vector<Element> parameter2;
			if (contentString[0] != "")
			{
				InfixToElements(contentString[0], error, oldPos + currentName.length() + 1, parameter1);
				if (error != "")
					return;
				InfixToElements(contentString[1], error, oldPos + currentName.length() + contentString[0].length() + 2, parameter2);
				if (error != "")
					return;

				Element evaluatedContent1;
				evaluatedContent1.operation = 0;
				evaluatedContent1.var = EvaluateElements(parameter1);

				Element evaluatedContent2;
				evaluatedContent2.operation = 0;
				evaluatedContent2.var = EvaluateElements(parameter2);

				vector<Variable> fargs;
				fargs.push_back(evaluatedContent1.var);
				fargs.push_back(evaluatedContent2.var);
				evaluatedContent1.var = SelectFunction(Functions[currentName], fargs);
				Elements.push_back(evaluatedContent1);
			}
			else
			{
				InfixToElements(contentString[1], error, oldPos + currentName.length() + 1, parameter1);
				if (error != "")
					return;

				Element evaluatedContent1;
				evaluatedContent1.operation = 0;
				evaluatedContent1.var = EvaluateElements(parameter1);

				vector<Variable> fargs;
				fargs.push_back(evaluatedContent1.var);
				evaluatedContent1.var = SelectFunction(Functions[currentName], fargs);
				Elements.push_back(evaluatedContent1);
			}
			InfixToElements(input.substr(input.find(')') + 1, input.length() - (input.find(')') + 1)), error, oldPos + input.find(')') + 1, Elements); // Parse content after parenthesis
			return;
		}
		else
		{
			error = "Caracter neasteptat pe pozitia " + to_string(pos) + "!\n";
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
		if (GetTypeOfChar(input[pos]) == 3) // Constant Case
		{
			if (currentNumber.find('.') != string::npos) // Check for more than 1 decimal point
			{
				int pos1 = currentNumber.find('.') != string::npos;
				if (currentNumber.find('.', pos1 + 1) != string::npos)
				{
					error = "Caracter neasteptat pe pozitia " + to_string(oldPos + currentNumber.find('.', pos1 + 1)) + "!\n";
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
			error = "Caracter neasteptat pe pozitia " + to_string(oldPos + pos) + "!\n";
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
			InfixToElements(input.substr(pos, input.length()), error, oldPos + 1, Elements);
			return;
		}
		else
		{
			error = "Caracter neasteptat pe pozitia " + to_string(oldPos + 1) + "!\n";
			return;
		}
	}
	
	if (charType == 4)
	{
		if (input.find(')') == string::npos)
		{
			error = "Lipseste paranteza inchisa pentru paranteza de pe pozitia '" + to_string(oldPos) + "!\n";
			return;
		}
		if (GetTypeOfChar(input[input.find(')') + 1]) != 3)
		{
			error = "Caracter neasteptat pe pozitia " + to_string(input.find(')') + 1) + "!\n";
			return;
		}
		vector<Element> content;
		InfixToElements(input.substr(1, input.find(')') - 1), error, oldPos + 1, content); // Parse content of parenthesis
		if (error != "")
			return;
		Element evaluatedContent;
		evaluatedContent.operation = 0;
		evaluatedContent.var = EvaluateElements(content);
		Elements.push_back(evaluatedContent);
		InfixToElements(input.substr(input.find(')') + 1, input.length() - (input.find(')') + 1)), error, oldPos + input.find(')') + 1, Elements); // Parse content after parenthesis
		return;
	}
}

Variable EvaluateElements(vector<Element> expression)
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
				if (!opStack.empty())
				{
					if (opStack.top().operation >= 3)
					{
						postFix.push_back(opStack.top());
						opStack.pop();
					}
				}
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
			postFix.erase(postFix.begin() + pos + 2);
			postFix.erase(postFix.begin() + pos + 1);
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
		if (var2.value == 0)
			var.value = 0;
		else
			var.value = var1.value / var2.value;
		return var; // /
	}
	if (op == 5)
	{
		var.type = 2;
		if (var2.value == 0)
			var.value = 0;
		else
			var.value = ((int)(var1.value)) / ((int)(var2.value));
		return var; // \\ 
	}
	if (op == 6)
	{
		var.type = 2;
		if (var2.value == 0)
			var.value = 0;
		else
			var.value = ((int)(var1.value)) % ((int)(var2.value));
		return var; // %
	}
	return var;
}