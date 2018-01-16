//*Abs, acos, asin, atan, ceiling, cos, floor, log, log10, max, min, pow, round, sign, sqrt, tan, truncate
#include<iostream>
#include<vector>
#include<cmath>

#include "Headers.h"

using namespace std;

Variable SelectFunction(int n, vector<Variable> Variables)
{
	if (n == 1)
	{
		Variable v = Variables[0];
		v.value = abs(v.value);
		return v;
	}
	if (n == 2) return acos(Elements);
	if (n == 3) return asin(Elements);
	if (n == 4) return atan(Elements);
	if (n == 5) return ceil(Elements);
	if (n == 6) return cos(Elements);
	if (n == 7) return floor(Elements);
	if (n == 8)
	{
		Variable v = Variables[0];
		Variable base;
		if (Variables.size() == 2)
		{
			base = Variables[1];
			v.value = log(v.value) / log(base.value);
			return v;
		}
		v.value = log(v.value);
		return v;

	}
	if (n == 9) return log10(Elements) // Included in log
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
