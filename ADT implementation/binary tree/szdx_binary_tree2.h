//
// binary_tree.h
// Linked implementation of binary tree.

#ifndef SZDX_BINARY_TREE_TEST 
#define SZDX_BINARY_TREE_TEST
#include <iostream>
#include <queue>

template <class Entry>
struct Binary_node {
  // data members: 
  Entry data;
  Binary_node<Entry>* left;
  Binary_node<Entry>* right;
  // constructors: 
  Binary_node();
  Binary_node(const Entry& x);
};

template <class Entry>
class Binary_tree {
public:
  Binary_tree();
  bool empty() const;
  void inorder(void(*visit)(Entry&));
  void preorder(void(*visit)(Entry&));
  void postorder(void(*visit)(Entry&));
  void levelorder(void(*visit)(Entry&));

  int size();
  Binary_node <Entry>* visit_root() const;
  void clear();
  int find_node(const int order);
  int height();
  int breadth();
  void insert(const Entry& x);
  Binary_tree(const Binary_tree<Entry>& original);
  Binary_tree<Entry>& operator = (const Binary_tree<Entry>& original);
  ~Binary_tree();
protected:
  int recursive_find_node_0(Binary_node <Entry>* sub_root);
  int recursive_find_node_1(Binary_node <Entry>* sub_root);
  int recursive_find_node_2(Binary_node <Entry>* sub_root);
  void recursive_inorder(Binary_node <Entry>* sub_root, void (*visit)(Entry&));
  void recursive_preorder(Binary_node <Entry>* sub_root, void (*visit)(Entry&));
  void recursive_postorder(Binary_node <Entry>* sub_root, void (*visit)(Entry&));
  void recursive_delete(Binary_node <Entry>* sub_root);
  int recursive_height(Binary_node <Entry>* sub_root);
  void recursive_copy(Binary_node <Entry>* new_root, Binary_node <Entry>* origin_root);
  Binary_node <Entry>* root;
  int count;
};

template <class Entry>
Binary_node <Entry>::Binary_node()
/* Post: An empty binary_node has been created. */
{
  data = NULL;
  left = NULL;
  right = NULL;
}

template <class Entry>
Binary_node <Entry>::Binary_node(const Entry& x)
/* Post: Override constructor. A binary_node with data set to x has been created. */
{
  data = x;
  left = NULL;
  right = NULL;
}

template <class Entry>
Binary_tree<Entry>::Binary_tree()
/* Post: An empty binary tree has been created. */
{
  root = NULL;
  count = 0;
}

template <class Entry>
bool Binary_tree<Entry>::empty() const
/* Post: A result of true is returned if the binary tree is empty.
			 Otherwise, false is returned. */
{
  return root == NULL;
}

template <class Entry>
void Binary_tree<Entry>::inorder(void(*visit)(Entry&))
/* Post: The tree has been been traversed in infix order sequence.
   Uses: The function recursive_inorder */
{
  recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node <Entry>* sub_root, void (*visit)(Entry&))
/* Pre: sub_root is either NULL or points to a subtree of the Binary_tree.
   Post: The subtree has been been traversed in inorder sequence.
   Uses: The function recursive_inorder recursively */
{
  if (sub_root != NULL) {
	recursive_inorder(sub_root->left, visit);
	visit(sub_root->data);
	recursive_inorder(sub_root->right, visit);
  }
}

template <class Entry>
void Binary_tree<Entry>::preorder(void(*visit)(Entry&))
/* Post: The tree has been been traversed in prefix order sequence.
   Uses: The function recursive_preorder */
{
  recursive_preorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node <Entry>* sub_root, void(*visit)(Entry&))
/* Pre: sub_root is either NULL or points to a subtree of the Binary_tree.
   Post: The subtree has been been traversed in preorder sequence.
   Uses: The function recursive_preorder recursively */
{
  if (sub_root != NULL) {
	visit(sub_root->data);
	recursive_preorder(sub_root->left, visit);
	recursive_preorder(sub_root->right, visit);
  }
}

