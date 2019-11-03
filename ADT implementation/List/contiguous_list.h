//
// contiguous_list.h
// contiguous list implementation using array as entry storage.

#include "utility.h"

const int max_list = 100;

template <class List_entry>
class List {
public:
  // methods of the list ADT
  List();
  int size() const;
  bool full() const;
  bool empty() const;
  void clear();
  void traverse(void (*visit)(List_entry&));
  Error_code retrieve(int position, List_entry& x) const;
  Error_code replace(int position, const List_entry& x);
  Error_code remove(int position, List_entry& x);
  Error_code insert(int position, const List_entry& x);
 protected:
  // data members for a contiguous list implementation
  int count;
  List_entry entry[max_list];
};

template <class List_entry>
List <List_entry>::List()
{
  count = 0;
}

template <class List_entry>
int List <List_entry>::size() const
{
  return count;
}

template <class List_entry>
bool List <List_entry>::full() const
{
  return count == max_list;
}

template <class List_entry>
bool List <List_entry>::empty() const
{
  return count == 0;
}

template <class List_entry>
void List <List_entry>::clear()
{
  count = 0;
}

template <class List_entry>
void List <List_entry>::traverse(void (*visit)(List_entry&))
{
  for (int i = 0; i < count; i++) {
	(*visit)(entry[i]);
  }
}

template <class List_entry>
Error_code List <List_entry>::retrieve(int position, List_entry& x) const
{
  if (full())
	return Error_code::overflow;
  if (position < 0 || position > count)
	return Error_code::range_error;
  x = entry[position];
  return Error_code::success;
}

template <class List_entry>
Error_code List <List_entry>::replace(int position, const List_entry& x)
{
  if (full())
	return Error_code::overflow;
  if (position < 0 || position > count)
	return Error_code::range_error;
  entry[position] = x;
  return Error_code::success;
}

template <class List_entry>
Error_code List <List_entry>::remove(int position, List_entry& x)
{
  if (full())
	return Error_code::overflow;
  if (position < 0 || position > count)
	return Error_code::range_error;
  x = entry[position];
  for (int i = position; i < count; i++)
	entry[i] = entry[i + 1];
  count--;
  return Error_code::success;
}

template <class List_entry>
Error_code List <List_entry>::insert(int position, const List_entry& x)
{
  if (full())
	return Error_code::overflow;
  if (position < 0 || position > count)
	return Error_code::range_error;
  for (int i = count; i > position; i--)
	entry[i] = entry[i - 1];
  entry[position] = x;
  count++;
  return Error_code::success;
}
