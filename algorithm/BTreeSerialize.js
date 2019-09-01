//二叉树节点定义
function TreeNode(val) {
  this.val = val;
  this.left = this.right = null;
}


/**
 * 将二叉树编码为字符串
 * @param {TreeNode} root
 * @return {string} [1,2,3,null,null,4, 5]
 */
var serialize = function (root) {
  let res = [];
  let q = [root];
  while (q.length != 0) {
    let front = q.shift();
    if (front != null) {
      res.push(front.val);
      q.push(front.left);
      q.push(front.right);
    } else {
      res.push('null'); // 需要保存null节点的情况
    }
  }
  return res.join(',');
};

/**
 * 将编码后的字符串解码为二叉树
 * @param {string} data
 * @return {TreeNode}
 */
var deserialize = function (data) {
  data = data.split(',');
  let parent = []; // 保存上一层的父节点
  let index = 0;
  let root = null;
  while (index < data.length) {
    if (parent.length == 0) {  // 根节点的情况
      if (data[index] == 'null') return null; // 根节点为空
      root = new TreeNode(data[index]);
      parent.push(root);
      index++;
      continue;
    }
    let p = parent.shift();
    if (data[index] == 'null') { // p的左节点
      p.left = null;
    } else {
      let l = new TreeNode(data[index]);
      p.left = l;
      parent.push(l)
    }
    index++;
    if (index >= data.length) break;
    if (data[index] == 'null') {// p的右节点
      p.right = null;
    } else {
      let r = new TreeNode(data[index]);
      p.right = r;
      parent.push(r)
    }
    index++;
  }
  return root;
};

/**
 * Your functions will be called as such:
 * deserialize(serialize(root));
 */
function preOrder(root) {
  if (!root) return;
  console.log(root.val);
  preOrder(root.left);
  preOrder(root.right);
}
let r = new TreeNode(1);
let l1 = new TreeNode(2);
let r1 = new TreeNode(3);
r.left = l1;
r.right = r1;
let lr1 = new TreeNode(4);
let rr1 = new TreeNode(5);
r1.left = lr1;
r1.right = rr1;
let lr2 = new TreeNode(6);
let rr2 = new TreeNode(7);
lr1.left = lr2;
lr1.right = rr2;
preOrder(r);
console.log(serialize(r));
preOrder(deserialize(serialize(r)));