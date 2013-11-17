#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>

#include <map>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <list>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>

#include "question.h"
//#include "structures.h"

#if Q_N == Array_and_String_8
using std::string;
bool isRotation_old(string s1, string s2) {
  int size1 = s1.size(), size2 = s2.size();
  int len = 0, i = 0, j = 0;
  if (size1 != size2) return false;
  while (j < size2) {
    while (j < size2 && s1[i] != s2[j]) {
      ++j;
      len = j;
    }
    if (j < size2) {
      ++i, ++j;
    }
  }
  j = 0;
  for (; i < size1; ++i) {
    if (s1[i] != s2[j]) return false;
    ++j;
  }
  return true;
}
bool isRotation(string s1, string s2) {
  int size1 = s1.size(), size2 = s2.size();
  if (size1 != size2) return false;
  string s3 = s2 + s2;
  return s3.find(s1) != string::npos;
}
void doTest() {
  string s1 = "waterbottle", s2 = "erbottlewae";
  printf("%d\n", isRotation(s1, s2));
}
#endif  // Array_and_String_8

#if Q_N == Array_and_String_7
void setZero(int** array, int M, int N) {
  bool row_zero = false, col_zero = false;
  for (int i = 0; i < M; ++i) {
    if (array[i][0] == 0) {
      col_zero = true;
      break;
    }
  }
  for (int j = 0; j < N; ++j) {
    if (array[0][j] == 0) {
      row_zero = true;
      break;
    }
  }
  for (int i = 1; i < M; ++i) {
    for (int j = 1; j < N; ++j) {
      if (array[i][j] == 0) {
        array[i][0] = 0;
        array[0][j] = 0;
      }
    }
  }
  for (int i = 1; i < M; ++i) {    // Not from 0
    for (int j = 1; j < N; ++j) {  // Not from 0
      if (array[i][0] == 0 || array[0][j] == 0)
        array[i][j] = 0;
    }
  }
  if (row_zero) {
    for (int j = 0; j < N; ++j)
      array[0][j] = 0;
  }
  if (col_zero) {
    for (int i = 0; i < M; ++i)
      array[i][0] = 0;
  }
}
void doTest() {
}
#endif  // Array_and_String_7

#if Q_N == Array_and_String_6
void rotate(std::vector<std::vector<int>>& matrix) {
  int N = matrix.size();
  if (N <= 1 || matrix[0].size() != N) return;
  int max_i = N - 1, min_i = 0;
  while (max_i > min_i) {
    for (int i = 0; i < max_i - min_i; ++i) {
      int temp = matrix[min_i][min_i + i];
      matrix[min_i][min_i + i] = matrix[max_i - i][min_i];
      matrix[max_i - i][min_i] = matrix[max_i][max_i - i];
      matrix[max_i][max_i - i] = matrix[min_i + i][max_i];
      matrix[min_i + i][max_i] = temp;
    }
    ++min_i, --max_i;
  }
}
void doTest() {
  int data[5][5] = {
    {8, 3, 6, 9, 7}, {0, 3, 7, 0, 0}, {5, 3, 6, 7, 1}, {8, 7, 2, 5, 0}, {0, 2, 9, 9, 3}
  };
  std::vector<std::vector<int>> matrix(5, std::vector<int>(5));
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      matrix[i][j] = data[i][j];
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  //for (int i = 0; i < 4; ++i)
  rotate(matrix);
  printf("\n");
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}
#endif  // Array_and_String_6

#if Q_N == Array_and_String_5
std::string compressString(const std::string& s) {
  int size = s.size();
  if (size <= 2) return s;
  std::string str(1, s[0]);
  int j = 1, count = 1;
  while (str.size() < size  && j <= size) {
    if (str.back() != s[j]) {
      char buf[32];
      itoa(count, buf, 10);
      str.append(buf);
      if (j < size)
        str.push_back(s[j]);
      count = 1;
    } else {
      ++count;
    }
    ++j;
  }
  if (str.size() < size) {
    return str;
  } else {
    return s;
  }
}
void doTest() {
  std::string s = "aabccccdccaaa";
  printf("%s\n", compressString(s).c_str());
}
#endif  // Array_and_String_5

#if Q_N == Array_and_String_4
void replaceSpace(char* str, int size) {
  int space_num = 0;
  char* p = str, *new_p = NULL;
  while (*p != '\0') {
    if (*p == ' ')
      ++space_num;
    ++p;
  }
  new_p = p + space_num * 2;
  while (p >= str) {
    if (*p == ' ') {
      strncpy(new_p - 2, "%20", 3);
      new_p -= 2;
    } else {
      *new_p = *p;
    }
    --p, --new_p;
  }
}


void doTest() {
  char str[] = " Mr Li\0       ";
  printf("%s\n", str);
  replaceSpace(str, sizeof(str));
  printf("%s\n", str);
}
#endif  // Array_and_String_4

#if Q_N == Array_and_String_3
bool isPermutation(const std::string& s1, const std::string& s2) {
  int size1 = s1.size(), size2 = s2.size();
  if (size1 != size2) return false;
  if (size1 == 0) return true;
  int char_count[256];
  memset(char_count, 0, sizeof(char_count));
  for (int i = 0; i < size1; ++i) {
    ++char_count[s1[i]];
    --char_count[s2[i]];
  }
  for (int i = 0; i < 256; ++i) {
    if (char_count[i] != 0)
      return false;
  }
  return true;
}
void doTest() {
  std::string s1 = "waterbottle", s2 = "bottlewater";
  printf("%d\n", isPermutation(s1, s2));
}
#endif  // Array_and_String_3

#if Q_N == Array_and_String_2
void reverse(char* str) {
  if (str == NULL || *str == '\0') return;
  char* p = str;
  while (*p != '\0')
    ++p;
  --p;
  while (str < p) {
    std::swap(*str, *p);
    ++str, --p;
  }
}
void doTest() {
  char str[] = "abcdefdge";
  reverse(str);
  printf("%s\n", str);
}
#endif  // Array_and_String_2

#if Q_N == Linked_Lists_1
class Node {
  int val;
  Node* next;
 public:
  void append(Node* n) {
    if (n == NULL) return;
    Node* p = this;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = n;
    n->next = NULL;
  }
};

void removeDuplicate(ListNode* head) {
  if (head == NULL || head->next == NULL) return;
  std::unordered_set<int> node_set;
  node_set.insert(head->val);
  while (head != NULL && head->next != NULL) {
    int val = head->next->val;
    if (node_set.find(val) != node_set.end()) {
      ListNode* p = head->next;
      head->next = head->next->next;
      delete p;
    } else {
      node_set.insert(val);
      head = head->next;
    }
  }
}
void removeDuplicate2(ListNode* head) {
  if (head == NULL || head->next == NULL) return;
  ListNode* p = head;
  while (p != NULL && p->next != NULL) {
    ListNode* runner = p->next;
    while (runner != NULL && runner->next != NULL) {
      if (runner->next->val == p->val) {
        ListNode* q = runner->next;
        runner->next = runner->next->next;
        delete q;
      } else {
        runner = runner->next;
      }
    }
    p = p->next;
  }
}
void doTest() {
  int data[] = {1, 2, 4, 2, 1, 1, 1, 1, 1, 1, 3, 1, 4, 2};
  // create linked list
  ListNode* head = new ListNode(-1), *p = head;
  int len = sizeof(data) / sizeof(int);
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    p->next = new ListNode(data[i]);
    p = p->next;
  }
  //removeDuplicate(head->next);
  removeDuplicate2(head->next);
  ListNode::printList(head->next);
  // printf("%d\n", );
}
#endif  // Linked_Lists_1

#if Q_N == Linked_Lists_2
ListNode* findKth(ListNode* head, int k) {
  if (head == NULL || k <= 0) return NULL;
  ListNode* slow = head, *fast = head;
  while (k > 0 && fast != NULL) {
    fast = fast->next;
    --k;
  }
  if (fast == NULL) return NULL;
  while (fast != NULL) {
    slow = slow->next;
    fast = fast->next;
  }
  return slow;
}

ListNode* findKth(ListNode* head, int k, int& i) {
  if (head == NULL)  return NULL;
  ListNode* node = findKth(head->next, k, i);
  ++i;
  if (i == k)
    return head;
  return node;
}

void doTest() {
  int data[] = {1, 2, 3, 4, 5, 6, 7};
  // create linked list
  ListNode* head = new ListNode(-1), *p = head;
  int len = sizeof(data) / sizeof(int);
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    p->next = new ListNode(data[i]);
    p = p->next;
  }
  int i = 0;
  p = findKth(head->next, 3, i);
  while (p != NULL) {
    printf("%d ", p->val);
    p = p->next;
  }
  // printf("%d\n", );
}
#endif  // Linked_Lists_2

#if Q_N == Linked_Lists_3
void deleteNode(ListNode* p) {
  assert(p != NULL && p->next != NULL);
  p->val = p->next->val;
  ListNode* q = p->next;
  p->next = p->next->next;
  delete q;
}

void doTest() {
  int data[] = {1, 2, 3, 4, 5, 6, 7};
  // create linked list
  ListNode* head = new ListNode(-1), *p = head;
  int len = sizeof(data) / sizeof(int);
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    p->next = new ListNode(data[i]);
    p = p->next;
  }
  deleteNode(head->next->next->next);
  p = head->next;
  while (p != NULL) {
    printf("%d ", p->val);
    p = p->next;
  }
  // printf("%d\n", );
}
#endif  // Linked_Lists_3

#if Q_N == Linked_Lists_4
ListNode* partitionList(ListNode* head, int x) {
  ListNode dummy = ListNode(-1), *tail = &dummy, *p = &dummy;
  dummy.next = head;
  while (p->next != NULL) {
    if (p->next->val < x) {
      if (tail->next == p->next) {
        tail = p->next;
        p = p->next;
      } else {
        ListNode* q = p->next;
        p->next = p->next->next;
        q->next = tail->next;
        tail->next = q;
        tail = q;
      }
    } else {
      p = p->next;
    }
  }
  return dummy.next;
}

using std::string;
string read(FILE* fp, size_t size) {
  char* str = new char[size + 1];
  fread(str, 1, size, fp);
  str[size] = '\0';
  string s(str);
  delete[] str;
  return s;
}
void printInReverseOrder() {
  std::string left, buf;
  size_t file_size, pos, block_size = 512;
  // get file size
  char* file_name = "in.txt";
  FILE* fp = fopen(file_name, "rb");
  FILE* fp_out = fopen("out.txt", "wb");
  std::vector<string> output;
  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  pos = file_size;
  while (pos > 0) {
    size_t read_size = std::min(pos, block_size);
    pos -= read_size;
    fseek(fp, pos, SEEK_SET);
    buf = read(fp, read_size);
    buf.append(left);
    left.clear();
    int size = buf.size(), i = size - 1, prev_i = size - 1;
    while (i >= 0) {
      while (i >= 0 && buf[i] != '\n')
        --i;
      if (i < 0) break;
      if (prev_i - i - 1 > 0)
        puts(buf.substr(i + 1, prev_i - i - 1).c_str());
      prev_i = i;
      --i;
    }
    left = buf.substr(0, prev_i);
  }
  if (left.size() > 0) {
    puts(left.c_str());
  }
  fclose(fp);
  fclose(fp_out);
}

void doTest() {
  int data[] = {4, 5, 6, 7, 1, 2, 3};
  // create linked list
  ListNode* head = new ListNode(-1), *p = head;
  int len = sizeof(data) / sizeof(int);
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    p->next = new ListNode(data[i]);
    p = p->next;
  }
  p = partitionList(head->next, 3);
  printInReverseOrder();
  while (p != NULL) {
    printf("%d ", p->val);
    p = p->next;
  }
  std::string s = "";
  // printf("%d\n", );
}
#endif  // Linked_Lists_4

#if Q_N == Linked_Lists_5
ListNode* addNumber(ListNode* left, ListNode* right) {
  ListNode dummy(-1), *p = &dummy;
  int carry = 0;
  while (left != NULL || right != NULL || carry > 0) {
    int sum = carry;
    if (left != NULL) {
      sum += left->val;
      left = left->next;
    }
    if (right != NULL) {
      sum += right->val;
      right = right->next;
    }
    p->next = new ListNode(sum % 10);
    p = p->next;
    carry = sum / 10;
  }
  return dummy.next;
}
ListNode* addNumber2(ListNode* left, ListNode* right) {
  std::vector<int> left_stack, right_stack;
  ListNode dummy(-1);
  int carry = 0;
  while (left != NULL) {
    left_stack.push_back(left->val);
    left = left->next;
  }
  while (right != NULL) {
    right_stack.push_back(right->val);
    right = right->next;
  }
  while (!left_stack.empty() || !right_stack.empty() || carry > 0) {
    int sum = carry;
    if (!left_stack.empty()) {
      sum += left_stack.back();
      left_stack.pop_back();
    }
    if (!right_stack.empty()) {
      sum += right_stack.back();
      right_stack.pop_back();
    }
    ListNode* p = new ListNode(sum % 10);
    carry = sum / 10;
    p->next = dummy.next;
    dummy.next = p;
  }
  return dummy.next;
}
void doTest() {
  ListNode* left = ListNode::buildLinkedList("4,5,6,7,1");
  ListNode* right = ListNode::buildLinkedList("6,7,1");
  ListNode::printList(left);
  ListNode::printList(right);
  // create linked list
  ListNode* res = addNumber(left, right);
  ListNode::printList(res);
  res = addNumber2(left, right);
  ListNode::printList(res);
}
#endif  // Linked_Lists_5

#if Q_N == Linked_Lists_6
ListNode* findFirstLoopNode(ListNode* head) {
  if (head == NULL) return NULL;
  std::unordered_set<ListNode*> node_set;
  while (head != NULL) {
    if (node_set.find(head) != node_set.end())
      return head;
    else
      node_set.insert(head);
    head = head->next;
  }
  return NULL;
}
ListNode* findFirstLoopNode2(ListNode* head) {
  ListNode* fast = head, *slow = head;
  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) break;
  }
  if (fast == NULL || fast->next == NULL) {
    return NULL;
  }
  //collosion point
  slow = head;
  while (slow != fast) {
    slow = slow->next;
    fast = fast->next;
  }
  return slow;
}
void doTest() {
  ListNode* head = ListNode::buildLinkedList("1,2,3,4,5");
  head->next->next->next->next->next = head->next;
  printf("%d\n", findFirstLoopNode2(head)->val);
}
#endif  // Linked_Lists_6
#if Q_N == Linked_Lists_7
bool isPalindrome(ListNode* head, int len, ListNode*& tail) {
  if (len <= 1) {
    if (len == 0)
      tail = head;
    else
      tail = head->next;
    return true;
  }
  bool res = isPalindrome(head->next, len - 2, tail);
  res = res && (head->val == tail->val);
  tail = tail -> next;
  return res;
}
void doTest() {
  int data[] = {1, 2, 4, 2, 1};
  // create linked list
  ListNode* head = new ListNode(-1), *p = head;
  int len = sizeof(data) / sizeof(int);
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    p->next = new ListNode(data[i]);
    p = p->next;
  }
  ListNode* tail;
  printf("%d\n", isPalindrome(head->next, len, tail));
}
#endif  //

#if Q_N == Stacks_and_Queues_1
template<class T = int, int N = 3>
class Stack {
 public:
  Stack(int total_capacity) {
    int sub_capacity = total_capacity / N, start = 0;
    array_ = new T[total_capacity];
    for (int i = 0; i < N; ++i) {
      start_[i] = start;
      pointer_[i] = -1;
      capacity_[i] = sub_capacity;
      start += sub_capacity;
    }
    capacity_[N - 1] = total_capacity - sub_capacity * (N - 1);
  }

  void Push(T elem, int index) {
    assert(index < N && pointer_[index] + 1 < capacity_[index]);
    ++pointer_[index];
    array_[start_[index] + pointer_[index]] = elem;
  }
  void Pop(int index) {
    assert(index < N && pointer_[index] >= 0);
    // T elem = array[start_[index] + pointer_[index]];
    --pointer_[index];
    // return elem;
  }
  T Peek(int index) {
    assert(index < N && pointer_[index] >= 0);
    return array_[start_[index] + pointer_[index]];
  }
  bool Empty(int index) {
    return pointer_[index] < 0;
  }

 private:
  int capacity_[N];
  int pointer_[N];
  int start_[N];
  T* array_;
};
void doTest() {
  Stack<int, 3> S(101);
  for (int i = 0; i < 33; ++i) {
    S.Push(i, 0);
    S.Push(i + 30, 1);
    S.Push(i + 60, 2);
  }
  for (int i = 0; i < 3; ++i) {
    while (!S.Empty(i)) {
      int a = S.Peek(i);
      S.Pop(i);
      printf("%d ", a);
    }
    puts("");
  }
}
#endif  // Stacks_and_Queues_1

#if Q_N == Stacks_and_Queues_2
template<class T = int>
class MinStack {
 public:
  MinStack(int capacity) : capacity_(capacity), pointer_(-1), min_index_(-1) {
    array_ = new std::pair<T, int>[capacity];
  }

  void Push(T elem) {
    assert(pointer_ + 1 < capacity_);
    ++pointer_;
    if (min_index_ < 0 || array_[array_[min_index_].second].first > elem) {
      min_index_ = pointer_;
    }
    array_[pointer_] = std::pair<T, int>(elem, min_index_);
  }
  void Pop() {
    assert(pointer_ >= 0);
    --pointer_;
    min_index_ = array_[pointer_].second;
  }
  T Min() {
    assert(pointer_ >= 0);
    return array_[min_index_].first;
  }
  T Peek() {
    assert(pointer_ >= 0);
    return array_[pointer_].frist;
  }
  bool Empty() {
    return pointer_ < 0;
  }
 private:
  int capacity_;
  int pointer_;
  int min_index_;
  std::pair<T, int>* array_;
};
void doTest() {
  MinStack<int> S(100);
  for (int i = 30; i >= 0; --i) {
    S.Push(i);
    S.Push(i + 20);
  }
  while (!S.Empty()) {
    int a = S.Min();
    S.Pop();
    printf("%d ", a);
  }
  puts("");
}
#endif  // Stacks_and_Queues_2

#if Q_N == Stacks_and_Queues_4
void Hanoi(int N, int from, int to, int mid) {
  if (N == 0) return;
  Hanoi(N - 1, from, mid, to);
  printf("%d -> %d\n", from, to);
  Hanoi(N - 1, mid, to, from);
}
struct Problem {
  int N;
  int from, to, mid;
  bool visited;
  Problem(int N, int from, int to, int mid):
  N(N), from(from), to(to), mid(mid), visited(false) {}
};

