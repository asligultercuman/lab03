#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

string Infix2Postfix(string &s) {
	stack<char> op;
	string result, toNoneSpace;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ') { toNoneSpace.push_back(s[i]); }
	}
	s = toNoneSpace;
	char tmp = '0';
	for (int i = 0; i < s.length(); i++)
	{
		char c = s[i];
		if ( c >= '0' && c <= '9')
		{
			if (tmp < '0' || tmp > '9')
			{
				result.push_back(' ');
				result.push_back(c);
			}
			else result.push_back(c);
		}
		else if (c == '(') { op.push('('); }
		else if (c == ')') 
		{
			while (op.top() != '(')
			{
				result.push_back(' ');
				result.push_back(op.top());
				op.pop();
			}
			op.pop();
		}
		else 
		{
			int a = 0, b = 0;
			while (!op.empty()) {
				if (c == '/' || c == '*') { a = 2; }
				else if (c == '+' || c == '-') { a = 1; }
				if (op.top() == '/' || op.top() == '*') { b = 2; }
				else if (op.top() == '+' || op.top() == '-') { b = 1; }
				if (a <= b && op.top() != '(')
				{
					result.push_back(' ');
					result.push_back(op.top());
					op.pop();
				}
				else break;
			}
			op.push(c);
		}
		tmp = c;
	}
	while (!op.empty()) 
	{
		result.push_back(' ');
		result.push_back(op.top());
		op.pop();
	}

	return result;
} // end-Infix2Postfix----------------------------------------------------------------
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
