#ifndef LOCK_BASED_QUEUE_HPP
#define LOCK_BASED_QUEUE_HPP

#include <mutex>
#include <queue>

namespace lock_based_queue {

template <typename T>
class LockBasedQueue {
public:
    // std::mutex::try_lock() 
    bool tryPop(T& val);
    void push(const T& val);
private:
    std::queue<T> queue_;
    std::mutex mut_;
};


} // namespace lock_based_queue

#endif // LOCK_BASED_QUEUE_HPP