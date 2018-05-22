
#ifndef tree_h
#define tree_h
#include <iostream>
#include <fstream>
#include <string>

namespace BSTree {
	enum traversal_order {
		direct = 'a',
		 cross = 'b',
		  opposite = 'c'
	};
  
	template <typename T>
	struct Node {
		Node<T> *left;
		 Node<T> *right;
		  T data;
		   Node(T val);
	};
  
	template <typename T>
	class Tree {
		Node<T> *root;
	public:
		bool empty();
		Tree();
		Tree(std::initializer_list<T> list);
		Tree(const Tree<T> &tree);
		bool insert(T val);
		bool exists(T val) const;
		bool remove(T val);
		bool print(traversal_order order) const;
		void print() const;
		bool save(const std::string &path);
		bool load(const std::string& path);
    
		//friend auto operator << (std::ostream& stream, const Tree &q)->std::ostream &;
		friend auto operator << (std::ostream& stream, const Tree<T> &q)->std::ostream & { // Надо const Tree &q!!!
			q.save(stream, q.root);
			return stream;
      
		}
		auto operator=(const Tree<T>&)->Tree<T>&;
		void swap(Tree<T>& tree);
		~Tree();
    
	private:
		void clean(Node<T> * &node) const;
		void print(Node<T> *node, int level) const;
		void direct_bypass(Node<T> *node) const;
		void cross_bypass(Node<T> *node) const;
		void opposite_bypass(Node<T> *node) const;
		void save(std::ostream & stream, Node<T> *node) const;
		void copy_insert(Node<T> *node);
	};
}

template <typename T>
BSTree::Node<T>::Node(T val) : left(nullptr), right(nullptr) {
	data = val;
}
template <typename T>
bool BSTree::Tree<T>::empty() {
	if (root == nullptr) {
		return true;
	}
	return false;
}

template <typename T>
BSTree::Tree<T>::Tree() : root(nullptr) {}

template <typename T>
BSTree::Tree<T>::Tree(std::initializer_list<T> list) : Tree() {
	for (auto& item : list) {
		this->insert(item);
	}
}

template <typename T>
void BSTree::Tree<T>::copy_insert(Node<T> * node) {
	if (node != nullptr) {
		this->insert(node->data);
		  copy_insert(node->left);
		   copy_insert(node->right);
	}
}

template <typename T>
BSTree::Tree<T>::Tree(const Tree<T> &tree) {
	copy_insert(tree.root);
}

template <typename T>
auto BSTree::Tree<T>::operator=(const Tree<T> &tree) -> Tree<T> & {
	Tree<T> tree_temp(tree);
	  this->swap(tree_temp);
	    return *this;
}

template <typename T>
BSTree::Tree<T>::~Tree() { clean(root); }

template <typename T>
void BSTree::Tree<T>::clean(Node<T> * &node) const {
	if (node != nullptr) {
		clean(node->left);
		clean(node->right);
		delete node;
		node = nullptr;
	}
}

template <typename T>
bool BSTree::Tree<T>::remove(T val) {
	if (root == nullptr) {
		return false;
	}
  
	Node<T> *p = root;
	Node<T> *temp = p;
	if (p->data == val && p->right == nullptr) {
		root = p->left;
		delete p;
		return true;
	}
  
	if (p->data == val && p->right != nullptr) {
		p = p->right;
		if (p->left == nullptr) {
			p->left = root->left;
			delete root;
			root = p;
			return true;
		}
    
   		while (p->left != nullptr) {
			temp = p;
			p = p->left;
      }
      
		temp->left = p->right; // было temp->left = nullptr;
		p->left = root->left;
		p->right = root->right;
		delete root;
		root = p;
		return true;
	}
  
	while (p != nullptr) {
		if (val == p->data) {
			if (p->left == p->right) {
				val > temp->data ? temp->right = nullptr : temp->left = nullptr;
				  delete p;
				    return true;
			}
      
			if (p->data == val && p->right == nullptr) {
				p->data > temp->data ? temp->right = p->left : temp->left = p->left;
				  delete p;
				    return true;
			}
      
			if (p->data == val && p->right != nullptr) {
				Node<T> *before_delete_node = temp;
				  temp = p;
				    Node<T> *delete_node = p;
				p = p->right;
				if (p->left == nullptr) {
					temp->data > before_delete_node->data ? before_delete_node->right = temp->right : before_delete_node->left = temp->right;
					  p->left = temp->left;
					    delete temp;
					      return true;
				}
        
				while (p->left != nullptr) {
					temp = p;
					  p = p->left;
				}
        
				temp->left = p->right; // было temp->left = nullptr;
				p->data > before_delete_node->data ? before_delete_node->right = p : before_delete_node->left = p;
				p->left = delete_node->left;
				p->right = delete_node->right;
				delete delete_node;
				return true;
			}
		}
    
		temp = p;
		val > p->data ? p = p->right : p = p->left;
	}
  
	return false;
}

