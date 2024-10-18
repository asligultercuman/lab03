#pragma once

struct PolyNode {
	
	double coef; // Coefficient
	int exp; // Exponent
	struct PolyNode* next; // Next polynomial node

	PolyNode(double coef, int exp) : coef(coef), exp(exp), next(nullptr) {}//constructor

}; //end-PolyNode