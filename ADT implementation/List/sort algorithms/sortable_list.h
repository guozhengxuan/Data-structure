//
// sortable_list.h
// sortable list class derived from either sequential or linked list with several sorting algorithms.

#include "contiguous_list.h"
#include <vector>
using namespace std;

template <class Record>
class Sortable_list : public List <Record> {
public:
  void insertion_sort();
  void selection_sort();
  void shell_sort();
  void merge_sort();
  void quick_sort();
  void heap_sort();
private:
  int max_key(int low, int high);
  void swap(int low, int high);
  void sort_interval(int start, int increment);
  void recursive_merge_sort(vector <Record>& a);
  vector <Record> divide(vector <Record>& a);
  vector <Record> merge(vector <Record> left_half, vector <Record> right_half);
  void recursive_quick_sort(int low, int high);
  int partition(int low, int high);
  void insert_heap(const Record& current, int low, int high);
  void build_heap();
};

template <class Record>
void Sortable_list <Record>::insertion_sort()
/* Post: The entries of the Sortable_list have been rearranged so that the
         keys in all entries are sorted into nondecreasing order.
   Uses: Methods for the class record; the contiguous List implementation.*/
{
  int first_unsorted;
  int position;
  Record current;
  for (first_unsorted = 1; first_unsorted < this->count; first_unsorted++)
	if (this->entry[first_unsorted] < this->entry[first_unsorted - 1]) {
	  position = first_unsorted;
	  current = this->entry[first_unsorted];
	  do {
        this->entry[position] = this->entry[position - 1];
		position--;
	  } while (position > 0 && this->entry[position - 1] > current);
      this->entry[position] = current;
	}
}

template <class Record>
void Sortable_list <Record>::selection_sort()
/* Post: The entries The entries of the Sortable_list have been rearranged so that the
         keys in all entries are sorted into nondecreasing order.
   Uses: max_key, swap.*/
{
  for (int position = this->count - 1; position > 0; position--) {
	int max = max_key(0, position);
	swap(max, position);
  }
}

template <class Record>
int Sortable_list <Record>::max_key(int low, int high)
/* Pre: low and high are valid positions in the Sorted_list and low <= high.
   Post: The position of the entry between low and high with the largest key
         is returned.
   Uses: The class Record. The contiguous List implementation.*/
{
  int largest, current;
  largest = low;
  for (current = low + 1; current <= high; current++)
	if (this->entry[largest] < this->entry[current])
	  largest = current;
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
void Sortable_list <Record>::shell_sort()
/* Post: The entries of the Sortable_list have been rearranged so that the
         keys in all entries are sorted into nondecreasing order.
   Uses: sort_interval*/
{
  int increment, start;
  increment = this->count;
  do {
	increment = increment / 3 + 1;
	for (start = 0; start < increment; start++)
	  sort_interval(start, increment);
  } while (increment > 1);
}

template <class Record>
void Sortable_list <Record>::sort_interval(int start, int increment)
/* Post: auxiliary function that modified insertion_sort.*/
{
  int first_unsorted;
  int position;
  Record current;
  for (first_unsorted = start + increment; first_unsorted < this->count; first_unsorted += increment)
	if (this->entry[first_unsorted] < this->entry[first_unsorted - increment]) {
	  position = first_unsorted;
	  current = this->entry[first_unsorted];
	  do {
        this->entry[position] = this->entry[position - increment];
		position -= increment;
	  } while (position > start&& this->entry[position - increment] > current);
      this->entry[position] = current;
	}
}

template <class Record>
void Sortable_list <Record>::merge_sort()
{
  vector <Record> vec_entry;
  for (int i = 0; i < this->size(); i++)
	vec_entry.push_back(this->entry[i]);
  recursive_merge_sort(vec_entry);
  for (int i = 0; i < this->size(); i++)
	this->entry[i] = vec_entry[i];
}

template <class Record>
void Sortable_list <Record>::recursive_merge_sort(vector <Record>& a)
{
  if (a.size() >= 2) {
	vector <Record> right_half = divide(a);
	recursive_merge_sort(a);
	recursive_merge_sort(right_half);
	a = merge(a, right_half);
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
vector <Record> Sortable_list <Record>::merge(vector <Record> left_half, vector <Record> right_half)
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
void Sortable_list <Record>::quick_sort()
{
  recursive_quick_sort(0, this->count - 1);
}

template <class Record>
void Sortable_list <Record>::recursive_quick_sort(int low, int high)
{
  int pivot_index;
  if (low < high) {
    pivot_index = partition(low, high);
    recursive_quick_sort(low, pivot_index - 1);
    recursive_quick_sort(pivot_index + 1, high);
  }
}

template <class Record>
int Sortable_list <Record>::partition(int low, int high)
{
  Record pivot;
  int i, last_small;
  swap(low, (low + high) / 2);
  pivot = this->entry[low];
  last_small = low;
  for (i = low + 1; i <= high; i++)
    if (this->entry[i] < pivot) {
      last_small++;
      swap(last_small, i);
    }
  swap(low, last_small);
  return last_small;
}

template <class Record>
void Sortable_list <Record>::heap_sort()
{
  Record current;
  int last_unsorted;
  build_heap();
  for (last_unsorted = this->count - 1; last_unsorted > 0; last_unsorted--) {
    current = this->entry[last_unsorted];
    this->entry[last_unsorted] = this->entry[0];
    insert_heap(current, 0, last_unsorted - 1);
  }
}

template <class Record>
void Sortable_list <Record>::insert_heap(const Record& current, int low, int high)
{
  int large = 2 * low + 1;
  while (large <= high) {
    if (large < high && this->entry[large] < this->entry[large + 1])
      large++;
    if (current >= this->entry[large])
      break;
    else {
      this->entry[low] = this->entry[large];
      low = large;
      large = 2 * low + 1;
    }
  }
  this->entry[low] = current;
}

template <class Record>
void Sortable_list <Record>::build_heap()
{
  int low;
  for (low = this->count / 2 - 1; low >= 0; low--) {
    Record current = this->entry[low];
    insert_heap(current, low, this->count - 1);
  }
}