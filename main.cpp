#include <iostream>
#include "EventQueue.hpp"

class X {
public:
    void funF() {
        std::cout << "Full screen of X.\n";
    }

    void funR() {
        std::cout << "Resize of X.\n";
    }

    void AddF() {
        EventQueue::AddEvent(FullScreen);
    }
};

class Y {
public:
    void funF() {
        std::cout << "Full screen of Y.\n";
    }

    void funR() {
        std::cout << "Resize of Y.\n";
    }
};

int main() {
    X x;
    Y y;

    EventQueue::SubscribeAssociated(Resize, std::bind(&X::AddF, &x));
    EventQueue::SubscribeIndependent(FullScreen, std::bind(&X::funF, &x), Identity::X);

    EventQueue::SubscribeIndependent(Resize, std::bind(&Y::funR, &y), Identity::Y);
    EventQueue::SubscribeIndependent(FullScreen, std::bind(&Y::funF, &y), Identity::Y);
    
    EventQueue::AddEvent(Resize);
    // EventQueue::AddIndependentEvent(FullScreen);

    EventQueue::Dispatch();

    // EventQueue::AddIndependentEvent(Resize);

    EventQueue::Dispatch();

    return 0;
}