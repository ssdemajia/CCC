/*
    线段树实现
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
#define INT_MAX 100000

class SegmentTree {
public:
    // 默认是1000个叶子节点，随着题目的条件增加
    SegmentTree(vector<int> & height){
        nums = vector<int>(30, -1);
        arr = vector<int>(height);
        build(height, 0, 0, arr.size()-1);
    }
    
    // height是外部的数组，build将height变为完全二叉树数组
    // 区域只有一个节点的为叶子结点
    void build(vector<int> &height, int root_index, int left, int right) { 
        if (left == right) {
            nums[root_index] = left;
            return;
        }
        int mid = (left + right)/2;
        build(height, root_index*2+1, left, mid);
        build(height, root_index*2+2, mid+1, right);
        int lindex = nums[root_index*2+1];
        int rindex = nums[root_index*2+2];
        nums[root_index] = arr[lindex] > arr[rindex]? rindex: lindex;
    }
    
    int query(int start, int end) {
        return __query(0, 0, arr.size()-1, start, end);
    }

    // 这里的index是在arr中的索引，而不是二叉树数组中的索引
    // 在__update中更新arr
    void update(int index, int val) {
        arr[index] = val;
        __update(0, 0, arr.size()-1);
    }
private:
    // 查询[target_left, target_right]范围内的数最小值, [start, end]表示当前查询的区域
    // 返回区域内最小值结点索引
    // 1. 当前节点表示的区域被包含于所要查询的区域，则直接返回节点索引.
    // 2. 当前节点区域与目标区域没有相交， 那么返回INT_MAX
    // 3. 当前节点区域与目标区域相交，那么分别查询左右两半区域，分属左右子节点，得到左右区域最小值的索引，取整个区域最小的值的索引
    //
    int __query(int root_index, int start, int end, int target_left, int target_right) {
        if (start >= target_left && end <= target_right)  return nums[root_index];
        if (end < target_left || start > target_right) return -1;
        int mid = (start+end)/2;
        int lindex = __query(root_index*2+1, start, mid, target_left, target_right);
        int rindex = __query(root_index*2+2, mid+1, end, target_left, target_right);
        if (lindex == -1 && rindex == -1) return -1;
        if (lindex == -1) return rindex;
        if (rindex == -1) return lindex;
        return arr[lindex] > arr[rindex]? rindex: lindex;
    }

    void __update(int root_index, int start, int end) {
        if (start >= end) return;
        int mid = (start + end) / 2;
        __update(root_index*2+1, start, mid);
        __update(root_index*2+2, mid+1, end);
        int lindex = nums[root_index*2+1];
        int rindex = nums[root_index*2+2];
        nums[root_index] = arr[lindex] > arr[rindex]? rindex: lindex;
    }
    vector<int> arr; // 外部数组
    vector<int> nums; // 完全二叉树数组
};

#define CHECK(left_index, right_index, target_index, tree)  cout << tree->query(left_index, right_index) << endl;\
                              assert(tree->query(left_index, right_index) == target_index);\

int main(int argc, char const *argv[])
{
    vector<int> height = {2,1,5,6,2,3};
    SegmentTree* t = new SegmentTree(height);
    CHECK(0, 0, 0, t)
    CHECK(0, 5, 1, t)
    CHECK(3, 5, 4, t)
    t->update(0, 0);
    CHECK(0, 5, 0, t)
    return 0;
}
