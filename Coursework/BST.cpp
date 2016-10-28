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
void BST<T>::insert_integer(T key) {
	insert_integer(&root, key);
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
void BST<T>::insert_integer(typename BST<T>::Node **tree, T key) {
	if ((*tree) == NULL) {
		*tree = new Node<T>;
		(*tree)->key = key;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		count++;
	} 
	else if (key < (*tree)->key) {
		insert_integer(&(*tree)->left, key);
	}
	else if (key > (*tree)->key) {
		insert_integer(&(*tree)->right, key);
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
		if(leaf->left) print_tree(leaf->left);
		std::cout << count << " " << leaf->key << std::endl;
		if (leaf->right) print_tree(leaf->right);
	}
	else
		std::cout << "The tree is empty" << std::endl;
}