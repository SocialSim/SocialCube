#ifndef __SIMPLE_GITHUB_USER__AGENT__
#define __SIMPLE_GITHUB_USER__AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/SimpleBehaviorModel.hpp"
#include "common/Event.hpp"

class SimpleGithubUserAgent : public UserAgent {
    private:

        const StatisticProxy& m_statProxy;

        HourlyActionRate& m_hourlyActionRate;

        ObjectPreference& m_objectPreference;

    public:
        SimpleGithubUserAgent(const std::string& t_id);

        ~SimpleGithubUserAgent();

        std::vector<std::unique_ptr<Event>> step(uint64_t t_currentTime, uint64_t t_unitTime);
};

#endif
