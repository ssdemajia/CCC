#include <vector>
#include <iostream>
#include <functional>
#include <cassert>

using namespace std;

struct Node
{
  int height = 1;  // 叶子节点的高度为1
  int val = 0;
  Node *parent = nullptr;  // 指向父结点
  Node *left = nullptr;
  Node *right = nullptr;
  Node() = default;
  Node(int val) : val(val) {}
};

class AVLTree
{
public:
  void print(bool height = true) 
  {
    function<void(Node *)> in_order = [&](Node *n) {  //中序遍历打印
      if (!n)
        return;
      in_order(n->left);
      if (height)
        cout << n->height << ":";
      cout << n->val << " ";
      in_order(n->right);
    };
    cout << "inOrder:";
    in_order(root);
    cout << endl;

    function<void(Node *)> pre_order = [&](Node *n) { // 前序遍历打印
      if (!n)
        return;
      if (height)
        cout << n->height << ":";
      cout << n->val << " ";
      pre_order(n->left);
      pre_order(n->right);
    };

    cout << "preOrder:";
    pre_order(root);
    cout << endl;
  }

  void insert(int val)  // 插入一个数
  {
    cout << "insert:" << val << endl;
    Node *prev = nullptr;
    Node *p = root;

    while (p)  // 找到插入节点，prev是插入节点的父结点
    {
      prev = p;
      if (p->val == val)
        return;
      if (p->val < val)
      {
        p = p->right;
      }
      else
      {
        p = p->left;
      }
    }
    if (!prev)
    { // 树里面没有一个值时，当前树为空
      root = new Node(val);
      return;
    }
    Node *n = new Node(val);
    bool in_left = false;  // 判断插入到父节点的左边还是右边
    if (val < prev->val)
    {
      in_left = true;
      prev->left = n;
      if (prev->right) return; // 新插入的节点有兄弟节点，那么不需要调整
    }
    else
    {
      prev->right = n;
      if (prev->left) return; // 新插入的节点有兄弟节点，那么不需要调整
    }
    n->parent = prev;
    p = prev;
    while (p)  //因为添加了一个节点，子节点向上的节点高度都加一
    {
      p->height += 1;
      p = p->parent;
    }
    fix(n, in_left);
  }

  friend int get_height(AVLTree tree);

private:
  int fix_height(Node *h)
  {// 调整当前阶段的高度
    Node *l = h->left;
    Node *r = h->right;
    int l_h = 0;
    int r_h = 0;
    if (l)
      l_h = l->height;
    if (r)
      r_h = r->height;
    h->height = max(l_h, r_h) + 1;
  }
  void fix(Node *n, bool in_left)
  { // 调整当前节点
    Node *p = n;
    while (p)
    {
      Node *l = p->left;
      Node *r = p->right;
      int l_h = 0;
      int r_h = 0;
      if (l)
        l_h = l->height;
      if (r)
        r_h = r->height;
      if (abs(l_h - r_h) > 1) break; // 当前节点不平衡
      p = p->parent;
    }
    if (!p)  // 如果没有节点不平衡
      return;
    Node *l = p->left;
    Node *r = p->right;
    int l_h = 0;
    int r_h = 0;
    if (l)
      l_h = l->height;
    if (r)
      r_h = r->height;
    if (abs(l_h - r_h) <= 1)
      return;
    // 下面是对不平衡的树进行旋转
    if (in_left) // 新结点在父节点的左边
    {
      if (l_h > r_h)  // 左子树更高
        rotate_right(p);
      else
        rotate_right_left(p); // 右子树更高
    }
    else
    {
      if (l_h < r_h) // 右子树更高，新节点在父节点右边
        rotate_left(p);
      else
        rotate_left_right(p); // 左子树更高，新节点在父节点右边
    }
  }
  /*
        3
      /
     2
    /
   1
  */
  void rotate_right(Node *n)
  {
    cout << "rotate_right" << endl;
    Node *parent = n->parent;
    Node *t = n->left;
    n->left = t->right;
    if (n->left)
      n->left->parent = n;
    n->parent = t;
    t->right = n;
    if (parent)
    {
      if (parent->left == n)
        parent->left = t;
      else
        parent->right = t;
    }
    else
    {
      root = t;
    }
    t->parent = parent;

    fix_height(n);
    fix_height(t);
    if (parent)
      fix_height(parent);
    cout << "rotate right end" << endl;
  }

  /*
      1
       \
        2
         \
          3      */
  void rotate_left(Node *n)
  {
    cout << "rotate left:" << n->val << endl;
    Node *parent = n->parent;
    Node *t = n->right;
    n->right = t->left;
    n->parent = t;
    if (n->right)
      n->right->parent = n;
    t->left = n;
    if (parent)
    {
      if (parent->left == n)
        parent->left = t;
      else
        parent->right = t;
    }
    else
    {
      root = t;
    }
    t->parent = parent;
    fix_height(n);
    fix_height(t);
    if (parent)
      fix_height(parent);
    cout << "rotate left end" << endl;
  }

  /*
      4
    /
   2
    \
     3
  */
  void rotate_left_right(Node *n)
  {
    cout << "rotate left right" << endl;
    rotate_left(n->left);
    rotate_right(n);
    cout << "rotate left right end" << endl;
  }

  /*
        3
         \
          5
        /
       4
  */
  void rotate_right_left(Node *n)
  {
    cout << "rotate right left" << endl;
    rotate_right(n->right);
    rotate_left(n);
    cout << "rotate right left end" << endl;
  }
  Node *root = nullptr;
};

int get_height(AVLTree tree)
{
  return tree.root->height;
}

int main()
{
  AVLTree tree;
  tree.insert(1);
  tree.print();

  tree.insert(2);
  tree.print();

  tree.insert(3);
  tree.print();

  tree.insert(4);
  tree.print();

  tree.insert(5);
  tree.print();

  tree.insert(6);
  tree.print();

  tree.insert(7);
  tree.insert(0);
  tree.insert(-1);
  tree.insert(-2);
  tree.insert(-3);
  tree.insert(-4);
  tree.print(false);

  assert(get_height(tree) == 4);
}