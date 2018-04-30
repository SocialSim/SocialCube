#ifndef __SIMULATOR__
#define __SIMULATOR__

#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <cstdint>
#include <fstream>

#include "common/Event.hpp"
#include "common/Exception.hpp"
#include "Agent/UserAgent/UserAgent.hpp"
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "DependentEventLogger/DependentEventLogger.hpp"
#include "Log/Log.hpp"
#include "SimulatorProfiler/SimulatorProfiler.hpp"
#include "CommunityManager.hpp"

class Simulator {

protected:
    // Private member variables
    
    std::unique_ptr<CommunityManager> m_communityManager;

    time_t m_startTime;

    time_t m_endTime;

    time_t m_unitTime;

    // Private member function

    virtual void preSimulationConfig();

    virtual void postSimulationConfig();

    virtual void simulateImpl();

	virtual void printConfig();

public:

    Simulator();

    virtual ~Simulator();

    /********************** All setter function *************************/

    virtual void setStartTime(time_t t_startTime);

    virtual void setEndTime(time_t t_endTime);

    virtual void setUnitTime(time_t t_unitTime);

    virtual void addUserAgent(Agent const * t_agent);

    virtual void addObjectAgent(Agent const * t_agent);

    virtual void simulate() final;
};

#endif
