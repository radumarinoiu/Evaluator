#pragma once
#include <string>
#include <unordered_map>

#include "DataStructures.h"

extern std::unordered_map<std::string, Variable> Vars;
extern std::unordered_map<std::string, int> Functions;
extern std::unordered_map<std::string, int> BasicMathOperations;
extern std::unordered_map<int, std::string> BasicMathOperationsReverse;

bool Parse(std::string, std::string&);
void InfixToElements(std::string, std::string&, int, std::vector<Element>&);
Variable EvaluateElements(std::vector<Element>, uint8_t&);
Variable ApplyBasicOperation(Variable, Variable, uint8_t);
void InitializeMaps();