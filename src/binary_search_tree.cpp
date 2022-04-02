#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key, value, root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* node_ = find(key, root_);
    if (node_ == nullptr) {
      return std::nullopt;
    }
    return node_->value;
  }

  bool BinarySearchTree::Contains(int key) const {
    return Find(key) != std::nullopt;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    if (root_ == nullptr) {
      return std::nullopt;
    }
    return find_min(root_)->value;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    if (root_ == nullptr) {
      return std::nullopt;
    }
    return find_max(root_)->value;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node == nullptr) {
      node = new Node(key, value);
      node->key = key;
      return;
    }
    if (key == node->key) {
      node->value = value;
      return;
    }
    if (key < node->key) {
      insert(key, value, node->left);
    } else {
      insert(key, value, node->right);
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (node == nullptr) {
      return false;
    }
    if (key < node->key) {
      remove(key, node->left);
    } else if (key > node->key) {
      remove(key, node->right);
    } else if(node->left != nullptr && node->right != nullptr) {
      node->key = find_min(node->right)->key;
      remove(node->key, node->right);
    } else if (node->left != nullptr) {
      node = node->left;
    } else if (node->right != nullptr) {
      node = node->right;
    } else {
      node = nullptr;
    }
    return true;
  }

  void BinarySearchTree::clear(Node* node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->key == key) {
      return node;
    } else if (node->key > key) {
      return find(key, node->left);
    } else if (node->key < key) {
      return find(key, node->right);
    }
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    while (node->right != nullptr) {
      node = node->right;
    }
    return node;
  }

}  // namespace assignment