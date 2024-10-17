// Polynomial functions are implemened in Poly.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include "Poly.h"
using namespace std;

// Helper function to remove spaces - for function CreatePoly
string RemoveSpaces(const string& str) {
    string result;
    for (char c : str) {
        if (!isspace(c)) {
            result += c;
        }
    }
    return result;
}

PolyNode* CreatePoly( char* expr) {

    string input = RemoveSpaces(expr);
    istringstream stream(input);
    PolyNode* head = nullptr;
    PolyNode* tail = nullptr;

    double coef = 0;
    int exp = 0;
    bool isNegative = false;

    size_t i = 0;
    while (i < input.size()) {
        // Handle sign
        if (input[i] == '-' || input[i] == '+') {
            isNegative = (input[i] == '-');
            ++i;
        }

        // Parse coefficient
        if (isdigit(input[i]) || input[i] == '.') {
            size_t coefEnd;
            coef = stod(input.substr(i), &coefEnd);
            i += coefEnd;
        }
        else if (input[i] == 'x') {
            coef = 1; // Implied coefficient of 1 for x terms
        }

        if (isNegative) {
            coef = -coef;
        }

        // Parse exponent if present
        if (i < input.size() && input[i] == 'x') {
            ++i; // Skip 'x'
            if (i < input.size() && input[i] == '^') {
                ++i; // Skip '^'
                size_t expEnd;
                exp = stoi(input.substr(i), &expEnd);
                i += expEnd;
            }
            else {
                exp = 1; // Implied exponent of 1
            }
        }
        else {
            exp = 0; // Constant term
        }

        // Create a new node
        PolyNode* newNode = new PolyNode(coef, exp);

        // Append to linked list
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }

        // Reset flags
        coef = 0;
        exp = 0;
        isNegative = false;
    }

    return head;
}
void DeletePoly(PolyNode* poly) {
    while (poly != nullptr) {
        PolyNode* nextNode = poly->next;
        delete poly;
        poly = nextNode;
    }
}

// Function to add a node (coefficient, exponent) to polynomial
PolyNode* AddNode(PolyNode* head, double coefficient, int exponent) {
    PolyNode* newNode = new PolyNode(coefficient, exponent);
    
    if (!head) {
        return newNode;
    }

    
    PolyNode* current = head;
    PolyNode* prev = nullptr;

    
    while (current && current->exp > exponent) {
        prev = current;
        current = current->next;
    }

   
    if (current && current->exp == exponent) {
        
        
        current->coef += coefficient;

        
        if (current->coef == 0) {
            
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;  
            }
            delete current;
        }

        
        delete newNode;
    } else {
        
        if (prev) {
            prev->next = newNode;
        } else {
            head = newNode;  
        }
        newNode->next = current;
    }

    return head;
}


 // end-AddNode

PolyNode *Add(PolyNode *poly1, PolyNode *poly2){
PolyNode* add = nullptr;
PolyNode*tail= nullptr;
while(poly1 || poly2){
    double coefficient=0;
    int exponent=0;
    if (poly1 && ( poly1->exp > poly2->exp)) {
           
            coefficient = poly1->coef;
            exponent = poly1->exp;
            poly1 = poly1->next;  
        } else if (poly2 && ( poly2->exp > poly1->exp)) {
           
            coefficient = poly2->coef;
            exponent = poly2->exp;
            poly2 = poly2->next;  
        } else {
            
            coefficient = poly1->coef + poly2->coef;
            exponent = poly1->exp;
            poly1 = poly1->next;  
            poly2 = poly2->next;
        }
        if (coefficient != 0) {
           PolyNode* newNode = new PolyNode{coefficient, exponent};
            if (!add) {
                add = tail = newNode; 
            } else {
                tail->next = newNode;  
                tail = newNode;        
            }
        }
    }
    return add;
}/* 
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2) {

}
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2) {

}
double Evaluate(PolyNode* poly, double x) {

}
PolyNode* Derivative(PolyNode* poly) {

}
void Plot(PolyNode* poly, int x1, int x2) {

}
void Print(PolyNode* poly) {

}*/
