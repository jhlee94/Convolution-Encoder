#pragma once
#include <iostream>
#include<iomanip>

template <typename T>
class BST {
public:
	struct Node {
	public:
		T key;
		int metric;
		Node* left;
		Node* right;
	};

	BST();
	~BST();

	void insert_integer(T key, int metric);
	typename BST<T>::Node *search(T key);
	void terminate_tree();
	void print_tree();
	void postorder();

	int count;
private:
	void terminate_tree(typename BST<T>::Node *leaf);
	void insert_integer(typename BST<T>::Node **tree, T key, int metric);
	typename BST<T>::Node *search(T key, typename BST<T>::Node *leaf);
	void print_tree(typename BST<T>::Node *leaf);
	void postorder(typename BST<T>::Node *p, int indent = 0);

	typename BST<T>::Node *root;
};

#include "BST.h"

template <typename T>
BST<T>::BST() {
	root = NULL;
	count = 0;
}

template <typename T>
BST<T>::~BST() {
	terminate_tree();
}

template <typename T>
void BST<T>::insert_integer(T key, int metric) {
	insert_integer(&root, key, metric);
}
template <typename T>
typename BST<T>::Node *BST<T>::search(T key) {
	return search(key, root);
}
template <typename T>
void BST<T>::terminate_tree() {
	terminate_tree(root);
}
template <typename T>
void BST<T>::print_tree() {
	print_tree(root);
}

// private
template <typename T>
void BST<T>::terminate_tree(typename BST<T>::Node *leaf) {
	if (leaf != NULL)
	{
		terminate_tree(leaf->left);
		terminate_tree(leaf->right);
		delete leaf;
	}
}

template <typename T>
void BST<T>::insert_integer(typename BST<T>::Node **tree, T key, int metric) {
	if ((*tree) == NULL) {
		*tree = new typename BST<T>::Node;
		(*tree)->key = key;
		(*tree)->metric = key;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		count++;
	}
	else if (key <= (*tree)->key) {
		insert_integer(&(*tree)->left, key, metric);
	}
	else if (key > (*tree)->key) {
		insert_integer(&(*tree)->right, key, metric);
	}
}

template <typename T>
typename BST<T>::Node *BST<T>::search(T key, typename BST<T>::Node *leaf) {
	if (leaf != NULL) {
		if (key == leaf->key) {
			return leaf;
		}
		if (key < leaf->key)
			return search(key, leaf->left);
		else
			return search(key, leaf->right);
	}
	else
		return NULL;
}

template <typename T>
void BST<T>::print_tree(typename BST<T>::Node *leaf) {
	if (leaf != NULL) {
		if (leaf->left) print_tree(leaf->left);
		std::cout << leaf->key << " ";
		if (leaf->right) print_tree(leaf->right);
	}
	else
		std::cout << "The tree is empty" << std::endl;
}

template <typename T>
void BST<T>::postorder()
{
	postorder(root);
}


template <typename T>
void BST<T>::postorder(typename BST<T>::Node* p, int indent = 0)
{
	if (p != NULL) {
		if (p->right) {
			postorder(p->right, indent + 4);
		}
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
		std::cout << p->key<< "\n ";
		if (p->left) {
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postorder(p->left, indent + 4);
		}
	}
}