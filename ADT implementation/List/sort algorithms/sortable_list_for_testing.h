#include <vector>
#include <time.h>
#include "contiguous_list.h"
#include <fstream>
using namespace std;

typedef double clock_count;

template <class Record>
class Sortable_list : public List <Record> {
public:
  void (Sortable_list <Record>::*sort)(int&, int&);
  void set_sort(char choice);
  void insertion_sort(int& compare, int& move);
  void selection_sort(int& compare, int& move);
  void shell_sort(int& compare, int& move);
  void merge_sort(int& compare, int& move);
  void merge_sort2();
  void quick_sort(int& compare, int& move);
  void heap_sort(int& compare, int& move);
  clock_count abs_runtime(const long repeat, int& compare, int& move);
private:
  int max_key(int low, int high, int& compare);
  void swap(int low, int high);
  void sort_interval(int start, int increment, int& compare, int& move);
  void recursive_merge_sort(vector <Record>& a, int& compare);
  void recursive_merge_sort2(int low, int high);
  void merge(int low, int high);
  vector <Record> divide(vector <Record>& a);
  vector <Record> merge(vector <Record> left_half, vector <Record> right_half, int& compare);
  void recursive_quick_sort(int low, int high, int& compare, int& move);
  int partition(int low, int high, int& compare, int& move);
  void insert_heap(const Record& current, int low, int high, int& compare, int& move);
  void build_heap(int& compare, int& move);
};

template <class Record>
void Sortable_list <Record>::insertion_sort(int& compare, int& move)
/* Post: The entries of the Sortable_list have been rearranged so that the
		 keys in all entries are sorted into nondecreasing order.
   Uses: Methods for the class record; the contiguous List implementation.*/
{
  int first_unsorted;
  int position;
  Record current;
  compare = 0;
  move = 0;
  for (first_unsorted = 1; first_unsorted < this->count; first_unsorted++)
	if (this->entry[first_unsorted] < this->entry[first_unsorted - 1]) {
	  compare++;
	  position = first_unsorted;
	  current = this->entry[first_unsorted];
	  do {
		move++;
		this->entry[position] = this->entry[position - 1];
		position--;
	  } while (position > 0 && this->entry[position - 1] > current);
	  this->entry[position] = current;
	}
}

template <class Record>
void Sortable_list <Record>::selection_sort(int& compare, int& move)
/* Post: The entries The entries of the Sortable_list have been rearranged so that the
		 keys in all entries are sorted into nondecreasing order.
   Uses: max_key, swap.*/
{
  compare = 0;
  move = 0;
  for (int position = this->count - 1; position > 0; position--) {
	int max = max_key(0, position, compare);
	swap(max, position);
	move++;
  }
}

template <class Record>
int Sortable_list <Record>::max_key(int low, int high, int& compare)
/* Pre: low and high are valid positions in the Sorted_list and low <= high.
   Post: The position of the entry between low and high with the largest key
		 is returned.
   Uses: The class Record. The contiguous List implementation.*/
{
  int largest, current;
  largest = low;
  for (current = low + 1; current <= high; current++)
	if (this->entry[largest] < this->entry[current]) {
	  compare++;
	  largest = current;
	}
  return largest;
}

template <class Record>
void Sortable_list <Record>::swap(int low, int high)
/* Pre: low and high are valid positions in the Sortable_list.
   Post: The entry at position low is swapped with the entry at
		 position high.
   Uses: The contiguous List implementation.*/
{
  Record temp;
  temp = this->entry[low];
  this->entry[low] = this->entry[high];
  this->entry[high] = temp;
}

template <class Record>
void Sortable_list <Record>::shell_sort(int& compare, int& move)
/* Post: The entries of the Sortable_list have been rearranged so that the
		 keys in all entries are sorted into nondecreasing order.
   Uses: sort_interval*/
{
  compare = 0;
  move = 0;
  int increment, start;
  increment = this->count;
  do {
	increment = increment / 3 + 1;
	for (start = 0; start < increment; start++)
	  sort_interval(start, increment, compare, move);
  } while (increment > 1);
}

