#include <iostream>
#include <utility>

template<typename T>
class shared_ptr {
private:
    T* ptr;
    size_t* ref_count;
    
    // 释放资源的私有方法
    void release() {
        if (ref_count) {
            --(*ref_count);
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
            }
        }
    }
    
public:
    // 默认构造函数
    shared_ptr() : ptr(nullptr), ref_count(nullptr) {}
    
    // 从裸指针构造
    explicit shared_ptr(T* p) : ptr(p), ref_count(new size_t(1)) {}
    
    // 拷贝构造函数
    shared_ptr(const shared_ptr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) {
            ++(*ref_count);
        }
    }
    
    // 移动构造函数
    shared_ptr(shared_ptr&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }
    
    // 拷贝赋值运算符
    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) {
                ++(*ref_count);
            }
        }
        return *this;
    }
    
    // 移动赋值运算符
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }
    
    // 析构函数
    ~shared_ptr() {
        release();
    }
    
    // 解引用运算符
    T& operator*() const {
        return *ptr;
    }
    
    // 指针访问运算符
    T* operator->() const {
        return ptr;
    }
    
    // 获取原始指针
    T* get() const {
        return ptr;
    }
    
    // 获取引用计数
    size_t use_count() const {
        return ref_count ? *ref_count : 0;
    }
    
    // 检查是否为空
    bool empty() const {
        return ptr == nullptr;
    }
    
    // 重置为空
    void reset() {
        release();
        ptr = nullptr;
        ref_count = nullptr;
    }
    
    // 重置为新指针
    void reset(T* p) {
        release();
        ptr = p;
        ref_count = p ? new size_t(1) : nullptr;
    }
    
    // 布尔转换
    explicit operator bool() const {
        return ptr != nullptr;
    }
    
    // 比较运算符
    bool operator==(const shared_ptr& other) const {
        return ptr == other.ptr;
    }
    
    bool operator!=(const shared_ptr& other) const {
        return ptr != other.ptr;
    }
};

// 工厂函数 make_shared
c

// 测试用例
class TestClass {
public:
    int value;
    
    TestClass(int v) : value(v) {
        std::cout << "TestClass constructed with value: " << value << std::endl;
    }
    
    ~TestClass() {
        std::cout << "TestClass destructed with value: " << value << std::endl;
    }
    
    void print() const {
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    std::cout << "=== shared_ptr 测试 ===" << std::endl;
    
    // 测试1: 基本构造和引用计数
    {
        std::cout << "\n--- 测试1: 基本功能 ---" << std::endl;
        shared_ptr<TestClass> ptr1 = make_shared<TestClass>(42);
        std::cout << "ptr1 引用计数: " << ptr1.use_count() << std::endl;
        
        {
            shared_ptr<TestClass> ptr2 = ptr1;
            std::cout << "ptr1 引用计数: " << ptr1.use_count() << std::endl;
            std::cout << "ptr2 引用计数: " << ptr2.use_count() << std::endl;
            
            ptr1->print();
            ptr2->print();
        }
        
        std::cout << "ptr2 销毁后，ptr1 引用计数: " << ptr1.use_count() << std::endl;
    }
    
    // 测试2: 移动语义
    {
        std::cout << "\n--- 测试2: 移动语义 ---" << std::endl;
        shared_ptr<TestClass> ptr1 = make_shared<TestClass>(100);
        std::cout << "ptr1 引用计数: " << ptr1.use_count() << std::endl;
        
        shared_ptr<TestClass> ptr2 = std::move(ptr1);
        std::cout << "移动后 ptr1 引用计数: " << ptr1.use_count() << std::endl;
        std::cout << "移动后 ptr2 引用计数: " << ptr2.use_count() << std::endl;
        std::cout << "ptr1 是否为空: " << ptr1.empty() << std::endl;
    }
    
    // 测试3: reset 功能
    {
        std::cout << "\n--- 测试3: reset 功能 ---" << std::endl;
        shared_ptr<TestClass> ptr = make_shared<TestClass>(200);
        std::cout << "重置前引用计数: " << ptr.use_count() << std::endl;
        
        ptr.reset();
        std::cout << "重置后引用计数: " << ptr.use_count() << std::endl;
        std::cout << "ptr 是否为空: " << ptr.empty() << std::endl;
        
        ptr.reset(new TestClass(300));
        std::cout << "重新赋值后引用计数: " << ptr.use_count() << std::endl;
    }
    
    std::cout << "\n=== 测试完成 ===" << std::endl;
    return 0;
}