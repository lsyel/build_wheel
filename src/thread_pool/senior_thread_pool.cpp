#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>
#include <memory>

class ThreadPool {
public:
    // 单例模式获取实例
    static ThreadPool& getInstance(size_t threads = std::thread::hardware_concurrency()) {
        static ThreadPool instance(threads);
        return instance;
    }

    // 禁止拷贝和移动
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // 提交任务接口（完美转发）
    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        // 获取返回类型
        using return_type = decltype(f(args...));
        
        // 创建packaged_task（使用完美转发）
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        // 获取future
        std::future<return_type> res = task->get_future();
        
        {
            // 加锁保护任务队列
            std::unique_lock<std::mutex> lock(queue_mutex);
            
            // 如果线程池已停止，不允许添加新任务
            if (stop.load()) {
                throw std::runtime_error("submit on stopped ThreadPool");
            }
            
            // 将任务添加到队列
            tasks.emplace([task]() { (*task)(); });
        }
        
        // 通知一个等待线程
        condition.notify_one();
        return res;
    }

    // 停止线程池
    void shutdown() {
        // 原子操作设置停止标志
        stop.store(true);
        
        // 唤醒所有线程
        condition.notify_all();
        
        // 等待所有线程结束
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    // 获取任务队列大小
    size_t pendingTasks() {
        std::unique_lock<std::mutex> lock(queue_mutex);
        return tasks.size();
    }

    ~ThreadPool() {
        if (!stop.load()) {
            shutdown();
        }
    }

private:
    // 私有构造函数（单例模式）
    ThreadPool(size_t threads) : stop(false) {
        // 创建工作线程
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    
                    {
                        // 等待新任务或停止信号
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] {
                            return this->stop.load() || !this->tasks.empty();
                        });
                        
                        // 如果停止且任务队列为空，结束线程
                        if (this->stop.load() && this->tasks.empty()) {
                            return;
                        }
                        
                        // 获取任务
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    
                    // 执行任务
                    task();
                }
            });
        }
    }

    // 工作线程
    std::vector<std::thread> workers;
    
    // 任务队列（生产者-消费者模型）
    std::queue<std::function<void()>> tasks;
    
    // 互斥锁（保护任务队列）
    std::mutex queue_mutex;
    
    // 条件变量（线程同步）
    std::condition_variable condition;
    
    // 停止标志（原子操作）
    std::atomic<bool> stop;
};

// 测试函数
int main() {
    // 获取线程池实例
    ThreadPool& pool = ThreadPool::getInstance(4);
    
    // 提交多个任务
    std::vector<std::future<int>> results;
    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.submit([i] {
                std::cout << "Task " << i << " started on thread " 
                          << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "Task " << i << " finished" << std::endl;
                return i * i;
            })
        );
    }
    
    // 获取结果
    for (auto& result : results) {
        std::cout << "Result: " << result.get() << std::endl;
    }
    
    // 检查任务队列
    std::cout << "Pending tasks: " << pool.pendingTasks() << std::endl;
    
    // 停止线程池
    pool.shutdown();
    
    return 0;
}