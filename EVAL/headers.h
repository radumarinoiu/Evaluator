#pragma once
#include <string>
#include <unordered_map>

#include "DataStructures.h"

extern std::unordered_map<std::string, Variable> Vars;
extern std::unordered_map<std::string, int> Functions;
extern std::unordered_map<std::string, int> BasicMathOperations;
extern std::unordered_map<int, std::string> BasicMathOperationsReverse;
extern std::vector<Element> Elements;

void InfixToElements(std::string, std::string&, int);
void InitializeMaps();