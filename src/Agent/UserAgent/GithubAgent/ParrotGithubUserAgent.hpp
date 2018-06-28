#ifndef __PARROT_GITHUB_USER__AGENT__
#define __PARROT_GITHUB_USER__AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/WeeklyEventCountBehaviorModel.hpp"
#include "common/Event.hpp"

class ParrotGithubUserAgent : public UserAgent {
protected:

    const StatisticProxy& m_statProxy;

    DailyActivityLevel& m_dailyActivityLevel;

    WeeklyEventCount& m_weeklyEventCount;

    ObjectPreference& m_objectPreference;

    TypeDistribution& m_typeDistribution;

public:
    ParrotGithubUserAgent(const std::string& t_id, const std::string& t_cc, const int& t_al);

    virtual ~ParrotGithubUserAgent();

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(std::vector<float> temp_pref_data, time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;
};

#endif