void Hanoi2(int N, int from, int to, int mid) {
  std::stack<Problem> S;
  S.push(Problem(N, from, to, mid));
  while (!S.empty()) {
    auto p = S.top();
    if (p.N == 0) {
      S.pop();
      continue;
    } else {
      if (!p.visited) {
        S.top().visited = true;
        S.push(Problem(p.N - 1, p.from, p.mid, p.to));
      } else {
        S.pop();
        printf("%d -> %d\n", p.from, p.to);
        S.push(Problem(p.N - 1, p.mid, p.to, p.from));
      }
    }
  }
}
void doTest() {
  // Hanoi(3, 1, 3, 2);
  Hanoi2(3, 1, 3, 2);
}
#endif  // Stacks_and_Queues_4

#if Q_N == Stacks_and_Queues_5
template<class T = int>
class MyQueue {
 public:
  MyQueue() {}

  void Push(T elem) {
    while (!main_stack_.empty()) {
      temp_stack_.push(main_stack_.top());
      main_stack_.pop();
    }
    main_stack_.push(elem);
    while (!temp_stack_.empty()) {
      main_stack_.push(temp_stack_.top());
      temp_stack_.pop();
    }
  }
  void Pop() {
    main_stack_.pop();
  }
  T Peek() {
    return main_stack_.top();
  }
 private:
  std::stack<T> main_stack_, temp_stack_;
};

template<class T = int>
class MyQueue2 {
 public:
  MyQueue2() {}

  void Push(T elem) {
    main.push(elem);
  }
  T Pop() {
    checkAndReverse();
    assert(!secondary.empty());
    T elem = secondary.top();
    secondary.pop();
    return elem;
  }
  T Peek() {
    checkAndReverse();
    assert(!secondary.empty());
    return secondary.top();
  }
 private:
  void checkAndReverse() {
    if (secondary.empty()) {
      while (!main.empty()) {
        secondary.push(main.top());
        main.pop();
      }
    }
  }
  std::stack<T> main, secondary;
};
void doTest() {
  MyQueue2<int> Q;
  std::queue<int> Q2;
  for (int i = 0; i < 20000; ++i) {
    int r = rand();
    if (r % 10 < 5) {
      Q.Push(r);
      Q2.push(r);
    } else {
      if (!Q2.empty()) {
        assert(Q.Peek() == Q2.front());
        Q.Pop();
        Q2.pop();
      }
    }
  }
}
#endif  // Stacks_and_Queues_5

#if Q_N == Stacks_and_Queues_6

void sortStack2(std::stack<int>& S) {
  if (S.empty() || S.size() == 1) return;
  int size = S.size();
  std::stack<int> T;
  for (int i = 0; i < size - 1; ++i) {
    int min = S.top();
    S.pop();
    while (S.size() > i) {
      int elem = S.top();
      S.pop();
      T.push(std::max(min, elem));
      min = std::min(min, elem);
    }
    S.push(min);
    while (!T.empty()) {
      S.push(T.top());
      T.pop();
    }
  }
}

void sortStack(std::stack<int>& S) {
  std::stack<int> temp_stack;
  int size = S.size(), min = INT_MAX;
  if (size <= 1) return;
  while (S.size() > 1) {
    temp_stack.push(S.top());
    S.pop();
  }
  while (!temp_stack.empty()) {
    int elem = temp_stack.top();
    temp_stack.pop();
    while (!S.empty() && S.top() > elem) {
      temp_stack.push(S.top());
      S.pop();
    }
    S.push(elem);
  }
}
void doTest() {
  std::stack<int> S;
  for (int i = 0; i < 2000; ++i) {
    S.push(rand());
  }
  sortStack(S);
  int prev = INT_MAX;
  while (!S.empty()) {
    //printf("%d\n", S.top());
    assert(S.top() <= prev);
    prev = S.top();
    S.pop();
  }
}
#endif  // Stacks_and_Queues_6

#if Q_N == Stacks_and_Queues_7
//class AnimalShelter {
//public:
//  struct Animal{
//    int type;
//    int no;
//    Animal(int type, int no):type(type), no(no){}
//  };
//  AnimalShelter():no_(1), num_cat_(0), num_dog_(0){
//    head = new ListNode<Animal>(Animal(-1, -1));
//    tail = head;
//  }
//
//  void Enqueue(int type) {
//    assert(type == kCat || type == kDog);
//    Animal n(type, no_);
//    tail->next = new ListNode<Animal>(n);
//    ++no_;
//    tail = tail->next;
//    if (type == kCat)
//      ++num_cat_;
//    else
//      ++num_dog_;
//  }
//  Animal DequeueAny() {
//    assert(head->next != NULL);
//    Animal animal = head->next->val;
//    auto q = head;
//    head = head->next;
//    delete q;
//    if (head->val.type == kCat)
//      --num_cat_;
//    else
//      --num_dog_;
//    return animal;
//  }
//  Animal DequeueCat() {
//    assert(num_cat_ > 0);
//    --num_cat_;
//    return Dequeue(kCat);
//  }
//  Animal DequeueDog() {
//    assert(num_dog_ > 0);
//    --num_dog_;
//    return Dequeue(kDog);
//  }
//  int num_dog() { return num_dog_;}
//  int num_cat() { return num_cat_;}
//  int size() { return num_dog_ + num_cat_;}
//
//  const static int kDog = 0, kCat = 1;
//private:
//  Animal Dequeue(int type) {
//    assert(head->next != NULL);
//    Animal animal(-1, -1);
//    auto p = head;
//    while (p->next != NULL && p->next->val.type != type) {
//      p = p->next;
//    }
//    if (p->next != NULL) {
//      animal = p->next->val;
//      auto q = p->next;
//      p->next = p->next->next;
//      delete q;
//    }
//    return animal;
//  }
//
//  int no_;
//  int num_cat_, num_dog_;
//  ListNode<Animal> *head, *tail;
//  std::list<Animal> dogs_, cats_;
//};
class AnimalShelter {
 public:
  struct Animal {
    int no;
    std::string type;
    Animal(std::string type): no(0), type(type) {}
    Animal(std::string type, int no): no(no), type(type) {}
  };
  AnimalShelter(): no_(0) {}
  void Enqueue(Animal& animal) {
    animal.no = ++no_;
    if (animal.type == "cat") {
      cats_.push_back(animal);
    } else if (animal.type == "dog") {
      dogs_.push_back(animal);
    }
  }
  Animal DequeueAny() {
    if (cats_.size() == 0) {
      return DequeueDog();
    } else if (dogs_.size() == 0) {
      return DequeueCat();
    }
    if (cats_.front().no < dogs_.front().no) {
      return DequeueCat();
    } else {
      return DequeueDog();
    }
  }
  Animal DequeueCat() {
    Animal animal("Unknown");
    if (cats_.size() > 0) {
      animal = cats_.front();
      cats_.pop_front();
    }
    return animal;
  }
  Animal DequeueDog() {
    Animal animal("Unknown");
    if (dogs_.size() > 0) {
      animal = dogs_.front();
      dogs_.pop_front();
    }
    return animal;
  }
  int size() const {
    return cats_.size() + dogs_.size();
  }
  int num_dog() const {
    return dogs_.size();
  }
  int num_cat() const {
    return cats_.size();
  }
 private:
  int no_;
  std::list<Animal> cats_, dogs_;
};
//void doTest2() {
//  AnimalShelter shelter;
//  for (int i = 0; i < 50; ++i) {
//    int r = rand();
//    if (r % 10 < 5) {
//      shelter.Enqueue(AnimalShelter::kCat);
//    } else {
//      shelter.Enqueue(AnimalShelter::kDog);
//    }
//  }
//  while (shelter.size() > 0) {
//    int r = rand() %10;
//    AnimalShelter::Animal animal(-1, -1);
//    if (r < 3) {
//      animal = shelter.DequeueAny();
//      printf("Any ");
//    } else if (r < 7 && shelter.num_dog() > 0) {
//      animal = shelter.DequeueDog();
//      printf("Dog ");
//    } else if (shelter.num_cat() > 0){
//      animal = shelter.DequeueCat();
//      printf("Cat ");
//    }
//    printf("Type: %d, No: %d, Dog:%d, Cat:%d\n", animal.type, animal.no, shelter.num_dog(), shelter.num_cat());
//  }
//}
void doTest() {
  AnimalShelter shelter;
  for (int i = 0; i < 50; ++i) {
    int r = rand();
    AnimalShelter::Animal animal("cat");
    if (r % 10 < 5) {
      animal.type = "cat";
    } else {
      animal.type = "dog";
    }
    shelter.Enqueue(animal);
  }
  while (shelter.size() > 0) {
    int r = rand() % 10;
    AnimalShelter::Animal animal("OK");
    if (r < 3) {
      animal = shelter.DequeueAny();
      printf("Any ");
    } else if (r < 7 && shelter.num_dog() > 0) {
      animal = shelter.DequeueDog();
      printf("Dog ");
    } else if (shelter.num_cat() > 0) {
      animal = shelter.DequeueCat();
      printf("Cat ");
    }
    printf("Type: %s, No: %d, Dog:%d, Cat:%d\n", animal.type.c_str(), animal.no, shelter.num_dog(), shelter.num_cat());
  }
}
#endif  // Stacks_and_Queues_7

#if Q_N == Trees_and_Graphs_1
bool IsBalanced(TreeNode* root, int& height) {
  if (root == NULL) {
    height = 0;
    return true;
  }
  int left_height, right_height;
  bool left_balance = IsBalanced(root->left, left_height);
  if (!left_balance) return false;
  bool right_balance = IsBalanced(root->right, right_height);
  height = std::max(left_height, right_height) + 1;
  return left_balance && right_balance &&
         abs(left_height - right_height) <= 1;
}
void doTest() {
  TreeNode* root = TreeNode::parseTreeNode("1,2,3,4,5,#,6,7");
  int height;
  printf("%d\n", IsBalanced(root, height));
}
#endif  // Trees_and_Graphs_1

#if Q_N == Trees_and_Graphs_2
bool IsConnect(Graph& g, int start_id, int end_id) {
  std::unordered_set<int> visited;
  std::queue<int> Q;
  Q.push(start_id);
  while (!Q.empty()) {
    int node_id = Q.front();
    Q.pop();
    if (node_id == end_id) return true;
    std::vector<int> neighbor = g.GetNeighbor(node_id);
    for (auto ptr = neighbor.begin(); ptr != neighbor.end(); ++ptr) {
      if (visited.find(*ptr) == visited.end()) {
        visited.insert(*ptr);
        Q.push(*ptr);
      }
    }
  }
  return false;
}
void doTest() {
  Graph g("2,3;3,4;6;5;7;5");
  for (int i = 1; i < 7; ++i) {
    for (int j = i + 1; j <= 7; ++j) {
      printf("%d->%d:%d\n", i, j, IsConnect(g, i, j));
    }
  }
}
#endif  // Trees_and_Graphs_2

#if Q_N == Trees_and_Graphs_3
TreeNode* createBST(int A[], int start, int end) {
  if (start > end) return NULL;
  int mid = start + ((end - start) >> 1);
  TreeNode* root = new TreeNode(A[mid]);
  root->left = createBST(A, start, mid - 1);
  root->right = createBST(A, mid + 1, end);
  return root;
}
void doTest() {
  int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  TreeNode* root = createBST(A, 0, sizeof(A) / sizeof(int) - 1);
  //puts(TreeNode::SerializeTree(root).c_str());
  puts(TreeNode::InorderTraverse(root).c_str());
}
#endif  // Trees_and_Graphs_3

#if Q_N == Trees_and_Graphs_4
std::vector<TreeNode*> getLists(TreeNode* root) {
  std::vector<TreeNode*> lists;
  std::queue<std::pair<TreeNode*, int>> Q;
  Q.push(std::pair<TreeNode*, int>(root, 0));
  while (!Q.empty()) {
    auto p = Q.front();
    Q.pop();
    if (p.first == NULL) continue;
    Q.push(std::pair<TreeNode*, int>(p.first->left, p.second + 1));
    Q.push(std::pair<TreeNode*, int>(p.first->right, p.second + 1));
    p.first->right = NULL;
    if (p.second == lists.size()) {
      lists.push_back(p.first);
    } else {
      lists.back()->right = p.first;
    }
  }
  return lists;
}
void doTest() {
  TreeNode* root = TreeNode::parseTreeNode("1,2,4,#,3,5,#,#,#,6,7");
  auto lists = getLists(root);
  for (auto ptr = lists.begin(); ptr != lists.end(); ++ptr) {
    TreeNode* p = (*ptr);
    while (p != NULL) {
      printf("%d ", p->val);
      p = p->right;
    }
    puts("");
  }
}
#endif  // Trees_and_Graphs_4

#if Q_N == Trees_and_Graphs_5
//bool IsBST(TreeNode *root, int &min_val, int &max_val) {
//  if (root == NULL) return true;
//  int left_max, right_min;
//  min_val = max_val = root->val;
//  if (root->left != NULL) {
//    bool left_bst = IsBST(root->left, min_val, left_max);
//    if (!left_bst || left_max >= root->val) {
//      return false;
//    }
//  }
//  if (root->right != NULL) {
//    bool right_bst = IsBST(root->right, right_min, max_val);
//    if (!right_bst || right_min <= root->val) {
//      return false;
//    }
//  }
//  return true;
//}
//bool IsBST(TreeNode *root, int &min_val, int &max_val) {
//  if (root == NULL) return true;
//  int left_max = INT_MIN, right_min = INT_MAX;
//  min_val = max_val = root->val;
//  return IsBST(root->left, min_val, left_max) &&
//    IsBST(root->right, right_min, max_val) &&
//    (root->val > left_max) && (root->val < right_min);
//}
bool IsBST(TreeNode* root, int min_val, int max_val) {
  if (root == NULL) return true;
  if (root->val <= min_val || root->val >= max_val) return false;
  return IsBST(root->left, min_val, root->val) && IsBST(root->right, root->val, max_val);
}
void doTest() {
  //TreeNode *root = TreeNode::parseTreeNode("7,6,9,5,8,7,#,#,4");
  TreeNode* root = TreeNode::parseTreeNode("8,6,9,5,7,#,10");
  int max_val = INT_MAX, min_val = INT_MIN;
  printf("%d\n", IsBST(root, min_val, max_val));
}
#endif  // Trees_and_Graphs_5

#if Q_N == Trees_and_Graphs_6
TreeNode* findNext(TreeNode* root) {
  if (root == NULL) return NULL;
  TreeNode* parent = root->parent, *right = root->right;
  if (right != NULL) {
    while (right->left != NULL) {
      right = right->left;
    }
    return right;
  }
  while (parent != NULL && root == parent->right) {
    root = parent;
    parent = parent->parent;
  }
  return parent;
}

void doTest() {
  TreeNode* root = TreeNode::parseTreeNode("8,6,12,5,7,10,15,#,#,#,#,9,#,13,17");
  TreeNode* min_node = root;
  while (min_node->left != NULL) {
    min_node = min_node->left;
  }
  while (min_node != NULL) {
    printf("%d ", min_node->val);
    min_node = findNext(min_node);
  }
  printf("\n");
}
#endif  // Trees_and_Graphs_6

#if Q_N == Trees_and_Graphs_7
TreeNode* getLCA(TreeNode* n1, TreeNode* n2) {
  TreeNode* p1 = n1, *p2 = n2;
  int d1 = 0, d2 = 0;
  while (p1 != NULL) {
    ++d1;
    p1 = p1->parent;
  }
  while (p2 != NULL) {
    ++d2;
    p2 = p2->parent;
  }
  p1 = n1, p2 = n2;
  while (d1 > d2) {
    --d1;
    p1 = p1->parent;
  }
  while (d2 > d1) {
    --d2;
    p2 = p2->parent;
  }
  while (p1 != p2) {
    p1 = p1->parent;
    p2 = p2->parent;
  }
  return p1;
}
int LCA(TreeNode* root, TreeNode* n1, TreeNode* n2, TreeNode*& ancestor) {
  if (root == NULL) return 0;
  if (root == n1) return 1;
  if (root == n2) return 2;
  int l_val, r_val;
  TreeNode* l_ancestor, *r_ancestor;
  l_val = LCA(root->left, n1, n2, l_ancestor);
  r_val = LCA(root->right, n1, n2, r_ancestor);
  if (l_val + r_val == 3) {
    if (l_val == 3)
      ancestor = l_ancestor;
    else if (r_val == 3)
      ancestor = r_ancestor;
    else
      ancestor = root;
  }
  return l_val + r_val;
}
void doTest() {
  TreeNode* root = TreeNode::parseTreeNode("1,2,3,4,5,7,#,6,#,#,#,6,8,#,#,9,10");
  TreeNode* n1 = root->left->left->left, *n2 = root->right->left->right;
  //TreeNode *n1 = new TreeNode(-1), *n2 = root->right->left->right;
  TreeNode* ancestor = getLCA(n1, n2);
  TreeNode* ancestor2 = NULL;
  int res = LCA(root, n1, n2, ancestor2);
  //if (res == 3 && ancestor != NULL) {
  if (ancestor != NULL) {
    printf("%d\n", ancestor->val);
    printf("%d\n", ancestor2->val);
  } else {
    puts("NULL");
  }
}
#endif  // Trees_and_Graphs_7

#if Q_N == Trees_and_Graphs_8
bool matchTree(TreeNode* r1, TreeNode* r2) {
  if (r1 == NULL && r2 == NULL) return true;
  if (r1 == NULL || r2 == NULL) return false;
  return r1->val == r2->val &&
         matchTree(r1->left, r2->left) &&
         matchTree(r1->right, r2->right);
}

bool isSubTree(TreeNode* big, TreeNode* small) {
  if (matchTree(big, small)) return true;
  if (big == NULL) return false;
  return isSubTree(big->left, small) || isSubTree(big->right, small);
}
void doTest() {
  TreeNode* big = TreeNode::parseTreeNode("1,2,3,4,5,7,#,6,#,#,#,6,8,#,#,9,10");
  TreeNode* small = TreeNode::parseTreeNode("7,6,8,9,10");
  printf("%d\n", isSubTree(big, small));
}
#endif  // Trees_and_Graphs_8

