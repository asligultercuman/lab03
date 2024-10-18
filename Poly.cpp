#include <stdio.h>
#include "Poly.h"
#include <sstream>
using namespace std;

//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
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
PolyNode *CreatePoly(char *expr){		
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
} //end-CreatePoly

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {
	while (poly != nullptr) {
        PolyNode* nextNode = poly->next;
        delete poly;
        poly = nextNode;
    }
} // end-DeletePoly
	
//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
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
} // end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
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
} //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2) {

    PolyNode* head1 = poly1;
    PolyNode* head2 = poly2;
    PolyNode* result = nullptr;   
    PolyNode* tail = nullptr;         

    while (head1 != nullptr || head2 != nullptr) {
        PolyNode* newNode = new PolyNode(); // Yeni düğüm oluştur

        if (head1 != nullptr && head2 != nullptr && head1->exp == head2->exp) { // Üsler eşitse çıkarma işlemi yap
            newNode->exp = head1->exp;
            newNode->coef = head1->coef - head2->coef;
            head1 = head1->next;
            head2 = head2->next;
        }
        else if (head1 != nullptr && (head2 == nullptr || head1->exp > head2->exp)) { // head1'deki üs büyükse
            newNode->exp = head1->exp;
            newNode->coef = head1->coef;
            head1 = head1->next;
        }
        else { // head2'deki üs büyükse
            newNode->exp = head2->exp;
            newNode->coef = -head2->coef;
            head2 = head2->next;
        }

        // Eğer yeni düğümün katsayısı sıfır değilse sonucu listeye ekle
        if (newNode->coef != 0) {
            if (result == nullptr) {
                result = newNode;
                tail = result;
            }
            else {
                tail->next = newNode;
                tail = tail->next;
            }
        }
        else {
            delete newNode; // Katsayı sıfırsa bu düğümü iptal et
        }
    }
    return result;
}//end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode *Multiply(PolyNode *poly1, PolyNode *poly2){
	// Fill this in
	return NULL;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode *poly, double x){
	// Fill this in
	return 0;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode* Derivative(PolyNode* poly) {
    PolyNode* head1 = poly;
    PolyNode* result = nullptr;    
    PolyNode* tail = nullptr;       

    while (head1 != nullptr) {
        if (head1->exp != 0) {  
            PolyNode* newNode = new PolyNode();
            newNode->exp = head1->exp - 1;
            newNode->coef = head1->coef * head1->exp; 

            if (result == nullptr) {
                result = newNode;
                tail = result;
            }
            else {
                tail->next = newNode;
                tail = tail->next;
            }
        }
        head1 = head1->next;
    }

    return result;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode *poly, int x1, int x2){
	// Fill this in	
} //end-Plot