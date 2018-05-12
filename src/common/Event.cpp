#include "Event.hpp"

using namespace std;

Event::Event(const string& t_userID, const string& t_objectID, const string& t_eventType, time_t t_timestamp) :
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

string Event::getTimestamp() const {

    char buf[sizeof "1970-00-00T00:00:00Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&m_timestamp));
    return buf;
}

void Event::show() const {
    cout << getTimestamp() << " " << getObjectID() << " " << getUserID() << " " << getEventType() << "\n";
}

ostream& operator<<(ostream& os, const Event& e)
{  
    os << e.getTimestamp() << "," << e.getEventType() << "," << e.getUserID() << "," << e.getObjectID() << "\n";
    return os;  
} 
