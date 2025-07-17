#include "thread_pool.h"
#include <stdexcept>
ThreadPool::ThreadPool(size_t size):stop(false)
{
    for (size_t i = 0; i < size; i++)
    {
        workers.emplace_back(
            [this]()
            {
                while (true)
                {
                    void_task_type task;
                    {
                        std::unique_lock<std::mutex> lock(mut);
                        cond.wait(lock, [this]
                                  { return stop || !tasks.empty(); });
                        if (stop && tasks.empty())
                        {
                            return;
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
    }
}
ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex>lock(mut);
        stop = true;
    }
    cond.notify_all();
    for(auto & work :workers){
        if(work.joinable()){
            work.join();
        }
        
    }
}