template <typename T>
void BSTree::Tree<T>::direct_bypass(Node<T> *node) const {
	if (node != nullptr) {
		std::cout << node->data << "|";
		  direct_bypass(node->left);
		    direct_bypass(node->right);
	}
}

template <typename T>
void BSTree::Tree<T>::cross_bypass(Node<T> *node) const {
	if (node != nullptr) {
		cross_bypass(node->left);
		  std::cout << node->data << "|";
		    cross_bypass(node->right);
	}
}

template <typename T>
void BSTree::Tree<T>::opposite_bypass(Node<T> *node) const {
	if (node != nullptr) {
		opposite_bypass(node->left);
		  opposite_bypass(node->right);
		    std::cout << node->data << "|";
	}
}

template <typename T>
bool BSTree::Tree<T>::print(traversal_order order) const {
	switch (order)
	{
	case direct:
		direct_bypass(root);
		  break;
	case cross:
		cross_bypass(root);
		  break;
	case opposite:
		opposite_bypass(root);
		  break;
	default:
		std::cout << "Неправильный ввод данных" << std::endl;
		  return false;
		    break;
	}
  
	return true;
}

template <typename T>
void BSTree::Tree<T>::print() const {
	print(root, 0);
}

template <typename T>
void BSTree::Tree<T>::print(Node<T> * node, int depth) const {
	if (root == nullptr) {
		std::cout << "Дерево пусто!" << std::endl;
	}
  
	int temp_depth = depth;
	if (node != nullptr) {
		if (node == root) {
			print(node->right, temp_depth);
			std::cout << std::endl;
			std::cout << node->data;
			std::cout << std::endl;
			print(node->left, temp_depth);
			return;
		}
    
		temp_depth++;
		print(node->right, temp_depth);
		for (int i = 0; i < temp_depth; i++)  std::cout << "   ";
		std::cout << "- " << node->data << std::endl;
		print(node->left, temp_depth);
		temp_depth--;
		return;
	}
}

template <typename T>
bool BSTree::Tree<T>::insert(T val) {
	Node<T> *p = root;
	while (p != nullptr) {
		if (p->data != val) {
			if (val > p->data && p->right == nullptr) {
				p->right = new Node<T>{ val };
				return true;
			}
      
			if (val < p->data && p->left == nullptr) {
				p->left = new Node<T>{ val };
				return true;
			}
      
			val > p->data ? p = p->right : p = p->left;
			continue;
		}
		return false;
	}
  
	root = new Node<T>{ val };
	return true;
}

template <typename T>
bool BSTree::Tree<T>::save(const std::string & path) {
	std::ifstream temp(path);
	bool exist = temp.is_open();
	temp.close();
	if (exist) {
		std::cout << "Такой файл уже существует, перезаписать ? (Yes|No): ";
		std::string answer;
		std::cin >> answer;
		if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes" || answer == "YES") {
			std::ofstream filew(path);
			filew << *this;
			filew.close();
			return true;
		}
    
		std::ofstream filew(path, std::ios_base::app);
		filew << std::endl;
		filew << *this;
		filew.close();
		return true;
	}
  
	std::ofstream filew(path);
	filew << *this;
	filew.close();
	return true;
}

template <typename T>
void BSTree::Tree<T>::save(std::ostream & stream, Node<T> *node) const {
	if (node != nullptr) {
		stream << node->data << " ";
		save(stream, node->left);
		save(stream, node->right);
	}
}

template <typename T>
bool BSTree::Tree<T>::load(const std::string & path) {
	std::ifstream file(path);
	if (file.is_open() == 0) {
		return false;
	}
  
	int buff;
	Tree<T> temp_tree;
	while (!file.eof()) {
		file >> buff;
		temp_tree.insert(buff);
	}
  
	this->swap(temp_tree);
	return true;
}

template <typename T>
bool BSTree::Tree<T>::exists(T val) const {
	Node<T> *p = root;
	while (p != nullptr) {
		if (p->data == val) {
			return true;
		}
    
		val > p->data ? p = p->right : p = p->left;
	}
	return false;
}

template <typename T>
void BSTree::Tree<T>::swap(Tree<T> &tree) {
	Node<T> *temp = this->root;
	this->root = tree.root;
	tree.root = temp;
}

#endif 
