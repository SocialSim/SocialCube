#ifndef __SIMULATOR__
#define __SIMULATOR__

#include <vector>
#include <string>

#include "common/Event"

using namespace std;

class Simulator {

private:
    vector<UserAgent*> m_userAgents;

    vector<ObjectAgent*> m_objectAgents;

    vector<Event> m_eventHistory;

    DepdendentEventLogger *m_dependentEventLogger;

    uint64_t m_currentTime;

    uint64_t m_startTime;

    uint64_t m_endTime;

    uint64_t m_unitTime;

public:

    Simulator();

    ~Simulator();

    void setCurrentTime(uint64_t t_currentTime);

    void setStartTime(uint64_t t_startTime);

    void setEndTime(uint64_t t_endTime);

    void setUnitTime(uint64_t t_unitTime);

    void setDependentEventLogger(DepdendentEventLogger *t_dependentEventLogger);

    void addUserAgent(UserAgent *t_agent);

    void addObjectAgent(ObjectAgent *t_agent);

    void simulate();

    void step();

    void logEventInDependentEventLogger(const vector<Event> &t_events);

    void appendEventInEventHistory(const vector<Event> &t_events);

    void showEvent();

    uint64_t getCurrentTime();

    vector<string> getAllUserIDs();
};

#endif
