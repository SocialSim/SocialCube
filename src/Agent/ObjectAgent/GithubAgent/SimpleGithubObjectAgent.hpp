#ifndef __SIMPLE_GITHUB_AGENT__
#define __SIMPLE_GITHUB_AGENT__

#include <vector>
#include <string>
#include <memory>
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "common/Event.hpp"

class SimpleGithubObjectAgent : public ObjectAgent{
    private:

        string m_id;

        shared_ptr<StatisticProxy> m_statProxy;

        HourlyActionRates m_hourlyActionRates;

        ObjectPreference m_objectPreference;

    public:
        SimpleGithubObjectAgent(string t_id);

        ~SimpleGithubObjectAgent();

        void setStatisticProxy(shared_ptr<StatisticProxy> t_statProxy);

        void build();

        std::vector<Event> step(uint64_t t_currentTime, uint64_t t_unitTime);
};

#endif
