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

    uint64_t m_timestamp;

public:
    Event(const std::string& t_userID, const std::string& t_objectID, const std::string& t_eventType, 
            uint64_t m_timestamp);

    ~Event();

    std::string getUserID() const;

    std::string getObjectID() const;

    std::string getEventType() const;

    uint64_t getTimestamp() const;

    void show() const;

    friend std::ostream& operator<<(std::ostream& os, const Event& e);  
};

#endif
