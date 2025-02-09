#ifndef OBSERVER_N_SUBJECT_HPP
#define OBSERVER_N_SUBJECT_HPP

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

namespace observer_n_subject {

enum class EventType: std::int8_t { 
    GAME_FIELD_UPDATE = 0,
    GAME_SCORE_UPDATE,
    GAME_FINISH
};

class Subject;

class Observer {
public:
    virtual void update(Subject& subject, EventType event) = 0;
    virtual ~Observer() {}
};

class Subject {
public:
    virtual void attach(std::shared_ptr<Observer> observer, EventType event) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;

protected:
    virtual void notify(EventType event) = 0;

public:
    virtual ~Subject() {}

private:
    std::vector<std::pair<std::weak_ptr<Observer>, EventType>> observers_;
};

} // namespace observer_n_subject

#endif // OBSERVER_N_SUBJECT_HPP