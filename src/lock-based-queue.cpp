#if 0

#include "../include/lock-based-queue.hpp"

#include <mutex>

namespace lock_based_queue {

template <typename T>
bool LockBasedQueue<T>::tryPop(T& val) {    
    std::unique_lock<std::mutex> lk {mut_}; 
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
    
template <typename T>   
void LockBasedQueue<T>::push(const T& val) {    
    std::lock_guard<std::mutex> lk{mut_};   
    queue_.push(val);   
}   
    
} // namespace lock_based_queue 

#endif