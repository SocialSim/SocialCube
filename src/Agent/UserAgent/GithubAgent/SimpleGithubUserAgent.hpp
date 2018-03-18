#ifndef __SIMPLE_GITHUB_USER__AGENT__
#define __SIMPLE_GITHUB_USER__AGENT__

#include <vector>
#include <string>
#include <memory>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "common/Event.hpp"

class SimpleGithubUserAgent : public UserAgent {
    private:

        string m_id;

        shared_ptr<StatisticProxy> m_statProxy;

        HourlyActionRate m_hourlyActionRate;

        ObjectPreference m_objectPreference;

    public:
        SimpleGithubAgent(string t_id);

        ~SimpleGithubAgent();

        void setStatisticProxy(shared_ptr<StatisticProxy> t_statProxy);

        void build();

        std::vector<Event> step(uint64_t t_currentTime, uint64_t t_unitTime);
};

#endif
