#ifndef __EVENT__
#define __EVENT__

#include <string>
#include <cstdint>
#include <iostream>
#include "StatisticProxy/StatisticProxy.hpp"

class Event {
private:
    std::string m_userID;

    std::string m_objectID;

    std::string m_eventType;

    time_t m_timestamp;

    std::string m_action;

    bool m_merged;

public:
    Event(const std::string& t_userID, const std::string& t_objectID, const std::string& t_eventType, time_t m_timestamp);

    ~Event();

    std::string getUserID() const;

    std::string getObjectID() const;

    std::string getEventType() const;

    time_t getTimestamp() const;

    std::string getTimestampStr() const;

    std::string getTimestampStrInSeconds() const;

    std::string getAction() const;

    std::string getMerged() const;

    void setAction(double p_opened, double p_closed, double p_reopened);

    void setMerged(double p);

    void warpTimestamp(time_t startTime, double ratio);

    void show() const;

//    bool operator< (const Event &other) const;

    friend std::ostream& operator<<(std::ostream& os, const Event& e);
};

#endif
