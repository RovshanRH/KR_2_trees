#include <iostream>

using namespace std;

struct Node {
	int key;
	Node* left, * right, * parent;
	char color;

	Node(int val) : key(val), left(nullptr), right(nullptr), parent(nullptr), color('b') {}
};

class BRTree {
public:
	Node* head;
	BRTree() : head(nullptr) {};
	
	~BRTree() {
		destroy(head);
	}
	
	void destroy(Node* node) {
		if (!node) return;
		destroy(node->left);
		destroy(node->right);
		delete node;
	}

	Node* insert(Node*& path, int val) {
		Node* newnode = new Node(val);

		if (!path) {
			path = newnode;
			if (!head) head = newnode;
			return path;
		} 
		Node* cur = head;
		if (val < cur->key) {
			
			if (!cur->left){
				cur->left = insert(cur->left, val);
			}
			else {
				cur = cur->left;
			}
			cur->parent = path;
			

		}
		else if (val > cur->key) {
			
			if (!cur->right){
				cur->right = insert(cur->right, val);
			}
			else {
				cur = cur->right;
			}
			cur->parent = path;
			
		}
		else {
			return path;
		}
	}

	void printTree(Node* node) {
		if (node != nullptr) {
			printTree(node->left);
			cout << "( " << node->key << " , " << node->color << ") ";
			printTree(node->right);
		}
	}

};

int main() {
	BRTree tree;
	Node* h = tree.head;

	h = tree.insert(h, 1);
	h = tree.insert(h, 2);
	h = tree.insert(h, 10);
	tree.printTree(tree.head);

}