#if Q_N == Trees_and_Graphs_9
using std::vector;
//void findPath(TreeNode *root, int target, bool is_root,  vector<int> &v, vector<vector<int>> &res) {
//  if (root == NULL || target <= root->val) {
//    if (root != NULL && target == root->val) {
//      v.push_back(root->val);
//      res.push_back(v);
//      v.pop_back();
//    }
//    return;
//  }
//  if (is_root) {
//    for (int i = 1; i < target - root->val; ++i) {
//      vector<vector<int>> left, right;
//      vector<int> new_v;
//      findPath(root->left, i, false, new_v, left);
//      if (left.size() == 0) continue;
//      findPath(root->right, target - root->val - i, false, new_v, right);
//      if (right.size() == 0) continue;
//      for (int j = 0; j < left.size(); ++j) {
//        for (int k = 0; k < right.size(); ++k) {
//          new_v = left[j];
//          std::reverse(new_v.begin(), new_v.end());
//          new_v.push_back(root->val);
//          new_v.insert(new_v.end(), right[k].begin(), right[k].end());
//          res.push_back(new_v);
//        }
//      }
//    }
//    if (root->left != NULL)
//      findPath(root->left, target, true, v, res);
//    if (root->right != NULL)
//      findPath(root->right, target, true, v, res);
//  }
//  v.push_back(root->val);
//  if (root->left != NULL)
//    findPath(root->left, target - root->val, false, v, res);
//  if (root->right != NULL)
//    findPath(root->right, target - root->val, false, v, res);
//  v.pop_back();
//}
void findPath(TreeNode* root, int target, bool is_root,  vector<int>& v, vector<vector<int>>& res) {
  if (root == NULL)  return;
  if (is_root) {
    for (int i = 1; i < target - root->val; ++i) {
      vector<vector<int>> left, right;
      vector<int> new_v;
      findPath(root->left, i, false, new_v, left);
      if (left.size() == 0) continue;
      findPath(root->right, target - root->val - i, false, new_v, right);
      if (right.size() == 0) continue;
      for (int j = 0; j < left.size(); ++j) {
        for (int k = 0; k < right.size(); ++k) {
          new_v = left[j];
          std::reverse(new_v.begin(), new_v.end());
          new_v.push_back(root->val);
          new_v.insert(new_v.end(), right[k].begin(), right[k].end());
          res.push_back(new_v);
        }
      }
    }
    findPath(root->left, target, true, v, res);
    findPath(root->right, target, true, v, res);
  }
  v.push_back(root->val);
  if (target - root->val == 0) res.push_back(v);
  findPath(root->left, target - root->val, false, v, res);
  findPath(root->right, target - root->val, false, v, res);
  v.pop_back();
}

void getPath(TreeNode* root, int target, bool is_root, vector<int>& v, vector<vector<int>>& res) {
  if (root == NULL) return;
  v.push_back(root->val);
  if (target - root->val == 0)
    res.push_back(v);
  getPath(root->left, target - root->val, false, v, res);
  getPath(root->right, target - root->val, false, v, res);
  v.pop_back();
  if (is_root) {
    vector<int> v2;
    getPath(root->left, target, true, v2, res);
    getPath(root->right, target, true, v2, res);
  }
}

void doTest() {
  TreeNode* root = TreeNode::parseTreeNode("1,2,4,3,6,8,1,3,1,3,#,-4,#,#,#,2");
  vector<int> v;
  vector<vector<int>> res;
  //findPath(root, 10, true,v, res);
  getPath(root, 9, true, v, res);
  for (int i = 0; i < res.size(); ++i) {
    for (int j = 0; j < res[i].size(); ++j) {
      printf("%d->", res[i][j]);
    }
    puts("");
  }
}
void evenFab() {
  int f0 = 0, f1 = 1;
  int f = f0 + f1;
  long long sum = 0;
  while (f <= 4000000) {
    if (f % 2 == 0)
      sum += f;
    f0 = f1;
    f1 = f;
    f = f0 + f1;
  }
  printf("%lld", sum);
}
#endif  // Trees_and_Graphs_9

#if Q_N == Trees_and_Graphs_10

void doTest() {
}
#endif  // Trees_and_Graphs_10

#if Q_N == Trees_and_Graphs_0
#include "structures.h"
void doTest() {
  BST bst;
  int data[] = {1, 5, 6, 2, 4, 8, 9, 10, 53, 7};
  int size = sizeof(data) / sizeof(int);
  for (int i = 0; i < size ; ++i) {
    bst.insert(data[i]);
  }
  auto node = bst.search(1);
  while (node != NULL) {
    printf("%d ", node->val);
    node = bst.successor(node);
  }
  printf("\n");
  node = bst.search(53);
  while (node != NULL) {
    printf("%d ", node->val);
    node = bst.predecessor(node);
  }
  printf("\n");
  for (int i = 0; i < size; ++i) {
    node = bst.search(data[i]);
    assert(node != NULL);
    bst.deleteNode(node);
    bst.traverse();
    puts("");
  }
}

#endif  // Trees_and_Graphs_0
#if Q_N == Bit_Manipulation_1
int insertBits(int N, int M, int i, int j) {
  int n = j - i + 1;
  unsigned int mask = ~((1 << n) - 1) << i;
  N = (N & mask) | (M << i);
  return N;
}
void printBinary(int n) {
  int b = 1;
  while (n >= b) b <<= 1;
  b >>= 1;
  while (b > 0) {
    printf("%d", (n & b) != 0);
    n %= b;
    b >>= 1;
  }
}
void doTest() {
  int N = 0x400, M = 0x13;
  int i = 2, j = 6;
  printBinary(N);
  puts("");
  printBinary(M);
  puts("");
  printBinary(insertBits(N, M, i, j));
  puts("");
}
#endif  // Bit_Manipulation_1

#if Q_N == Bit_Manipulation_2
std::string BinaryFloat(double f) {
  std::string s = "0.";
  int count = 0;
  double d = 0.5;
  while (count < 30 && f > 0) {
    if (f >= d) {
      f -= d;
      s.push_back('1');
    } else {
      s.push_back('0');
    }
    ++count;
    d /= 2;
  }
  if (f != 0)
    return "ERROR";
  else
    return s;
}
void doTest() {
  double f = std::pow(0.5, 13) + std::pow(0.5, 30);
  puts(BinaryFloat(f).c_str());
}
#endif  // Bit_Manipulation_2

#if Q_N == Bit_Manipulation_3
void nextPermutation(std::vector<int>& v) {
  int size = v.size(), pos = size - 2;
  for (; pos >= 0; --pos) {
    if (v[pos + 1] > v[pos])
      break;
  }
  if (pos >= 0) {
    for (int i = size - 1; i > pos; --i) {
      if (v[i] > v[pos]) {
        std::swap(v[i], v[pos]);
        break;
      }
    }
  }
  std::sort(v.begin() + (pos + 1), v.end());
}
std::string IntToBinary(unsigned int n) {
  if (n == 0) return "0";
  std::string res;
  while (n > 0) {
    res.push_back('0' + n % 2);
    n /= 2;
  }
  std::reverse(res.begin(), res.end());
  return res;
}
void doTest2() {
  int data[] = {1, 2, 3, 4, 5};
  std::vector<int> v;
  v.insert(v.end(), data, data + sizeof(data) / sizeof(int));
  for (int i = 0; i < 120; ++i) {
    for (int j = 0; j < v.size(); ++j) {
      printf("%d ", v[j]);
    }
    printf("\n");
    nextPermutation(v);
  }
}
void setBit(int& n, int i) {
  int mask = (1 << i);
  n |= mask;
}
void clearBit(int& n, int i) {
  int mask = ~(1 << i);
  n &= mask;
}
int getBit(int n, int i) {
  int mask = (1 << i);
  return (n & mask) != 0;
}
int findLarger(int n) {
  int num_one = 0;
  for (int i = 0; i < 32; ++i) {
    if (getBit(n, i) == 1) {
      ++num_one;
    } else if (num_one > 0) {
      setBit(n, i);
      n = n & (~0 << i);  // clear [0, i - 1]
      n = n | ((1 << (num_one - 1)) - 1);  // set [0, num_one - 1]
      return n;
    }
  }
  return -1;
}
int findSmaller(int n) {
  int num_zero = 0;
  for (int i = 0; i < 32; ++i) {
    if (getBit(n, i) == 0) {
      ++num_zero;
    } else if (num_zero > 0) {
      clearBit(n, i);
      n = n | ((1 << i) - 1);
      n = n & (~0 << (num_zero - 1));
      return n;
    }
  }
  return -1;
}

void doTest() {
  int n = 0xcc;
  puts(IntToBinary(n).c_str());
  for (int i = 0; i < 5; ++i) {
    n = findLarger(n);
    puts(IntToBinary(n).c_str());
  }
  puts("");
  for (int i = 0; i < 5; ++i) {
    n = findSmaller(n);
    puts(IntToBinary(n).c_str());
  }
}
#endif  // Bit_Manipulation_3

#
#if Q_N == Bit_Manipulation_5
std::string IntToBinary(unsigned int n) {
  if (n == 0) return "0";
  std::string res;
  while (n > 0) {
    res.push_back('0' + n % 2);
    n /= 2;
  }
  std::reverse(res.begin(), res.end());
  return res;
}
int getDist(std::string s1, std::string s2) {
  int size1 = s1.size(), size2 = s2.size();
  int* D = new int[size2 + 1], *D2 = new int[size2 + 1];
  for (int i = 0; i <= size1; ++i) {
    D2[0] = i;
    for (int j = 1; j <= size2; ++j) {
      if (i == 0) {
        D2[j] = j;
        continue;
      }
      int diff = s1[i - 1] == s2[j - 1] ? 0 : 1;
      D2[j] = std::min(D[j - 1] + diff, std::min(D[j] + 1, D2[j - 1] + 1));
    }
    std::swap(D, D2);
  }
  int dist = D[size2];
  delete[] D, delete[] D2;
  return dist;
}
int getDist(int a, int b) {
  int count = 0, c = a ^ b;
  while (c != 0) {
    ++count;
    c = c & (c - 1);
  }
  return count;
}
void doTest() {
  int num[] = {0x58, 0x5};
  printf("%d\n", getDist(num[0], num[1]));
  //printf("%d\n", getDist(IntToBinary(num[0]), IntToBinary(num[1])));
}
#endif  // Bit_Manipulation_5

#if Q_N == Bit_Manipulation_6
std::string IntToBinary(uint32_t n) {
  if (n == 0) return "0";
  std::string res;
  while (n > 0) {
    res.push_back('0' + n % 2);
    n /= 2;
  }
  std::reverse(res.begin(), res.end());
  return res;
}

uint32_t swapBits(uint32_t n) {
  uint32_t n0 = n & 0x55555555;
  uint32_t n1 = n & 0xaaaaaaaa;
  return (n0 << 1) | (n1 >> 1);
}
void doTest() {
  for (int i = 0; i < 10; ++i) {
    int n = rand();
    printf("%32s\n", IntToBinary(n).c_str());
    printf("%32s\n", IntToBinary(swapBits(n)).c_str());
  }
}
#endif  // Bit_Manipulation_6

#if Q_N == Bit_Manipulation_7
int fetchBit(int n, int i) {
  return ((n & (1 << i)) != 0);
}
int findMissingNum(int A[], int n) {
  assert(n % 2 == 1);
  int count[32];
  memset(count, 0, sizeof(count));
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < 32; ++j) {
      count[j] += fetchBit(A[i], j);
    }
  }
  int res = n * (n + 1) / 2, b = 1;
  for (int i = 0; i < 32; ++i) {
    res -= count[i] << i;
  }
  return res;
}

void doTest() {
  int A[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int res = findMissingNum(A, sizeof(A) / sizeof(int) + 1);
  printf("%d\n", res);
}
#endif  // Bit_Manipulation_7

#if Q_N == Bit_Manipulation_8
void setBits(uint8_t& n, int from, int len) {
  uint8_t mask = ((1 << len) - 1) << (8 - from - len);
  n |= mask;
}
void drawHorizontalLine(uint8_t screen[], int height, int width, int x1, int x2, int y) {
  int start = (y * width + x1) / 8, end = (y * width + x2) / 8;
  for (int i = start + 1; i < end; ++i) {
    screen[i] = 0xff;
  }
  if (start == end) {
    setBits(screen[start], x1 % 8, x2 - x1 + 1);
  } else {
    setBits(screen[start], x1 % 8, 8 - x1 % 8);
    setBits(screen[end], 0, x2 % 8 + 1);
  }
}
std::string ByteToBinary(uint8_t n) {
  std::string res;
  while (n > 0) {
    res.push_back(n % 2 + '0');
    n /= 2;
  }
  while (res.size() < 8)
    res.push_back('0');
  std::reverse(res.begin(), res.end());
  return res;
}
void display(uint8_t screen[], int height, int width) {
  width /= 8;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      printf("%s", ByteToBinary(screen[i * width + j]).c_str());
    }
    puts("");
  }
}



void doTest() {
  uint8_t* screen = new uint8_t[32];
  memset(screen, 0, 32);
  int width = 32;
  int height = 8;
  display(screen, height, width);
  drawHorizontalLine(screen, height, width, 0, 10, 3);
  drawHorizontalLine(screen, height, width, 10, 12, 4);
  drawHorizontalLine(screen, height, width, 13, 29, 5);
  puts("");
  display(screen, height, width);
}
#endif  // Bit_Manipulation_8

#if Q_N == Mathematics_and_Probability_4

int neg(int n) {
  assert(n != INT_MIN);
  int64_t w[32], w1[32];
  int res = 0, sum = 0;
  w[0] = 1, w1[0] = -1;
  for (int i = 1; i < 32; ++i) {
    w[i] = w[i - 1] + w[i - 1];
    w1[i] = w1[i - 1] + w1[i - 1];
  }
  for (int i = 31; i >= 0; --i) {
    if (n > 0 && sum + w[i] <= n) {
      sum += w[i];
      res += w1[i];
    } else if (n < 0 && sum + w1[i] >= n) {
      sum += w1[i];
      res += w[i];
    }
  }
  return res;
}

int64_t multiply(int n, int multiplier) {
  assert(n != INT_MIN && multiplier != INT_MIN);
  int64_t weight[32], weight2[32], res = 0;
  int c = 0;
  bool negtive = false;
  if (multiplier < 0) {
    multiplier = neg(multiplier);
    negtive = true;
  }
  weight[0] = 1, weight2[0] = n;
  for (int i = 1; i < 32; ++i) {
    weight[i] = weight[i - 1] + weight[i - 1];
    weight2[i] = weight2[i - 1] + weight2[i - 1];
  }
  for (int i = 31; i >= 0; --i) {
    if (c + weight[i] <= multiplier) {
      res += weight2[i];
      c += weight[i];
    }
  }
  if (negtive) res = neg(res);
  return res;
}
int divide(int n, int divisor) {
  assert(divisor != 0 && n != INT_MIN);
  int64_t w[32], w2[32], sum = 0;
  int res = 0;
  bool negtive = false;
  if (divisor < 0) {
    divisor = neg(divisor);
    negtive = !negtive;
  }
  if (n < 0) {
    n = neg(n);
    negtive = !negtive;
  }
  w[0] = 1, w2[0] = divisor;
  for (int i = 1; i < 32; ++i) {
    w[i] = w[i - 1] + w[i - 1];
    w2[i] = w2[i - 1] + w2[i - 1];
  }
  for (int i = 31; i >= 0; --i) {
    if (n >= sum + w2[i]) {
      res += w[i];
      sum += w2[i];
    }
  }
  if (negtive) res = neg(res);
  return res;
}
int sub(int a, int b) {
  return a + neg(b);
}

void doTest() {
  //int64_t n = 12345, multiplier = 872933, divisor = 15;
  int64_t n = -12345, divisor = -1;
  //int64_t res = multiply(n, multiplier);
  int res = divide(n, divisor);
  int res2 = n / divisor;
  printf("%d\n", multiply(-3, 0));
  printf("%d\n", sub(9, 10011));
  printf("%d %d\n", res, res2);
}
#endif  // Mathematics_and_Probability_4

#if Q_N == Mathematics_and_Probability_6
struct Point {
  double x, y;
  Point(double x, double y): x(x), y(y) {}
};
class Line {
 public:
  Line(const Point& p1, const Point& p2) {
    assert(!(equals(p1.x, p2.x) && equals(p1.y, p2.y)));
    if (equals(p1.x, p2.x)) {
      b = 0;
      a = -1;
      c = p1.x;
    } else {
      double k = (p2.y - p1.y) / (p2.x - p1.x);
      a = k;
      b = -1;
      c = p1.y - k * p1.x;
    }
  }
  double slope() {
    if (b == 0) return DBL_MAX;
    return a;
  }
  bool equals(const Line& l) {
    return equals(a, l.a) && equals(b, l.b) && equals(c, l.c);
  }
  double a, b, c;
 private:
  bool equals(double v1, double v2) {
    double epsilon = 0.0000001;
    return abs(v1 - v2) < epsilon;
  }
};
void doTest() {
  Point p1(1, 3), p2(1, 9), p3(3, 8), p4(3, 6);
  Line l(p1, p2), l2(p3, p4);
  printf("A=%f, B=%f, C=%f, k=%f\n", l.a, l.b, l.c, l.slope());
  printf("A=%f, B=%f, C=%f\n", l2.a, l2.b, l2.c);
  printf("%d\n", l.equals(l2));
}
#endif  // Mathematics_and_Probability_6

#if Q_N == Recursion_and_Dynamic_Programming_1
int64_t getWays(int n) {
  if (n < 0) return 0;
  int64_t* f = new int64_t[n + 1];
  f[0] = 1, f[1] = 1, f[2] = 2;
  for (int i = 3; i <= n; ++i) {
    f[i] = f[i - 1] + f[i - 2] + f[i - 3];
  }
  return f[n];
}
void doTest() {
  int n = 4;
  printf("%lld\n", getWays(n));
}
#endif  // Recursion_and_Dynamic_Programming_1

