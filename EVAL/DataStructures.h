#pragma once
struct Variable {
	uint8_t type; // 1-bool / 2-int / 3-double
	double value = 0;
};

struct Element {
	uint8_t operation = 0;
	Variable var;
};
