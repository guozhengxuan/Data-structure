//
// search_in_list.h
// search algorithms for contiguous ordered lists.

#include "ordered_list.h"

typedef int Record;
typedef int Key;

Error_code sequential_search(const Ordered_list <Record>& the_list, const Key& target,
  int& position, int& compare)
  /* Post: If an entry in the the_list has key equal to target, then return 
		   success and the output parameter position locates such an entry 
		   within the list.
		   Otherwise return not_present and position becomes invalid(-1).*/
{
  compare = 0;
  for (position = 0; position < the_list.size(); position++) {
	Record data;
	the_list.retrieve(position, data);
	compare++;
	if (data == target) return success;
  }
  position = -1;
  return not_present;
}

//REGARDLESS EQULITY

Error_code recursive_binary_1(const Ordered_list <Record>& the_list, const Key& target,
  int bottom, int top, int& position, int& compare)
  /* Pre: The indices bottom to top define the range in the list to search for
			the target.
	 Post: If an Record in the of the location has key equal to target, then return 
		   success and the output parameter position locates such an entry 
		   within the list. Otherwise return not_present and position becomes 
		   invalid(-1).
	 Uses: recursive_binary_1 and methods of the classes List and Record.*/
{
  Record data;
  if (bottom < top) {
	compare++;
	int mid = (bottom + top) / 2;
	the_list.retrieve(mid, data);
	if (data < target)
	  return recursive_binary_1(the_list, target, mid + 1, top, position, compare);
	else
	  return recursive_binary_1(the_list, target, bottom, mid, position, compare);
  }
  else if (bottom > top) {
	compare++;
	position = -1;
	return not_present;
  }
  else {
	position = top;
	the_list.retrieve(top, data);
	if (data == target) return success;
	else {
	  position = -1;
	  return not_present;
	}
  }
}

Error_code run_recursive_binary_1(const Ordered_list <Record>& the_list, const Key& target,
  int& position, int& compare)
{
  return recursive_binary_1(the_list, target, 0, the_list.size() - 1, position, compare);
}

Error_code binary_search_1(const Ordered_list <Record>& the_list, const Key& target,
  int& position, int& compare)
  /* Post: If an entry in the the_list has key equal to target, then return
		   success and the output parameter position locates such an entry
		   within the list.
		   Otherwise return not_present and position becomes invalid(-1).
	 Uses: Methods for classes List and Record.*/
{
  Record data;
  int bottom = 0, top = the_list.size() - 1;
  while (bottom < top) {
	compare++;
	int mid = (bottom + top) / 2;
	the_list.retrieve(mid, data);
	if (data < target)
	  bottom = mid + 1;
	else
	  top = mid;
  }
  compare++;
  if (top < bottom) {
	position = -1;
	return not_present;
  }
  else {
	position = top;
	the_list.retrieve(top, data);
	if (data == target) return success;
	else {
	  position = -1;
	  return not_present;
	}
  }
}

// RECOGNIZING EQUALITY

Error_code recursive_binary_2(const Ordered_list <Record>& the_list, const Key& target,
  int bottom, int top, int& position, int& compare)
  /* Pre: The indices bottom to top define the range in the list to search for
		  the target.
	 Post: If an Record in the of the location has key equal to target, then return
		   success and the output parameter position locates such an entry
		   within the list. Otherwise return not_present and position becomes
		   invalid(-1).
	 Uses: recursive_binary_2 and methods of the classes List and Record.*/
{
  Record data;
  if (bottom <= top) {
	int mid = (bottom + top) / 2;
	the_list.retrieve(mid, data);
	if (data == target) {
	  compare++;
	  position = mid;
	  return success;
	}
	else {
	  compare++;
	  if (data < target)
		return recursive_binary_2(the_list, target, mid + 1, top, position, compare);
	  else
		return recursive_binary_2(the_list, target, bottom, mid - 1, position, compare);
	}
  }
  else {
	position = -1;
	return not_present;
  }
}

Error_code run_recursive_binary_2(const Ordered_list <Record>& the_list, const Key& target,
  int& position, int& compare)
{
  return recursive_binary_2(the_list, target, 0, the_list.size() - 1, position, compare);
}

Error_code binary_search_2(const Ordered_list <Record>& the_list, const Key& target,
  int& position, int& compare)
  /* Pre: The indices bottom to top define the range in the list to search for
		  the target.
	 Post: If an Record in the of the location has key equal to target, then return
		   success and the output parameter position locates such an entry
		   within the list. Otherwise return not_present and position becomes
		   invalid(-1).
	 Uses: recursive_binary_2 and methods of the classes List and Record.*/
{
  Record data;
  int bottom = 0, top = the_list.size() - 1;
  while (bottom <= top) {
	position = (bottom + top) / 2;
	the_list.retrieve(position, data);
	if (data == target) {
	  compare++;
	  return success;
	}
	compare++;
	if (data < target) bottom = position + 1;
	else top = position - 1;
  }
  position = -1;
  return not_present;
}