#include <vector>
#include <string>

#include "Headers.h"

using namespace std;

int EvaluatePostfix(string expr)
{
	vector<string> expression;
	unsigned left = 0;
	expr += " ";
	while (expr.length() - 1 > left)
	{
		int spacePos = expr.find_first_of(' ', left);
		expression.push_back(expr.substr(left, spacePos - left));
		left = spacePos + 1;
	}
	int i = 0;
	while (expression.size() > 1)
	{
		if (expression[i].length() == 1 && GetTypeOfChar(expression[i].c_str()[0]) == 3)
		{
			expression[i - 2] = IntToString(ApplyBasicOperation(expression[i], ParseInt(expression[i - 2]), ParseInt(expression[i - 1])));
			expression.erase(expression.begin() + i);
			expression.erase(expression.begin() + i - 1);
			i = i - 2;
		}
		i++;
	}
	return ParseInt(expression[0]);
}