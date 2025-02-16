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
    USER_ASKED_CLOSE_GAME,
    USER_ASKED_PAUSE_GAME
};

class ISubject;

class IObserver {
public:
    virtual void update(ISubject& subject, EventType event) = 0;
    virtual ~IObserver() {}
};

class ISubject {
public:
    virtual void attach(std::shared_ptr<IObserver> observer, EventType event) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;

public:
    virtual ~ISubject() {}
};

class SubjectImpl : public ISubject {
public:
    void attach(std::shared_ptr<IObserver> observer, EventType event) override;
    void detach(std::shared_ptr<IObserver> observer) override;

protected:
    void notify(EventType event);

private:
    std::vector<std::pair<std::weak_ptr<IObserver>, EventType>> observers_;
};

} // namespace observer_n_subject

#endif // OBSERVER_N_SUBJECT_HPP