template <class Record>
void Sortable_list <Record>::sort_interval(int start, int increment, int& compare, int& move)
/* Post: auxiliary function that modified insertion_sort.*/
{
  int first_unsorted;
  int position;
  Record current;
  for (first_unsorted = start + increment; first_unsorted < this->count; first_unsorted += increment)
	if (this->entry[first_unsorted] < this->entry[first_unsorted - increment]) {
	  compare++;
	  position = first_unsorted;
	  current = this->entry[first_unsorted];
	  do {
		this->entry[position] = this->entry[position - increment];
		position -= increment;
		move++;
	  } while (position > start && this->entry[position - increment] > current);
	  this->entry[position] = current;
	}
}

template <class Record>
void Sortable_list <Record>::merge_sort(int& compare, int& move)
{
  vector <Record> vec_entry;
  compare = 0;
  move = this->size();
  for (int i = 0; i < this->size(); i++)
	vec_entry.push_back(this->entry[i]);
  recursive_merge_sort(vec_entry, compare);
  for (int i = 0; i < this->size(); i++)
	this->entry[i] = vec_entry[i];
}

template <class Record>
void Sortable_list <Record>::recursive_merge_sort(vector <Record>& a, int& compare)
{
  if (a.size() >= 2) {
	vector <Record> right_half = divide(a);
	recursive_merge_sort(a, compare);
	recursive_merge_sort(right_half, compare);
	a = merge(a, right_half, compare);
  }
}

template <class Record>
vector <Record> Sortable_list <Record>::divide(vector <Record>& a)
{
  size_t l_size = a.size() / 2;
  size_t r_size = a.size() - a.size() / 2;
  vector <Record> left_half, right_half;
  for (size_t i = 0; i < l_size; i++)
	left_half.push_back(a[i]);
  for (size_t i = l_size; i < a.size(); i++)
	right_half.push_back(a[i]);
  a = left_half;
  return right_half;
}

template <class Record>
vector <Record> Sortable_list <Record>::merge(vector <Record> left_half, vector <Record> right_half, int& compare)
{

  vector <Record> combination;
  size_t l_index = 0, r_index = 0, comb_index = 0;
  while (l_index <= left_half.size() - 1 && r_index <= right_half.size() - 1) {
	if (left_half[l_index] < right_half[r_index]) {
	  combination.push_back(left_half[l_index]);
	  l_index++;
	  comb_index++;
	}
	else {
	  combination.push_back(right_half[r_index]);
	  r_index++;
	  comb_index++;
	}
    compare++;
  }
  while (l_index <= left_half.size() - 1) {
	combination.push_back(left_half[l_index]);
	l_index++;
	comb_index++;
  }
  while (r_index <= right_half.size() - 1) {
	combination.push_back(right_half[r_index]);
	r_index++;
	comb_index++;
  }
  return combination;
}

template <class Record>
void Sortable_list <Record>::merge_sort2()
{
  recursive_merge_sort2(0, this->size() - 1);
}


template <class Record>
void Sortable_list <Record>::recursive_merge_sort2(int low, int high)
{
  int mid = (low + high) / 2;
  recursive_merge_sort2(low, mid);
  recursive_merge_sort2(mid + 1, high);
  merge(low, high);
}

template <class Record>
void Sortable_list <Record>::merge(int low, int high)
{

}

template <class Record>
void Sortable_list <Record>::quick_sort(int& compare, int& move)
{
  compare = 0;
  move = 0;
  recursive_quick_sort(0, this->count - 1, compare, move);
}

template <class Record>
void Sortable_list <Record>::recursive_quick_sort(int low, int high, int& compare, int& move)
{
  int pivot_index;
  if (low < high) {
	pivot_index = partition(low, high, compare, move);
	recursive_quick_sort(low, pivot_index - 1, compare, move);
	recursive_quick_sort(pivot_index + 1, high, compare, move);
  }
}

template <class Record>
int Sortable_list <Record>::partition(int low, int high, int& compare, int& move)
{
  Record pivot;
  int i, last_small;
  swap(low, (low + high) / 2); move++;
  pivot = this->entry[low];
  last_small = low;
  for (i = low + 1; i <= high; i++) {
	if (this->entry[i] < pivot) {
	  last_small++;
	  swap(last_small, i); move++;
	}
	compare++;
  }
  swap(low, last_small); move++;
  return last_small;
}

