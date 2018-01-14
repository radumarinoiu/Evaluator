#include <cmath>
#include <algorithm> //Nu include la operatii

#include "Headers.h"

using namespace std;

int ParseInt(string ToParseString)
{
	int ParsedInt = 0;
	int sign = 1;
	if (ToParseString[0] == '-')
	{
		sign = -1;
		ToParseString = ToParseString.substr(1, ToParseString.length() - 1);
	}
	for (unsigned i = 0; i < ToParseString.length(); i++)
	{
		ParsedInt = ParsedInt * 10 + ToParseString[i] - '0';
	}
	return ParsedInt * sign;
}

string IntToString(int ToParseInt)
{
	string ParsedString = "";
	bool negative = false;
	if (ToParseInt < 0)
	{
		negative = true;
		ToParseInt *= -1;
	}
	do
	{
		ParsedString += ((char)(ToParseInt % 10) + '0');
		ToParseInt /= 10;
	} while (ToParseInt != 0);
	reverse(ParsedString.begin(), ParsedString.end());
	if(negative)
	{
		ParsedString = '-' + ParsedString;
	}
	return ParsedString;
}

int ApplyBasicOperation(string operation, int val1, int val2)
{
	if (operation == "+")
		return val1 + val2;
	if (operation == "-")
		return val1 - val2;
	if (operation == "*")
		return val1 * val2;
	if (operation == "/")
		return val1 / val2;
	return 0;
}

string ApplyOperation(string operation, float v1, float v2, float v3,/*....*/ string &response)
{
	return "";
}