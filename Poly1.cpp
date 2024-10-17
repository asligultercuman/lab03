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

PolyNode* CreatePoly(const char* expr) {

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

void DeletePoly (PolyNode* poly) {

}
PolyNode* AddNode(PolyNode* head, double coef, int exp) {
PolyNode* AddNode(PolyNode* head, double coefficient, int exponent){
    // Yeni düğüm oluştur
    PolyNode* newNode = new PolyNode;
    newNode->coef = coefficient;
    newNode->exp = exponent;
    newNode->next = nullptr;

    if (!head) {
        return newNode;
    }

    // Polinoma uygun yere ekle (sıralı ekleme)
    PolyNode* current = head;
    PolyNode* prev = nullptr;

    while (current && current->exp > exponent) {
        prev = current;
        current = current->next;
    }

   
    if (current && current->exp == exponent) {
        current->coef += coefficient;
        delete newNode;  
    }
    else {
        if (prev) {
            prev->next = newNode;
        }
        else {
            head = newNode;  
        }
        newNode->next = current;
    }

    return head;
} // end-AddNode
}/*
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
