//
// doubly_linked_list.h
// linked list implementation using nodes as entry storage with both head and tail pointer.

#pragma once
#include "utility.h"

template <class Node_entry>
struct Node
{
  // data members
  Node_entry entry;
  Node <Node_entry>* next;
  Node <Node_entry>* back;
  // constructors
  Node();
  Node(
	Node_entry item, 
	Node <Node_entry>* link_back = NULL, 
	Node <Node_entry>* link_next = NULL);
};


template <class List_entry>
class List {
public:
  // specifications for List methods.
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
  // The following methods replace compiler-generated defaults.
  ~List();
  List(const List <List_entry>& original);
  void operator = (const List <List_entry>& original);
private:
  // Data members for the doubly linked list implementation now follow.
  int count;
  mutable int current_position;
  mutable Node <List_entry>* current;
  // The following auxiliary function is used to locate list positions.
  void set_position(int position) const;
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//Implementations of constructors of nodes and methods of template class List.
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

template <class Node_entry>
Node <Node_entry>::Node()
/* Post: Initialize the node with both head and tail pointer 
         pointing to NULL.*/
{
  back = next = NULL;
}

template <class Node_entry>
Node <Node_entry>::Node(
  Node_entry item,
  Node <Node_entry>* link_back,
  Node <Node_entry>* link_next)
  /* Post: The Node is initialized with its pointers pointing
		   to link_back and link_next respectively and entry
		   assigned to item.*/
{
  entry = item;
  back = link_back;
  next = link_next;
}

template <class List_entry>
List <List_entry>::List()
/* Post: The list has been created and is initialized to be empty.*/
{
  count = 0;
  current = NULL;
  current_position = 0;
}

template <class List_entry>
int List <List_entry>::size() const
/* Post: Returns current number of the entries in the List.*/
{
  return count;
}

template <class List_entry>
bool List <List_entry>::full() const
/* Post: If there is no spare memory able to be allocated
		 to creating addtional node to the List: Returns
		 true.
		 Else: Returns false.*/
{
  Node <List_entry>* attempt = new Node <List_entry>();
  if (attempt == NULL) return true;
  else
  {
	delete attempt;
	return false;
  }
}

template <class List_entry>
bool List <List_entry>::empty() const
/* Post: If there are no Nodes in the List: Returns
		 true.
		 Else: Returns false.*/
{
  return count == 0;
}

template <class List_entry>
void List <List_entry>::clear()
/* Post: All entries have been removed; the list is empty.*/
{
  if (count == 0) return;
  set_position(0);
  while (current != NULL) {
	Node <List_entry>* iterate = current;
	current = current->next;
	delete iterate;
  }
  count = 0;
}

template <class List_entry>
void List <List_entry>::traverse(void (*visit)(List_entry&))
/* Post: The action is specified by function (*visit) has
		 been performed on every entry of the List, beginning
		 at position 0 and doing each in turn.*/
{
  if (count == 0) return;
  set_position(0);
  while (current != NULL) {
	(*visit)(current->entry);
	current = current->next;
  }
}

template <class List_entry>
Error_code List <List_entry>::retrieve(int position, List_entry& x) const
/* Post: If 0 <= position < n, where n is the number of entries in the
		 List, the method succeeds: The entry at position is copied to
		 x; all other entries remain unchanged.
		 Else: The method fails with a diagnostic error code.*/
{
  if (position < 0 || position >= count)
	return Error_code::range_error;
  set_position(position);
  x = current->entry;
  return Error_code::success;
}

template <class List_entry>
Error_code List <List_entry>::replace(int position, const List_entry& x)
/* Post: If 0 <= position < n, where n is the number of entries in the
		 List, the method succeeds: The entry at position is replaced by
		 x, all other entries remain unchanged.
		 Else: The method fails with a diagnostic error code.*/
{
  if (position < 0 || position >= count)
	return Error_code::range_error;
  set_position(position);
  current->entry = x;
  return Error_code::success;
}

template <class List_entry>
Error_code List <List_entry>::remove(int position, List_entry& x)
/* Post: If 0 <= position < n, where n is the number of entries
		 in the List, the method succeeds: The entry at position
		 is removed from the List, and all later entries have their
		 position numbers decreased by 1. The parameter x records
		 a copy of the entry formerly at position.
		 Else: The method fails with a diagnostic error code.*/
{
  if (count == 0)
	return Error_code::fail;
  if (position < 0 || position >= count)
	return Error_code::range_error;
  set_position(position);
  Node <List_entry>* useless = current;
  x = current->entry;
  current = current->next;
  if (position == 0) {
    if (count != 1)
	  current->back = NULL;
  }
  else {
	(useless->back)->next = current;
	current->back = useless->back;
  }
  delete useless;
  count--;
  return Error_code::success;
}       

template <class List_entry>
Error_code List <List_entry>::insert(int position, const List_entry& x)
/* Post: If the List is not full and 0 <= position <= n, where n is the 
         number of entries in the List, the method succeeds. Any entry
		 formerly at position and all later entries have their postion 
		 numbers increased by 1, and x is inserted at position in the 
		 List.
		 Else: The method fails with a diagnostic error code*/
{
  Node <List_entry>* new_node, * following, * preceding;
  if (position < 0 || position > count)
	return Error_code::range_error;
  if (position == 0) {
	if (count == 0) following = NULL;
	else {
	  set_position(0);
	  following = current;
	}
	preceding = NULL;
  }
  else {
	set_position(position - 1);
	preceding = current;
	following = preceding->next;
  }
  new_node = new Node <List_entry>(x, preceding, following);
  if (new_node == NULL) return overflow;
  if (preceding != NULL) preceding->next = new_node;
  if (following != NULL) following->back = new_node;
  current = new_node;
  current_position = position;
  count++;
  return Error_code::success;
}

template <class List_entry>
void List <List_entry>::set_position(int position) const
/* Pre: Parameter "position" should be a valid position in List;
		0 <= position < count.
   Post: The current Node pointer references the Node in position.*/
{
  if (current_position < position)
	for (; current_position != position; current_position++)
	  current = current->next;
  if (current_position > position)
	for (; current_position != position; current_position--)
	  current = current->back;
}

template <class List_entry>
List <List_entry>::~List()
/* Post: The List is cleared.*/
{
  set_position(0);
  for (int i = 0; i < count; i++) {
	Node <List_entry>* iterate = current;
	current = current->next;
	delete iterate;
  }
}

template <class List_entry>
List <List_entry>::List(const List <List_entry>& original)
/* Post: The List is initialized as a copy of original.*/
{
  int step = 0;
  original.set_position(0);
  Node <List_entry>* new_node, * original_node = original.current;
  current_position = 0;
  if (original_node == NULL)
	current = NULL;
  else {
	current = new_node = new Node <List_entry>(original_node->entry);
	step++;
	while (original_node->next != NULL) {
	  original_node = original_node->next;
	  new_node = new Node <List_entry>(original_node->entry);
	  current->next = new_node;
	  new_node->back = current;
	  current = current->next;
	  current_position++;
	  step++;
	}
  }
  count = step;
}

template <class List_entry>
void List <List_entry>::operator = (const List <List_entry>& original)
/* Post: Override the assignment operator.*/
{
  clear();
  int step = 0;
  original.set_position(0);
  Node <List_entry>* new_node, * original_node = original.current;
  if (original_node != NULL) {
	current = new_node = new Node <List_entry>(original_node->entry);
	step++;
	while (original_node->next != NULL) {
	  original_node = original_node->next;
	  new_node = new Node <List_entry>(original_node->entry);
	  current->next = new_node;
	  new_node->back = current;
	  current = current->next;
	  current_position++;
	  step++;
	}
  }
  count = step;
}
