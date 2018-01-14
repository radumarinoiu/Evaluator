#include <string>
#include <vector>

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
	return -1; // Unknows Symbol
}

void InfixToElements(string input, string &error, int oldPos)
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
			InfixToElements(input.substr(pos, input.length() - pos), error, oldPos + pos);
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
			InfixToElements(input.substr(pos, input.find(')') - pos), error, oldPos + pos); // Parse content of parenthesis
			InfixToElements(input.substr(input.find(')') + 1, input.length() - (input.find(')') + 1)), error, oldPos + input.find(')') + 1); // Parse content after parenthesis
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
			currentElement.var.isFloatingPoint = (currentNumber.find('.') != string::npos); // Determine if constant is floating point or integer
			if (currentElement.var.isFloatingPoint)
				currentElement.var.value = stod(currentNumber);
			else
				currentElement.var.value = stoi(currentNumber);
			Elements.push_back(currentElement);
			InfixToElements(input.substr(pos, input.length() - pos), error, oldPos + pos);
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
			InfixToElements(input.substr(pos, input.length()), error, oldPos);
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
		InfixToElements(input.substr(1, input.find(')') - 1), error, oldPos + 1); // Parse content of parenthesis
		InfixToElements(input.substr(input.find(')') + 1, input.length() - (input.find(')') + 1)), error, oldPos + input.find(')') + 1); // Parse content after parenthesis
		return;
	}
}