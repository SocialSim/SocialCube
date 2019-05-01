#ifndef __SEED_GITHUB_USER_AGENT__
#define __SEED_GITHUB_USER_AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/SeedHourlySimpleBehaviorModel.hpp"
#include "common/Event.hpp"

class SeedGithubUserAgent : public UserAgent {

public:
    SeedGithubUserAgent(const std::string& t_id);

    virtual ~SeedGithubUserAgent();

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;
};

#endif
