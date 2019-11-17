using namespace std;
#include <iostream>

enum Error_code
{
  success, fail, range_error, underflow, overflow, fatal, not_present, \
  duplicate_error, entry_inserted, entry_found, internal_error
};

/*bool say_yes()
{
  int c;
  bool initial_response = true;
  do {                           // Loop until an approriate input is received.
	if (initial_response)
      cout << "(y, n)?" << flush;
	else
	  cout << "Response with either y or n: " << flush;
	do {
	  c = cin.get();
	} while (c == '\n' || c == ' ' || c == '\t');
	initial_response = false;
  } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
  return (c == 'y' || c == 'Y');
}*/