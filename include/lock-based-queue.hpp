#ifndef LOCK_BASED_QUEUE_HPP
#define LOCK_BASED_QUEUE_HPP

#include <mutex>
#include <queue>

namespace lock_based_queue {

template <typename T>
class LockBasedQueue {
public:
    // std::mutex::try_lock() 
    bool tryPop(T& val) {
        std::unique_lock<std::mutex> lk(mut_, std::defer_lock_t{}); 
        if (!lk.try_lock()) return false;   
        if (queue_.empty()) return false;   
        auto pop = [&] {    
            auto front = std::move(queue_.front()); 
            queue_.pop();   
            return front;   
        };  
        val = pop();    
        return true;  
    }

    void push(const T& val) {
        std::lock_guard<std::mutex> lk{mut_};   
        queue_.push(val);  
    }
private:
    std::queue<T> queue_;
    std::mutex mut_;
};


} // namespace lock_based_queue

#endif // LOCK_BASED_QUEUE_HPP