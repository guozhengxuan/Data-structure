//
// simply_linked_list.h
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
  // The following auxiliary function is used to locate list positions.
  Node <List_entry>* set_position(int position) const;
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
  head = NULL;
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
  for (int i  = 0; i < count; i++){
    Node <List_entry> *iterate = head;
    head = head->next;
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
  Node <List_entry>* pointer = set_position(position);
  x = pointer->entry;
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
  Node <List_entry>* pointer = set_position(position);
  pointer->entry = x;
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
  Node <List_entry> *previous, *present;
  if (position == 0)
  {
    present = head;
	head = head->next;
  }
  else
  {
    previous = set_position(position - 1);
	present = previous->next;
	previous->next = present->next;
  }
  x = present->entry;
  delete present;
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
		 Else: The method fails with a diagnostic error code.*/
{
  if (position < 0 || position > count)
    return Error_code::range_error;
  Node <List_entry> *previous = NULL, *following, *new_node;
  if (position > 0)
  {
    previous = set_position(position - 1);
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
  count++;
  return Error_code::success;
}

template <class List_entry>
Node <List_entry> *List <List_entry>::set_position(int position) const
/* Pre: parameter "position" should be a valid position in List; 
        0 <= position < count.
   Post: Returns a pointer to the Node in position.*/
{
  Node <List_entry> *iterate = head;
  for (int i = 0; i < position; i++)
	iterate = iterate->next;
  return iterate;
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
  Node <List_entry>* new_node, * original_node = original.head;
  if (original_node == NULL) head = NULL;
  else {
	head = new_node = new Node <List_entry>(original_node->entry);
	step++;
	while (original_node->next != NULL) {
	  original_node = original_node->next;
	  new_node->next = new Node <List_entry>(original_node->entry);
	  step++;
	  new_node = new_node->next;
	}
  }
  count = step;
}

template <class List_entry>
void List <List_entry>::operator=(const List <List_entry>& original)
/* Post: Override the assignment operator.*/
{
  int step = 0;
  Node <List_entry>* new_node, * new_head, * original_node = original.head;
  if (original_node == NULL) new_head = NULL;
  else {
	new_head = new_node = new Node <List_entry>(original_node->entry);
	step++;
	while (original_node->next != NULL) {
      original_node = original_node->next;
	  new_node->next = new Node <List_entry>(original_node->entry);
	  step++;
	  new_node = new_node->next;
	}
  }
  clear();
  head = new_head;
  count = step;
}