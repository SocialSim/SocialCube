#ifndef __SIMPLE_GITHUB_AGENT__
#define __SIMPLE_GITHUB_AGENT__

#include <vector>
#include <string>
#include <memory>
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "common/Event.hpp"

class SimpleGithubObjectAgent : public ObjectAgent {
    private:

        const StatisticProxy& m_statProxy;

    public:
        SimpleGithubObjectAgent(const std::string& t_id, const std::string& t_cc, const int& t_al);

        ~SimpleGithubObjectAgent();

        virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

        virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;
};

#endif