template <class Entry>
void Binary_tree<Entry>::postorder(void(*visit)(Entry&))
/* Post: The tree has been been traversed in postfix order sequence.
   Uses: The function recursive_postorder */
{
  recursive_postorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node <Entry>* sub_root, void(*visit)(Entry&))
/* Pre: sub_root is either NULL or points to a subtree of the Binary_tree.
   Post: The subtree has been been traversed in postorder sequence.
   Uses: The function recursive_postorder recursively */
{
  if (sub_root != NULL) {
	recursive_postorder(sub_root->left, visit);
	recursive_postorder(sub_root->right, visit);
	visit(sub_root->data);
  }
}

template <class Entry>
void Binary_tree<Entry>::levelorder(void(*visit)(Entry&))
/* Post: The tree has been been traversed in level order sequence.*/
{
  std::queue <Binary_node <Entry>*> generation;
  Binary_node <Entry>* pointer = root;
  generation.push(pointer);
  int width = generation.size();
  while (width != 0) {
	for (int i = 0; i < width; i++) {
	  pointer = generation.front();
	  visit(pointer->data);
	  generation.pop();
	  if (pointer->left != NULL)
		generation.push(pointer->left);
	  if (pointer->right != NULL)
		generation.push(pointer->right);
	}
	width = generation.size();
  }
} 

template <class Entry>
int Binary_tree <Entry>::size()
/* Post: Return the the total number of all nodes that the tree currently contains.*/
{
  return count;
}

template <class Entry>
Binary_node <Entry>* Binary_tree<Entry>::visit_root() const
/* Post: An access to the root of the tree.*/
{
  return root;
}

template <class Entry>
void Binary_tree<Entry>::clear()
/* Post: Empty the tree.*/
{
  recursive_delete(root);
  root = NULL;
  count = 0;
}

template <class Entry>
void Binary_tree<Entry>::recursive_delete(Binary_node <Entry>* sub_root)
/* Pre: sub_root is either NULL or points to a subtree of the Binary_tree.
   Post: sub_root and its children have been deleted.
   Uses: The function recursive_delete recursively */
{
  if (sub_root != NULL) {
	recursive_delete(sub_root->left);
	recursive_delete(sub_root->right);
	delete sub_root;
  }
}

template <class Entry>
int Binary_tree<Entry>::height()
/* Post: Return the height of the tree.*/
{
  return recursive_height(root);
}

template <class Entry>
int Binary_tree<Entry>::find_node(const int order)
/* Post: Return the total number of nodes with the given order.*/
{
  int num = 0;
  switch (order)
  {
  case 0:
	num = recursive_find_node_0(root);
	break;
  case 1:
	num = recursive_find_node_1(root);
	break;
  case 2:
	num = recursive_find_node_2(root);
	break;
  default:
	num = 0;
	break;
  }
  return num;
}

template <class Entry>
int Binary_tree <Entry>::recursive_find_node_0(Binary_node <Entry>* sub_root)
/* Return the total number of the node with order 0 in the sub_root tree.*/
{
  if (sub_root != NULL) {
	if (sub_root->left != NULL || sub_root->right != NULL)
	  return recursive_find_node_0(sub_root->left) + recursive_find_node_0(sub_root->right);
	else
	  return 1;
  }
  else
	return 0;
}

template <class Entry>
int Binary_tree <Entry>::recursive_find_node_1(Binary_node <Entry>* sub_root)
/* Return the total number of the node with order 1 in the sub_root tree.*/
{
  if (sub_root != NULL) {
	if (sub_root->left != NULL && sub_root->right != NULL)
	  return recursive_find_node_1(sub_root->left) + recursive_find_node_1(sub_root->right);
	else if (sub_root->left != NULL)
	  return recursive_find_node_1(sub_root->left) + 1;
	else if (sub_root->right != NULL)
	  return recursive_find_node_1(sub_root->right) + 1;
	else
	  return 0;
  }
  else
	return 0;
}

