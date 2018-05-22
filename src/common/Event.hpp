#ifndef __EVENT__
#define __EVENT__

#include <string>
#include <cstdint>
#include <iostream>

class Event {
private:
    std::string m_userID;

    std::string m_objectID;

    std::string m_eventType;

    time_t m_timestamp;

public:
    Event(const std::string& t_userID, const std::string& t_objectID, const std::string& t_eventType, time_t m_timestamp);

    ~Event();

    std::string getUserID() const;

    std::string getObjectID() const;

    std::string getEventType() const;

    std::string getTimestamp() const;

    void warpTimestamp(time_t startTime, double ratio);

    void show() const;

    friend std::ostream& operator<<(std::ostream& os, const Event& e);  
};

#endif
