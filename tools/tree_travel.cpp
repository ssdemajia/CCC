#include <iostream>
#include <stack>

/*
  二叉树先序遍历
 */
struct TreeNode {
  TreeNode (int val) {
    this->val = val;
  }
  int val;
  TreeNode* left;
  TreeNode* right;
};

void preOrderTravel(TreeNode * root) {
//非递归先序遍历
  std::stack<TreeNode*> st;
  TreeNode* p = root;
  while (p!=nullptr || !st.empty()) {
    
    while (p!=nullptr) {
      std::cout << p->val << std::endl;
      st.push(p);
      p = p->left;
    }
    if (st.empty()) break;
    p = st.top();
    st.pop();
    p = p->right;
  }
}

void postTravel(TreeNode * root) {
  // 二叉树后序遍历
  std::stack<TreeNode*> st;
  TreeNode * pre = nullptr;
  st.push(root);
  while (!st.empty()) {
    TreeNode * p = st.top();
    if ((!p->left && !p->right) || 
        (pre && (p->left == pre || p->right == pre))) {
      std::cout << p->val << std::endl;
      st.pop();
      pre = p;
    }
    else {
      if (p->right) {
        st.push(p->right);
      }
      if (p->left) {
        st.push(p->left);
      }
    }
  }
}
int main() {
  TreeNode* root = new TreeNode(1),
          * l1 = new TreeNode(2),
          * r1 = new TreeNode(3),
          * l2 = new TreeNode(4),
          * r2 = new TreeNode(5);
  root->left = l1;
  root->right = r1;
  l1->left = l2;
  l1->right = r2;
  preOrderTravel(root);
  postTravel(root);
}