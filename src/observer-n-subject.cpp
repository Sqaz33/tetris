#include <../include/observer-n-subject.hpp>

#include <algorithm>

namespace observer_n_subject {

void Subject::attach(std::shared_ptr<Observer> observer, EventType event) {
    observers_.push_back({observer, event});
}

void Subject::detach(std::shared_ptr<Observer> observer) {
    std::erase(
        observers_,
        [observer](const auto& p) {
            return p.first.lock() == observer;
        }
    );
}

void Subject::notify(EventType event) {
    for (auto it = observers_.begin(); it != observers_.end();) {
        auto wptr = it->first;
        auto curEvent = it->second;
        if (auto obs = wptr.lock() && curEvent == event) {
            obs->update(this, event);
            ++it;
        } else if (!obs) {
            observers_.erase(it);
        }
    }
}   

} // namespace observer_n_subject