#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

template<class T, class Cmp = std::less<T>>
class Set {
  struct Node {
    Node(const T &key, Node *parent, bool colored_black = false);
    T key;
    bool colored_black;
    Node *right;
    Node *left;
    Node *parent;
  };
  Node *DeepCopy(Node *other, Node *parent);
  void DeleteNode(Node *node);
  void FixInsert(Node *node);
  void FixErase(Node *node);
  bool ColoredBlack(Node *node);
  void Turn(Node *node);
  Node *root_;
  size_t size_;
  Cmp cmp;

 public:
  class iterator {
   public:
    iterator();
    iterator operator++();
    iterator operator++(int);
    iterator operator--();
    iterator operator--(int _);
    const T &operator*() const;
    T *operator->() const;
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
   private:
    iterator(const Set<T, Cmp> *owner, Set<T, Cmp>::Node *ptr = nullptr);
    Set<T, Cmp>::Node *ptr_;
    Set<T, Cmp> const *owner_;
    friend Set<T, Cmp>;
  };
  Set();
  template<class Iter>
  Set(Iter begin, Iter end);
  explicit Set(const std::initializer_list<T> &init_list);
  Set(const Set &other);
  ~Set();
  Set &operator=(const Set &other);
  size_t size() const;
  bool empty() const;
  void insert(T element);
  void erase(T element);
  iterator find(T element) const;
  iterator lower_bound(T element) const;
  iterator begin() const;
  iterator end() const;
};

template<class T, class Cmp>
Set<T, Cmp>::Node::Node(const T &key, Node *parent, bool colored_black) {
  this->key = key;
  this->colored_black = colored_black;
  this->parent = parent;
  this->right = this->left = nullptr;
}

template<class T, class Cmp>
typename Set<T, Cmp>::Node *Set<T, Cmp>::DeepCopy(Node *other, Node *parent) {
  if (!other) {
    return nullptr;
  }
  Node *result = new Node(other->key, parent, other->colored_black);
  result->left = DeepCopy(other->left, result);
  result->right = DeepCopy(other->right, result);
  return result;
}

template<class T, class Cmp>
void Set<T, Cmp>::DeleteNode(Node *node) {
  if (node) {
    DeleteNode(node->right);
    DeleteNode(node->left);
    delete node;
  }
}

template<class T, class Cmp>
bool Set<T, Cmp>::ColoredBlack(Node *node) {
  if (node) {
    return node->colored_black;
  }
  return true;
}

template<class T, class Cmp>
Set<T, Cmp>::Set() {
  root_ = nullptr;
  size_ = 0;
}

template<class T, class Cmp>
template<class Iter>
Set<T, Cmp>::Set(Iter begin, Iter end)
    : Set() {
  for (auto it = begin; it != end; ++it) {
    this->insert(*it);
  }
}

template<class T, class Cmp>
Set<T, Cmp>::Set(const std::initializer_list<T> &init_list)
    : Set() {
  for (const auto &element : init_list) {
    this->insert(element);
  }
}

template<class T, class Cmp>
Set<T, Cmp>::Set(const Set &other) {
  size_ = other.size_;
  root_ = DeepCopy(other.root_, nullptr);
};

template<class T, class Cmp>
Set<T, Cmp>::~Set() {
  DeleteNode(root_);
}

template<class T, class Cmp>
Set<T, Cmp> &Set<T, Cmp>::operator=(const Set<T, Cmp> &other) {
  if (&other == this) {
    return *this;
  }
  size_ = other.size_;
  DeleteNode(root_);
  root_ = DeepCopy(other.root_, nullptr);
}

template<class T, class Cmp>
size_t Set<T, Cmp>::size() const {
  return size_;
}

template<class T, class Cmp>
bool Set<T, Cmp>::empty() const {
  return size_ == 0;
}

