#include "Headers.h"

using namespace std;

void InitializeMaps()
{
	BasicMathOperations["+"] = 1;
	BasicMathOperations["-"] = 2;
	BasicMathOperations["*"] = 3;
	BasicMathOperations["\\"] = 4;
	BasicMathOperations["/"] = 5;
	BasicMathOperations["%"] = 6;
	BasicMathOperations["&"] = 7;
	BasicMathOperations["|"] = 8;
	BasicMathOperations["^"] = 9;
	BasicMathOperationsReverse[1] = "+";
	BasicMathOperationsReverse[2] = "-";
	BasicMathOperationsReverse[3] = "*";
	BasicMathOperationsReverse[4] = "\\";
	BasicMathOperationsReverse[5] = "/";
	BasicMathOperationsReverse[6] = "%";
	BasicMathOperationsReverse[7] = "&";
	BasicMathOperationsReverse[8] = "|";
	BasicMathOperationsReverse[9] = "^";
	Functions["abs"] = 1;
	Functions["acos"] = 2;
	Functions["asin"] = 3;
	Functions["atan"] = 4;
	Functions["ceiling"] = 5;
	Functions["cos"] = 6;
	Functions["floor"] = 7;
	Functions["log"] = 8;
	Functions["max"] = 9;
	Functions["min"] = 10;
	Functions["pow"] = 11;
	Functions["round"] = 12;
	Functions["sign"] = 13;
	Functions["sin"] = 14;
	Functions["sqrt"] = 15;
	Functions["tan"] = 16;
	Functions["trun"] = 17;
	OperatorPrecedence[3] = 1;
	OperatorPrecedence[4] = 1;
	OperatorPrecedence[5] = 1;
	OperatorPrecedence[6] = 1;
	OperatorPrecedence[1] = 2;
	OperatorPrecedence[2] = 2;
	OperatorPrecedence[7] = 3;
	OperatorPrecedence[8] = 3;
	OperatorPrecedence[9] = 3;
}