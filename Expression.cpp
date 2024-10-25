#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string &s) {
	// Fill this in
	string result;

	return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
    stack<int> stack;
    string num;

    for (char ch : s) {
        if (isdigit(ch)) {
            num += ch; 
        } else if (ch == ' ') {
            if (!num.empty()) {
                stack.push(stoi(num));
                num.clear(); 
            }
        } else {
            if (!num.empty()) {
                stack.push(stoi(num));
                num.clear();
            }

            int operand2 = stack.top();
            stack.pop();
            int operand1 = stack.top();
            stack.pop();

            if (ch == '+') {
                stack.push(operand1 + operand2);
            } else if (ch == '-') {
                stack.push(operand1 - operand2);
            } else if (ch == '*') {
                stack.push(operand1 * operand2);
            } else if (ch == '/') {
                stack.push(operand1 / operand2);
            }
        }
    }
    return stack.top();
}