template<class T, class Cmp>
void Set<T, Cmp>::insert(T element) {
  if (root_ == nullptr) {
    root_ = new Node(element, nullptr, true);
    ++size_;
    return;
  }
  Node *parent = root_;
  while (cmp(element, parent->key) || cmp(parent->key, element)) {
    if (cmp(element, parent->key)) {
      if (parent->left) {
        parent = parent->left;
      } else {
        parent->left = new Node(element, parent);
        ++size_;
        FixInsert(parent->left);
        return;
      }
    } else {
      if (parent->right) {
        parent = parent->right;
      } else {
        parent->right = new Node(element, parent);
        ++size_;
        FixInsert(parent->right);
        return;
      }
    }
  }
}

template<class T, class Cmp>
void Set<T, Cmp>::erase(T element) {
  Node *node = root_;
  while (node) {
    if (cmp(element, node->key)) {
      node = node->left;
    } else if (cmp(node->key, element)) {
      node = node->right;
    } else {
      break;
    }
  }
  if (!node) {
    return;
  }
  if (node->right && node->left) {
    Node *next_node = node->right;
    while (next_node->left) {
      next_node = next_node->left;
    }
    node->key = next_node->key;
    node = next_node;
  }

  if (ColoredBlack(node)) {
    FixErase(node);
  }

  if (node->right) { // right case
    if (node->parent) {
      (node->parent->left == node ? node->parent->left : node->parent->right) = node->right;
    } else {
      root_ = node->right;
      if (root_) {
        root_->colored_black = true;
      }
    }
    if (node->right) {
      node->right->parent = node->parent;
    }
  } else {          // left case
    if (node->parent) {
      (node->parent->right == node ? node->parent->right : node->parent->left) = node->left;
    } else {
      root_ = node->left;
      if (root_) {
        root_->colored_black = true;
      }
    }
    if (node->left) {
      node->left->parent = node->parent;
    }
  }
  delete node;
  --size_;
}

template<class T, class Cmp>
void Set<T, Cmp>::Turn(Node *node) {
  if (node->parent->left == node) { // left case
    node->parent->left = node->right;
    if (node->right) {
      node->right->parent = node->parent;
    }
    node->right = node->parent;
    node->parent = node->parent->parent;
    if (node->parent) {
      if (node->parent->left == node->right) {
        node->parent->left = node;
      } else {
        node->parent->right = node;
      }
    }
    node->right->parent = node;
  } else {                          // right case
    node->parent->right = node->left;
    if (node->left) {
      node->left->parent = node->parent;
    }
    node->left = node->parent;
    node->parent = node->parent->parent;
    if (node->parent) {
      if (node->parent->right == node->left) {
        node->parent->right = node;
      } else {
        node->parent->left = node;
      }
    }
    node->left->parent = node;
  }
  if (!node->parent) {
    root_ = node;
  }
}

template<class T, class Cmp>
void Set<T, Cmp>::FixInsert(Node *node) {
  if (!node->parent) {
    node->colored_black = true;
    return;
  }
  if (ColoredBlack(node->parent)) {
    return;
  }

  if (node->parent == node->parent->parent->left) { // left case
    if (!ColoredBlack(node->parent->parent->right)) { // red parent, red uncle
      if (node->parent->parent->right) {
        node->parent->parent->right->colored_black = true;
      }
      node->parent->colored_black = true;
      node->parent->parent->colored_black = false;
      return FixInsert(node->parent->parent);
    } else {                                          // red parent, black uncle
      if (node->parent->left == node) { // double left
        Turn(node->parent);
        node->parent->colored_black = true;
        node->parent->right->colored_black = false;
      } else {  // left right
        Turn(node);
        Turn(node);
        node->colored_black = true;
        node->right->colored_black = false;
      }
    }
  } else {                                        // right case
    if (!ColoredBlack(node->parent->parent->left)) { // red parent, red uncle
      if (node->parent->parent->left) {
        node->parent->parent->left->colored_black = true;
      }
      node->parent->colored_black = true;
      node->parent->parent->colored_black = false;
      return FixInsert(node->parent->parent);
    } else {                                         // red parent, black uncle
      if (node->parent->right == node) { // double right
        Turn(node->parent);
        node->parent->colored_black = true;
        node->parent->left->colored_black = false;
      } else {  // right left
        Turn(node);
        Turn(node);
        node->colored_black = true;
        node->left->colored_black = false;
      }
    }
  }
}

