#include "ThreadPool.h"

namespace cpp
{

ThreadPool::ThreadPool(size_t num)
    : m_bStop(false)
{
    num = num <= 0 ? 4 : num;

    for (size_t i = 0; i < num; i++)
    {
        m_vecThreads.emplace_back(new std::thread([this](){

            while (!m_bStop)
            {
                task_t task; 
                {
                    std::unique_lock<std::mutex> lock(m_mutex);
                    m_cv.wait(lock, [this](){
                        return m_bStop || !m_queueTasks.empty(); 
                    });

                    if (m_bStop && m_queueTasks.empty())
                    {
                        return;
                    }
                    task = m_queueTasks.front();
                    m_queueTasks.pop();
                }

                task();
            }
        }));
    }

}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_bStop = true;
    }
    m_cv.notify_all();

    for (auto t : m_vecThreads)
    {
        if(t->joinable())
        {
            t->join();
        }
    }
}
   
} // namespace cpp
