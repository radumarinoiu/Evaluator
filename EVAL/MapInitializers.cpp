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
	Variable v;
	v.type = 2;
	v.value = 156;
	Vars["x"] = v;
}