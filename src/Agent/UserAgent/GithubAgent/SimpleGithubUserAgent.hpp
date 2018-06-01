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
    protected:

        const StatisticProxy& m_statProxy;

        HourlyActionRate& m_hourlyActionRate;

        ObjectPreference& m_objectPreference;

        TypeDistribution& m_typeDistribution;

    public:
        SimpleGithubUserAgent(const std::string& t_id, const std::string& t_cc, const int& t_al);

        virtual ~SimpleGithubUserAgent();

        virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

        virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

        virtual uint64_t getCommunityTag() const;
};

#endif
