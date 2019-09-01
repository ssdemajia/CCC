/*
    使用javascript实现并差集，可用于leetcode547
*/


function UnionSet() {
    this.parent = new Array({length:300}, x => -1);
    this.height = new Array({length:300}, x => -1);
    this.len;
}

UnionSet.prototype.makeSet = function(x) {
    for (let i = 0; i < x; i++) {
        this.parent[i] = i;
        this.height[i] = 1;
    }
    this.len = x;
}

UnionSet.prototype.find = function(x) {
    let root = x;
    while (root != this.parent[root]) {  // 找到根结点
        root = this.parent[root];
    }
    
    while (x != root) { // 路径压缩，也就是修改父节点
        let parentX = this.parent[x];
        this.height[x] = 1;
        this.parent[x] = root;
        x = parentX;
    }
    this.height[root] = 2;
    return root;
}

UnionSet.prototype.union = function (x, y) { // 合并两个集合
    let rootX = this.find(x);
    let rootY = this.find(y);
    if (rootX == rootY) return;
    if (this.height[rootX] < this.height[rootY]) { // rootY将作为RootX的新父节点
        this.parent[rootX] = rootY;
    } else {
        if (this.height[rootX] == this.height[rootY]) {
            this.height[rootX] += 1;
        }
        this.parent[rootY] = rootX;
    }
}
UnionSet.prototype.size = function () {
    let roots = new Set();
    for (let i = 0; i < this.len; i++) {
        roots.add(this.find(i));
    }
    return roots.size;
}

// 测试效果
var findCircleNum = function(m) {
    let s = new UnionSet();
    s.makeSet(m.length);
    for (let i = 0; i < m.length; i++) {
        for (let j = 0; j < m[i].length; j++) {
            if (i>j && m[i][j] == 1) {
                s.union(i, j);
            }
        }
    }
    return s.size();
};

function main() {
    let m = [
        [1, 1, 0, 0],
        [1, 1, 1, 0],
        [0, 1, 0, 1],
        [0, 0, 1, 0]
    ]
    console.log(findCircleNum(m) === 1);
}