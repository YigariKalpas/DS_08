#pragma once

#ifndef debug_mode
#define debug_mode 0
#endif // debug_mode

#ifndef developer
#define developer 0
#endif // developer

#include<iostream>
#include"vector_m.h"	

template<typename T>
class tree_node {
public:
	T value;
	tree_node<T>* left; 
	tree_node<T>* right;
	tree_node() :value(T()) {
		left = nullptr;
		right = nullptr;
	};
	tree_node(T given_value) :value(given_value) {
		left = nullptr;
		right = nullptr;
	}
	~tree_node() {
		delete left;
		delete right;
	}
	virtual void add_left(tree_node<T>* new_node) {
		left = new_node;
	}
	virtual void add_right(tree_node<T>* new_node) {
		right = new_node;
	}
	virtual void do_something(const tree_node<T>* now_node) {
#if debug_mode
		std::cout << "do something" << std::endl;
#endif // 0
		return;
	}
	virtual void mid_turn_travel(const tree_node<T>* now_node) {
		if (now_node == nullptr) return;
		mid_turn_travel(now_node->left);
		do_something(now_node) ;
		mid_turn_travel(now_node->right);
		return;
	}
	void delete_left(const tree_node<T>* target_node) {
		tree_node<T>* &temp= target_node->left;
		target_node->left = nullptr;
		delete temp;
	}
	void delete_right(const tree_node<T>* target_node) {
		tree_node<T>*& temp = target_node->right;
		target_node->right = nullptr;
		delete temp;
	}
};

template<typename T>
class heap_m :public tree_node<T> {
public:
	int line_count;
	tree_node<T> *head;
	heap_m() {
		head = new tree_node<T>;
		head->value = T();
	};
	heap_m(vector_m<T> target_array) {
		//...
	}
#if 0
	void add_node(tree_node<T>* target_node, tree_node<T>* now_node = this) {
		if (!target_node) return;
		if (target_node->value > now_node->value) {
			if (now_node->right) {
				now_node = now_node->right;
				add_node(target_node, now_node);
			}
			else {
				now_node->right = target_node;
			}
		}
		else {
			if (now_node->left) {
				now_node = now_node->left;
				add_node(target_node, now_node);
			}
			else {
				now_node->left = target_node;
			}
		}
	}
	#endif
	/// <summary>
	/// before the use of this function ,  need to recheck whether the this pointer is the root of the total heap
	/// </summary>
	/// <param name="target_value"></param>
	/// <param name="now_node"></param>
	void add_node(T target_value, tree_node<T> *root, long long& times) {
		//every node would be added at the left side of the head node ,head node is used to develope a more override friendly style of language
		if (target_value > root->value || root == head) {
			if (root->left) {
				times++;
				add_node(target_value, root->left,times);
			}
			else {
				tree_node<T> *target_node_pointer = new tree_node<T>;
				target_node_pointer->value = target_value;
				root->add_left(target_node_pointer);
				times++;
			}
		}
		else {
			if (root->right) {
				times++;
				add_node(target_value, root->right,times);
			}
			else {
				tree_node<T> *target_node_pointer = new tree_node<T>;
				target_node_pointer->value = target_value;
				root->add_right(target_node_pointer);
			}
		}
	}
	virtual void mid_turn_travel(const tree_node<T>* now_node) override {
		if (now_node == nullptr) return;
		mid_turn_travel(now_node->left);
		std::cout << now_node->value << "  ";
		if (!((++line_count) % 5))
			std::cout << std::endl;
		mid_turn_travel(now_node->right);
		return;
	}
	void show_heap() {
		mid_turn_travel(head->left);
	}
};


