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

    // Traverse the list to find the correct position
    PolyNode* current = head;
    PolyNode* prev = nullptr;

    // Traverse the list until you find where to insert the new node
    while (current && current->exp > exponent) {
        prev = current;
        current = current->next;
    }

    // If the exponents match, add the coefficients
    if (current && current->exp == exponent) {
        // Debug output for tracking coefficient addition
        
        
        current->coef += coefficient;

        // If the result is zero, remove the node
        if (current->coef == 0) {
            // Remove the node since coefficient is now zero
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;  // If it's the head node, move the head
            }
            delete current;
        }

        // Since we no longer need `newNode`, free the memory
        delete newNode;
    } else {
        // Otherwise, insert the new node in its correct position
        if (prev) {
            prev->next = newNode;
        } else {
            head = newNode;  // If inserting at the head
        }
        newNode->next = current;
    }

    return head;
}


 // end-AddNode
/*
PolyNode* Add(PolyNode* poly1, PolyNode* poly2) {

}
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
