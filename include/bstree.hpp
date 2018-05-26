#include <fstream>
#include <initializer_list>
#include <cstddef>
#include <iostream>

enum col { BLUE, GREEN, WHITE, RED, CYAN };
namespace BSTree{
enum class traversal_order {pre, in, post};
template <typename T>
struct Node {
  int data;
  Node<T>* left;
  Node<T>* right;
};

template <typename T>
class Tree {
  Node<T>* root;
 public:
  Tree();
  Tree(std::initializer_list<T> list);
  Tree(Tree<T>& tree);
  auto empty() -> bool;
  auto swap(Tree<T>& tree) -> void;
  auto insert(T value) -> void;
  auto print_tree() -> void;
  auto exists(T value) -> bool;
  auto remove(T value) -> bool;
  auto remove(Node<T>*&) -> void;
  auto add_element(T value) -> bool;
  auto print(traversal_order order) -> void;
  auto save(const std::string& path) -> bool;
  auto load(const std::string& path) -> bool;
  template <typename T1>
  auto friend operator<<(std::ostream& ,const Tree<T1>&) -> std::ostream&;
  auto operator=(Tree&) -> Tree&;
  ~Tree();
};

template <typename T>
auto Tree<T>::empty() -> bool{
  if(root == nullptr)
  return true;
  return false;
}

template <typename T>
Tree<T>::Tree() : root{nullptr} {
  
};

template <typename T>
auto copy(Tree<T>& tree, Node<T>* curr) -> void{
  tree.insert(curr->data);
  if (curr->left != nullptr)
  copy(tree, curr->left);
  if (curr->right != nullptr)
  copy(tree, curr->right);
}

template <typename T>
auto Tree<T>::swap(Tree<T>& tree) -> void{
  std::swap(this->root, tree.root);
}

template <typename T>
Tree<T>::Tree(Tree<T>& tree){
  root = nullptr;
  copy(*this, tree.root);  
}

template <typename T>
auto add(Node<T>*& curr, T value) -> void {
  if (curr == nullptr){
    curr = new Node<T>{value, nullptr, nullptr};
  }
  else {
    if (curr->data < value) add(curr->right, value);
    if (curr->data > value) add(curr->left, value);
  }
}

template <typename T>
auto Tree<T>::insert(T value) -> void {
  add(root, value);
  return; 
}

template <typename T>
Tree<T>::Tree(std::initializer_list<T> list){
  root = nullptr;
  for (auto& x:list) {
      insert(x);
    }
};

//DETOUR{

template <typename T>
auto pre_detour(Node<T>* curr) -> void{
    if (curr != nullptr){
    std::cout << curr->data << " ";
    pre_detour(curr->left);
    pre_detour(curr->right);
    }
    else return;
  }
  
template <typename T>
auto in_detour(Node<T>* curr) -> void{
    if (curr != nullptr){
    in_detour(curr->left);
    std::cout << curr->data << " ";
    in_detour(curr->right);
    }
    else return;
  }
  
template <typename T>
auto post_detour(Node<T>* curr) -> void{
    if (curr != nullptr){
    post_detour(curr->left);
    post_detour(curr->right);
    std::cout << curr->data << " ";
    }
    else return;
  }  
  
//}

template <typename T>
auto Tree<T>::print(traversal_order order) -> void{
  Node<T>* curr = root;
  switch (order){
    case traversal_order::pre:{
      pre_detour(curr);
    }break;
    
    case traversal_order::in:{
      in_detour(curr);
    }break;
    
    case traversal_order::post:{
      post_detour(curr);
    }break;
  }
}

template <typename T>
auto print_(Node<T>* curr, T level, T root_data) -> void {
  if (curr != nullptr) {
    if (curr->right != nullptr) {
      print_(curr->right, level + 1, root_data);
    }
    for (unsigned i = 0; i < level; ++i) std::cout << "   ";
    if (curr->data != root_data) {
      std::cout << "--";
    }
    std::cout << curr->data << std::endl;
    if (curr->left != nullptr) {
      print_(curr->left, level + 1, root_data);
    }
  }
}

template <typename T>
auto Tree<T>::print_tree() -> void {
  print_(root, 0, root->data); 
}

template <typename T>
auto Tree<T>::add_element(T value) -> bool{
  if (root == nullptr){
    add(root, value);
    return true;
  }
    Node<T>* curr = root;
    Node<T>* parent = curr;
     while(curr != nullptr){
       parent = curr;
       if (curr->data != value){
         if (curr->data > value)
          curr = curr->left;
         else curr = curr->right;
       }
       else return false;
     }
     add(parent, value);
     return true;
}

template <typename T>
auto Tree<T>::remove(T value) -> bool{
  //Проверка наличия потомков у корня
  if ((root->right == nullptr)&&(root->left == nullptr)){
    delete root;
    root = nullptr;
    return true;
  }
  Node<T>* curr = root;
  Node<T>* parent = root;
  Node<T>* parent_delete = root;
  //Проверка наличия элемента в дереве
  while(1){
    if(value == root->data) break; //Проверка корня
    if ((value >= curr->data)&&(curr->right != nullptr)){
     parent = curr;
     curr = curr->right;
     if (curr->data == value) break;
    }
    else {
      if(curr->left != nullptr){
      parent = curr;
      curr = curr->left;
      if (curr->data == value) break;
    }
    else return false;
    }
  }
  
  //Элемент не имеет потомков
  if((curr->left == nullptr)&&(curr->right == nullptr)){
    if(curr->data > parent->data)
    parent->right = curr->right;
    else
    parent->left = curr->left;
    delete curr;
    curr = parent;
    return true;
  }
  //Элемент находится в середине дерева
  parent_delete = curr;
  parent = curr;
  if(curr->right != nullptr){
    curr = curr->right;
    while(1){
      if (curr->left != nullptr){
        parent_delete = curr;
        curr = curr->left;
      }
      else{
        if(parent->data == parent_delete->data)
        parent_delete->right = curr->right;
        if(parent->data != parent_delete->data)
        parent_delete->left = curr->right;
        parent->data = curr->data;
        delete curr;
        curr = nullptr;
        return true;
      }
    }
  }
  else{
    curr = curr->left;
    while(1){
      if(curr->right != nullptr){
        parent_delete = curr;
        curr = curr->right;
      }
      else{
        if(parent->data == parent_delete->data)
        parent_delete->left = curr->left;
        if(parent->data != parent_delete->data)
        parent_delete->right = curr->left;
        parent->data = curr->data;
        delete curr;
        curr = nullptr;
        return true;
      }
    }
  }
}

template <typename T>
auto Tree<T>::remove(Node<T>*& curr) -> void{
      if (curr->right != nullptr)
        remove(curr->right);
      if (curr->left != nullptr)
        remove(curr->left);
      delete curr;
      curr = nullptr;
}

//DETOUR_OUT{
template <typename T>
auto pre_detour_out(Node<T>* curr, std::ostream &stream) -> void{
    if (curr != nullptr){
    stream << curr->data << " ";
    pre_detour_out(curr->left, stream);
    pre_detour_out(curr->right, stream);
    }
    else return;
  }
  
//}

template <typename T>
auto Tree<T>::save(const std::string& path) -> bool {
      std::ofstream stream(path);
      pre_detour_out(root, stream);
      stream.close();
      return true;
}

template <typename T>
auto Tree<T>::load(const std::string& path) -> bool {
  std::ifstream stream(path);
  if (stream){
    if (root != nullptr)
    remove(root);
    int val;
    stream >> val;
     while(stream){
       this->insert(val);
       stream >> val;
     }
     return true;
  }
  else return false;
}

template <typename T>
auto Tree<T>::exists(T value) -> bool{
  if (root == nullptr) return false;
  Node<T>* curr = root;
  while (curr != nullptr){
    if (curr->data == value)
        return true;
    if (curr->data > value)
        curr = curr->left;
    else curr = curr->right;
  }
  return false;
}

namespace BSTree{

template <typename T1>
auto operator<<(std::ostream& stream,const Tree<T1>& tree) -> std::ostream& {
      Node<T1>*curr= tree.root;
      pre_detour_out(curr, stream);
      return stream;
  }
  
}

template <typename T>
auto Tree<T>::operator=(Tree<T>& tree) -> Tree&{
  Tree tmp(tree);
  tmp.swap(*this);
  return *this;
};

template <typename T>
Tree<T>::~Tree(){
  if(root != nullptr)
  remove(root);
};

}

auto change_color(int c) -> void {
#ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
  switch (c) {
    case BLUE:  // blue color
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
      std::cout << "\033[34m";
#endif
#ifdef _WIN32
      SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 3));
#endif
      break;
    case GREEN:  // green
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
      std::cout << "\033[32m";
#endif
#ifdef _WIN32
      SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
#endif
      break;
    case WHITE:  // white
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
      std::cout << "\033[39;49m";
#endif
#ifdef _WIN32
      SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
#endif
      break;
    case RED:  // red
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
      std::cout << "\033[31m";
#endif
#ifdef _WIN32
      SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
#endif
      break;
    case CYAN:
#if defined(__gnu_linux__) || (defined(__APPLE__) && defined(__MACH__))
      std::cout << "\033[36m";
#endif
#ifdef _WIN32
      SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
#endif
  }
}
