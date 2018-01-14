#include <cstring>

#include "Headers.h"

using namespace std;

int GetTypeOfStr(string &str, string &response)
{
	unsigned pos = 0;
	int firstChar = GetTypeOfChar(str[0]);
	if (firstChar == 3) // Check if it's a basic arithmetic operation - Return 2
	{
		response = str[0];
		str = str.substr(1, str.length() - 1);
		return 2;
	}
	if(firstChar == 2) //Check if it's a constant - Return 1 and Value
	{
		pos = 0;
		pos++;
		while (GetTypeOfChar(str[pos]) == 2)
			pos++;
		response = str.substr(0, pos);
		str = str.substr(pos, str.length() - pos);
		return 1;
	}
	if (firstChar == 4) // Check if it's a parenthesis - Return 1 and Value of expression
	{
		int pcount = 1;
		while (pcount != 0 && ++pos < str.length())
		{
			if (str[pos] == '(')
				pcount++;
			if (str[pos] == ')')
				pcount--;
		}
		if (pcount == 0)
		{
			string expr = str.substr(1, pos - 1);
			response = InfixToPostfix(expr);
			str = str.substr(pos + 1, str.length() - pos - 1);
			return 1;
		}
		return -1;
	}
	if (firstChar == 1) // Check if it's a variable or a function
	{
		pos = 0;
		int nextCharType = GetTypeOfChar(str[++pos]);
		while (nextCharType == 1 || nextCharType == 2)
			nextCharType = GetTypeOfChar(str[++pos]);
		if (nextCharType == 3)//Variable
		{
			string varName = str.substr(0, pos - 1);
			response = Vars[varName].value;
			return 1;
		}
		if (nextCharType == 4)//Function
		{
			int oldPos = pos;
			int pcount = 1;
			while (pcount != 0 && ++pos < str.length())
			{
				if (str[pos] == '(')
					pcount++;
				if (str[pos] == ')')
					pcount--;
			}
			if (pcount == 0)
			{
				string func = str.substr(0, oldPos);
				string expr = str.substr(oldPos + 1, pos - oldPos - 1);
				response = InfixToPostfix(expr);
				str = "";
				response = "";// ApplyOperation(func, response);
				return 1;
			}
		}
	}
	return -1;
}

int GetTypeOfChar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1; // Case Insensitive Letter
	if (c >= '0' && c <= '9')
		return 2; // Digit
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return 3; // Basic Arithmetic Operation
	if (c == '(' || c == ')')
		return 4; // Parenthesis
	return -1; // Unknows Symbol
}