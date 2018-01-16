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
	BasicMathOperationsReverse[1] = "+";
	BasicMathOperationsReverse[2] = "-";
	BasicMathOperationsReverse[3] = "*";
	BasicMathOperationsReverse[4] = "\\";
	BasicMathOperationsReverse[5] = "/";
	BasicMathOperationsReverse[6] = "%";
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
}