#if Q_N == Recursion_and_Dynamic_Programming_2
int getWays(int X, int Y) {
  if (X < 0 || Y < 0) return 0;
  int* D = new int[Y + 1];
  for (int i = 0; i <= X; ++i) {
    for (int j = 0; j <= Y; ++j) {
      if (i == 0 || j == 0) {
        D[j] = 1;
      } else {
        D[j] = D[j] + D[j - 1];
      }
    }
  }
  return D[Y];
}
int getWays(int** A, int X, int Y) {
  if (X < 0 || Y < 0) return 0;
  int* D = new int[Y + 1];
  for (int i = 0; i <= X; ++i) {
    for (int j = 0; j <= Y; ++j) {
      if (A[i][j] != 0) {
        D[j] = 0;
        continue;
      }
      if (i == 0 || j == 0) {
        D[j] = 1;
      } else {
        D[j] = D[j] + D[j - 1];
      }
    }
  }
  return D[Y];
}
//int findMagic(int *A, int n) {
//  int lo = 0, hi = n - 1;
//  if (A == NULL || n <= 0 || A[lo] >= n || A[hi] < 0)
//    return -1;
//  while (lo < hi && sign(A[lo] - lo) * sign(A[hi] - hi) > 0)
//    ++lo;
//  while (lo < hi && sign(A[lo] - lo) * sign(A[hi] - hi) < 0) {
//    int mid = lo + ((hi - lo) >> 1));
//    if (A[mid] == mid)
//      return mid;
//    if (sign(A[mid] - mid) * sign(A[lo] - lo) < 0) {
//      hi = mid - 1;
//    } else {
//      lo = mid + 1;
//    }
//  }
//  if (A[lo] - lo == 0)
//    return lo;
//  if (A[hi] - hi == 0)
//    return hi;
//  return -1;
//}

void doTest() {
  printf("%d\n", getWays(1, 9));
}
#endif  // Recursion_and_Dynamic_Programming_2

#if Q_N == Recursion_and_Dynamic_Programming_3
int getMagic(int* A, int s, int e) {
  if (A == NULL || s > e)
    return -1;
  int mid = s + ((e - s) >> 1), lo, hi, idx;
  int mid_val = A[mid];
  if (mid_val == mid) return mid;
  hi = std::min(mid - 1, mid_val);
  idx = getMagic(A, s, hi);
  if (idx >= 0) return idx;
  lo = std::max(mid + 1, mid_val);
  idx = getMagic(A, lo, e);
  return idx;
}
int getMagic2(int* A, int n) {
  int lo = 0, hi = n - 1;
  if (A == NULL || n <= 0) return -1;
  while (lo <= hi) {
    int mid = lo + ((hi - lo) >> 1);
    if (A[mid] == mid) return mid;
    if (A[mid] < mid) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return -1;
}
void doTest() {
  //int A[] = {-1, 1, 3, 3, 3, 4, 6, 6, 7};
  int A[] = { -1, 2, 2, 2, 3, 4, 5, 8};
  //int idx = getMagic(A, 0, sizeof(A) / sizeof(int) - 1);
  int idx = getMagic2(A, sizeof(A) / sizeof(int));
  printf("idx: %d, val: %d\n", idx, A[idx]);
}
#endif  // Recursion_and_Dynamic_Programming_3

#if Q_N == Recursion_and_Dynamic_Programming_4
using std::vector;
void getSubsets(const vector<int>& data, int pos, int n, vector<int>& v, vector<vector<int>>& res) {
  if (n == 0) {
    res.push_back(v);
    return;
  }
  int size = data.size();
  for (int i = pos; i < size; ++i) {
    v.push_back(data[i]);
    getSubsets(data, i + 1, n - 1, v, res);
    v.pop_back();
  }
}
vector<vector<int>> getSubsets(const vector<int>& data) {
  vector<int> v;
  vector<vector<int>> res;
  int size = data.size();
  for (int i = 1; i <= size; ++i) {
    getSubsets(data, 0, i, v, res);
  }
  return res;
}
void doTest() {
  int data[] = {3, 4, 8, 7};
  vector<int> v;
  v.insert(v.end(), data, data + sizeof(data) / sizeof(int));
  auto res = getSubsets(v);
  for (int i = 0; i < res.size(); ++i) {
    for (int j = 0; j < res[i].size(); ++j) {
      printf("%d ", res[i][j]);
    }
    printf("\n");
  }
}
#endif  // Recursion_and_Dynamic_Programming_4

#if Q_N == Recursion_and_Dynamic_Programming_5
using std::list;
using std::vector;
void getPerm(list<char>* str, vector<char>* v, vector<vector<char>>* res) {
  if (str->size() == 0) {
    res->push_back(*v);
    return;
  }
  for (auto itr = str->begin(); itr != str->end(); ++itr) {
    char c = *itr;
    v->push_back(c);
    itr = str->erase(itr);
    getPerm(str, v, res);
    itr = str->insert(itr, c);
    v->pop_back();
  }
}
using std::list;
using std::vector;
//void getPerm(list<char> *str, vector<char> *v, vector<vector<char>> *res) {
//  if (str->size() == 0) {
//    res->push_back(*v);
//    return;
//  }
//  for (auto itr = str->begin(); itr != str->end(); ++itr) {
//    char c = *itr;
//    v->push_back(c);
//    itr = str->erase(itr);
//    getPerm(str, v, res);
//    itr = str->insert(itr, c);
//    v->pop_back();
//  }
//}

void getPerm(vector<char>* str, vector<bool>* choosen, int left, vector<char>* v, vector<vector<char>>* res) {
  if (left == 0) {
    res->push_back(*v);
    return;
  }
  int size = str->size();
  for (int i = 0; i < size; ++i) {
    if (choosen->at(i)) continue;
    choosen->at(i) = true;
    v->push_back(str->at(i));
    getPerm(str, choosen, left - 1, v, res);
    v->pop_back();
    choosen->at(i) = false;
  }
}
void doTest() {
  char* data = "abcd";
  vector<char> str, v;
  vector<vector<char>> res;
  int size = strlen(data);
  str.insert(str.begin(), data, data + strlen(data));
  vector<bool> choosen(size, false);
  getPerm(&str, &choosen, size, &v, &res);
  for (int i = 0; i < res.size(); ++i) {
    for (int j = 0; j < res[i].size(); ++j) {
      printf("%c", res[i][j]);
    }
    printf("\n");
  }
}
#endif  // Recursion_and_Dynamic_Programming_5

#if Q_N == Recursion_and_Dynamic_Programming_6
using std::vector;
using std::string;
void getParenthese(int left, int right, string* v, vector<string>* res) {
  if (left == 0 && right == 0) {
    res->push_back(*v);
    return;
  }
  assert(left <= right);
  if (left > 0) {
    v->push_back('(');
    getParenthese(left - 1, right, v, res);
    v->pop_back();
  }
  if (right > left) {
    v->push_back(')');
    getParenthese(left, right - 1, v, res);
    v->pop_back();
  }
}
void doTest() {
  vector<string> res;
  string v;
  int count = 4;
  getParenthese(count, count, &v, &res);
  for (int i = 0; i < res.size(); ++i) {
    for (int j = 0; j < res[i].size(); ++j) {
      printf("%c", res[i][j]);
    }
    printf("\n");
  }
}
#endif  // Recursion_and_Dynamic_Programming_6

#if Q_N == Recursion_and_Dynamic_Programming_7
void fill(int** image, int m, int n, int i, int j, int old_color, int new_color) {
  if (image == NULL || i < 0 || i >= m || j < 0 || j >= n || image[i][j] != old_color)
    return;
  image[i][j] = new_color;
  int dir[4][2] = {{1, 0}, { -1, 0}, {0, 1}, {0, -1}};
  for (int k = 0; k < 4; ++k) {
    fill(image, m, n, i + dir[k][0], j + dir[k][1], old_color, new_color);
  }
}
void doTest() {
  int data[] = {4, 2, 1, -1, 3, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1};
  int** image = new int *[4];
  for (int i = 0; i < 4; ++i) {
    image[i] = new int [4];
    for (int j = 0; j < 4; ++j) {
      image[i][j] = data[i * 4 + j];
    }
  }
  fill(image, 4, 4, 2, 0, image[2][0], 5);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      printf("%d ", image[i][j]);
    }
    printf("\n");
  }
}
#endif  // Recursion_and_Dynamic_Programming_7
#if Q_N == Recursion_and_Dynamic_Programming_8
void getNum(const int* val, int num_val, int k, int n, int& total_num) {
  if (val == NULL) return;
  if (n == 0) {
    ++total_num;
    return;
  }
  for (int i = k; i < num_val; ++i) {
    int count = n / val[i];
    for (int j = 1; j <= count; ++j) {
      getNum(val, num_val, i + 1, n - j * val[i], total_num);
    }
  }
}
int getNum(const int* val, int num_val, int k, int n) {
  if (val == NULL) return 0;
  if (n == 0) return 1;
  int num = 0;
  for (int i = k; i < num_val; ++i) {
    int count = n / val[i];
    for (int j = 1; j <= count; ++j) {
      num += getNum(val, num_val, i + 1, n - j * val[i]);
    }
  }
  return num;
}

void doTest() {
  int val[] = {25, 15, 5, 1};
  int n = 15;
  //getNum(val, 4, 0, n, total_num);
  int total_num = getNum(val, 4, 0, n);
  printf("%d\n", total_num);
}
#endif  // Recursion_and_Dynamic_Programming_8

#if Q_N == Recursion_and_Dynamic_Programming_9
void Queen(int* board, int row_index, int n, int& total_count) {
  if (row_index == n) {
    ++total_count;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (j != board[i]) {
          printf("O");
        } else {
          printf("*");
        }
      }
      printf("\n");
    }
    printf("\n");
    return;
  }
  for (int j = 0; j < n; ++j) {
    bool collapse = false;
    for (int i = 0; i < row_index; ++i) {
      if (board[i] == j || (row_index - i) == abs(j - board[i])) {
        collapse = true;
        break;
      }
    }
    if (!collapse) {
      board[row_index] = j;
      Queen(board, row_index + 1, n, total_count);
    }
  }
}
void doTest() {
  int total_count = 0;
  int n = 8;
  int* board = new int[n];
  Queen(board, 0, n, total_count);
  printf("%d\n", total_count);
  delete[] board;
}
#endif  // Recursion_and_Dynamic_Programming_9

#if Q_N == Recursion_and_Dynamic_Programming_10
using std::vector;
struct Box {
  int height, width, depth;
  bool canAbove(const Box& b) const {
    return height > b.height && width > b.width && depth > b.width;
  }
  //Box(int h, int w, int d) : height(h), width(w), depth(d) {}
};
bool cmpBox(const Box& b1, const Box& b2) {
  return b1.height > b2.height;
}

int buildStack(const vector<Box>& boxes, int pos, int* D) {
  int size = boxes.size();
  if (pos >= size) return 0;
  if (D[pos] > 0) return D[pos];
  int max_height = boxes[pos].height, height = boxes[pos].height;
  for (int i = pos + 1; i < size; ++i) {
    if (boxes[pos].canAbove(boxes[i])) {
      int temp_height = buildStack(boxes, i, D);
      if (temp_height + height > max_height) {
        max_height = temp_height + height;
      }
    }
  }
  D[pos] = max_height;
  return max_height;;
}
int buildStack(vector<Box>& boxes) {
  std::sort(boxes.begin(), boxes.end(), cmpBox);
  int size = boxes.size();
  int* D = new int[size];
  memset(D, 0, sizeof(int) * size);
  int max_height = 0;
  for (int i = 0; i < size; ++i) {
    int height = buildStack(boxes, i, D);
    if (height > max_height) {
      max_height = height;
    }
  }
  // backtrace
  int height = max_height;
  for (int i = 0; i < size; ++i) {
    if (D[i] == height) {
      printf("%d %d %d\n", boxes[i].height, boxes[i].width, boxes[i].depth);
      height -= boxes[i].height;
    }
  }
  return max_height;
}
void doTest() {
  Box data[] = {{3, 1, 0}, {4, 2, 3}, {4, 2, 1}, {7, 4, 2}, {8, 4, 7}, {10, 2, 5}};
  vector<Box> boxes;
  boxes.insert(boxes.end(), data, data + sizeof(data) / sizeof(Box));
  int height = buildStack(boxes);
  printf("%d\n", height);
}
#endif  // Recursion_and_Dynamic_Programming_10

#if Q_N == Recursion_and_Dynamic_Programming_11
using std::string;
using std::unordered_map;
int catalan(int n) {
  // catalan
  int64_t cn = 1, c2n = 1;
  for (int i = 1; i <= n; ++i) {
    c2n *= (2 * n - i + 1);
    cn *= i;
  }
  return (int)(c2n / cn / (n + 1));
}
int getNum(const string& exp, int s, int e, bool result, unordered_map<string, int>& dict) {
  if (s == e) {
    bool res = exp[s] - '0';
    return (res == result) ? 1 : 0;
  }
  if (!result)
    return catalan((e - s) / 2) - getNum(exp, s, e, true, dict);
  int count = 0;
  string sub_exp = exp.substr(s, e - s + 1);
  auto ptr = dict.find(sub_exp);
  if (ptr == dict.end()) {
    for (int i = s + 1; i < e; i += 2) {
      if (exp[i] == '&') {
        count += getNum(exp, s, i - 1, true, dict) * getNum(exp, i + 1, e, true, dict);
      } else if (exp[i] == '^') {
        count += getNum(exp, s, i - 1, true, dict) * getNum(exp, i + 1, e, false, dict);
        count += getNum(exp, s, i - 1, false, dict) * getNum(exp, i + 1, e, true, dict);
      } else if (exp[i] == '|') {
        count += getNum(exp, s, i - 1, true, dict) * getNum(exp, i + 1, e, true, dict);
        count += getNum(exp, s, i - 1, true, dict) * getNum(exp, i + 1, e, false, dict);
        count += getNum(exp, s, i - 1, false, dict) * getNum(exp, i + 1, e, true, dict);
      }
    }
    dict[sub_exp] = count;
  } else {
    count = ptr->second;
  }
  return count;
}
void doTest() {
  for (int i = 3; i < 10; ++i) {
    //printf("%d\n", catalan(i));
  }
  string exp = "1^0|0|1";
  unordered_map<string, int> dict;
  printf("%d\n", getNum(exp, 0, exp.size() - 1, false, dict));
}
#endif  // Recursion_and_Dynamic_Programming_11

#if Q_N == Scalability_and_Memory_Limits_4
class Bitset {
 public:
  Bitset(int size) {
    len_ = (size + 1) / 8;
    array_ = new char[len_];
    memset(array_, 0, len_);
  }
  ~Bitset() {
    delete[] array_;
    array_ = NULL;
  }
  void set(int pos) {
    assert(pos < len_ * 8);
    array_[pos >> 3] |= 1 << (pos & 0x7);
  }
  bool get(int pos) {
    assert(pos < len_ * 8);
    return (array_[pos >> 3] & (1 << (pos & 0x7))) != 0;
  }
 private:
  char* array_;
  char len_;
};

void getDup(int* A, int N, int max_size) {
  if (A == NULL || N <= 0) return;
  Bitset set(max_size);
  for (int i = 0; i < N; ++i) {
    int num = A[i];
    if (set.get(num - 1)) {
      printf("%d\n", num);
    } else {
      set.set(num - 1);
    }
  }
}
void doTest() {
  int A[] = {1, 2, 3, 4, 9, 6, 6, 8, 10, 100, 9};
  getDup(A, sizeof(A) / sizeof(int), 1000);
}
#endif  // Scalability_and_Memory_Limits_4
#if Q_N == Sorting_and_Searching_0
class Heap {
 public:
  Heap() {
    capacity_ = 16;
    n_ = 0;
    A_ = new int[capacity_];
  }
  Heap(int* data, int n) {
    n_ = n;
    capacity_ = 1;
    while (capacity_ <= n)
      capacity_ <<= 1;
    A_ = new int[capacity_];
    memcpy(A_, data, n * sizeof(int));
    makeHeap();
  }
  void Insert(int val);
  void RemoveMin();
  int Min() {
    assert(n_ > 0);
    return A_[0];
  }
 private:
  void makeHeap();
  void adjust(int i);

  int* A_;
  int n_, capacity_;
};

