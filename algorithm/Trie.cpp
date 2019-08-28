/*
    前缀树的实现
*/
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;
struct Node {
    bool word;
    unordered_map<char, Node*> words;
};
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new Node();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node* p = root;
        for (char c: word) {
            if (p->words.find(c) == p->words.end()) {
                Node* t = new Node();
                p->words[c] = t;
            } 
            p = p->words[c];
        }
        p->word = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node* p = root;
        for (char c: word) {
            if (p->words.find(c) == p->words.end()) return false;
            p = p->words[c];
        }
        return p->word;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node* p = root;
        for (char c: prefix) {
            if (p->words.find(c) == p->words.end()) return false;
            p = p->words[c];
        }
        return true;
    }
private:
    Node* root;
};


#ifdef TESTS
int main() {
  Trie* t = new Trie();
  t->insert("abc");
  t->insert("abcde");
  cout << (t->search("ab")? "true":"false") << endl;
  cout << (t->startsWith("ab")?"true":"false") << endl;
  cout << (t->startsWith("abc")?"true":"false") << endl;
}
#endif