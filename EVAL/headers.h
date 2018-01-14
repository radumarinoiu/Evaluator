#pragma once
#include <vector>
#include <string>
#include "DataStructures.h"
using namespace std;
int GetTypeOfStr(string&, string&);
int GetTypeOfChar(char);
string InfixToPostfix(string);
int EvaluatePostfix(string);
int ApplyBasicOperation(string, int, int);
string IntToString(int);
int ParseInt(string);