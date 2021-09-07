#ifndef __EVENT_QUEUE_HPP__
#define __EVENT_QUEUE_HPP__
#include <functional>
#include <vector>
#include <bitset>
#include <queue>
#include "ClassIdentity.hpp"

enum Event {
    Resize,
    FullScreen
};

constexpr std::uint32_t EventsNumber = 2u;

class EventQueue {
private:
    struct EventData {
        Event eventType;
        Identity::ClassIdentity classId;
        std::function<void()> callbackFun;
    };

public:
    static void SubscribeIndependent(
        Event event, std::function<void()> callback, Identity::ClassIdentity id
    ) noexcept;
    static void SubscribeAssociated(Event event, std::function<void()> callback) noexcept;
    static void AddEvent(Event event) noexcept;
    static void Dispatch() noexcept;

private:
    void _SubscribeIndependent(
        Event event, std::function<void()> callback, Identity::ClassIdentity id
    ) noexcept;
    void _SubscribeAssociated(Event event, std::function<void()> callback) noexcept;
    void _AddEvent(Event event) noexcept;
    void _Dispatch() noexcept;

private:
    bool m_isSubQueueSorted = false;
    std::bitset<EventsNumber> m_events;
    std::vector<EventData> m_eventSubIndependent;
    std::vector<std::vector<std::function<void()>>> m_eventSubAssociated{EventsNumber};
    std::queue<Event> m_associatedEvents;

    static EventQueue s_instance;
};
#endif