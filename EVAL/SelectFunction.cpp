//*Abs, acos, asin, atan, ceiling, cos, floor, log, log10, max, min, pow, round, sign, sqrt, tan, truncate
#include<iostream>
#include<vector>
#include<cmath.h>

#include "Headers.h"

using namespace std;

double SelectFunction(int n, vector<Element> Elements)
{
	if (n == 1) return abs(Elements);
	if (n == 2) return acos(Elements);
	if (n == 3) return asin(Elements);
	if (n == 4) return atan(Elements);
	if (n == 5) return ceil(Elements);
	if (n == 6) return cos(Elements);
	if (n == 7) return floor(Elements);
	if (n == 8) return log(Elements);
	if (n == 9) return log10(Elements);
	if (n == 10) return fmax(Elements);
	if (n == 11) return fmin(Elements);
	if (n == 12) return pow(Elements);
	if (n == 13) return round(Elements);
	if (n == 14) return sign(Elements);
	if (n == 15) return sin(Elements);
	if (n == 16) return sqrt(Elements);
	if (n == 17) return tan(Elements);
	if (n == 18) return trunc(Elements);
}
