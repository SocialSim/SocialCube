#ifndef __EVENT__
#define __EVENT__

#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
//#include "StatisticProxy/StatisticProxy.hpp"

class Event {
private:
    std::string m_userID;

    std::string m_objectID;

    std::string m_eventType;

    std::string m_parentID;

    std::string m_rootID;

    time_t m_timestamp;

    std::string m_action;

    std::string m_communityID;

    std::string m_infoID;

    bool m_merged;

public:
    Event(const std::string& t_userID, const std::string& t_objectID, const std::string& t_eventType, time_t m_timestamp);

    Event(const std::string& t_userID, const std::string& t_objectID, const std::string& t_eventType,
          const std::string& t_parentID, const std::string& t_rootID, time_t t_timestamp);

    Event(const std::string& t_userID, const std::string& t_objectID, const std::string& t_eventType,
          const std::string& t_parentID, const std::string& t_rootID);

    ~Event();

    std::string getUserID() const;

    std::string getObjectID() const;

    std::string getEventType() const;

    std::string getParentID() const;

    std::string getRootID() const;

    time_t getTimestamp() const;

    std::string getTimestampStr() const;

    std::string getTimestampStrInSeconds() const;

    std::string getAction() const;

    std::string getMerged() const;

    std::string getCommunityID() const;

    std::string getInfoID() const;

    void setTime(time_t p_time);

    void setAction(double p_opened, double p_closed, double p_reopened);

    void setCommunityID(std::string p_communityID);

    void setMerged(double p);

    void setInfoID(std::string p_infoID);

    void warpTimestamp(time_t startTime, double ratio);

    void show() const;

//    bool operator< (const Event &other) const;

    friend std::ostream& operator<<(std::ostream& os, const Event& e);
};

#endif
