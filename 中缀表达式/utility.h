#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

bool is_operator(char ch);
int priority(char op);
double operation(char op, double a, double b);
vector <string> seperate(string &original);
double calculate(vector <string> &storage);