template<class T, class Cmp>
void Set<T, Cmp>::FixErase(Node *node) {
  if (!ColoredBlack(node)) {
    node->colored_black = true;
    return;
  }
  if (!node->parent) {
    return;
  }
  if (node->parent->left == node) { // left case
    if (!ColoredBlack(node->parent->right)) {
      Turn(node->parent->right);
      node->parent->colored_black = false;
      node->parent->parent->colored_black = true;
    }
    if (ColoredBlack(node->parent->right->left) && ColoredBlack(node->parent->right->right)) {
      node->parent->right->colored_black = false;
      return FixErase(node->parent);
    }

    if (ColoredBlack(node->parent->right->right)) {
      node->parent->right->colored_black = false;
      node->parent->right->left->colored_black = true;
      Turn(node->parent->right->left);
    }
    Turn(node->parent->right);
    node->parent->parent->right->colored_black = true;
    node->parent->parent->colored_black = node->parent->colored_black;
    node->parent->colored_black = true;
  } else {                          // right case
    if (!ColoredBlack(node->parent->left)) {
      Turn(node->parent->left);
      node->parent->colored_black = false;
      node->parent->parent->colored_black = true;
    }
    if (ColoredBlack(node->parent->left->right) && ColoredBlack(node->parent->left->left)) {
      node->parent->left->colored_black = false;
      return FixErase(node->parent);
    }

    if (ColoredBlack(node->parent->left->left)) {
      node->parent->left->colored_black = false;
      node->parent->left->right->colored_black = true;
      Turn(node->parent->left->right);
    }

    Turn(node->parent->left);
    node->parent->parent->left->colored_black = true;
    node->parent->parent->colored_black = node->parent->colored_black;
    node->parent->colored_black = true;
  }
}

template<class T, class Cmp>
typename Set<T, Cmp>::iterator Set<T, Cmp>::find(T element) const {
  Set<T, Cmp>::Node *current_node = root_;
  while (current_node != nullptr) {
    if (cmp(current_node->key, element)) {
      current_node = current_node->right;
    } else if (cmp(element, current_node->key)) {
      current_node = current_node->left;
    } else {
      return iterator(this, current_node);
    }
  }
  return end();
}

template<class T, class Cmp>
typename Set<T, Cmp>::iterator Set<T, Cmp>::lower_bound(T element) const {
  Node *result = nullptr;
  std::function<void(Set<T, Cmp>::Node *node)> find_lower_bound;
  find_lower_bound = [this, &result, &element, &find_lower_bound](Set<T, Cmp>::Node *node) {
    if (node == nullptr) {
      return;
    }
    if (cmp(node->key, element)) {
      find_lower_bound(node->right);
    } else {
      result = node;
      find_lower_bound(node->left);
    }
  };
  find_lower_bound(root_);
  return iterator(this, result);
}

template<class T, class Cmp>
typename Set<T, Cmp>::iterator Set<T, Cmp>::begin() const {
  Node *ptr = root_;
  if (ptr == nullptr) {
    return iterator(this);
  }
  while (ptr->left != nullptr) {
    ptr = ptr->left;
  }
  return iterator(this, ptr);
}

template<class T, class Cmp>
typename Set<T, Cmp>::iterator Set<T, Cmp>::end() const {
  return iterator(this);
}

template<class T, class Cmp>
Set<T, Cmp>::iterator::iterator() {
  owner_ = nullptr;
  ptr_ = nullptr;
}

template<class T, class Cmp>
Set<T, Cmp>::iterator::iterator(const Set<T, Cmp> *owner, Set<T, Cmp>::Node *ptr) {
  owner_ = owner;
  ptr_ = ptr;
}

template<class T, class Cmp>
typename Set<T, Cmp>::iterator Set<T, Cmp>::iterator::operator++(int __) {
  iterator result = *this;
  ++(*this);
  return result;
}

