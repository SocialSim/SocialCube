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

string Event::getTimestampStr() const {

    char buf[sizeof "1970-00-00T00:00:00Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&m_timestamp));
    return buf;
}

time_t Event::getTimestamp() const {
    return m_timestamp;
}

void Event::warpTimestamp(time_t startTime, double ratio) {
    cout << "startTime = " << ctime(&startTime) << ", ratio = " << ratio << ", m_timestamp = " << ctime(&m_timestamp);
    m_timestamp = (m_timestamp - startTime) * ratio + startTime;
    cout << ", new m_timestamp = " << ctime(&m_timestamp) << endl;
}

void Event::show() const {
    cout << getTimestampStr() << " " << getObjectID() << " " << getUserID() << " " << getEventType() << "\n";
}

ostream& operator<<(ostream& os, const Event& e)
{  
    os << e.getTimestampStr() << "," << e.getEventType() << "," << e.getUserID() << "," << e.getObjectID() << "\n";
    return os;  
}

//bool Event::operator< (const Event &other) const {
//    std::cout << "operator <" << std::endl;
//    return m_timestamp < other.getTimestamp();
//}