#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
	Node* parent;
	int height;

	Node(int val) : data(val), left(nullptr), right(nullptr), 
		parent(nullptr), height(1) {}
};

class BalancedTree {
private:
	Node* LeftRotate(Node* x) {
		Node* y = x->right;
		Node* T2 = y->left;

		y->left = x;
		x->right = T2;

		if (T2) T2->parent = x;
		y->parent = x->parent;
		x->parent = y;

		x->height = 1 + max(height(x->left), height(x->right));
		y->height = 1 + max(height(y->left), height(y->right));

		return y;
	}
	Node* RightRotate(Node* x) {
		Node* y = x->left;
		Node* T2 = y->right;

		y->right = x;
		x->left = T2;

		if (T2) T2->parent = x;
		y->parent = x->parent;
		x->parent = y;
		
		x->height = 1 + max(height(x->left), height(x->right));
		y->height = 1 + max(height(y->left), height(y->right));

		return y;
	}
	Node* LeftRightRotate(Node* x) {
		x->left = LeftRotate(x->left);
		return RightRotate(x);
	}
	Node* RightLeftRotate(Node* x) {
		x->right = RightRotate(x->right);
		return LeftRotate(x);
	}
public:
	Node* head;

	BalancedTree() : head(nullptr) {}
	
	~BalancedTree() {
		if (head) {
			destroyTree(head);
		}
	}

	void destroyTree(Node* node) {
		if (!node) return;
		destroyTree(node->left);
		destroyTree(node->right);
		delete node;
	}

	int height(Node* node) {
		if (!node) return 0;
		return node->height;
	}
	int getBalance(Node* node) {
		if (!node) return 0;
		return height(node->left) - height(node->right);
	}

	Node* append(Node*& node, int val) {
		if (!node) {
			Node* newNode = new Node(val);
			if (!head) head = newNode; // Обновляем head при добавлении первого узла
			return newNode;
		}
		if (val < node->data) {
			node->left = append(node->left, val);
			node->left->parent = node;
		}
		else if (val > node->data) {
			node->right = append(node->right, val);
			node->right->parent = node;
		}
		else {
			return node;
		}

		node->height = 1 + max(height(node->left), height(node->right));

		int balance = getBalance(node);

		if (balance > 1) {
			if (val < node->left->data) {
				Node* newRoot = RightRotate(node);
				if (node == head) head = newRoot; // Обновляем head при повороте
				return newRoot;
			}
			else { // left right
				Node* newRoot = LeftRightRotate(node);
				if (node == head) head = newRoot; // Обновляем head при повороте
				return newRoot;

			}
		}
		if (balance < -1) { // right right
			if (val > node->right->data) {
				Node* newRoot = LeftRotate(node);
				if (node == head) head = newRoot; // Обновляем head при повороте
				return newRoot;
			}
			else {
				Node* newRoot = RightLeftRotate(node);
				if (node == head) head = newRoot; // Обновляем head при повороте
				return newRoot;
			}
		}

		return node;
	}

	void printTree(Node* node) { // inOrder
		if (!head) {
			cout << "empty";
			return;
		}
		if (node != nullptr) {

			printTree(node->left);
			cout << "(" << node->data << " , " << getBalance(node) << ") ";
			printTree(node->right);
		}
		return;
	}

	Node* deleteNode(Node*& node, int val) {
		if (!node) return nullptr;
		
		
		// searching for needed node
		if (val < node->data) {
			node->left = deleteNode(node->left, val);
		}
		else if (val > node->data) {
			node->right = deleteNode(node->right, val);
		}
		// deleting node
		else {
			if (!node->left || !node->right) {
				Node* temp = node->left ? node->left : node->right;
				if (!temp) {
					temp = node;
					node = nullptr;
				}
				else {
					node = temp;
				}
				delete temp;
				temp = nullptr;
				node = nullptr;
			}
			else {
				Node* minnode = node->right;
				while (minnode->left) {
					minnode = minnode->left;
				}
				node->data = minnode->data;
				node->right = deleteNode(node->right, minnode->data);
			}
		}
		
		if (!node) return nullptr;
		
		// finding heights
		node->height = 1 + max(height(node->left), height(node->right));
		// balancing
		int balance = getBalance(node);

		if (balance > 1) {
			if (getBalance(node->left) >= 0) {
				Node* newRoot = RightRotate(node);
				if (node == head) head = newRoot; // Обновляем head при повороте
				return newRoot;
			}
			else { // left right
				Node* newRoot = LeftRightRotate(node);
				if (node == head) head = newRoot;
				return newRoot;
			}
		}
		if (balance < -1) { // right right
			if (getBalance(node->right) <= 0) {
				Node* newRoot = LeftRotate(node);
				if (node == head) head = newRoot;
				return newRoot;
			}
			else {
				Node* newRoot = RightLeftRotate(node);
				if (node == head) head = newRoot;
				return newRoot;
			}
		}
		printTree(head);
		cout << endl;
		return node;

	}

	Node* deleteHead() {
		return deleteNode(head, head->data);
	}
};

int main() {
	BalancedTree tree;
	Node* h = tree.head;
	h = tree.append(h,20);
	h = tree.append(h,60);
	h = tree.append(h,40);
	h = tree.append(h,10);
	h = tree.append(h,30);
	tree.printTree(h);
	cout << "\n";
	h = tree.deleteNode(h, 30);
	h = tree.deleteNode(h, 40);
	h = tree.deleteNode(h, 10);
	h = tree.deleteNode(h, 60);
	h = tree.deleteHead();
	//h = tree.deleteNode(h, 60);
	//h = tree.deleteNode(h, 20);
	tree.printTree(h);
}
