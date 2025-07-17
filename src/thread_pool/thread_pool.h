#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <future>
#include <stdexcept>
class ThreadPool
{
public:
    using void_task_type = std::function<void()>;
    
    explicit ThreadPool(size_t size);
    ThreadPool(const ThreadPool &other) = delete;
    ThreadPool &operator=(const ThreadPool &other) = delete;
    ~ThreadPool();
    template <typename T>
    auto enqueue(T &&task) -> std::future<decltype(task())>
    {
        using ReturnType = decltype(task());
        auto ptask = std::make_shared<std::packaged_task<ReturnType()>>(
            std::forward<T>(task));
        std::future<ReturnType> ret = ptask->get_future();
        {
            std::unique_lock<std::mutex> lock(mut);
            if (stop)
            {
                throw std::runtime_error("forbidden add a task to a stoped threadpool");
            }

            tasks.emplace([ptask]()
                          { (*ptask)(); });
        }

        cond.notify_one();
        return ret;
    }

private:
    std::vector<std::thread> workers;
    std::queue<void_task_type> tasks;
    bool stop;
    std::mutex mut;
    std::condition_variable cond;
};