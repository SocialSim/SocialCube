#ifndef __SIMULATOR__
#define __SIMULATOR__

#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <cstdint>

#include "common/Event.hpp"
#include "Agent/UserAgent/UserAgent.hpp"
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "DependentEventLogger/DependentEventLogger.hpp"
#include "Log/Log.hpp"
#include "SimulatorProfiler.hpp"

using namespace std;

class Simulator {

protected:
    // Private member variables
    
    vector<unique_ptr<UserAgent>> m_userAgents;

    vector<unique_ptr<ObjectAgent>> m_objectAgents;

    vector<unique_ptr<Event>> m_eventHistory;

    uint64_t m_currentTime;

    uint64_t m_startTime;

    uint64_t m_endTime;

    uint64_t m_unitTime;

    unique_ptr<DependentEventLogger> m_dependentEventLogger;

    unique_ptr<SimulatorProfiler> m_profiler;

    bool m_profileOn;

    // Private member function

    void simulationCheck();

    void step();

    void logEventInDependentEventLogger(const vector<unique_ptr<Event>>& t_events);

    void appendEventInEventHistory(vector<unique_ptr<Event>>& t_events);

    void showProfile();

    virtual void simulateImpl();

public:

    Simulator();

    virtual ~Simulator();

    void setCurrentTime(uint64_t t_currentTime);

    void setStartTime(uint64_t t_startTime);

    void setEndTime(uint64_t t_endTime);

    void setUnitTime(uint64_t t_unitTime);

    void setProfile(bool t_profileOn);

    void setDependentEventLogger(unique_ptr<DependentEventLogger>& t_dependentEventLogger);

    void addUserAgent(unique_ptr<UserAgent> t_agent);

    void addObjectAgent(unique_ptr<ObjectAgent> t_agent);

    void transferUserAgent(vector<unique_ptr<UserAgent>>& t_agentList);

    virtual void simulate() final;

    void showEvent();

    uint64_t getCurrentTime();

    vector<string> getAllUserIDs();
};

#endif