template <class Record>
void Sortable_list <Record>::heap_sort(int& compare, int& move)
{
  Record current;
  int last_unsorted;
  compare = 0;
  move = 0;
  build_heap(compare, move);
  for (last_unsorted = this->count - 1; last_unsorted > 0; last_unsorted--) {
	current = this->entry[last_unsorted];
	this->entry[last_unsorted] = this->entry[0];
	insert_heap(current, 0, last_unsorted - 1, compare, move);
  }
}

template <class Record>
void Sortable_list <Record>::insert_heap(const Record& current, int low, int high, int& compare, int& move)
{
  int large = 2 * low + 1;
  while (large <= high) {
	if (large < high && this->entry[large] < this->entry[large + 1])
	  large++;
	compare += 2;
	if (current >= this->entry[large])
	  break;
	else {
	  this->entry[low] = this->entry[large];
	  move++;
	  low = large;
	  large = 2 * low + 1;
	}
  }
  this->entry[low] = current;
}

template <class Record>
void Sortable_list <Record>::build_heap(int& compare, int& move)
{
  int low;
  for (low = this->count / 2 - 1; low >= 0; low--) {
	Record current = this->entry[low];
	insert_heap(current, low, this->count - 1, compare, move);
  }
}

template <class Record>
void Sortable_list <Record>::set_sort(char choice)
{
  switch (choice) {
  case 'A':
    this->sort = &Sortable_list <Record>::insertion_sort;
    break;
  case 'B':
    this->sort = &Sortable_list <Record>::selection_sort;
    break;
  case 'C':
    this->sort = &Sortable_list <Record>::shell_sort;
    break;
  case 'D':
    this->sort = &Sortable_list <Record>::merge_sort;
    break;
  case 'E':
    this->sort = &Sortable_list <Record>::quick_sort;
    break;
  case 'F':
    this->sort = &Sortable_list <Record>::heap_sort;
    break;
  }
}

template <class Record>
clock_count Sortable_list <Record>::abs_runtime(const long repeat, int& compare, int& move)
{
  clock_t start, finish;
  const int size = this->size();
  Record* order_copy = new Record[size];
  Record* sort_copy = new Record[size];

  for (int i = 0; i < this->size(); i++)
	order_copy[i] = this->entry[i];
  (this->*sort)(compare, move);
  for (int i = 0; i < this->size(); i++)
    sort_copy[i] = this->entry[i];
  for (int i = 0; i < this->size(); i++)
    this->entry[i] = order_copy[i];

  // start to calculate duration 1.
  start = clock();
  for (int i = 0; i < repeat; i++) {
	(this->*sort)(compare, move);
	for (int i = 0; i < this->size(); i++)
	  this->entry[i] = order_copy[i];
  }
  finish = clock();
  clock_count duration_1 = ((double)(finish - start) / CLOCKS_PER_SEC);

  // start to calculate duration 2.
  start = clock();
  for (int i = 0; i < repeat; i++)
	for (int i = 0; i < this->size(); i++)
	  this->entry[i] = order_copy[i];
  finish = clock();
  clock_count duration_2 = ((double)(finish - start) / CLOCKS_PER_SEC);
  clock_count duration = duration_1 - duration_2;

  for (int i = 0; i < this->size(); i++)
    this->entry[i] = sort_copy[i];
  delete[] order_copy;
  delete[] sort_copy;
  return duration;
}

void write_int_file()
{
  fstream int_file;
  int_file.open("20.txt", ios::in | ios::out | ios::trunc);
  unsigned seed;
  int input_to_file;
  seed = time(0);
  srand(seed);
  for (int i = 0; i < 20; i++) {
	input_to_file = rand() % 20 + 1;
	int_file << input_to_file << endl;
  }
  int_file.close();
  int_file.open("200.txt", ios::in | ios::out | ios::trunc);
  for (int i = 0; i < 200; i++) {
	input_to_file = rand() % 200 + 1;
    int_file << input_to_file << endl;
  }
  int_file.close();
  int_file.open("2000.txt", ios::in | ios::out | ios::trunc);
  for (int i = 0; i < 2000; i++) {
	input_to_file = rand() % 2000 + 1;
	int_file << input_to_file << endl;
  }
  int_file.close();
}