void Heap::adjust(int i) {
  while (i < (n_ - 1) / 2) {
    int min_i = i;
    if (A_[min_i] > A_[2 * i + 1])
      min_i = 2 * i + 1;
    if (2 * i + 2 < n_ && A_[min_i] > A_[2 * i + 2])
      min_i = 2 * i + 2;
    if (min_i != i) {
      std::swap(A_[i], A_[min_i]);
      i = min_i;
    } else {
      break;
    }
  }
}
void Heap::makeHeap() {
  for (int i = (n_ - 1) / 2 - 1; i >= 0; --i) {
    adjust(i);
  }
}
void Heap::RemoveMin() {
  A_[0] = A_[--n_];
  adjust(0);
}
void Heap::Insert(int val) {
  int i = n_;
  // assert(n < capacity);
  A_[n_++] = val;
  while (i > 0 && A_[i] < A_[(i - 1) / 2]) {
    std::swap(A_[i], A_[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}
void adjust(int* A, int i, int n) {
  while (i <= n / 2 - 1) {
    int max_i = i;
    if (2 * i + 1 < n && A[max_i] < A[2 * i + 1])
      max_i = 2 * i + 1;
    if (2 * i + 2 < n && A[max_i] < A[2 * i + 2])
      max_i = 2 * i + 2;
    if (max_i != i) {
      std::swap(A[i], A[max_i]);
      i = max_i;
    } else {
      break;
    }
  }
}

void heapSort(int* A, int n) {
  // make heap
  for (int i = n / 2 - 1; i >= 0; --i) {
    adjust(A, i, n);
  }
  // sort
  while (n > 0) {
    std::swap(A[n - 1], A[0]);
    --n;
    adjust(A, 0, n);
  }
}
void fillData(int* A, int n) {
  srand(time(NULL));
  for (int i = 0; i < n; ++i) {
    A[i] = rand();
  }
}
void doTest2() {
  int data[] = {3, 8, 9, 6, 1, 4, 5, 7, 2};
  int n = sizeof(data) / sizeof(int);
  Heap heap(data, n);
  printf("%d\n", heap.Min());
  heap.Insert(0);
  heap.RemoveMin();
  printf("%d\n", heap.Min());
  heapSort(data, n);
}
void quickSort(int* A, int s, int e) {
  if (s >= e) return;
  int i = s, j = e, key = A[i];
  while (i < j) {
    while (i < j && A[j] >= key)
      --j;
    A[i] = A[j];
    while (i < j && A[i] <= key)
      ++i;
    A[j] = A[i];
  }
  A[i] = key;
  quickSort(A, s, i - 1);
  quickSort(A, i + 1, e);
}
void quickSort2(int* A, int s, int e) {
  if (s >= e) return;
  int key = A[e], i = s - 1;
  for (int j = s; j <= e; ++j) {
    if (A[j] <= key) {
      ++i;
      std::swap(A[i], A[j]);
    }
  }
  quickSort2(A, s, i - 1);
  quickSort2(A, i + 1, e);
}
void mergeSort(int* A, int s, int e) {
}
void doTest() {
  const int N = 100;
  int data[N] = {0, 4, 5, 9, 8, 2, 3, 7, 1, 6}, data2[N];
  fillData(data, N);
  memcpy(data2, data, sizeof(data));
  //heapSort(data2, N);
  quickSort2(data2, 0, N - 1);
  std::sort(data, data + N);
  for (int i = 0; i < N; ++i) {
    assert(data[i] == data2[i]);
  }
}
#endif  // Sorting_and_Searching_0

#if Q_N == Sorting_and_Searching_1
void merge(int* A, int m, int* B, int n) {
  if (A == NULL || B == NULL) return;
  int i = m - 1, j = n - 1, k = m + n - 1;
  while (i >= 0 && j >= 0) {
    if (A[i] >= B[j]) {
      A[k--] = A[i--];
    } else {
      A[k--] = B[j--];
    }
  }
  while (j >= 0)
    A[k--] = A[j--];
}
void doTest() {
  int A[] = {1, 2, 9, 16, 31, 0, 0, 0, 0};
  int B[] = {6, 12, 17};
  merge(A, 5, B, 3);
  for (int i = 0; i < sizeof(A) / sizeof(int); ++i) {
    printf("%d ", A[i]);
  }
}
#endif  // Sorting_and_Searching_1

#if Q_N == Sorting_and_Searching_2
using std::vector;
using std::string;
using std::unordered_map;
bool isAnagram(const string& s1, const string& s2) {
  if (s1.size() != s2.size()) return false;
  int i = 0, j = s1.size() - 1;
  while (i < j) {
    if (s1[i] != s2[j]) return false;
    ++i, --j;
  }
  return true;
}

void sortAnagram(vector<string>& v) {
  int i = 0, size = v.size();
  for (int i = 0; i < size; ++i) {
    for (int j = i + 1; j < size; ++j) {
      if (isAnagram(v[i], v[j])) {
        std::swap(v[i + 1], v[j]);
        break;
      }
    }
  }
}
string sortString(const string& s) {
  string new_s = s;
  std::sort(new_s.begin(), new_s.end());
  return new_s;
}

void sort(vector<string>& v) {
  int size = v.size();
  if (size <= 2) return;
  unordered_map<string, vector<string>> dict;
  for (int i = 0; i < size; ++i) {
    dict[sortString(v[i])].push_back(v[i]);
  }
  int pos = 0;
  for (auto ptr = dict.begin(); ptr != dict.end(); ++ptr) {
    for (auto ptr2 = ptr->second.begin(); ptr2 != ptr->second.end(); ++ptr2) {
      v[pos++] = *ptr2;
    }
  }
}
void quickSort(int* A, int s, int e) {
  if (A == NULL || s >= e) return;
  int x = A[e], i = s - 1;
  for (int j = s; j <= e; ++j) {
    if (A[j] <= x) {
      ++i;
      if (i != j)
        std::swap(A[i], A[j]);
    }
  }
  quickSort(A, s, i - 1);
  quickSort(A, i + 1, e);
}
void doTest() {
  char* data[] = {"ab", "ba", "ab", "ca", "cde", "ac", "de", "ef", "ef", "dec", "cat", "tac"};
  vector<string> v;
  v.insert(v.end(), data, data + sizeof(data) / sizeof(char*));
  //sortAnagram(v);
  sort(v);
  for (int i = 0; i < v.size(); ++i) {
    printf("%s ", v[i].c_str());
  }
  printf("\n");
}
#endif  // Sorting_and_Searching_2

#if Q_N == Sorting_and_Searching_3
int binarySeach(int* A, int n, int target) {
  if (A == NULL || n <= 0) return -1;
  int lo = 0, hi = n - 1;
  while (lo <= hi) {
    int mid = lo + ((hi - lo) >> 1);
    if (A[mid] == target) return mid;
    if (A[mid] > A[lo]) {  // increase from lo to mid
      if (target >= A[lo] && target < A[mid]) {
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    } else if (A[mid] < A[lo]) {
      if (target > A[mid] && target <= A[hi]) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    } else {
      ++lo;
    }
  }
  return -1;
}
void doTest() {
  int A[] = {14, 16, 16, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14, 14};
  int size = sizeof(A) / sizeof(int);
  for (int i = 0; i < size; ++i) {
    int pos = binarySeach(A, size, A[i]);
    printf("%d ", pos);
  }
  int pos = binarySeach(A, size, 100);
  printf("%d ", pos);
  printf("\n");
}
#endif  // Sorting_and_Searching_3

#if Q_N == Sorting_and_Searching_5
using std::string;
using std::vector;
int binarySeach(vector<string>& v, const string& target) {
  int size = v.size();
  if (size == 0 || target.size() == 0) return -1;
  int lo = 0, hi = size - 1;
  while (lo <= hi) {
    while (v[lo] == "" && lo <= hi) ++lo;
    while (v[hi] == "" && hi >= lo) --hi;
    if (lo > hi) return -1;
    int mid = lo + ((hi - lo) >> 1);
    int i = mid;
    while (v[i] == "" && i <= hi) ++i;
    if (i > hi) {
      hi = mid - 1;
    } else {
      if (v[i] == target) {
        return i;
      }
      if (v[i] < target) {
        lo = i + 1;
      } else {
        hi = i - 1;
      }
    }
  }
  return -1;
}
void doTest() {
  char* data[] = {"at", "", "", "", "ball", "", "", "car", "", "", "dad", ""};
  vector<string> v;
  v.insert(v.end(), data, data + sizeof(data) / sizeof(char*));
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] != "") {
      int pos = binarySeach(v, v[i]);
      printf("%d ", pos);
    }
  }
  int pos = binarySeach(v, "");
  printf("%d ", pos);
  printf("\n");
}
#endif  // Sorting_and_Searching_5

#if Q_N == Sorting_and_Searching_6
using std::vector;
void findInMatrix(int** matrix, int M, int N, int target, int& row, int& col) {
  row = -1, col = -1;
  if (matrix == NULL || M <= 0 || N <= 0) {
    return;
  }
  int lo = 0, hi = M - 1;
  while (lo <= hi) {
    int mid = lo + ((hi - lo) >> 1);
    if (matrix[mid][0] == target) {
      row = mid, col = 0;
      return;
    }
    if (target < matrix[mid][0]) {
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  row = hi;
  if (hi < 0) return;
  lo = 0, hi = N - 1;
  while (lo <= hi) {
    int mid = lo + ((hi - lo) >> 1);
    if (matrix[row][mid] == target) {
      col = mid;
      return;
    }
    if (target < matrix[row][mid]) {
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
}
struct Coord {
  int row, col;
  Coord(int r, int c) : row(r), col(c) {}
  static Coord getMiddle(const Coord& lo, const Coord& hi) {
    return Coord(lo.row + ((hi.row - lo.row) >> 1), lo.col + ((hi.col - lo.col) >> 1));
  }
  bool IsLE(const Coord& c) const {
    return row <= c.row && col <= c.col;
  }
  bool IsInRange(int m, int n) const {
    return row >= 0 && row < m && col >= 0 && col < n;
  }
  bool IsValid() const {
    return row >= 0 && col >= 0;
  }
};
int m = matrix.size(), n = m > 0 ? matrix[0].size() : 0;
if (!start.IsInRange(m, n) || !end.IsInRange(m, n) || !start.IsLE(end))
  return Coord(-1, -1);
if (matrix[start.row][start.col] == target)
  return start;
int len = std::min(end.col - start.col, end.row - start.row);
Coord lo = start, hi(lo.row + len, lo.col + len);
while (lo.IsLE(hi)) {
  Coord mid = Coord::getMiddle(lo, hi);
  if (target > matrix[mid.row][mid.col]) {
    lo.row = mid.row + 1;
    lo.col = mid.col + 1;
  } else if (target < matrix[mid.row][mid.col]) {
    hi.row = mid.row - 1;
    hi.col = mid.col - 1;
  } else {
    return mid;
  }
}
Coord res = FindInMatrix(matrix, Coord(lo.row, start.col), Coord(end.row, hi.col), target);
if (!res.IsValid())
  res = FindInMatrix(matrix, Coord(start.row, lo.col), Coord(hi.row, end.col), target);
return res;
}
void doTest() {
  //int data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 16};
  int data[] = {2, 4, 9, 21, 3, 5, 10, 23, 5, 7, 11, 24, 7, 8, 13, 27};
  vector<vector<int>> matrix(4, vector<int>(4, 0));
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      matrix[i][j] = data[i * 4 + j];
    }
  }
  int size = sizeof(data) / sizeof(int);
  for (int i = 0; i < size; ++i) {
    Coord res = FindInMatrix(matrix, Coord(0, 0), Coord(3, 3), data[i]);
    printf("%d %d\n", res.row, res.col);
  }
  printf("\n");
}
#endif  // Sorting_and_Searching_6

#if Q_N == Sorting_and_Searching_7
using std::vector;
class Person {
 public:
  int h, w;
  bool canAbove(const Person& p) const {
    return h < p.h && w < p.w;
  }
};
bool cmpPerson(const Person& p1, const Person& p2) {
  return p1.h < p2.h;
}
int maxHeight(const vector<Person>& ps, int pos, int* D) {
  if (D[pos] > 0) return D[pos];
  int max_height = ps[pos].h;
  for (int i = pos - 1; i >= 0; --i) {
    if (ps[i].canAbove(ps[pos])) {
      int height = maxHeight(ps, i, D) + ps[pos].h;
      if (height > max_height)
        max_height = height;
    }
  }
  D[pos] = max_height;
  return max_height;
}

int maxHeight(vector<Person>& ps) {
  if (ps.size() <= 0) return 0;
  int size = ps.size(), max_height = 0;
  int* D = new int[size];
  memset(D, 0, size * sizeof(int));
  std::sort(ps.begin(), ps.end(), cmpPerson);
  for (int i = size - 1; i >= 0; --i) {
    int height = maxHeight(ps, i, D);
    if (height > max_height)
      max_height = height;
  }
  for (int i = size - 1; i >= 0; --i) {
    if (max_height == D[i]) {
      printf("%d %d\n", ps[i].h, ps[i].w);
      max_height -= ps[i].h;
    }
  }
}
void doTest() {
  Person data[] = {{65 , 100}, {70, 150}, {56, 90}, {75, 190}, {60, 95}, {68, 110}};
  vector<Person> ps;
  ps.insert(ps.end(), data, data + sizeof(data) / sizeof(Person));
  int height = maxHeight(ps);
}
#endif  // Sorting_and_Searching_7

#if Q_N == Sorting_and_Searching_8
struct TreeNode {
  TreeNode* left, *right;
  int val, left_size;
  TreeNode(int val) : left(NULL), right(NULL), val(val), left_size(0) {}
};

TreeNode* root = NULL;
void track(int x) {
  if (root == NULL) {
    root = new TreeNode(x);
    return;
  }
  TreeNode* n = root;
  while (n != NULL) {
    if (x < n->val) {
      ++n->left_size;
      if (n->left != NULL) {
        n = n->left;
      } else {
        n->left = new TreeNode(x);
        break;
      }
    } else if (x > n->val) {
      if (n->right != NULL) {
        n = n->right;
      } else {
        n->right = new TreeNode(x);
        break;
      }
    } else {
      ++n->left_size;
      break;
    }
  }
}
int getRankNumber(int x) {
  TreeNode* n = root;
  int rank = 0;
  while (n != NULL) {
    if (x < n->val) {
      n = n->left;
    } else if (x > n->val) {
      rank += n->left_size + 1;
      n = n->right;
    } else {
      rank += n->left_size;
      break;
    }
  }
  if (n == NULL)
    rank = -1;
  return rank;
}

void doTest() {
  int data[] = {5, 1 , 4, 4, 5, 9, 7, 13, 3};
  int size = sizeof(data) / sizeof(int);
  for (int i = 0; i < size; ++i) {
    track(data[i]);
  }
  std::sort(data, data + size);
  for (int i = 0; i < size; ++i) {
    printf("%d ", data[i]);
  }
  printf("\n");
  for (int i = 0; i < size; ++i) {
    int rank = getRankNumber(data[i]);
    printf("%d ", rank);
  }
  printf("\n");
}
#endif  // Sorting_and_Searching_8

#if Q_N == Sorting_and_Searching_9
using std::vector;
int LIS_old(const vector<int>& v) {
  int size = v.size();
  int* D = new int[size];
  int* P = new int[size];
  int max_len = 0, max_i = -1;
  D[0] = 1, P[0] = -1;
  for (int i = 1; i < size; ++i) {
    for (int j = 0; j < i; ++j) {
      if (v[i] >= v[j]) {
        if (D[j] + 1 > D[i]) {
          D[i] = D[j] + 1;
          P[i] = j;
        }
      }
    }
  }
  int temp_len = max_len;
  for (int i = 0; i < size; ++i) {
    if (D[i] > max_len) {
      max_i = i;
      max_len = D[i];
    }
  }
  while (max_i >= 0) {
    printf("%d ", v[max_i]);
    max_i = P[max_i];
  }
  printf("\n");
  delete[] D, delete[] P;
  return temp_len;
}
//int LIS(const vector<int> &v) {
//  int size = v.size(), max_len = 1;
//  // M[i] is the index of the last element of the sequence whose length is i
//  int *M = new int[size];
//  // P[i] is the index of the previous element of i in the sequence, which is used to print the whole sequence
//  int *P = new int[size];
//  M[0] = 0; P[0] = -1;
//  for (int i = 1; i < size; ++i) {
//    if (v[i] > v[M[max_len - 1]]) {
//      M[max_len] = i;
//      P[i] = M[max_len - 1];
//      ++max_len;
//      continue;
//    }
//    // Find the position to insert i using binary search
//    int lo = 0, hi = max_len - 1;
//    while (lo <= hi) {
//      int mid = lo + ((hi - lo) >> 1);
//      if (v[i] < v[M[mid]]) {
//        hi = mid - 1;
//      } else if (v[i] > v[M[mid]]) {
//        lo = mid + 1;
//      } else {
//        lo = mid;
//        break;
//      }
//    }
//    P[i] = P[M[lo]];  // Modify the previous pointer
//    M[lo] = i;
//  }
//  // Print the whole subsequence
//  int i = M[max_len - 1];
//  while (i >= 0) {
//    printf("%d ", v[i]);
//    i = P[i];
//  }
//  printf("\n");
//  delete[] M, delete[] P;
//  return max_len;
//}

int LIS(const vector<int>& v) {
  int size = v.size();
  if (size <= 0) return 0;
  int* M = new int[size], *P = new int[size];
  P[0] = -1;
  M[0] = 0;
  int max_len = 1;
  for (int i = 1; i < size; ++i) {
    if (v[i] > v[M[max_len - 1]]) {
      M[max_len] = i;
      P[i] = M[max_len - 1];
      ++max_len;
      continue;
    }
    int lo = 0, hi = max_len - 1;
    while (lo <= hi) {
      int mid = lo + ((hi - lo) >> 1);
      if (v[i] < v[M[mid]]) {
        hi = mid - 1;
      } else if (v[i] > v[M[mid]]) {
        lo = mid + 1;
      } else {
        lo = mid;
        break;
      }
    }
    P[i] = P[M[lo]];
    M[lo] = i;
  }
  // Print the sequence
  int i = M[max_len - 1];
  while (i >= 0) {
    printf("%d ", v[i]);
    i = P[i];
  }
  delete[] M, delete[] P;
  return max_len;
}
void doTest() {
  int data[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
  vector<int> v;
  v.insert(v.end(), data, data + sizeof(data) / sizeof(int));
  LIS(v);
}
#endif  // Sorting_and_Searching_9
#if Q_N == C_and_Cpp_1
using std::vector;
using std::string;
vector<string> readLines(const char* file_name, int k) {
  vector<string> lines;
  FILE* fp = fopen(file_name, "rb");
  if (fp == NULL) return lines;
  const int BLOCK_SIZE = 3;
  fseek(fp, 0, SEEK_END);
  size_t pos = ftell(fp);
  char* last_cr, buf[BLOCK_SIZE];
  string last_line;
  while (lines.size() < k) {
    int size = pos > BLOCK_SIZE ? BLOCK_SIZE : pos;
    pos -= size;
    fseek(fp, pos, SEEK_SET);
    fread(buf, 1, size, fp);
    last_cr = buf + size;
    for (char* c = buf + size - 1; c >= buf; --c) {
      if (*c == '\r') {
        string line(c + 1, last_cr);
        line.append(last_line);
        last_line.clear();
        last_cr = c;
        lines.push_back(line);
        if (lines.size() >= k) break;
      }
    }
    last_line.insert(last_line.begin(), buf, last_cr);
    if (pos == 0) break;
  }
  if (last_line.size() > 0 && lines.size() < k)
    lines.push_back(last_line);
  std::reverse(lines.begin(), lines.end());
  fclose(fp);
  return lines;
}

void readLastLines(const char* file_name, int k) {
  if (file_name == NULL || k <= 0) return;
  FILE* fp = fopen(file_name, "rb");
  if (fp == NULL) return;
  int count = 0;
  const int MAX_LEN = 10240;
  char buf[MAX_LEN];
  vector<string> lines(k, "");
  while (fgets(buf, MAX_LEN, fp)) {
    lines[count % k] = string(buf);
    ++count;
  }
  int offset = count > k ? count % k : 0;
  count = std::min(count, k);
  for (int i = 0; i < count; ++i) {
    printf("%s\n", lines[(i + offset) % k].c_str());
  }
}

void readLines2(const char* file_name, int k) {
  if (file_name == NULL || k <= 0) return;
  FILE* fp = fopen(file_name, "rb");
  if (fp == NULL) return;
  vector<string> lines(k, "");
  int max_len = 1024, count = 0, offset = 0;
  char* buf = new char[max_len + 1];
  while (fgets(buf, max_len, fp)) {
    lines[count % k] = string(buf);
    ++count;
  }
  offset = count > k ? count % k : 0;
  for (int i = 0; i < std::min(k, count); ++i) {
    printf("%s\n", lines[(i + offset) % k].c_str());
  }
  delete[] buf;
  fclose(fp);
}
class A {
 public:
  virtual void print() {
    printf("A\n");
  }
};

class B : public A {
 public:
  virtual void print() {
    printf("B\n");
  }
};

void doTest() {
  B* b = new B;
  b->print();
  const char* file_name = "data/main.cc";
  readLines2(file_name, 10);
  //return;
  //vector<string> lines = readLines(file_name, 10);
  //for(auto ptr = lines.begin(); ptr != lines.end(); ++ptr) {
  //  //puts(ptr->c_str());
  //  printf("%s", ptr->c_str());
  //}
}

#endif  // C_and_Cpp_1

#if Q_N == C_and_Cpp_7
using std::unordered_map;
struct RandomListNode {
  int label;
  RandomListNode* next, *random;
  RandomListNode(int label) : label(label), next(NULL), random(NULL) {}
};
RandomListNode* copyRandomList(RandomListNode* head) {
  // IMPORTANT: Please reset any member data you declared, as
  // the same Solution instance will be reused for each test case.
  unordered_map<RandomListNode*, RandomListNode*> dict;
  return copyRandomList(head, dict);
}
RandomListNode* copyRandomList(RandomListNode* head, unordered_map<RandomListNode*, RandomListNode*>& dict) {
  if (head == NULL) return NULL;
  auto ptr = dict.find(head);
  if (ptr != dict.end()) {
    return ptr->second;
  }
  RandomListNode* new_head = new RandomListNode(head->label);
  dict[head] = new_head;
  new_head->next = copyRandomList(head->next, dict);
  new_head->random = copyRandomList(head->random, dict);
  return new_head;
}
void doTest() {
}
#endif  // C_and_Cpp_7

#if Q_N == C_and_Cpp_8
template <class T>
class SmartPointer {
 public:
  SmartPointer(T* pointer) : pointer(pointer) {
    ref_count = new int;
    *ref_count = 1;
  }
  SmartPointer(const SmartPointer& sp) {
    pointer = sp.pointer;
    ref_count = sp.ref_count;
    ++(*ref_count);
  }
  ~SmartPointer() {
    decrease();
  }
  SmartPointer& operator=(const SmartPointer& rhs) {
    if (this == &rhs)
      return *this;
    if (*ref_count > 0)
      decrease();
    pointer = rhs.pointer;
    ref_count = rhs.ref_count;
    ++(*ref_count);
    return *this;
  }
  T* val() {
    return pointer;
  }
  int refCount() {
    return *ref_count;
  }
 private:
  void decrease() {
    --(*ref_count);
    if (*ref_count == 0) {
      delete pointer;
      delete ref_count;
      pointer = NULL;
      ref_count = NULL;
    }
  }
  T* pointer;
  int* ref_count;
};
void constTest() {
  class A {
   public:
    A(int a) {
      val = &a;
    }
    int* val;
    void setVal(int v) {
    }
  };
  A a(3);
  printf("%d\n", *a.val);
  const A b = a;
}
void doTest() {
  SmartPointer<int> pt(new int);
  SmartPointer<int> pt2 = pt;
  //SmartPointer<int> pt3(pt);
  *pt2.val() = 3;
  printf("%d\n", *pt.val());
  printf("%d\n", pt.refCount());
}
#endif  // C_and_Cpp_8
#if Q_N == C_and_Cpp_9
void* myAlloc(int size, int b) {
  if (size <= 0 || (b & (b - 1)) != 0) return NULL;
  void* p = malloc(size + b - 1 + sizeof(void*));
  void* q = (void*)(((size_t)p + b - 1 + sizeof(void*)) & (~(b - 1)));
  ((void**)q)[-1] = p;
  return q;
}

void myFree(void* q) {
  if (q == NULL) return;
  void* p = ((void**)q)[-1];
  free(p);
}

void doTest() {
  void* p = myAlloc(19, 16);
  printf("%p\n", p);
  myFree(p);
}
#endif  // C_and_Cpp_9

#if Q_N == C_and_Cpp_10
template<class T>
T** mallocArray(int m, int n) {
  if (m <= 0 || n <= 0) return NULL;
  int offset = m * sizeof(T*);
  int size = offset + sizeof(T) * m * n;
  T** p = (T**)malloc(size);
  if (p == NULL) return NULL;
  for (int i = 0; i < m; ++i) {
    p[i] = (T*)((size_t)p + offset + sizeof(T) * n * i);
  }
  return p;
}
template<class T>
void freeArray(T** p) {
  free(p);
}
void doTest() {
  int m = 3, n = 4;
  auto A = mallocArray<char>(3, 4);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      A[i][j] = i + j;
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
  freeArray(A);
}
#endif  // C_and_Cpp_10

#if Q_N == Threads_and_Locks_0
#include <stdio.h>
#include "structures.h"


std::mutex mtx;
void print_thread_id(int id) {
  //mtx.lock();
  //printf("%d\n", id);
  std::chrono::milliseconds dur(500);
  std::this_thread::sleep_for(dur);
  printf("%d_2\n", id);
  //mtx.unlock();
}

void doTest() {
  std::thread threads[10];
  for (int i = 0; i < 10; ++i) {
    threads[i] = std::thread(print_thread_id, i);
  }
for (auto & th : threads)
    th.join();
}
#endif  // Threads_and_Locks_0

#if Q_N == Threads_and_Locks_3
void doTest() {
  // TO-DO Graph traverse!
}
#endif  // Threads_and_Locks_3

#if Q_N == Threads_and_Locks_5
#include "structures.h"
class Foo {
 public:
  Foo() : m1(1), m2(1), m3(1) {
    m1.wait();
    m2.wait();
    m3.wait();
  }
  void first() {
    std::chrono::milliseconds dur(100);
    std::this_thread::sleep_for(dur);
    printf("first\n");
    m1.notify();
  }
  void second() {
    std::chrono::milliseconds dur(100);
    std::this_thread::sleep_for(dur);
    m1.wait();
    m1.notify();
    printf("second\n");
    m2.notify();
  }
  void third() {
    std::chrono::milliseconds dur(100);
    std::this_thread::sleep_for(dur);
    m1.wait();
    m1.notify();
    m2.wait();
    m2.notify();
    printf("third\n");
    m3.notify();
  }
 private:
  semaphore m1, m2, m3;
};
void doWork(int id, void* f) {
  if (id == 0) {
    ((Foo*)f)->first();
  } else if (id == 1) {
    ((Foo*)f)->second();
    //f.second();
  } else {
    ((Foo*)f)->third();
    //f.third();
  }
}
void doWork2(int id, Foo& f) {
  if (id == 0) {
    f.first();
  } else if (id == 1) {
    f.second();
  } else {
    f.third();
  }
}
void doTest() {
  std::thread threads[3];
  Foo f;
  for (int i = 0; i < 3; ++i) {
    //threads[i] = std::thread(doWork2, i, f);
    threads[i] = std::thread(doWork2, i, std::ref(f));
  }
  for (int i = 0; i < 3; ++i) {
    threads[i].join();
  }
  semaphore s(1);
  s.wait();
  s.notify();
  printf("ab\n");
}
#endif  // Threads_and_Locks_5

#if Q_N == Moderate_3
//int getTralingZero(int n) {
//  int num_zeros = 0;
//  int prod = 1;
//  for (int i = 2; i <= n; ++i) {
//    prod *= i;
//    bool trailing = true;
//    while (prod >= 10) {
//      int r = prod % 10;
//      prod /= 10;
//      if (r == 0 && trailing) {
//        ++num_zeros;
//      } else {
//        trailing = false;
//      }
//    }
//  }
//  return num_zeros;
//}
int getNumOfFive(int n) {
  if (n <= 0) return 0;
  int num = 0;
  while (n > 0 && n % 5 == 0) {
    ++num;
    n /= 5;
  }
  return num;
}
int getTralingZero(int n) {
  int num_zeros = 0;
  while (n > 0) {
    num_zeros += n / 5;
    n = n / 5;
  }
  return num_zeros;
}
void doTest() {
  printf("%d\n", getTralingZero(202));
}
#endif  // Moderate_3

#if Q_N == Moderate_4
int sign(int n) {
  return (unsigned)(n) >> 31;
}
int getMax(int a, int b) {
  int A[4][2] = {{a, b}, {a, a}, {a, b}, {a, b}};
  int i = sign(a) << 1 | sign(b);
  int j = sign(a - b);
  return A[i][j];
}
void intTest() {
  int a = -1, b = -1 << 31, c = 1 << 31;
  unsigned a2 = -1, b2 = -1 << 31, c2 = 1 << 31;
  printf("a=%x, b=%x, c=%x", a, b, c);
  printf("a=%x, b=%x, c=%x", a2, b2, c2);
}
void doTest() {
  int a[2][4] = {};
  intTest();
  srand(time(NULL));
  for (int i = 0; i < 10; ++i) {
    int a = INT_MAX, b = -rand();
    int c = getMax(a, b);
    printf("a:%d, b:%d, max:%d\n", a, b, c);
    assert(c >= a && c >= b);
  }
}
#endif  // Moderate_4

#if Q_N == Moderate_5
int getIdx(char c) {
  int res = -1;
  switch (c) {
    case 'R':
      res = 0;
      break;
    case 'G':
      res = 1;
      break;
    case 'Y':
      res = 2;
      break;
    case 'B':
      res = 3;
      break;
  }
  return res;
}
void getHit(std::string real, std::string guess) {
  if (real.size() != guess.size()) return;
  int hit = 0, p_hit = 0;
  int count[2][4] = {};
  for (int i = 0; i < 4; ++i) {
    if (real[i] == guess[i]) {
      ++hit;
    } else {
      ++count[0][getIdx(real[i])];
      ++count[1][getIdx(guess[i])];
    }
  }
  for (int i = 0; i < 4; ++i) {
    p_hit += std::min(count[0][i], count[1][i]);
  }
  printf("hit:%d, pseudo hit:%d\n", hit, p_hit);
}
void doTest() {
  std::string real = "RGBB", guess = "GYGB";
  getHit(real, guess);
}
#endif  // Moderate_5

#if Q_N == Moderate_6
using std::vector;
struct Interval {
  int s, e;
  Interval(int s, int e) : s(s), e(e) {}
};
Interval getInterval(vector<int> v) {
  int size = v.size();
  if (size <= 1) return Interval(0, 0);
  int lo = 0, hi = 0;
  vector<int> maxs(size), mins(size);
  int max_val = INT_MIN, min_val = INT_MAX;
  for (int i = 0; i < size; ++i) {
    max_val = std::max(max_val, v[i]);
    min_val = std::min(min_val, v[size - i - 1]);
    maxs[i] = max_val;
    mins[size - i - 1] = min_val;
  }
  for (int i = 0; i < size; ++i) {
    if (lo == 0 && v[i] != mins[i]) {
      lo = i;
    }
    if (hi == 0 && v[size - i - 1] != maxs[size - i - 1]) {
      hi = size - i - 1;
    }
  }
  return Interval(lo, hi);
}
void printMin(const vector<int>& v) {
  int size = v.size();
  if (size <= 0) return;
  vector<int> S;
  for (int i = 0; i < size; ++i) {
    while (!S.empty() && v[S.back()] > v[i])
      S.pop_back();
    if (!S.empty()) {
      printf("%d:%d, %d:%d\n", i, v[i], S.back(), v[S.back()]);
    }
    S.push_back(i);
  }
}
void doTest() {
  int data[] = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19};
  vector<int> v;
  v.insert(v.end(), data, data + sizeof(data) / sizeof(int));
  printMin(v);
  auto itvl = getInterval(v);
  printf("s:%d, e:%d\n", itvl.s, itvl.e);
}
#endif  // Moderate_6

#if Q_N == Moderate_7
using std::string;
using std::vector;
string getDes(int64_t n) {
  string digit[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
                   };
  string tens[] = {"", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};
  string des[] = {"", "thousand", "million", "billion"};
  string res;
  if (n == 0) return digit[0];
  if (n < 0) return "negtive " + getDes(-n);
  if (n < 1000) {
    int hundred = n / 100, ten = (n % 100) / 10, one = n % 10;
    if (hundred > 0) {
      res.append(digit[hundred] + " hundred");
    }
    if (n % 100 > 0) {
      if (hundred > 0)  res.append(" ");
      if (n % 100 < 20) {
        res.append(digit[n % 100]);
      } else {
        res.append(tens[ten]);
        if (one > 0)
          res.append(" " + digit[one]);
      }
    }
    return res;
  }
  vector<int> v;
  while (n > 0) {
    v.push_back(n % 1000);
    n = n / 1000;
  }
  for (int i = v.size() - 1; i >= 0; --i) {
    if (v[i] == 0) continue;
    string s = getDes(v[i]);
    res.append(s + " " + des[i]);
    if (i > 0 && v[0] > 0)
      res.append(", ");
  }
  return res;
}
void doTest() {
  int cases[] = {0, 1, 8, 10, 100, 114, 1000, 1010, 1019, 30000001, -1234119123, INT_MIN};
  int size = sizeof(cases) / sizeof(int);
  for (int i = 0; i < size; ++i) {
    string s = getDes(cases[i]);
    printf("%d: %s\n", cases[i], s.c_str());
  }
}
#endif  // Moderate_7

#if Q_N == Moderate_8
int getMaxSum(const std::vector<int>& v) {
  int size = v.size();
  if (size == 0) return 0;
  int max_sum = INT_MIN, sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += v[i];
    max_sum = std::max(sum, max_sum);
    if (sum < 0) sum = 0;
  }
  return max_sum;
}
void doTest() {
  int data[] = {2, 3, -8, -1, 2, 4, -2, 3};
  std::vector<int> v;
  v.insert(v.end(), data, data + sizeof(data) / sizeof(int));
  int sum = getMaxSum(v);
  printf("%d\n", sum);
}
#endif  // Moderate_8

#if Q_N == Moderate_9
void doTest() {
}
#endif  // Moderate_9

#if Q_N == Moderate_11
int rand5() {
  return rand() % 5;
}
int rand7() {
  while (true) {
    int n = rand5() * 5 + rand5();
    if (n < 21) {
      return n % 7;
    }
  }
}
void doTest() {
  int count[7] = {0};
  for (int i = 0; i < 7 * 10240; ++i) {
    int n = rand7();
    ++count[n];
  }
  for (int i = 0; i < 7; ++i) {
    printf("%d:%d\n", i, count[i]);
  }
}
#endif  // Moderate_11

#if Q_N == Moderate_12
using std::vector;
vector<std::pair<int, int>> getPairs(const vector<int>& data, int target) {
  std::unordered_map<int, int> dict;
  vector<std::pair<int, int>> res;
  for (auto ptr = data.begin(); ptr != data.end(); ++ptr) {
    ++dict[*ptr];
  }
  for (auto ptr = dict.begin(); ptr != dict.end(); ++ptr) {
    auto ptr2 = dict.find(target - ptr->first);
    if (ptr2 != dict.end() && ptr->first <= ptr2->first && (ptr2->first != ptr->first || ptr->second > 1)) {
      res.push_back(std::pair<int, int>(ptr->first, ptr2->first));
    }
  }
  return res;
}
void doTest() {
  int data[] = {1, 7, 3, 11, 9, 10, 10};
  int target = 20;
  vector<int> v;
  v.insert(v.end(), data, data + sizeof(data) / sizeof(int));
  auto res = getPairs(v, target);
  for (int i = 0; i < res.size(); ++i) {
    printf("%d, %d\n", res[i].first, res[i].second);
  }
}
#endif  // Moderate_12

#if Q_N == Moderate_13
#include "structures.h"
void convert(TreeNode* root, TreeNode*& min_node, TreeNode*& max_node) {
  min_node = root, max_node = root;
  if (root == NULL) return;
  if (root->left != NULL) {
    TreeNode* tmpMax;
    convert(root->left, min_node, tmpMax);
    tmpMax->right = root;
    root->left = tmpMax;
  }
  if (root->right != NULL) {
    TreeNode* tmpMin;
    convert(root->right, tmpMin, max_node);
    tmpMin->left = root;
    root->right = tmpMin;
  }
}

void doTest() {
  std::string str = "7,5,9,4,#,8,10";
  TreeNode* root = TreeNode::parseTreeNode(str);
  TreeNode* min_node, *max_node;
  convert(root, min_node, max_node);
  while (min_node != NULL) {
    printf("%d ", min_node->val);
    min_node = min_node->right;
  }
  printf("\n");
  while (max_node != NULL) {
    printf("%d ", max_node->val);
    max_node = max_node->left;
  }
}
#endif  // Moderate_13

#if Q_N == Moderate_14

#include <algorithm>
using std::vector;
using std::string;
using std::unordered_map;
using std::map;
using std::set;
using std::unordered_set;
void punc(const string& sen, int start, int& min_left,
          unordered_map<string, string>& dict, vector<string>& v,
vector<string>& res) {
  if (min_left == 0) return;
  int size = sen.size();
  if (size - start < min_left) {
    res = v;
    min_left = size - start;
  }
  for (int i = start; i < size; ++i) {
    string s = sen.substr(start, i - start + 1);
    auto ptr = dict.find(s);
    if (ptr != dict.end()) {
      v.push_back(ptr->second);
      punc(sen, i + 1, min_left, dict, v, res);
      v.pop_back();
    }
  }
}
void punc(const string& sen, int start, int& min_left,
          map<string, string>& dict, vector<string>& v,
vector<string>& res, unordered_set<int>& cache) {
  if (min_left == 0) return;
  int size = sen.size();
  if (size - start < min_left) {
    res = v;
    min_left = size - start;
  }
  if (cache.find(start) != cache.end()) return;
  int tmp_min = min_left;
  for (int i = start; i < size; ++i) {
    string s = sen.substr(start, i - start + 1);
    auto ptr = dict.find(s);
    if (ptr == dict.end()) {
      auto ptr2 = dict.lower_bound(s);
      if (ptr2 == dict.end() || ptr2->first.compare(0, s.size(), s) != 0) break;
      else continue;
    }
    v.push_back(ptr->second);
    punc(sen, i + 1, min_left, dict, v, res, cache);
    v.pop_back();
  }
  cache.insert(start);
}
void doTest() {
  string words[] = {"AI", "al", "lis", "All", "already", "is", "well", "swell"};
  int word_count = sizeof(words) / sizeof(string), min_left = INT_MAX;
  map<string, string> dict;
  string sen = "alliswelllisb";
  for (int i = 0; i < word_count; ++i) {
    string lower = words[i];
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    dict[lower] = words[i];
  }
  vector<string> v, res;
  unordered_set<int> cache;
  punc(sen, 0, min_left, dict, v, res, cache);
  for (auto ptr = res.begin(); ptr != res.end(); ++ptr) {
    printf("%s ", ptr->c_str());
  }
}
void doTest_old() {
  string words[] = {"al", "all", "is", "well", "swell"};
  std::unordered_map<string, string> dict;
  string sen = "alliswell";
  int word_count = sizeof(words) / sizeof(string), min_left = INT_MAX;
  for (int i = 0; i < word_count; ++i) {
    string lower = words[i];
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    dict[lower] = words[i];
  }
  vector<string> v, res;
  punc(sen, 0, min_left, dict, v, res);
  for (auto ptr = res.begin(); ptr != res.end(); ++ptr) {
    printf("%s ", ptr->c_str());
  }
}

#endif  // Moderate_14

#if Q_N == Hard_1
int getBit(int n, int i) {
  return ((unsigned)n >> i) & 1;
}
void setBit(int& n, int i) {
  int mask = 1 << i;
  n |= mask;
}
int add_old(int a, int b) {
  int res = 0;
  int size = sizeof(int) * 8;
  int c = 0, mask = 1;
  for (int i = 0; i < size; ++i) {
    int bit_a = getBit(a, i);
    int bit_b = getBit(b, i);
    int r = bit_a ^ bit_b ^ c;
    c = (bit_a & bit_b) | (bit_b & c) | (bit_a & c);
    if (r == 1) setBit(res, i);
  }
  return res;
}
int add(int a, int b) {
  int r = a ^ b;
  int c = (a & b) << 1;
  if (c != 0) return add(r, c);
  return r;
}
void doTest() {
  srand(time(NULL));
  printf("%d\n", add(3, -5));
  for (int i = 0; i < 100; ++i) {
    int a = rand(), b = rand() - rand();
    int c = add(a, b);
    assert(c == a + b);
  }
}
#endif  // Hard_1

#if Q_N == Hard_2
using std::vector;
using std::unordered_map;
void shuffle(vector<int>& v) {
  int size = v.size();
  for (int i = size; i > 0; --i) {
    int j = rand() % i;
    std::swap(v[j], v[i - 1]);
  }
}
void doTest() {
  int data[] = {1, 2, 3, 4};
  vector<int> v(data, data + sizeof(data) / sizeof(int));
  unordered_map<int, int> dict;
  for (int i = 0; i < 120000; ++i) {
    vector<int> v2(v);
    shuffle(v2);
    int sum = 0;
    for (auto ptr = v2.begin(); ptr != v2.end(); ++ptr) {
      sum = sum * 10 + *ptr;
      //printf("%d ", *ptr);
    }
    ++dict[sum];
    //printf("\n");
  }
  for (auto ptr = dict.begin(); ptr != dict.end(); ++ptr) {
    printf("%d:%d\n", ptr->first, ptr->second);
  }
}
#endif  // Hard_2

#if Q_N == Hard_3
using std::vector;
using std::unordered_map;
vector<int> select(const vector<int> data, int n) {
  vector<int> res(n);
  vector<int> data2(data);
  int m = data2.size();
  for (int i = 0; i < n; ++i) {
    int idx = rand() % (m - i);
    res[i] = data2[idx];
    std::swap(data2[m - i - 1], data2[idx]);
  }
  return res;
}
void doTest() {
  int data[] = {1, 2, 3, 4};
  vector<int> v(data, data + sizeof(data) / sizeof(int));
  unordered_map<int, int> dict;
  for (int i = 0; i < 120000; ++i) {
    auto res = select(v, 2);
    int sum = 0;
    for (auto ptr = res.begin(); ptr != res.end(); ++ptr) {
      sum = sum * 10 + *ptr;
    }
    ++dict[sum];
  }
  for (auto ptr = dict.begin(); ptr != dict.end(); ++ptr) {
    printf("%d:%d\n", ptr->first, ptr->second);
  }
}
#endif  // Hard_3

#if Q_N == Hard_4

int getTwos(int nn, int t = 1) {
  int num = 0, n = nn;
  int a = 0, b = 1;
  while (n > 0) {
    int c = n % 10;
    num += c * a;
    if (c > t) {
      num += b;
    } else if (c == t) {
      num += nn % b + 1;
    }
    a = a * 10 + b;
    b *= 10;
    n /= 10;
  }
  return num;
}
int countTwos(int n, int t = 1) {
  int num = 0;
  while (n > 0) {
    if (n % 10 == t) ++num;
    n /= 10;
  }
  return num;
}
int getTwos2(int nn) {
  int num = 0;
  for (int i = 0; i <= nn; ++i) {
    num += countTwos(i);
  }
  return num;
}
void doTest() {
  FILE* fp = fopen("graph.txt", "w");
  for (int n = 0; n < 1000; ++n) {
    int a = getTwos(n);
    int b = getTwos2(n);
    assert(b == a);
    printf("%d:%d\n", n, a);
    fprintf(fp, "%d\t%d\n", n, a);
  }
  fclose(fp);
}
#endif  // Hard_4

#if Q_N == Hard_5
using std::unordered_map;
using std::vector;
using std::string;
char clean(char c) {
  if (!(c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')) {
    return ' ';
  } else if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 'a';
  }
}
vector<string> getWords(string file_name) {
  FILE* fp = fopen(file_name.c_str(), "rb");
  vector<string> words;
  string article;
  char buf[102500];
  while (!feof(fp)) {
    int size = fread(buf, 1, 102500, fp);
    buf[size] = '\0';
    article.append(buf);
  }
  article.push_back(' ');
  fclose(fp);
  // split word
  std::transform(article.begin(), article.end(), article.begin(), clean);
  bool word = false;
  int start = 0;
  for (int i = 0; i < article.size(); ++i) {
    if (article[i] == ' ') {
      if (word) {
        word = false;
        words.push_back(article.substr(start, i - start));
      }
    } else {
      if (!word) {
        word = true;
        start = i;
      }
    }
  }
  return words;
}
void getDist(string file_name) {
  unordered_map<string, vector<int>> dict;
  vector<string> words = getWords(file_name);
  int size = words.size();
  for (int i = 0; i < size; ++i) {
    dict[words[i]].push_back(i);
  }
  // get distance
  string w1 = "of", w2 = "not";
  auto ptr = dict.find(w1), ptr2 = dict.find(w2);
  if (ptr == dict.end() || ptr2 == dict.end()) return;
  vector<int> v1 = ptr->second, v2 = ptr2->second;
  int min_dist = INT_MAX, start = 0, end = 0;
  int i = 0, j = 0;
  int size1 = v1.size(), size2 = v2.size();
  while (i < size1 && j < size2) {
    if (abs(v1[i] - v2[j]) < min_dist) {
      min_dist = abs(v1[i] - v2[j]);
      start = v1[i], end = v2[j];
    }
    if (v1[i] < v2[j]) ++i;
    else ++j;
  }
  while (i < size1) {
    if (abs(v1[i] - v2.back()) < min_dist) {
      min_dist = abs(v1[i] - v2.back());
      start = v1[i], end = v2.back();
    }
    ++i;
  }
  while (j < size2) {
    if (abs(v1.back() - v2[j]) < min_dist) {
      min_dist = abs(v1.back() - v2[j]);
      start = v1.back(), end = v2[j];
    }
    ++j;
  }
  if (start > end) std::swap(start, end);
  for (int i = start; i <= end; ++i) {
    printf("%s ", words[i].c_str());
  }
  printf("\n%d\n", min_dist);
}
void doTest() {
  string file_name = "file.txt";
  getDist(file_name);
}

#endif  // Hard_5

#if Q_N == Hard_7
using std::unordered_map;
using std::string;
using std::vector;
using std::queue;
using std::unordered_set;
using std::pair;
bool strLenCmp(const string& s1, const string& s2) {
  return s1.size() < s2.size();
}
bool canGenerate(const string& word, bool isOrig, unordered_map<string, bool>& dict) {
  if (!isOrig) {
    auto ptr = dict.find(word);
    if (ptr != dict.end())
      return ptr->second;
  }
  int size = word.size();
  for (int i = 0; i < size - 1; ++i) {
    string left = word.substr(0, i + 1);
    string right = word.substr(i + 1);
    auto ptr = dict.find(left);
    if (ptr != dict.end() && ptr->second) {
      bool res = canGenerate(right, false, dict);
      dict[right] = res;
      if (res) return true;
    }
  }
  return false;
}

string getLongestWord(vector<string> words) {
  unordered_map<string, bool> dict;
  std::sort(words.begin(), words.end(), strLenCmp);
  int size = words.size();
  for (auto ptr = words.begin(); ptr != words.end(); ++ptr) {
    dict[*ptr] = true;
  }
  for (int i = size - 1; i >= 0; --i) {
    if (canGenerate(words[i], true, dict))
      return words[i];
  }
  return "";
}

vector<string>* getNeighbors(string& s, unordered_map<string, vector<string>>& neighbors, unordered_set<string>& dict) {
  auto ptr = neighbors.find(s);
  if (ptr != neighbors.end())
    return &ptr->second;
  int size = s.size();
  vector<string> v;
  for (int i = 0; i < size; ++i) {
    char c = s[i];
    for (int cc = 'a'; cc <= 'z'; ++cc) {
      if (cc == c) continue;
      s[i] = cc;
      if (dict.find(s) != dict.end())
        v.push_back(s);
    }
    s[i] = c;
  }
  neighbors[s] = v;
  return &neighbors[s];
}
struct Node {
  Node* prev;
  string s;
  int n;
  Node(string s, int n, Node* prev) : s(s), n(n), prev(prev) {}
};
vector<vector<string>> findLadders(string start, string end, unordered_set<string>& dict) {
  vector<vector<string>> res;
  queue<Node*> Q;
  unordered_map<string, vector<string>> neighbors;
  unordered_map<string, int> steps;
  dict.insert(end);
  Q.push(new Node(start, 1, NULL));
  while (!Q.empty()) {
    auto p = Q.front();
    Q.pop();
    auto ptr = steps.find(p->s);
    if (ptr != steps.end() && ptr->second < p->n) continue;
    steps[p->s] = p->n;
    dict.erase(p->s);
    if (p->s == end) {
      // generate result
      vector<string> v;
      while (p != NULL) {
        v.push_back(p->s);
        p = p->prev;
      }
      std::reverse(v.begin(), v.end());
      res.push_back(v);
      continue;
    }
    auto cands = getNeighbors(p->s, neighbors, dict);
    int size = cands->size();
    for (int i = 0; i < size; ++i) {
      Q.push(new Node(cands->at(i), p->n + 1, p));
    }
  }
  return res;
}

void doTest() {
  //string data[] = {"al", "ready", "already", "iamagenius", "a", "genius", "i", "am", "l"};
  //string data[] = {"a", "b", "c"};
  string data[] = {"hot", "dot", "dog", "lot", "log"};
  unordered_set<string> dict(data, data + sizeof(data) / sizeof(string));
  auto res = findLadders("hit", "cog", dict);
  for (int i = 0; i < res.size(); ++i) {
    for (int j = 0; j < res[i].size(); ++j) {
      printf("%s ", res[i][j].c_str());
    }
    printf("\n");
  }
  //vector<string> v(data, data + sizeof(data) / sizeof(string));
  //string str = getLongestWord(v);
  //printf("%s\n", str.c_str());
}

#endif  // Hard_7

#if Q_N == Hard_10
using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::queue;
vector<string>* getNeighbors(string& s, unordered_map<string, vector<string>>& neighbors, unordered_set<string>& dict) {
  auto ptr = neighbors.find(s);
  if (ptr != neighbors.end())
    return &ptr->second;
  int size = s.size();
  vector<string> v;
  for (int i = 0; i < size; ++i) {
    char c = s[i];
    for (int cc = 'a'; cc <= 'z'; ++cc) {
      if (cc == c) continue;
      s[i] = cc;
      if (dict.find(s) != dict.end())
        v.push_back(s);
    }
    s[i] = c;
  }
  neighbors[s] = v;
  return &neighbors[s];
}
vector<vector<string>> findLadders(string start, string end, unordered_set<string>& dict) {
  vector<vector<string>> res;
  queue<string> Q;
  unordered_map<string, vector<string>> neighbors;
  unordered_map<string, string> back_trace;
  unordered_set<string> visited;
  bool found = false;
  dict.insert(end);
  Q.push(start);
  while (!Q.empty()) {
    auto p = Q.front();
    Q.pop();
    dict.erase(p);
    if (p == end) {
      // generate result
      found = true;
      vector<string> v;
      while (true) {
        v.push_back(p);
        auto ptr = back_trace.find(p);
        if (ptr == back_trace.end()) break;
        p = ptr->second;
      }
      res.push_back(v);
    }
    if (found) continue;
    auto cands = getNeighbors(p, neighbors, dict);
    int size = cands->size();
    for (int i = 0; i < size; ++i) {
      string cand = cands->at(i);
      if (visited.find(cand) != visited.end()) continue;
      back_trace[cand] = p;
      visited.insert(cand);
      Q.push(cand);
    }
  }
  return res;
}
void doTest() {
  //string data[] = {"al", "ready", "already", "iamagenius", "a", "genius", "i", "am", "l"};
  //string data[] = {"a", "b", "c"};
  string data[] = {"hot", "dot", "dog", "lot", "log"};
  unordered_set<string> dict(data, data + sizeof(data) / sizeof(string));
  auto res = findLadders("hit", "cog", dict);
  for (int i = 0; i < res.size(); ++i) {
    for (int j = 0; j < res[i].size(); ++j) {
      printf("%s ", res[i][j].c_str());
    }
    printf("\n");
  }
  //vector<string> v(data, data + sizeof(data) / sizeof(string));
  //string str = getLongestWord(v);
  //printf("%s\n", str.c_str());
}
#endif  // Hard_10
#if Q_N == Hard_19
int candy(vector<int>& ratings) {
  int n = ratings.size(), res = 0;
  vector<int> order(n, 1), r_order(n, 1);
  for (int i = 1; i < n; ++i) {
    if (ratings[i] > ratings[i - 1]) {
      order[i] = order[i - 1] + 1;
    } else if (ratings[i] < ratings[i - 1]) {
      order[i] = 1;
    } else {
      order[i] = order[i - 1];
    }
  }
  for (int i = n - 2; i >= 0; --i) {
    if (ratings[i] > ratings[i + 1]) {
      r_order[i] = r_order[i + 1] + 1;
    } else if (ratings[i] < ratings[i + 1]) {
      r_order[i] = 1;
    } else {
      r_order[i] = r_order[i + 1];
    }
  }
  for (int i = 0; i < n; ++i) {
    res += std::max(order[i], r_order[i]);
  }
  return res;
}
#endif  // Hard_19

#if Q_N == Hard_20
using std::vector;
using std::string;
using std::unordered_map;
vector<vector<string>> partition(string& s, int pos, unordered_map<int, vector<vector<string>>>& cache, vector<vector<bool>>& D) {
  vector<vector<string>> res;
  int size = s.size();
  if (pos >= size) {
    res.push_back(vector<string>());
    return res;
  }
  auto ptr = cache.find(pos);
  if (ptr != cache.end()) return ptr->second;
  for (int i = pos; i < size; ++i) {
    if (D[pos][i]) {
      auto res2 = partition(s, i + 1, cache, D);
      for (int j = 0; j < res2.size(); ++j) {
        vector<string> v = res2[j];
        v.insert(v.begin(), s.substr(pos, i - pos + 1));
        res.push_back(v);
      }
    }
  }
  cache[pos] = res;
  return res;
}
vector<vector<string>> partition(string s) {
  int size = s.size();
  vector<vector<bool>> D(size, vector<bool>(size, false));
  for (int i = size - 1; i >= 0; --i) {
    for (int j = i; j < size; ++j) {
      if (s[i] == s[j] && (j - i <= 2 || D[i + 1][j - 1])) {
        D[i][j] = true;
      }
    }
  }
  unordered_map<int, vector<vector<string>>> cache;
  auto res = partition(s, 0, cache, D);
  return res;
}
void doTest() {
  auto res = partition("abbab");
  for (int i = 0; i < res.size(); ++i) {
    for (int j = 0; j < res[i].size(); ++j) {
      printf("%s ", res[i][j].c_str());
    }
    printf("\n");
  }
}
#endif  // Hard_20

#if Q_N == Hard_21
using std::string;
using std::unordered_map;
using std::vector;
int minCut(const string& s, int pos, unordered_map<int, int>& cache, vector<vector<int>>& D) {
  int size = s.size();
  if (size - pos <= 1) return 0;
  auto ptr = cache.find(pos);
  if (ptr != cache.end()) return ptr->second;
  int min_cut = size - 1;
  for (int i = pos; i < size; ++i) {
    if (D[pos][i]) {
      int cut = minCut(s, i + 1, cache, D) + 1;
      min_cut = std::min(cut, min_cut);
    }
  }
  cache[pos] = min_cut;
  return min_cut;
}

int minCut(string s) {
  unordered_map<int, int> cache;
  int size = s.size();
  vector<vector<int>> D(size, vector<int>(size, false));
  for (int i = size - 1; i >= 0; --i) {
    for (int j = i; j < size; ++j) {
      if (s[i] == s[j] && (j - i <= 2 || D[i + 1][j - 1])) {
        D[i][j] = true;
      }
    }
  }
  return minCut(s, 0, cache, D);
}
void doTest() {
}
#endif  // Hard_21

#if Q_N == Hard_22
#include "structures.h"
using std::vector;
TreeNode* doFlatten(TreeNode* root) {
  if (root == NULL) return NULL;
  TreeNode* tail = root, *right = root->right;
  if (root->left != NULL) {
    tail = doFlatten(root->left);
    root->right = root->left;
    tail->right = right;
  }
  if (right != NULL) {
    tail = doFlatten(right);
  }
  return tail;
}
void flatten(TreeNode* root) {
  // IMPORTANT: Please reset any member data you declared, as
  // the same Solution instance will be reused for each test case.
  doFlatten(root);
}
void doTest() {
  TreeNode* root = TreeNode::parseTreeNode("1,#,2");
  flatten(root);
}



#endif  // Hard_22

#if Q_N == Hard_23
#include "structures.h"
using std::vector;
TreeNode* buildTree(vector<int>& in, vector<int>& post, int in_s, int post_s, int n) {
  if (n <= 0) return NULL;
  int i = 0;
  for (; i < n; ++i) {
    if (in[in_s + i] == post[post_s + n - 1]) break;
  }
  TreeNode* root = new TreeNode(post[post_s + n - 1]);
  root->left = buildTree(in, post, in_s, post_s, i);
  root->right = buildTree(in, post, in_s + i + 1, post_s + i, n - i - 1);
  return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
  // IMPORTANT: Please reset any member data you declared, as
  // the same Solution instance will be reused for each test case.
  return buildTree(inorder, postorder, 0, 0, inorder.size());
}
void doTest() {
  int in[] = {2, 1}, pos[] = {2, 1};
  int size = sizeof(in) / sizeof(int);
  vector<int> inorder(in, in + size), postorder(pos, pos + size);
  auto root = buildTree(inorder, postorder);
  printf("root\n");
}
#endif  // Hard_23

#if Q_N == Hard_24
bool isPalindrome(int x) {
  if (x < 0) return false;
  int64_t b = 1;
  while (b <= x)
    b *= 10;
  b /= 10;
  while (x > 0) {
    int r = x % 10;
    int q = x / b;
    if (r != q) return false;
    x = (x % b) / 10;
    b /= 100;
  }
  return true;
}
void doTest() {
  int n = 1874994781;
  printf("%d\n", isPalindrome(n));
}
#endif  // Hard_24

#if Q_N == Hard_25
using std::vector;
using std::string;
void restore(string& s, int pos, int seg_count, string ip, vector<string>& res) {
  int size = s.size();
  if (size - pos > seg_count * 3 || size - pos < seg_count) return;
  if (pos == size) {
    res.push_back(ip);
    return;
  }
  int num = 0, end = std::min(pos + 2, size - seg_count);
  for (int i = pos; i <= end; ++i) {
    num = num * 10 + s[i] - '0';
    if (num >= 0 && num <= 255) {
      restore(s, i + 1, seg_count - 1, ip + "." + s.substr(pos, i - pos + 1), res);
    }
    if (num == 0) break;
  }
}
vector<string> restoreIpAddresses(string s) {
  // IMPORTANT: Please reset any member data you declared, as
  // the same Solution instance will be reused for each test case.
  vector<string> res;
  restore(s, 0, 4, "", res);
  return res;
}
void doTest() {
  auto res = restoreIpAddresses("0000");
}
#endif  // Hard_25

#if Q_N == Hard_26
struct TreeLinkNode {
  int val;
  TreeLinkNode* left, *right, *next;
  TreeLinkNode(int val) : val(val), left(NULL), right(NULL), next(NULL) {};
};
TreeLinkNode* getNextWithChild(TreeLinkNode* p, TreeLinkNode*& child) {
  while (p != NULL && p->left == NULL && p->right == NULL)
    p = p->next;
  if (p == NULL) {
    child = NULL;
  } else if (p->left != NULL) {
    child = p->left;
  } else {
    child = p->right;
  }
  return p;
}
void connect(TreeLinkNode* root) {
  TreeLinkNode* cur_layer_start, *next_layer_start;
  cur_layer_start = root;
  while (cur_layer_start != NULL) {
    // get next layer start
    TreeLinkNode* p, *child;
    p = getNextWithChild(cur_layer_start, next_layer_start);
    // connect current layer
    while (p != NULL) {
      auto next = getNextWithChild(p->next, child);
      if (p->left != NULL) {
        if (p->right != NULL) {
          p->left->next = p->right;
        } else {
          p->left->next = child;
        }
      }
      if (p->right != NULL) {
        p->right->next = child;
      }
      p = next;
    }
    cur_layer_start = next_layer_start;
  }
}
void doTest() {
}
#endif  // Hard_26

#if Q_N == Hard_27
using std::string;
using std::unordered_map;
struct Key {
  int p1, p2, len;
  Key(int p1, int p2, int len) : p1(p1), p2(p2), len(len) {}
};
bool check(string& s1, string& s2, int p1, int p2, int len, unordered_map<size_t, bool>& cache) {
  std::hash<Key> key_hash;
  auto key = key_hash(Key(p1, p2, len));
  auto ptr = cache.find(key);
  if (ptr != cache.end()) return ptr->second;
  int hash = 0;
  for (int i = 0; i < len; ++i) {
    hash += s1[p1 + i] - s2[p2 + i];
  }
  if (hash != 0) return false;
  if (len == 1) return s1[p1] == s2[p2];
  for (int sz = 1; sz < len; ++sz) {
    if (check(s1, s2, p1, p2, sz, cache) &&
        check(s1, s2, p1 + sz, p2 + sz, len - sz, cache))
      cache[key] = true;
    return true;
    if (check(s1, s2, p1, p2 + len - sz, sz, cache) &&
        check(s1, s2, p1 + sz, p2, len - sz, cache))
      cache[key] = true;
    return true;
  }
  return false;
}
bool isScramble(string s1, string s2) {
  // IMPORTANT: Please reset any member data you declared, as
  // the same Solution instance will be reused for each test case.
  int size = s1.size();
  if (s2.size() != size) return false;
  unordered_map<size_t, bool> cache;
  return check(s1, s2, 0, 0, size, cache);
}
void doTest() {
  bool res = isScramble("a", "a");
  printf("%d\n", res);
}
#endif  // Hard_27

#if Q_N == Hard_28
using std::vector;
vector<vector<int>> genInt(int m, int n) {
  srand(time(NULL));
  vector<vector<int>> res(m, vector<int>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      res[i][j] = rand();
    }
  }
  return res;
}
const int N = 10;
int a[][N] = {
  3, 4, 5, 6, 10, 11, 12, 13, 20, 21,
  1, 2, 7, 8, 9, 30, 31, 32, 33, 34,
  14, 15, 16, 17, 18, 19, 22, 23, 24, 25,
  26, 27, 28, 29, 35, 36, 37, 38, 39, 40,
  50, 51, 52, 54, 55, 65, 66, 67, 68, 69,
  53, 56, 57, 58, 59, 60, 61, 62, 63, 64,
  41, 42, 43, 44, 45, 46, 47, 48, 49, 2222,
  1, 2, 2, 4, 5, 6, 12, 13, 20, 21
};
void doTest() {
  vector<int> v;
}
#endif  // Hard_28

