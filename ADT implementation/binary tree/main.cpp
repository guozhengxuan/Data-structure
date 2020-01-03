#include "szdx_binary_tree2.h"
#include "szdx_binary_search_tree.h"
#include <iostream>
using namespace std;

void test_read(int& x)
{
  cout << x << " ";
}

int main() {
  char option;
  cout << "Welcome to binary tree functions testing!" << endl;
  cout << "Now select from the given two choices:" << endl;
  cout << "A: Test with binary tree." << endl;
  cout << "B: Test with binary search tree." << endl;
  cin >> option;
  if (option == 'A') {
    int x;
    char fuc;
    Binary_tree <int> tree1;
    cout << "Firstly you should construct a binary tree." << endl;
    cout << "Enter a sequence of integers with a terminating signal 0." << endl;
    cin >> x;
    while (x != 0) {
      tree1.insert(x);
      cin >> x;
    }
    cout << "Which function below do you want to test?" << endl;
    cout << "A: Inoder traversal." << endl;
    cout << "B: Preoder traversal." << endl;
    cout << "C: Postorder traversal." << endl;
    cout << "D: level order traversal." << endl;
    cout << "E clear." << endl;
    cout << "F: size." << endl;
    cout << "G: height." << endl;
    cout << "H: breadth." << endl;
    cout << "I: empty?" << endl; 
    cout << "J: insert." << endl;
	cout << "K: Number of nodes of a specific order." << endl;
	cout << "Enter '#' to exit function testing." << endl;
	cout << "Your choice: ";
	cin >> fuc;
	while (fuc != '#') {
	  cout << "Result: ";
	  switch (fuc)
	  {
	  case 'A':
		tree1.inorder(test_read);
		cout << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'B':
		tree1.preorder(test_read);
		cout << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'C':
		tree1.postorder(test_read);
		cout << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'D':
		tree1.levelorder(test_read);
		cout << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'E':
		tree1.clear();
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'F':
		cout << tree1.size() << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'G':
		cout << tree1.height() << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'H':
		cout << tree1.breadth() << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'I':
	  {
		bool y = tree1.empty();
		if (y) cout << "YES." << endl;
		else cout << "NO." << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  }
	  case 'J':
		cout << "Enter the integer you want to insert into the tree: ";
		int insert;
		cin >> insert;
		tree1.insert(insert);
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'K':
	  {
		int order, num;
		cout << "Enter the order (order = 0, 1 or 2): ";
		cin >> order;
		num = tree1.find_node(order);
		cout << "The number of all "<< order <<"-order nodes in the tree :" << num << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  }
	  }
	}
  }
  else if (option == 'B') {
	int x;
	char fuc;
	Search_tree <int> tree1;
	cout << "Firstly you should construct a binary tree." << endl;
	cout << "Enter a sequence of integers with a terminating signal 0." << endl;
	cin >> x;
	while (x != 0) {
	  tree1.insert(x);
	  cin >> x;
	}
	cout << "Which function below do you want to test?" << endl;
	cout << "A: Inoder traversal." << endl;
	cout << "B: Preoder traversal." << endl;
	cout << "C: Postorder traversal." << endl;
	cout << "D: level order traversal." << endl;
	cout << "E clear." << endl;
	cout << "F: size." << endl;
	cout << "G: height." << endl;
	cout << "H: breadth." << endl;
	cout << "I: empty?" << endl;
	cout << "J: insert." << endl;
	cout << "K: remove." << endl;
	cout << "L: tree_search." << endl;
	cout << "M: Number of nodes of a specific order." << endl;
	cout << "Enter '#' to exit function testing." << endl;
	cout << "Your choice: ";
	cin >> fuc;
	while (fuc != '#') {
	  cout << "Result: ";
	  switch (fuc)
	  {
	  case 'A':
		tree1.inorder(test_read);
		cout << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'B':
		tree1.preorder(test_read);
		cout << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'C':
		tree1.postorder(test_read);
		cout << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'D':
		tree1.levelorder(test_read);
		cout << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'E':
		tree1.clear();
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'F':
		cout << tree1.size() << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'G':
		cout << tree1.height() << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'H':
		cout << tree1.breadth() << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'I':
	  {
		bool y = tree1.empty();
		if (y) cout << "YES." << endl;
		else cout << "NO." << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  }
	  case 'J':
		cout << " Enter the integer you want to insert into the tree: ";
		int insert;
		cin >> insert;
		tree1.insert(insert);
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'K':
		cout << " Enter the integer you want to remove from the tree: ";
		int del;
		cin >> del;
		tree1.remove(del);
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'L':
		cout << "Enter the integer you want to search in the tree: ";
		int target;
		Error_code status;
		cin >> target;
		status = tree1.tree_search(target);
		if (status == success) cout << "Searching success: " << target << endl;
		else cout << "Searching failed." << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  case 'M':
	  {
		int order, num;
		cout << "Enter the order (order = 0, 1 or 2): ";
		cin >> order;
		num = tree1.find_node(order);
		cout << "The number of all " << order << "-order nodes in the tree :" << num << endl;
		cout << "Your choice: ";
		cin >> fuc;
		break;
	  default:
		fuc = '#';
		break;
	  }
	  }
	}
  }
}
