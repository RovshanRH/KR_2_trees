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

	// Вспомогательная функция для поиска минимального узла в поддереве
	Node* minimum(Node* node) {
		while (node->left != nullptr)
			node = node->left;
		return node;
	}

	// Вспомогательная функция для замены одного поддерева другим
	void transplant(Node*& root, Node* u, Node* v) {
		if (u->parent == nullptr)
			root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		if (v != nullptr)
			v->parent = u->parent;
	}

	// Основная функция удаления узла по ключу
	void deleteNode(Node* node) {
		if (!node) {
			cout << endl << "no node";
			return;
		}

		Node* z = node;
		Node* y = z;
		Node* x = nullptr;
		Color y_original_color = y->color;

		if (z->left == nullptr) {
			x = z->right;
			transplant(head, z, z->right);
		}
		else if (z->right == nullptr) {
			x = z->left;
			transplant(head, z, z->left);
		}
		else {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				if (x) x->parent = y;
			}
			else {
				transplant(head, y, y->right);
				y->right = z->right;
				if (y->right) y->right->parent = y;
			}
			transplant(head, z, y);
			y->left = z->left;
			if (y->left) y->left->parent = y;
			y->color = z->color;
		}
		delete z;

		// Восстановление свойств КЧД (упрощённо, без полного восстановления)
		// Для учебных целей: полноценная реализация требует дополнительного кода
		// для корректного восстановления свойств КЧД после удаления.
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
	tree.insert(tree.head, 3);
	tree.insert(tree.head, 4);
	tree.insert(tree.head, 5);
	tree.insert(tree.head, 6);
	tree.insert(tree.head, 10);
	tree.printTree(tree.head);
	tree.deleteNode(tree.head->right);
	cout << endl;
	tree.printTree(tree.head);
	cout << endl;
	tree.deleteNode(tree.head->right);
	tree.printTree(tree.head);
}