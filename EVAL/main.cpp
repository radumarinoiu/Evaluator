#include <iostream>
#include <vector>
#include <climits>

#include "headers.h"

using namespace std;

int main()
{
	string input;
	char cinput[1024];
	cin.getline(cinput, 1024);
	input = cinput;
	cout << EvaluatePostfix(InfixToPostfix(input));
	cin.get();
	return 0;
}