#if Q_N == Hard_29

int GetMedian(int a[], int n, int b[], int m, int k) {
  assert(a && b);
  if (n <= 0) return b[k - 1];
  if (m <= 0) return a[k - 1];
  if (k <= 1) return std::min(a[0], b[0]);
  if (b[m / 2] >= a[n / 2]) {
    if ((n / 2 + 1 + m / 2) >= k)
      return GetMedian(a, n, b, m / 2, k);
    else
      return GetMedian(a + n / 2 + 1, n - (n / 2 + 1), b, m, k - (n / 2 + 1));
  } else {
    if ((m / 2 + 1 + n / 2) >= k)
      return GetMedian(a, n / 2, b, m, k);
    else
      return GetMedian(a, n, b + m / 2 + 1, m - (m / 2 + 1), k - (m / 2 + 1));
  }
}
double findMedianSortedArrays(int A[], int m, int B[], int n) {
  if ((n + m) % 2 == 0) {
    return (GetMedian(A, m, B, n, (m + n) / 2) + GetMedian(A, m, B, n, (m + n) / 2 + 1)) / 2.0;
  } else {
    return GetMedian(A, m, B, n, (m + n) / 2 + 1);
  }
}
void doTest() {

}
#endif  // Hard_29

#if Q_N == Hard_30
#include "structures.h"
using std::vector;
using std::unordered_map;
using std::unordered_set;
void getCircles(Graph &g, int node_id, vector<int> &path, unordered_set<int> &visited, vector<int> &res) {
  if (res.size() > 0) return;
  if (visited.find(node_id) != visited.end()) {
    int size = path.size();
    res.push_back(node_id);
    for (int i = size - 1; i >= 0; --i) {
      res.push_back(path[i]);
      if (path[i] == node_id) break;
    }
    std::reverse(res.begin(), res.end());
    return;
  }
  path.push_back(node_id);
  visited.insert(node_id);
  vector<int> neighbors = g.GetNeighbor(node_id);
  for (int i = 0; i < neighbors.size(); ++i) {
    if (path.size() <= 1 || neighbors[i] != path[path.size() - 2]) {
      getCircles(g, neighbors[i], path, visited, res);
    }
  }
}
void doTest() {
  Graph g("2,3;1,4;1,4;2,3,5,6;4;4,7;6");
  vector<int> res, path;
  unordered_set<int> visited;
  getCircles(g, 7, path, visited, res);
  for (auto ptr = res.begin(); ptr != res.end(); ++ptr) {
    printf("%d->", *ptr);
  }
  printf("\n");
}
#endif  // Hard_30

