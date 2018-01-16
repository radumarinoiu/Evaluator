//Abs, acos, asin, atan, ceiling, cos, floor, log, log10, max, min, pow, round, sign, sqrt, tan, truncate
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
	if (n == 2)
	{
		Variable v = Variables[0];
		v.value = acos(v.value);
			return v;
	}
	if (n == 3)
	{
		Variable v = Variables[0];
		v.value = asin(v.value);
			return v;
	}
	if (n == 4) 
	{
		Variable v = Variables[0];
		v.value = atan(v.value);
			return v;
	}
	if (n == 5) 
	{
		Variable v = Variables[0];
		v.value = ceil(v.value);
			return v;
	}
	if (n == 6) 
	{
		Variable v = Variables[0];
		v.value = cos(v.value);
			return v;
	}
	if (n == 7)
	{
		Variable v = Variables[0];
		v.value = floor(v.value);
			return v;
	}
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
	if (n == 9) 
	{
		Variable v1 = Variables[0];
		Variable v2 = Variables[1];
		v1.value = fmax(v1.value, v2.value);
			return v1;
	}
	if (n == 10) 
	{
		Variable v1= Variables[0];
		Variable v2 = Variables[1];
			v1.value = fmin(v1.value, v2.value);
			return v1;
	}
	if (n == 11) 
	{
		Variable v = Variables[0];
		Variable power = Variables[1];
		v.value = pow(v.value, power.value);
			return v;
	}
	if (n == 12) 
	{
		Variable v = Variables[0];
		v.value = round(v.value);
			return v;
	}
	if (n == 13) 
	{
		Variable v = Variables[0];
		v.value = v.value / abs(v.value);
			return v;
	}
	if (n == 14) 
	{
		Variable v = Variables[0];
		v.value = sin(v.value);
			return v;
	}
	if (n == 15) 
	{
		Variable v = Variables[0];
		v.value = sqrt(v.value);
			return v;
	}
	if (n == 16) 
	{
		Variable v = Variables[0];
		v.value = tan(v.value);
			return v;
	}
	if (n == 17) 
	{
		Variable v = Variables[0];
		v.value = trunc(v.value);
			return v;
	}
}
