#pragma once

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>

namespace cpp
{

class ThreadPool
{
public:
    using ptr = std::shared_ptr<ThreadPool>; 
    using task_t = std::function<void()>;

    ThreadPool(size_t num = 4);

    ~ThreadPool();

    template<typename F, typename... Args>
    auto push(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> 
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_bStop)
            {
                throw "thread pool is stoped";
            }
            m_queueTasks.emplace([task](){ (*task)(); });
        }
        m_cv.notify_one();
        return res; 
    }

private:
    bool m_bStop;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::queue<task_t> m_queueTasks;
    std::vector<std::thread*> m_vecThreads;
};
    
} // namespace cpp