#if Q_N == Hard_31
double findKth(int a[], int m, int b[], int n, int k) {
  if (m < n) return findKth(b, n, a, m, k);
  if (m == 0) return b[k - 1];
  if (k == 1) return std::min(a[0], b[0]);
  int pa = std::min(m, k / 2), pb = k - pa;
  if (a[pa - 1] < b[pb - 1]) {
    return findKth(a + pa, m - pa, b, n, k - pa);
  } else if (a[pa - 1] > b[pb - 1]) {
    return findKth(a, m, b + pb, n - pb, k - pb);
  } else {
    return a[pa - 1];
  }
}
double findMedianSortedArrays(int A[], int m, int B[], int n) {
  // IMPORTANT: Please reset any member data you declared, as
  // the same Solution instance will be reused for each test case.
  if (n & 0x1 == 1) {
    return findKth(A, m, B, n, (m + n) / 2 + 1);
  } else {
    return (findKth(A, m, B, n, (m + n) /2) + findKth(A, m, B, n, (m + n) / 2 + 1)) / 2.0;
  }
}
void doTest() {
}
#endif  // Hard_31

#if Q_N == Hard_32
using std::string;
int lengthOfLongestSubstring(string s) {
  int max_len = 1, size = s.size();
  if (size == 0) return 0;
  bool dict[256] = {0};
  int i = 0, j = 0;
  while (j < size){
    while (j < size && !dict[s[j]]) {
      if (j - i + 1 > max_len) 
        max_len = j - i + 1;
      dict[s[j]] = true;
      ++j;
    }
    while (j < size && s[i] != s[j]) {
      dict[s[i]] = false;
      ++i;
    }
    ++i, ++j;
  }
  return max_len;
}
void doTest() {
  string s = "wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco";
  int max_len = lengthOfLongestSubstring(s);
  printf("%d\n", max_len);
}
#endif  // Hard_32

