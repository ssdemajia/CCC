/* 
跳表的实现， key是int，value是string类型

get_level()
  若p = rand()%100/100.0，则一个两层的节点需要p^2*(1-p), 三层的节点需要p^3(1-p),
  故平均层数等于(1-p) + 2p^2*(1-p) + 3p^3*(1-p) ... + n*p^n*(1-p) = 1/(1-p)
  因此如果p=1/4=0.25, 那么平均高度为1.33333
  */
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

struct Element
{
  Element() = default;
  Element(int k, string v, int level) : key(k), value(v), level(level), nexts(level) {}
  int key;
  string value;
  vector<Element *> nexts;
  int level;
};

class SkipList
{
public:
  SkipList(double p = 0.5, int max_level = 32) 
    :next_level_p(p), max_level(max_level), cur_level(0)
  {
    head = new Element();
    head->nexts = vector<Element*>(max_level); // 最大层数
    srand(time(0));
  }

  void Insert(int key, string value)
  {
    cout << "[insert]key:" << key << ",value:" << value << endl;
    Element* update[max_level];
    Element* x = head;
    for (int i = cur_level-1; i >= 0; i--)
    {
      while (x->nexts[i] && x->nexts[i]->key < key) {
        x = x->nexts[i];
      }
      update[i] = x; // 从上到下收集每一层最接近，且比key小的节点指针
    }
    Element* next = x->nexts[0];
    if (next && next->key == key) {
      next->value = value;
      return;
    }
    int level = get_level();
    cout << "[insert]level:" << level << endl;
    if (level > cur_level) { // 需要将新的层数指针也保持下来
      for (int i = cur_level; i < level; i++) {
        update[i] = head->nexts[i];
      }
      cur_level = level;
    }
    Element* ele = new Element(key, value, level);
    for (int i = 0; i < level; i++) { // 从下到上插入新节点
      if (!update[i]) {
        ele->nexts[i] = head->nexts[i];
        head->nexts[i] = ele;
        continue;
      }
      ele->nexts[i] = update[i]->nexts[i];
      update[i]->nexts[i] = ele;
    }
  }

  string Search(int key)
  {
    Element* x = head;
    for (int i = cur_level-1; i >= 0; i--) {
      while (x->nexts[i] && x->nexts[i]->key < key) {
        x = x->nexts[i];
      }
    }
    x = x->nexts[0];
    if (x && x->key == key) {
      return x->value;
    }
    return "";
  }

  void Delete(int key) {
    Element* update[max_level];
    Element* x = head;
    for (int i = cur_level-1; i >= 0; i--) {
      while (x->nexts[i] && x->nexts[i]->key < key) {
        x = x->nexts[i];
      }
      update[i] = x;
    }
    Element* target = x->nexts[0];
    if (!target || target->key != key) return;
    for (int i = 0; i < target->level; i++) {
      update[i]->nexts[i] = target->nexts[i];
    }
    while (cur_level > 0 && !head->nexts[cur_level]) // 降低高层空闲头部
      cur_level -= 1;
  }

private: 
  int get_level()
  {
    int level = 1;
    while (rand() % 100 / 100.0 < next_level_p && level < max_level)
    {
      level++;
    }
    return level;
  }
  double next_level_p;
  int max_level;
  int cur_level;
  Element* head;
};
#define HAS(s, key, value) assert(s.Search(key) == value);

int main()
{
  SkipList s;
  vector<pair<int, string>> input = {
    {1, "shaoshuai"},
    {2, "shao"},
    {3, "07"},
    {4, "bb"}
  };
  HAS(s, 1, "shuai")
  HAS(s, 2, "shao")
  HAS(s, 3, "07")
  HAS(s, 4, "bb")
  s.Delete(1);
  HAS(s, 1, "")
  s.Delete(2);
  HAS(s, 2, "")
}