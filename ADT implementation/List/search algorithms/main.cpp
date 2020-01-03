#include "test.h"

int main() {
  int size, entry, position, compare = 0;
  long repeat;
  char type;
  Key to_find;
  clock_count run_time;
  Ordered_list <Record> a_list;
  cout << "Welcome to Searching Algorithms testing!" << endl;
  cout << "Please enter the number of entries of the list: ";
  cin >> size;
  cout << "Please enter entries with an increasing order:" << endl;
  for (int i = 0; i < size; i++) {
	cin >> entry;
	a_list.insert(i, entry);
  }
  cout << "Please enter the entry you want to search for and times of repetition for the same searching:";
  cin >> to_find >> repeat;
  cout << "Now select the algorithms you want to test:" << endl;
  cout << "A. sequential search" << endl;
  cout << "B. recursive binary search regardless equality" << endl;
  cout << "C. binary search regardless equality" << endl;
  cout << "D. recursive binary search recognizing equality" << endl;
  cout << "E. binary search recognizing equality" << endl;
  cout << "(enter the corresponding letter of each algorithm.)" << endl;
  cin >> type;
  switch (type) {
  case 'A':
	run_time = abs_runtime(sequential_search, a_list, to_find, position, repeat);
	sequential_search(a_list, to_find, position, compare);
	break;
  case 'B':
	run_time = abs_runtime(run_recursive_binary_1, a_list, to_find, position, repeat);
	run_recursive_binary_1(a_list, to_find, position, compare);
	break;
  case 'C':
	run_time = abs_runtime(binary_search_1, a_list, to_find, position, repeat);
	binary_search_1(a_list, to_find, position, compare);
	break;
  case 'D':
	run_time = abs_runtime(run_recursive_binary_2, a_list, to_find, position, repeat);
	run_recursive_binary_2(a_list, to_find, position, compare);
	break;
  case 'E':
	run_time = abs_runtime(binary_search_2, a_list, to_find, position, repeat);
	binary_search_2(a_list, to_find, position, compare);
	break;
  }
  if (position != -1) {
	cout << "Search succeed. " << endl;
	cout << "Target position: " << position << endl;
  }
  else
	cout << "Search failed. " << endl;
  cout << "Absolute search time: " << run_time << endl;
  cout << "Comparing times: " << compare << endl;
}