#if Q_N == Hard_33
using std::vector;
using std::string;
bool exist(vector<vector<char>> &board, string &word, int pos, int i, int j) {
  int size = word.size();
  if (pos == size) return true;
  int m = board.size(), n = board[0].size();
  if (i < 0 || i >= m || j < 0 || j >= n || word[pos] != board[i][j]) 
    return false;
  int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
  char orig = board[i][j];
  board[i][j] = 0;
  for (int k = 0; k < 4; ++k) {
    int new_i = i + dir[k][0], new_j = j + dir[k][1];
    bool res = exist(board, word, pos + 1, new_i, new_j);
    if (res) return true;
  }
  board[i][j] = orig;
  return false;
}
bool exist(vector<vector<char> > &board, string word) {
  // IMPORTANT: Please reset any member data you declared, as
  // the same Solution instance will be reused for each test case.
  int m = board.size(), n = m > 0 ? board[0].size() : 0;
  if (m == 0 || n == 0) return false;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      bool res = exist(board, word, 0, i, j);
      if (res) return true;
    }
  }
  return false;
}
void doTest() {
  vector<vector<char>> board(1, vector<char>(2, 'a'));
  bool res = exist(board, "aaa");
  printf("%d\n", res);
}
#endif  // Hard_33

#if Q_N == Hard_34
using std::string;
string convert(string s, int nRows) {
  int size = s.size(), gs = nRows * 2 - 2, group_num = (size + gs - 1) / gs;
  string res;
  if (size <= nRows || nRows < 2) return s;
  for (int i = 0; i < nRows; ++i) {
    for (int j = 0; j < group_num; ++j) {
      if (j * gs + i < size) 
        res.push_back(s[j * gs + i]);
      if (i > 0 && i < nRows - 1 && j * gs + (gs - i) < size)
        res.push_back(s[j * gs + gs - i]);
    }
  }
  return res;
}
void doTest() {
  string s = "ABCDE";
  string new_s = convert(s, 2);
  printf("%s\n", new_s.c_str());
}
#endif  // Hard_34

#if Q_N == Hard_35
using std::vector;
using std::unordered_map;
void fourSum(vector<int> &num, int pos, int target, vector<int> &v, vector<vector<int>> &res, unordered_map<int, int> &dict) {
  if (v.size() == 3) {
    auto ptr = dict.find(target);
    if (ptr != dict.end() && ptr->second >= pos) {
      v.push_back(target);
      res.push_back(v);
      v.pop_back();
    }
    return;
  }
  if (num[pos] * (4 -v.size()) > target) {
    printf ("%d\n", (num[pos] * (4 - v.size())) > target);
    return;
  }
  int max_i = num.size() - (3 - v.size());
  for (int i = pos; i < max_i; ++i) {
    v.push_back(num[i]);
    fourSum(num, i + 1, target - num[i], v, res, dict);
    v.pop_back();
    while (i < max_i - 1 && num[i + 1] == num[i]) ++i;
  }
}
vector<vector<int> > fourSum(vector<int> &num, int target) {
  // IMPORTANT: Please reset any member data you declared, as
  // the same Solution instance will be reused for each test case.
  vector<vector<int>> res;
  if (num.size() < 4) return res;
  vector<int> v;
  unordered_map<int, int> dict;
  std::sort(num.begin(), num.end());
  for (int i = 0; i < num.size(); ++i) 
    dict[num[i]] = i;
  fourSum(num, 0, target, v, res, dict);
  return res;
}
void doTest() {
  int data[] = {2,1,0,-1};
  int size = sizeof(data) / sizeof(int);
  vector<int> num(data, data + size);
  auto res = fourSum(num, 2);
  for (auto itr = res.begin(); itr != res.end(); ++itr) {
    printf("%d ", *itr);
  }
}
#endif  // Hard_35

#if Q_N == Hard_36
int mod(int a, int b) {
  return (a % b + b) % b;
}
char *strStr(char *T, char *P) {
  if (T == NULL || P == NULL) return NULL;
  int n = strlen(T), m = strlen(P);
  if (m > n) return NULL;
  int M = 174763, B = 256, E = 1;
  int ht = 0, hp = 0;
  // get hp
  for (int i = 0; i < m; ++i) {
    hp = (hp * B + P[i]) % M;
    ht = (ht * B + T[i]) % M;
    if (i > 0)
      E = (E * B) % M;
  }
  for (int i = 0; i <= n - m; ++i) {
    if (ht == hp) {
      bool equal = true;
      for (int j = 0; j < m; ++j) {
        if (T[i + j] != P[j]) {
          equal = false;
          break;
        }
      }
      if (equal) return T + i;
    }
    ht = mod(ht - T[i] * E, M);
    ht = (ht * B + T[i + m]) % M;
  }
  return NULL;
}
void doTest() {
  char *T = "a", *P = "a";
  printf("%s\n", strStr(T,P));
}
#endif  // Hard_36

#if Q_N == Hard_37
using std::string;
using std::vector;
bool isLeft(char c) {
  return c == '(' || c == '[' || c == '{';
}
bool isRight(char c) {
  return c == ')' || c == ']' || c == '}';
}
bool isMatch(char l, char r) {
  return l == '(' && r == ')' ||
    l == '[' && r == ']' ||
    l == '{' && r == '}';
}
bool isValid(string s) {
  int size = s.size();
  vector<char> S;
  for (int i = 0; i < size; ++i) {
    if (isLeft(s[i])) {
      S.push_back(s[i]);
    } else if (!S.empty() && isRight(s[i]) && isMatch(S.back(), s[i])) {
      S.pop_back();
    } else {
      return false;
    }
  }
  return S.empty();  
}
void doTest() {
  string s = "{[]}()";
  printf("%d\n", isValid(s));
}
#endif  // Hard_37

#if Q_N == Hard_38
#include <algorithm>
using std::vector;


void doTest() {
  int data[] = {10, 13,59, 23, 98, 52, 92};
  int size = sizeof(data) / sizeof(int);
  std::vector<int> v(data, data + size);
  std::make_heap(v.begin(), v.end());
  srand(time(NULL));
  for (int i = 0; i < 10; ++i) {
    v.push_back(rand());
    push_heap(v.begin(), v.end());
  }
  while (!v.empty()) {
    printf("%d \n", v.front());
    pop_heap(v.begin(), v.end());
    v.pop_back();
  }
}
#endif  // Hard_38

#if Q_N == Hard_39
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int val) : val(val), next(NULL) {}
};
using std::vector;
bool cmp(const ListNode * l1, const ListNode *l2) {
  return l1->val > l2->val;
}
ListNode *mergeKLists(vector<ListNode *> &lists) {
  int k = lists.size();
  ListNode dummy(-1), *p = &dummy;
  std::make_heap(lists.begin(), lists.end(), cmp);
  while (!lists.empty()) {
    pop_heap(lists.begin(), lists.end(), cmp);
    p->next = lists.back();
    p = p->next;
    lists.back() = lists.back()->next;
    if (lists.back() == NULL) {
      lists.pop_back();
    } else {
      push_heap(lists.begin(), lists.end(), cmp);
    }
  }
  return dummy.next;
}
void doTest() {
  int k = 4, n = 5;
  srand(time(NULL));
  vector<ListNode *> lists(k, NULL);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < k; ++j) {
      auto node = new ListNode(rand() % 100);
      ListNode dummy(-1), *p = &dummy;
      dummy.next = lists[j];
      while (p->next != NULL && p->next->val <= node->val) {
        p = p->next;
      }
      node->next = p->next;
      p->next = node;
      lists[j] = dummy.next;
    }
  }
  for (int i = 0; i < k; ++i) {
    auto p = lists[i];
    while (p!= NULL) {
      printf("%d ", p->val);
      p = p->next;
    }
    printf("\n");
  }
  auto head = mergeKLists(lists);
  while (head != NULL) {
    printf("%d ", head->val);
    head = head->next;
  }
  printf("\n");
}
#endif  // Hard_39
int main(int argc, char* argv[]) {
  time_t start = clock();
  doTest();
  printf("\n%d ms\n", clock() - start);
  return 0;
}
