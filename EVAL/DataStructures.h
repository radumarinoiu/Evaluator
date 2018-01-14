#pragma once
struct Variable {
	bool isFloatingPoint = false;
	bool isBoolean = false;
	double value = 0;
};

struct Element {
	uint8_t operation = 0;
	Variable var;
};
