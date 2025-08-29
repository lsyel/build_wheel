#include <memory>
#include <vector>
#include <string>
using namespace std;
class TrieTree{
public:
    TrieTree(){
        root_ = make_shared<TrieNode>();
    }
    void insert(const string& word){
        NodePtr node = root_;
        for(const char & c:word){
            int index = c-'a';
            if(!node->children_[index]){
                node->children_[index] = make_shared<TrieNode>();
            }
            node = node->children_[index];
        }
        node->is_end_ = true;
    }
    bool search(const string & word){
        NodePtr node = root_;
        for(const char & c:word){
            int index = c -'a';
            if(!node->children_[index])return false;
            node = node->children_[index];
        }
        return node->is_end_;
    }
    bool start_with(const string & prefix){
        NodePtr node = root_;
        for(const char & c: prefix){
            int index = c - 'a';
            if(!node->children_[index]) return false;
            node = node->children_[index];
        }
        return true;
    }
private:
    struct TrieNode{
        bool is_end_;
        vector<shared_ptr<TrieNode>> children_;
        TrieNode():is_end_(false),children_(26){}
    };
    using NodePtr = shared_ptr<TrieNode>;
    NodePtr root_;
};