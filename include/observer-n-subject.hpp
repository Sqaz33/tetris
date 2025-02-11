#ifndef OBSERVER_N_SUBJECT_HPP
#define OBSERVER_N_SUBJECT_HPP

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

namespace observer_n_subject {

// TODO: 
// идея: подписочный сервис, Observer - чисто логический. Тип ивента - класс-тег.
// в сервисе, можно будет регистрироваться 
// Subjectам и Наблюдателям (+ указывать тип подписки/рассылки в виде тега)
enum class EventType: std::int8_t { 
    GAME_FIELD_UPDATE = 0,
    GAME_SCORE_UPDATE,
    GAME_FINISH,
    USER_ASKED_LEFT,
    USER_ASKED_RIGHT,
    USER_ASKED_DOWN,
    USER_ASKED_ROTATE_RIGHT,
    USER_ASKED_CLOSE_GAME
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