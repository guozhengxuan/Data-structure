//
// simply_cyclic_linked_list.h
// One direction linked list implementation using nodes as entry storage.

#pragma once
#include "utility.h"

template <class Node_entry>
struct Node
{
  // data members
  Node_entry entry;
  Node <Node_entry> *next;
  // constructors
  Node();
  Node(Node_entry item, Node <Node_entry> *link = NULL);
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
  void operator=(const List <List_entry>& original);
private:
  // Data members for the linked list implementation now follow.
  int count;
  Node <List_entry>* head;
  Node <List_entry>* tail;
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
/* Post: The Node is initialized with its pointer pointing
         to NULL and entry unassigned.*/
{
  next = NULL;
}

template <class Node_entry>
Node <Node_entry>::Node(Node_entry item, Node <Node_entry> *link)
/* Post: The Node is initialized with its pointer pointing
         to link and entry assigned to item.*/
{
  entry = item;
  next = link;
}

template <class List_entry>
List <List_entry>::List()
/* Post: The list has been created and is initialized to be empty.*/
{
  count = 0;
  tail = head = current = NULL;
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
  Node <List_entry> *attempt = new Node <List_entry>();
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
  Node <List_entry>* iterate;
  for (int i  = 0; i < count; i++){
    iterate = current;
    current = current->next;
	delete iterate;
  }
  current = head = tail = NULL;
  count = 0;
  current_position = 0;
}

template <class List_entry>
void List <List_entry>::traverse(void (*visit)(List_entry&))
/* Post: The action is specified by function (*visit) has
         been performed on every entry of the List, beginning
		 at position 0 and doing each in turn.*/
{
  Node <List_entry> iterate = head;
  for (int i = 0; i < count; i++) {
	(*visit)(iterate->entry);
	iterate = iterate->next;
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
  if (position = 0)
	set_position(count - 1);
  else
	set_position(position - 1);
  Node <List_entry> pointer = current->next;
  x = pointer->entry;
  current->next = pointer->next;
  delete pointer;
  if (count == 1) head = current = NULL;
  count--;
  current_position = position;
  return Error_code::success;
}

template <class List_entry>
Error_code List <List_entry>::insert(int position, const List_entry& x)
/* Post: If the List is not full and 0 <= position <= n, where n is the 
         number of entries in the List, the method succeeds. Any entry
		 formerly at position and all later entries have their postion 
		 numbers increased by 1, and x is inserted at position in the 
		 List.
		 Else: The method fails with a diagnostic error code.*/
{
  if (position < 0 || position > count)
    return Error_code::range_error;
  Node <List_entry> *previous = NULL, *following, *new_node;
  if (position > 0)
  {
    set_position(position - 1);
	previous = current;
	following = previous->next;
  }
  else following = head;
  new_node = new Node <List_entry>(x, following);
  if (new_node == NULL) 
    return Error_code::overflow;
  if (position == 0) 
	head = new_node;
  else
	previous->next = new_node;
  // If a node was inserted to the end of the list, \
	 we shall set the tail node.
  if (position == count) {
	tail = new_node;
	tail->next = head;
  }
  current = new_node;
  count++;
  if (count != 1) current_position++;
  return Error_code::success;
}

template <class List_entry>
void List <List_entry>::set_position(int position) const
/* Pre: parameter "position" should be a valid position in List; 
        0 <= position < count.
   Post: The current Node pointer references the Node in position.*/
{
  if (position < current_position) {
	current_position = 0;
	current = head;
  }
  for (; current_position != position; current_position++)
	current = current->next;
}

template <class List_entry>
List <List_entry>::~List()
/* Post: The List is cleared.*/
{
  for (int i = 0; i < count; i++) {
	Node <List_entry>* iterate = head;
	head = head->next;
	delete iterate;
  }
}

template <class List_entry>
List <List_entry>::List(const List <List_entry>& original)
/* Post: The List is initialized as a copy of original.*/
{
  int step = 0;
  Node <List_entry>* original_node = original.head;
  if (original_node == NULL) {
	tail = head = NULL;
	count = 0;
	current_position = 0;
  }
  else {
	head = current = new Node <List_entry>(original_node->entry);
	step++;
	while (original_node->next != original.head) {
	  original_node = original_node->next;
	  current->next = new Node <List_entry>(original_node->entry);
	  step++;
	  current = current->next;
	}
	current->next = head;
	tail = current;
	count = step;
	current_position = step - 1;
  }
}

template <class List_entry>
void List <List_entry>::operator=(const List <List_entry>& original)
/* Post: Override the assignment operator.*/
{
  clear();
  int step = 0;
  Node <List_entry>* new_node, * new_head, * new_tail, * original_node = original.head;
  if (original_node == NULL) 
	new_tail = new_head = NULL;
  else {
	new_head = new_node = new Node <List_entry>(original_node->entry);
	step++;
	while (original_node->next != original.head) {
      original_node = original_node->next;
	  new_node->next = new Node <List_entry>(original_node->entry);
	  step++;
	  new_node = new_node->next;
	}
	new_tail = new_node;
  }
  current = head = new_head;
  tail = new_tail;
  count = step;
}
