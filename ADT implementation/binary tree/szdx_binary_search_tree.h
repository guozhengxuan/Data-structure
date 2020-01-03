#include "szdx_binary_tree2.h"
#include "utility.h"

template <class Record> 
class Search_tree : public Binary_tree <Record> {
public:
  Error_code insert(const Record& new_data); 
  Error_code remove(const Record& old_data); 
  Error_code tree_search(Record& target) const; 
protected:
  Binary_node <Record>* search_for_node(
	Binary_node<Record>* sub_root, const Record& target) const;
  Error_code search_and_insert(
	Binary_node<Record>*& sub_root, const Record& new_data);
  Error_code remove_root(Binary_node<Record>*& sub_root);
  Error_code search_and_destroy(Binary_node<Record>*& sub_root, const Record& target);
};

template <class Record>
Error_code Search_tree<Record>::tree_search(Record& target) const 
/* Post:   If there is an entry in the tree whose key matches that in target, 
         the parameter target is replaced by the corresponding record from 
         the tree and a code of success is returned. 
           Otherwise a code of not_present is returned.
   Uses: function search_for_node */ 
{
  Error_code result = success; 
  Binary_node<Record>* found = search_for_node(this->root, target);
  if (found == NULL) 
    result = not_present;
  else 
    target = found->data; 
  return result;
}

template <class Record> 
Binary_node <Record>* Search_tree<Record> ::search_for_node(
  Binary_node<Record>* sub_root, const Record& target) const
{
  while (sub_root != NULL && sub_root->data != target) 
    if (sub_root->data < target) 
      sub_root = sub_root->right; 
    else 
      sub_root = sub_root->left;
  return sub_root;
}

template <class Record>
Error_code Search_tree<Record>::insert(const Record& new_data) 
{
  this->count++;
  return search_and_insert(this->root, new_data);
}

template <class Record> 
Error_code Search_tree <Record>::search_and_insert(
  Binary_node<Record>*& sub_root, const Record& new_data)
{
  if (sub_root == NULL) {
    sub_root = new Binary_node <Record>(new_data);
    return success;
  }
  else if (new_data < sub_root->data) 
    return search_and_insert(sub_root->left, new_data);
  else if (new_data > sub_root->data) 
    return search_and_insert(sub_root->right, new_data); 
  else return duplicate_error;
}

template <class Record> 
Error_code Search_tree<Record> ::remove_root(Binary_node<Record>*& sub_root)
/* Pre: sub_root is either NULL or points to a subtree of the Search_tree.
   Post:   If sub_root is NULL, a code of not_present is returned.
           Otherwise, the root of the subtree is removed in such a way that
         the properties of a binary search tree are preserved. The parameter
         sub_root is reset as the root of the modified subtree, and success
         is returned. */
{
  if (sub_root == NULL) 
    return not_present;
  Binary_node<Record>* to_delete = sub_root;
  if (sub_root->right == NULL) 
    sub_root = sub_root->left; 
  else if (sub_root->left == NULL) 
    sub_root = sub_root->right; 
  else {
    to_delete = sub_root->left;
    Binary_node <Record>* parent = sub_root;
    while (to_delete->right != NULL) {
      parent = to_delete;
      to_delete = to_delete->right;
    }
    sub_root->data = to_delete->data;
    if (parent == sub_root)
      sub_root->left = to_delete->left;
    else
      parent->right = to_delete->right;
  }
  delete to_delete; 
  return success;
}

template <class Record>
Error_code Search_tree<Record> ::remove(const Record& target) 
/* Post:   If a Record with a key matching that of target belongs to the Search_tree 
         a code of success is returned and the corresponding node is removed from the 
         tree. 
           Otherwise, a code of not_present is returned.
   Uses: Function search_and_destroy */ 
{
  this->count--;
  return search_and_destroy(this->root, target);
}

template <class Record>
Error_code Search_tree<Record> ::search_and_destroy(Binary_node<Record>*& sub_root, const Record& target)
/* Pre: sub_root is either NULL or points to a subtree of the Search_tree. 
   Post:   If the keyof target is not in the subtree, a code of not_present is returned. 
           Otherwise, a code of success is returned and the subtree node containing 
         target has been removed in such a way that the properties of a binary search 
         tree have been preserved.
   Uses: Functions search_and_destroy recursively and remove_root */ 
{
  if (sub_root == NULL || sub_root->data == target)
    return remove_root(sub_root);
  else if (target < sub_root->data)
    return search_and_destroy(sub_root->left, target);
  else 
    return search_and_destroy(sub_root->right, target);
}