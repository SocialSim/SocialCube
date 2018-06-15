#ifndef __DAILY_SIMPLE_GITHUB_USER__AGENT__
#define __DAILY_SIMPLE_GITHUB_USER__AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/DailySimpleBehaviorModel.hpp"
#include "common/Event.hpp"

class DailySimpleGithubUserAgent : public UserAgent {
protected:

    const StatisticProxy& m_statProxy;

    DailyActivityLevel& m_dailyActivityLevel;

    ObjectPreference& m_objectPreference;

    TypeDistribution& m_typeDistribution;

public:
    DailySimpleGithubUserAgent(const std::string& t_id);

    virtual ~DailySimpleGithubUserAgent();

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;
};

#endif
