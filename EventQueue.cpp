#include <algorithm>
#include "EventQueue.hpp"

EventQueue EventQueue::s_instance;

void EventQueue::SubscribeIndependent(
    Event event, std::function<void()> callback, Identity::ClassIdentity id
) noexcept {
    s_instance._SubscribeIndependent(event, callback, id);
}

void EventQueue::SubscribeAssociated(
    Event event, std::function<void()> callback
) noexcept {
    s_instance._SubscribeAssociated(event, callback);
}

void EventQueue::AddEvent(Event event) noexcept {
    s_instance._AddEvent(event);
}

void EventQueue::Dispatch() noexcept {
    s_instance._Dispatch();
}

void EventQueue::_SubscribeIndependent(
    Event event, std::function<void()> callback, Identity::ClassIdentity id
) noexcept {
    m_eventSubIndependent.emplace_back(event, id, callback);

    m_isSubQueueSorted = false;
}


void EventQueue::_SubscribeAssociated(
    Event event, std::function<void()> callback
) noexcept {
    m_eventSubAssociated[event].emplace_back(callback);
}

void EventQueue::_AddEvent(Event event) noexcept {
    if (!m_events[event])
        m_events[event].flip();
    
    m_associatedEvents.emplace(event);
}

void EventQueue::_Dispatch() noexcept {
    while (!m_associatedEvents.empty()) {
        Event event = m_associatedEvents.front();

        for (auto& callBacks : m_eventSubAssociated[event])
            callBacks();

        m_associatedEvents.pop();
    }

    if (!m_isSubQueueSorted) {
        std::sort(m_eventSubIndependent.begin(), m_eventSubIndependent.end(),
            [](EventData data1, EventData data2) {
                return data1.classId < data2.classId;
            }
        );

        m_isSubQueueSorted = true;
    }

    for (EventData eventData : m_eventSubIndependent)
        if (m_events[eventData.eventType])
            eventData.callbackFun();

    m_events.reset();
}