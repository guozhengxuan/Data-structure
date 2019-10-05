#include "utility.h"

bool is_operator(char ch) 
/* judge whether the given charactor is an operator or not.*/
{
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#';
}

int priority(char op)
/* clarify each operator's priority so that operations can be manipulated in order.*/
{
  int i;
  switch (op) {
    case '+':
		case '-': i = 1; break;
		case '*':
		case '/': i = 2; break;
		case '(': i = 3; break;
		case ')': i = 0; break;
		case '#': i = -1; break;
  }
	return i;
}

double operation(char op, double a, double b)
/* translate operators into real arithmetic operations.*/
{
  if(op == '+') return a + b;
  else if(op == '-') return a - b;
  else if(op == '*') return a * b;
  else if(op == '/') return a / b;
}

vector <string> seperate(string &original)
/*seperate operators and operands from each other and put them into storage.*/
{
  int operator_counter = 0;
  vector <string> storage;
  for (int i = 0; i < original.length(); i++) {
	if (is_operator(original[i])) {
	  int number_lenth = i - operator_counter;
	  if (number_lenth > 0) {
		string number = original.substr(operator_counter, number_lenth);
		storage.push_back(number);
	  }
	  string item(1, original[i]);
	  storage.push_back(item);
	  operator_counter = i + 1;
	}
  }
  return storage;
}

double calculate(vector <string> &storage)
/*according to operation priority to calculate seperated formula sequence stored in the vector.*/
{
  stack <double> operands;
  stack <char> operators;
  for (int i = 0; i < storage.size(); i++) {
	string item = storage[i];
	if (is_operator(item[0])) {
      operators.push(item[0]);
	  if (operands.size() < 2 && operators.size() < 2) continue;
	  while(true) {
		if (operators.size() == 1) break;
		char top = operators.top();
		operators.pop();
		char inside = operators.top();
		if (inside == '(') {
		  operators.push(top);
		  break;
		}
		if (priority(inside) >= priority(top)) {
		  double num1 = operands.top();
		  operands.pop();
		  double num2 = operands.top();
		  operands.pop();
		  operands.push(operation(inside, num2, num1));
		  operators.pop();
		  operators.push(top);
		  if (top == '#' && operands.size() == 1) return operands.top();
		}
		else {
		  operators.push(top);
		  break;
		}
		if (operators.top() == ')') {
		  operators.pop();
		  if (operators.top() == '(') {
			operators.pop();
			break;
		  }
		  else operators.push(')');
		}
	  }
	}
	else operands.push(stod(item));
  }
}