#include "Event.hpp"

using namespace std;

Event::Event(string t_userID, string t_objectID, string t_eventType, uint64_t t_timestamp) :
    m_userID(t_userID), m_objectID(t_objectID), m_eventType(t_eventType), 
    m_timestamp(t_timestamp) {
    return;
}

Event::~Event() {
    return;
}

string Event::getUserID() const {
    return m_userID;
}

string Event::getObjectID() const {
    return m_objectID;
}

string Event::getEventType() const {
    return m_eventType;
}

uint64_t Event::getTimestamp() const {
    return m_timestamp;
}

void Event::show() const {
    cout << m_userID << " " << m_objectID << " " << m_eventType << " " << m_timestamp << "\n";
}
