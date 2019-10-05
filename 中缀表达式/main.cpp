#include "utility.h"

int main()
{
  string formula;
  cout << "please enter arithmetic formula terminated with #." << endl;
  cout << "choose parentheses if needed." << endl;
  cout << "enter 0 to terminate." << endl;
  cin >> formula;
  while (formula != "0") {
	double result = calculate(seperate(formula));
	result;
	cout << "result: " << result << endl;
	cin >> formula;
  }
}