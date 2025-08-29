#include <iostream>
#include <unordered_map>
#include <memory>
using namespace std;
class LRUCache {
public:
    explicit LRUCache(size_t capacity):capacity_(capacity){
        head_ = make_shared<Node>();
        tail_ = make_shared<Node>();
        head_->next_ = tail_;
        tail_->pre_ = head_;
    }
    int* get(const int key){
        if(auto it = cache_map_.find(key);it !=cache_map_.end()){
            NodePtr node = it->second;
            node->pre_.lock()->next_ = node->next_;
            node->next_->pre_ = node->pre_;

            node->pre_ = head_;
            node->next_ = head_->next_;
            node->pre_.lock()->next_ = node;
            node->next_->pre_ = node;
            return &node->value_;
        }
        return nullptr;
    }
    void put(const int key,const int value){
        if(auto it = cache_map_.find(key);it!=cache_map_.end()){
            it->second->value_ = value;
            get(key);
            return;
        }else{
            NodePtr node = make_shared<Node>(key,value);
            cache_map_[key]=node;
            node->pre_ = head_;
            node->next_ = head_->next_;
            
            node->pre_.lock()->next_ = node;
            node->next_->pre_ = node;
            if(cache_map_.size()>capacity_){
                NodePtr del_node = tail_->pre_.lock();
                cache_map_.erase(del_node->key_);
                del_node->next_->pre_ = del_node->pre_;
                del_node->pre_.lock()->next_ = del_node->next_;
            }
            return;
        }

    }
    void print(){
        NodePtr p = head_;
        while(p){
            if(p == head_){
                cout<<"head->";
            }else if(p == tail_){
                cout<<"tail"<<endl;
            }else{
                cout<<p->value_<<"->";
            }
            p = p->next_;
        }
    }
private:
    struct Node{
        int key_;
        int value_;
        weak_ptr<Node> pre_;
        shared_ptr<Node> next_;
        Node() = default;
        Node(const int k,const int v):key_(k),value_(v),next_(nullptr){}
        ~Node(){
            cout<<"destruct"<<",key:"<<key_<<",value:"<<value_<<endl;
        }
    };
    using NodePtr  = shared_ptr<Node>;
    NodePtr head_;
    NodePtr tail_;
    unordered_map<int,NodePtr> cache_map_;
    size_t capacity_;
};

// 测试函数
void test_lru_cache() {
    std::cout << "=== LRUCache Test ===\n";
    
    // 创建容量为3的缓存
    LRUCache cache(3);
    
    // 测试1: 基本添加和获取
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.print();
    
    int* value = cache.get(1);
    if (value) {
        std::cout << "Get key 1: " << *value << "\n";
        *value = 11; // 直接修改缓存值
        std::cout << "Modified key 1: " << *cache.get(1) << "\n";
    }
    cache.print();
    
    // 测试2: 超出容量淘汰
    cache.put(4, 40);
    cache.print();
    
    // 检查被淘汰节点
    if (!cache.get(2)) {
        std::cout << "Key 2 correctly evicted\n";
    }
    // 测试3: 添加大量条目
    for (int i = 5; i <= 10; i++) {
        cache.put(i, i*10);
    }
    cache.print();
}

int main() {
    test_lru_cache();
    return 0;
}