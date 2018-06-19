#ifndef __SIMULATOR__
#define __SIMULATOR__

#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <math.h>  
#include <dirent.h>
#include <algorithm>

#include "common/Event.hpp"
#include "common/Exception.hpp"
#include "Agent/UserAgent/UserAgent.hpp"
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "DependentEventLogger/DependentEventLogger.hpp"
#include "Log/Log.hpp"
#include "SimulatorProfiler/SimulatorProfiler.hpp"
#include "CommunityManager.hpp"
#include "StatisticProxy/StatisticProxy.hpp"

class Simulator {

protected:
    // Private member variables
    
    std::unique_ptr<CommunityManager> m_communityManager;

    StatisticProxy& m_statProxy;

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

    std::vector<std::vector<float>> temp_pref_data;

    std::vector<std::vector<float>> temp_pref_data_weekly;

    std::vector<std::string> cc_list;

    /********************** All setter function *************************/

    virtual void setStartTime(time_t t_startTime);

    virtual void setEndTime(time_t t_endTime);

    virtual void setUnitTime(time_t t_unitTime);

    virtual void addUserAgent(Agent const * t_agent);

    virtual void addObjectAgent(Agent const * t_agent);

    virtual void simulate() final;

    virtual void testSetup() final;

    virtual std::string getCc(const std::string& s);
};

#endif
