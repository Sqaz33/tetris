#include "../include/observer-n-subject.hpp"

#include <algorithm>

namespace observer_n_subject {

void SubjectImpl::attach(std::shared_ptr<IObserver> observer, EventType event) {
    observers_.push_back({observer, event});
}

void SubjectImpl::detach(std::shared_ptr<IObserver> observer) {
    std::erase_if(
        observers_,
        [observer](auto& p) {
            return p.first.lock() == observer;
        }
    );
}

void SubjectImpl::notify(EventType event) {
    for (auto it = observers_.begin(); it != observers_.end();) {
        auto wptr = it->first;
        auto curEvent = it->second;
        auto obs = wptr.lock();
        if (obs) ++it;
        if (obs && curEvent == event) {
            obs->update(*this, event);
        } else if (!obs) {
            observers_.erase(it);
        }
    }
}   

} // namespace observer_n_subject