template<class T, class Cmp>
typename Set<T, Cmp>::iterator Set<T, Cmp>::iterator::operator++() {
  if (ptr_->right) {
    ptr_ = ptr_->right;
    while (ptr_->left) {
      ptr_ = ptr_->left;
    }
    return *this;
  }
  while (ptr_->parent) {
    if (ptr_->parent->left == ptr_) {
      ptr_ = ptr_->parent;
      return *this;
    }
    ptr_ = ptr_->parent;
  }
  ptr_ = nullptr;
  return *this;
}

template<class T, class Cmp>
typename Set<T, Cmp>::iterator Set<T, Cmp>::iterator::operator--(int __) {
  iterator result = *this;
  --(*this);
  return result;
}

template<class T, class Cmp>
typename Set<T, Cmp>::iterator Set<T, Cmp>::iterator::operator--() {
  if (ptr_ == nullptr) {
    ptr_ = owner_->root_;
    if (ptr_ == nullptr) {
      return iterator(this->owner_);
    }
    while (ptr_->right != nullptr) {
      ptr_ = ptr_->right;
    }
    return *this;
  }
  if (ptr_->left) {
    ptr_ = ptr_->left;
    while (ptr_->right) {
      ptr_ = ptr_->right;
    }
    return *this;
  }
  while (ptr_->parent) {
    if (ptr_->parent->right == ptr_) {
      ptr_ = ptr_->parent;
      return *this;
    }
    ptr_ = ptr_->parent;
  }
  ptr_ = nullptr;
  return iterator(this->owner_);
}

template<class T, class Cmp>
const T &Set<T, Cmp>::iterator::operator*() const {
  return ptr_->key;
}

template<class T, class Cmp>
T *Set<T, Cmp>::iterator::operator->() const {
  return &(ptr_->key);
}

template<class T, class Cmp>
bool Set<T, Cmp>::iterator::operator==(const Set<T, Cmp>::iterator &other) const {
  return owner_ == other.owner_ && ptr_ == other.ptr_;
}

template<class T, class Cmp>
bool Set<T, Cmp>::iterator::operator!=(const Set<T, Cmp>::iterator &other) const {
  return owner_ != other.owner_ || ptr_ != other.ptr_;
}

class Point {
 public:
  int x_cord, y_cord;
  Point *other;
  Point() {};
  Point(int x_cord, int y_cord) {
    this->x_cord = x_cord;
    this->y_cord = y_cord;
  }
  bool operator<(const Point &other) const {
    if (y_cord == other.y_cord) {
      return x_cord < other.x_cord;
    }
    return y_cord < other.y_cord;
  }
};

class Cmp {
 public:
  bool operator()(Point *left, Point *right) {
    return *left < *right;
  }
};

class CmpX {
 public:
  bool operator()(Point *left, Point *right) const {
    return left->x_cord < right->x_cord;
  }
};

std::vector<Point *> ReadInput(std::istream &in = std::cin) {
  size_t size;
  in >> size;
  std::vector<Point *> result;
  result.reserve(2 * size);
  for (int cycle_counter = 0; cycle_counter < static_cast<int>(size); ++cycle_counter) {
    int lx, ly, rx, ry;
    in >> lx >> ly >> rx >> ry;
    if (rx < lx) {
      std::swap(rx, lx);
    }
    if (ry < ly) {
      std::swap(ry, ly);
    }
    Point *lp = new Point(lx, ly);
    Point *rp = new Point(rx, ry);
    lp->other = rp;
    rp->other = lp;
    result.push_back(lp);
    result.push_back(rp);
  }
  return result;
}

void Solve(std::vector<Point *> points) {
  std::sort(points.begin(), points.end(), Cmp());
  Set<Point *, CmpX> set;
  int counter = 0;
  for (auto &point : points) {
    if (point->other->y_cord < point->y_cord) {
      if (set.find(point->other) != set.end()) {
        set.erase(point->other);
        ++counter;
      }
      continue;
    }
    auto it = --set.lower_bound(point);
    if (it == set.end() || (*it)->other->x_cord < point->x_cord) {
      set.insert(point);
    };
  };
  std::cout << counter;
  for (auto &point : points) {
    delete point;
  }
}

int main() {
  Solve(ReadInput());
  return 0;
}
