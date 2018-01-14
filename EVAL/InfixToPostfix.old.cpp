#include <string>
#include <stack>
#include <queue>
#include <vector>

#include "Headers.h"

using namespace std;

string InfixToPostfix(string InfixString)
{
	queue<string> TransferQueue;
	stack<string> TransferStack;
	string TempString;
	unsigned pos = 0;
	while (InfixString.length() > 0)
	{
		int strType = GetTypeOfStr(InfixString, TempString);
		if (strType == 1)
			TransferQueue.push(TempString);
		if (strType == 2)
		{
			if (TempString[0] == '+' || TempString[0] == '-')
			{
				while (!TransferStack.empty())
				{
					TransferQueue.push(TransferStack.top());
					TransferStack.pop();
				}
				TransferStack.push(TempString);
			}
			if (TempString[0] == '*' || TempString[0] == '/')
			{
				if (!TransferStack.empty())
				{
					if (TransferStack.top() == "*" || TransferStack.top() == "/")
					{
						TransferQueue.push(TransferStack.top());
						TransferStack.pop();
					}
				}
				TransferStack.push(TempString);
			}
		}
		pos++;
	}
	while (!TransferStack.empty())
	{
		TransferQueue.push(TransferStack.top());
		TransferStack.pop();
	}
	string returnedValues;
	while (!TransferQueue.empty())
	{
		returnedValues.append(TransferQueue.front());
		returnedValues.append(" ");
		TransferQueue.pop();
	}
	returnedValues = returnedValues.substr(0, returnedValues.length() - 1);
	return returnedValues;
}