template <class Entry>
int Binary_tree <Entry>::recursive_find_node_2(Binary_node <Entry>* sub_root)
/* Return the total number of the node with order 2 in the sub_root tree.*/
{
  if (sub_root != NULL) {
	if (sub_root->left != NULL && sub_root->right != NULL)
	  return recursive_find_node_2(sub_root->left) + recursive_find_node_2(sub_root->right) + 1;
	else if (sub_root->left != NULL || sub_root->right != NULL)
	  return recursive_find_node_2(sub_root->left) + recursive_find_node_2(sub_root->right);
	else
	  return 0;
  }
  else
	return 0;
}

template <class Entry>
int Binary_tree <Entry>::breadth()
/* Post: Return the breadth of the tree.*/
{
  std::queue <Binary_node <Entry>*> generation;
  Binary_node <Entry>* visit = root;
  int max_width, width;
  generation.push(visit);
  max_width = generation.size();
  width = generation.size();
  while (width != 0) {
	for (int i = 0; i < width; i++) {
	  visit = generation.front();
	  generation.pop();
	  if (visit->left != NULL)
		generation.push(visit->left);
	  if (visit->right != NULL)
		generation.push(visit->right);
	}
	width = generation.size();
	if (width > max_width)
	  max_width = width;
  }
  return max_width;
}

template <class Entry>
int Binary_tree <Entry>::recursive_height(Binary_node <Entry>* sub_root)
/* Post: Return the height of the subtree related to sub_root.*/
{
  if (sub_root != NULL) {
	if (recursive_height(sub_root->left) > recursive_height(sub_root->right))
	  return recursive_height(sub_root->left) + 1;
	else
	  return recursive_height(sub_root->right) + 1;
  }
  else
	return 0;
}

template <class Entry>
void Binary_tree <Entry>::insert(const Entry& x)
/* Post: Insert a new node into the position next to the latest branch or leave.*/
{
  Binary_node <Entry>* new_node = new Binary_node <Entry>(x);
  if (this->size() == 0) {
	root = new_node;
	count++;
	return;
  }
  Binary_node <Entry>* pointer = root;
  std::queue <Binary_node <Entry>*> generation;
  generation.push(pointer);
  int width = generation.size();
  while (width != 0) {
	for (int i = 0; i < width; i++) {
	  pointer = generation.front();
	  generation.pop();
	  if (pointer->left == NULL) {
		pointer->left = new_node;
		count++;
		return;
	  }
	  if (pointer->right == NULL) {
		pointer->right = new_node;
		count++;
		return;
	  }
	  if (pointer->left != NULL)
		generation.push(pointer->left);
	  if (pointer->right != NULL)
		generation.push(pointer->right);
	}
	width = generation.size();
  }
}

template <class Entry>
Binary_tree <Entry>::Binary_tree(const Binary_tree<Entry>& original)
/* Post: Override the copy operator.*/
{
  root = NULL;
  count = 0;
  recursive_copy(root, original.visit_root());
}

template <class Entry>
void Binary_tree <Entry>::recursive_copy(Binary_node <Entry>* new_root, Binary_node <Entry>* origin_root)
/* Post: Recursively copy a sub_root to a new_root.*/
{
  if (origin_root != NULL) {
	new_root = new Binary_node <Entry>(origin_root->data);
	count++;
	recursive_copy(new_root->left, origin_root->left);
	recursive_copy(new_root->right, origin_root->right);
  }
}

template <class Entry>
Binary_tree<Entry>& Binary_tree <Entry>::operator = (const Binary_tree<Entry>& original)
/* Post: Override the assignment operator.*/
{
  clear();
  recursive_copy(root, original.visit_root());
}

template <class Entry>
Binary_tree <Entry>::~Binary_tree()
/* Post: Override destructor.*/
{
  recursive_delete(root);
}


#endif