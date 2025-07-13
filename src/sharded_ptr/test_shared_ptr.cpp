// 测试用例
#include <iostream>
#include "shared_ptr.h"
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