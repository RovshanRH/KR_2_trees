#include <iostream>

using namespace std;

enum Color {RED, BLACK};

struct Node {
	int key;
	Node* left, * right, * parent;
	Color color;

	Node(int val) : key(val), left(nullptr), right(nullptr), parent(nullptr), color(BLACK) {}
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
		if (!path) {
			path = new Node(val);
			return path;
		} 
		if (val < path->key) {
			path->left = insert(path->left, val);
			path->left->parent = path;

		}
		else if (val > path->key) {
			path->right = insert(path->right, val);
			path->right->parent = path;
			
		}
		return path;
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
	
	tree.insert(tree.head, 1);
	tree.insert(tree.head, 2);
	tree.insert(tree.head, 10);
	tree.printTree(tree.head);


}