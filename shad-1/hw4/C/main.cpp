
#include <iostream>
#include <memory>
#include <queue>
#include <limits>

struct Node {
  int key;
  std::shared_ptr<Node> left, right;
};

std::queue<int> ReadInput() {
  int size;
  std::cin >> size;
  std::queue<int> result;
  for (int i = 0; i < size; ++i) {
    int key;
    std::cin >> key;
    result.push(key);
  }
  return result;
}

std::shared_ptr<Node> BuildFromPreOrder(std::queue<int> &keys, int max_key) {
  if (keys.empty() || keys.front() >= max_key) {
    return nullptr;
  }
  std::shared_ptr<Node> node = std::make_shared<Node>();
  node->key = keys.front();
  keys.pop();
  node->left = BuildFromPreOrder(keys, node->key);
  node->right = BuildFromPreOrder(keys, max_key);
  return node;
}

void PrintPreOrder(const std::shared_ptr<Node> &node) {
  if (node) {
    std::cout << node->key << " ";
    PrintPreOrder(node->left);
    PrintPreOrder(node->right);
  }
}

void PrintInOrder(const std::shared_ptr<Node> &node) {
  if (node) {
    PrintInOrder(node->left);
    std::cout << node->key << " ";
    PrintInOrder(node->right);
  }
}

void PrintPostOrder(const std::shared_ptr<Node> &node) {
  if (node) {
    PrintPostOrder(node->left);
    PrintPostOrder(node->right);
    std::cout << node->key << " ";
  }
}

void solve() {
  auto queue = ReadInput();
  auto root = BuildFromPreOrder(queue, std::numeric_limits<int>::max());
  PrintPostOrder(root);
  std::cout << "\n";
  PrintInOrder(root);
  std::cout << "\n";
}

int main() {
  solve();
  return 0;
}
