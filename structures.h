#ifndef CRACKING_CODING_INTERVIEW_STRUCTURES_H_
#define CRACKING_CODING_INTERVIEW_STRUCTURES_H_
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include <condition_variable>
#include <chrono>
#include <mutex>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <vector>

template<class T = int>
struct ListNode {
  T val;
  ListNode *next;
  ListNode(T val):val(val), next(NULL){}
};
template<>
struct ListNode<int> {
  int val;
  ListNode *next;
  ListNode(int val):val(val), next(NULL){}
  static ListNode *buildLinkedList(const std::string &s) {
    const char * str = s.c_str();
    ListNode dummy(-1), *p = &dummy;
    while (str != NULL && *str != '\0') {
      int num = atoi(str);
      p->next = new ListNode<int>(num);
      p = p->next;
      str = strchr(str, ',');
      if (str != NULL) ++str;
    }
    return dummy.next;
  }
  static void printList(ListNode *head) {
    while (head != NULL) {
      printf("%d ", head->val);
      head = head->next;
    }
    puts("");
  }
};

static std::vector<std::string> split(std::string s, char delim) {
  std::stringstream ss(s);
  std::vector<std::string> elems;
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}
struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode *parent;
  TreeNode(int val):val(val), left(NULL), right(NULL), parent(NULL){}

  static TreeNode* parseTreeNode(std::string s) {
    std::vector<std::string> elems = split(s, ',');
    size_t size = elems.size();
    if (size == 0 || elems[0] == "#") return NULL;
    int pos = 0;
    // get root node
    TreeNode* root = new TreeNode(std::atoi(elems[pos++].c_str()));
    std::queue<TreeNode*> Q;
    Q.push(root);
    while (pos < size) {
      TreeNode* node = Q.front();
      Q.pop();
      if (elems[pos] != "#") {
        node->left = new TreeNode(std::atoi(elems[pos].c_str()));
        node->left->parent = node;
        Q.push(node->left);
      }
      pos++;
      if (pos >= size) break;
      if (elems[pos] != "#") {
        node->right = new TreeNode(std::atoi(elems[pos].c_str()));
        node->right->parent = node;
        Q.push(node->right);
      }
      pos++;
    }
    return root;
  }
  static std::string SerializeTree(TreeNode* root) {
    if (root == NULL) return "#";
    std::string res;
    std::queue<TreeNode*> Q;
    Q.push(root);
    while (!Q.empty()) {
      TreeNode* node = Q.front();
      Q.pop();
      if (node == NULL) {
        res.append("#,");
      } else {
        char buf[sizeof(int)];
        itoa(node->val, buf, 10);
        res.append(buf);
        res.push_back(',');
        Q.push(node->left);
        Q.push(node->right);
      }
    }
    return res;
  }
  static std::string InorderTraverse(TreeNode *root) {
    std::string s;
    std::stack<TreeNode *> S;
    while (root != NULL || !S.empty()) {
      while (root != NULL) {
        S.push(root);
        root = root->left;
      }
      root = S.top();
      S.pop();
      char buf[33];
      itoa(root->val, buf, 10);
      s.append(buf);
      s.append(",");
      root = root->right;
    }
    return s;
  }
};

class Graph {
public:
  Graph() {
    data_.push_back(std::vector<int>());
  }
  Graph(const std::string s) {
    char *buf = new char[s.size() + 1];
    data_.push_back(std::vector<int>());
    strcpy(buf, s.c_str());
    buf = strtok(buf, ";");
    while(buf != NULL) {
      char *p = buf;
      std::vector<int> neighbor;
      while (p != NULL && *p != '\0') {
        int node_id = atoi(p);
        neighbor.push_back(node_id);
        p = strchr(p, ',');
        if (p != NULL) ++p;
      }
      data_.push_back(neighbor);
      buf = strtok(NULL, ";");
    }
    delete[] buf;     
  }

  std::vector<int> GetNeighbor(int node_id) {
    if (node_id >= data_.size())
      return std::vector<int>();
    return data_[node_id];
  }
private:
  std::vector<std::vector<int>> data_;
};

class BST {
public:
  BST() : root(NULL) {}
  void insert(int val) {
    TreeNode *node = new TreeNode(val);
    TreeNode *parent = NULL, *cur = root;
    while (cur != NULL) {
      parent = cur;
      if (val < cur->val) {
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    node->parent = parent;
    if (parent == NULL) {
      root = node;
    } else if (val < parent->val) {
      parent->left = node;
    } else {
      parent->right = node;
    }
  }
  TreeNode *search(int val) {
    TreeNode *cur = root;
    while (cur != NULL) {
      if (val < cur->val) {
        cur = cur->left;
      } else if(val > cur->val) {
        cur = cur->right;
      } else {
        break;
      }
    }
    return cur;
  }
  TreeNode *successor(TreeNode *node) {
    if (root == NULL || node == NULL) 
      return NULL;
    if (node ->right != NULL) {
      node = node->right;
      while (node->left != NULL) {
        node = node->left;
      }
      return node;
    }
    TreeNode *parent = node->parent;
    while (parent != NULL && parent->right == node) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }
  TreeNode *predecessor(TreeNode *node) {
    if (root == NULL || node == NULL) 
      return NULL;
    if (node->left != NULL) {
      node = node->left;
      while (node->right != NULL) {
        node = node->right;
      }
      return node;
    }
    TreeNode *parent = node->parent;
    while (parent != NULL && parent->left == node) {
      node = parent;
      parent = parent->parent;
    }
    return parent;
  }
  void deleteNode(TreeNode *node) {
    if (root == NULL || node == NULL)
      return;
    TreeNode *d_node, *child;
    // find the node to delete
    if (node->left == NULL || node->right == NULL) {
      d_node = node;
    } else {
      d_node = successor(node);
    }
    // find the child
    if (d_node->left != NULL) {
      child = d_node->left;
    } else {
      child = d_node->right;
    }
    if (child != NULL)
      child->parent = d_node->parent;
    // find the parent
    if (d_node->parent == NULL) {
      root = child;
    } else if (d_node->parent->left == d_node) {
      d_node->parent->left = child;
    } else {
      d_node->parent->right = child;
    }
    // change node data if necessary
    if (d_node != node) {
      node->val = d_node->val;
    }
    delete d_node;
  }
  void traverse() {
    traverse(root);
    printf("\n");
  }
 private:
  void traverse(TreeNode *node) {
    if (node == NULL) return;
    traverse(node->left);
    printf("%d ", node->val);
    traverse(node->right);
  }

private:
  TreeNode *root;
};

class semaphore {
 public:
  semaphore(int value = 1) : value_(value), wakeups_(0) {}
  void wait() {
    std::unique_lock<std::mutex> lock(mtx_);
    --value_;
    if (value_ < 0) {
      cv_.wait(lock, [&]() { return wakeups_ > 0; });
      --wakeups_;
    }
  }
  void notify() {
    std::lock_guard<std::mutex> lock(mtx_);
    ++value_;
    if (value_ <= 0) {
      ++wakeups_;
      cv_.notify_one();
    }
  }
  bool try_wait() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (value_ > 0) {
      --value_;
      return true;
    } else {
      return false;
    }
  }

 private:
  int value_;
  int wakeups_;
  std::mutex mtx_;
  std::condition_variable cv_;
};
#endif  // CRACKING_CODING_INTERVIEW_STRUCTURES_H_

