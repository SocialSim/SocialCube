#ifndef SOCIALCUBE_POISSONPROCESSOBJECTAGENT_HPP
#define SOCIALCUBE_POISSONPROCESSOBJECTAGENT_HPP

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "Dependency/PoissonProcessStat.hpp"
#include "BehaviorModel/PoissonProcessModel.hpp"
#include "common/Event.hpp"

class PoissonProcessObjectAgent: public ObjectAgent {
private:
    const StatisticProxy& m_statProxy;

    PoissonProcessStat& m_stat;

public:
    PoissonProcessObjectAgent(const std::string& t_id, const std::string& t_cc, const int& t_al);

    ~PoissonProcessObjectAgent() = default;

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(std::vector<float> temp_pref_data, time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;
};

#endif //SOCIALCUBE_POISSONPROCESSOBJECTAGENT_HPP
