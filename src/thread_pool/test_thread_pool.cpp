#include "thread_pool.h"
#include <iostream>
int main(){
// 测试用例
ThreadPool pool(4);

// 测试普通任务
auto future1 = pool.enqueue([]{ return 42; });

// 测试异常传播
auto future2 = pool.enqueue([]{
    throw std::runtime_error("test");
    return 0;
});

// 测试高并发
std::vector<std::future<int>> futures;
for (int i = 0; i < 1000; ++i) {
    futures.push_back(pool.enqueue([i]{ std::cout<<i<<"\t";return i * i; }));
}

// 测试安全关闭
pool.~ThreadPool(); // 显式析构测试
}