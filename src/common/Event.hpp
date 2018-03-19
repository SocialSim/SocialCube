#ifndef __EVENT__
#define __EVENT__

#include <string>
#include <iostream>

class Event {
private:
    std::string m_userID;

    std::string m_objectID;

    std::string m_eventType;

    std::string m_timestamp;
public:
    Event(std::string t_userID, std::string t_objectID, std::string t_eventType, 
            std::string m_timestamp);

    ~Event();

    std::string getUserID();

    std::string getObjectID();

    std::string getEventType();

    std::string getTimestamp();

    void show();
};

#endif
