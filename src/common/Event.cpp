#include "Event.hpp"

using namespace std;

Event::Event(string t_userID, string t_objectID, string t_eventType, string t_timestamp) :
    m_userID(t_userID), m_objectID(t_objectID), m_eventType(t_eventType), 
    m_timestamp(t_timestamp) {
    return;
}

Event::~Event() {
    return;
}

string Event::getUserID() {
    return m_userID;
}

string Event::getObjectID() {
    return m_objectID;
}

string Event::getEventType() {
    return m_eventType;
}

string Event::getTimestamp() {
    return m_timestamp;
}

void Event::show() {
    cout << m_userID << " " << m_objectID << " " << m_eventType << " " << m_timestamp << "\n";
}
