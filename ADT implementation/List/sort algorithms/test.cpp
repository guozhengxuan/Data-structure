#include "sortable_list_for_testing.h"

int main() {
  int size, entry, compare, move;
  long repeat;
  char choice;
  clock_count run_time;
  Sortable_list <int> a_list;
  cout << "Welcome to Sorting Algorithms testing!" << endl;
  cout << "Please choose the mode of testing:" << endl;
  cout << "A: Test with the help of the prepared files contains 20, 200, or 2000 integers." << endl;
  cout << "B: Directly enter the integers from keyboard." << endl;
  cout << "(enter the corresponding letter of each option.)" << endl;
  cin >> choice;
  if (choice == 'A') {
	// test with the help of the prepared files.
	cout << "Select the length of the list:" << endl;
	cout << "A: 20" << endl;
	cout << "B: 200" << endl;
	cout << "C: 2000" << endl;
	cout << "(enter the corresponding letter of each option.)" << endl;
	cin >> choice;
    cout << "integers stored in the file you chose are shown below in original order:" << endl;
	ifstream file_option;
	switch (choice)
	{
	case 'A':
      int x;
      file_option.open("20.txt", ios::in);
      while (file_option >> x) {
        cout << x << " ";
        a_list.insert(a_list.size(), x);
      }
      file_option.close();
	  break;
	case 'B':
      int y;
	  file_option.open("200.txt", ios::in);
      while (file_option >> y) {
        cout << y << " ";
        a_list.insert(a_list.size(), y);
      }
	  file_option.close();
	  break;
	case 'C':
      int z;
      file_option.open("2000.txt", ios::in);
      while (file_option >> z) {
        cout << z << " ";
        a_list.insert(a_list.size(), z);
      }
      file_option.close();
	  break;
	}
    cout << endl;
  }
  else if (choice == 'B') {
	// directly input option.
    cout << "Please enter the number of entries of the list: ";
    cin >> size;
	cout << "Please enter entries of the list:" << endl;
    for (int i = 0; i < size; i++) {
      cin >> entry;
      a_list.insert(i, entry);
    }
  }
  cout << "Please enter times of repetition for the same sorting:" << endl;
  cin >> repeat;
  cout << "Now select the sorting algorithm you want to test:" << endl;
  cout << "A: Insertion sort." << endl;
  cout << "B: Selection sort." << endl;
  cout << "C: Shell sort." << endl;
  cout << "D: Merge sort." << endl;
  cout << "E: Quick sort." << endl;
  cout << "F: Heap sort." << endl;
  cout << "(enter the corresponding letter of each algorithm.)" << endl;
  cin >> choice;
  a_list.set_sort(choice);
  run_time = a_list.abs_runtime(repeat, compare, move);
  cout << "Sorting results are shown below:" << endl;
  for (int i = 0; i < a_list.size(); i++) {
    a_list.retrieve(i, entry);
    cout << entry << " ";
  }
  cout << endl;
  cout << "Absolute running time of the algorithm function you have chose: ";
  cout << run_time << "s" << endl;
  cout << "Comparision times: " << compare << endl;
  cout << "Moving times of entries: " << move << endl;
}
