#ifndef _POLYNODE_H_
#define _POLYNODE_H_

// Each polynomial node consists of a coefficient and an exponent
struct PolyNode {
	double coef;             // Coefficient
	int exp;                 // Exponent
	struct PolyNode* next;   // Next polynomial node
	PolyNode(double coef=0.0, int exp=0) : coef(coef), exp(exp), next(nullptr) {}//constructor
}; //end-PolyNode

#endif