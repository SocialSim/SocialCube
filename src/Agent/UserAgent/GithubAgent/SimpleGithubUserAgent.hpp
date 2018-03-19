#ifndef __SIMPLE_GITHUB_USER__AGENT__
#define __SIMPLE_GITHUB_USER__AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "common/Event.hpp"

class SimpleGithubUserAgent : public UserAgent {
    private:

        const StatisticProxy& m_statProxy;

        const HourlyActionRate& m_hourlyActionRate;

        const ObjectPreference& m_objectPreference;

    public:
        SimpleGithubAgent(const std::string& t_id);

        ~SimpleGithubAgent();

        std::vector<Event> step(uint64_t t_currentTime, uint64_t t_unitTime);
};

#endif
