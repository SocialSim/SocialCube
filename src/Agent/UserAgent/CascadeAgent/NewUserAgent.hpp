#ifndef __New_USER_AGENT__
#define __New_USER_AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>
#include "Agent/UserAgent/UserAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "BehaviorModel/NewUserModel.hpp"
#include "common/Event.hpp"

class NewUserAgent : public UserAgent {
protected:

    const StatisticProxy& m_statProxy;

public:
    NewUserAgent(const std::string& t_id);

    virtual ~NewUserAgent();

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;

};

#endif
