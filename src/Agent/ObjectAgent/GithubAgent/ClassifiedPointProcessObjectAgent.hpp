#ifndef __CLASSIFIED_POINT_PROCESS_OBJECT_AGENT__
#define __CLASSIFIED_POINT_PROCESS_OBJECT_AGENT__

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "Dependency/PointProcessStat.hpp"
#include "BehaviorModel/IntegratedPointProcessModel.hpp"
#include "common/Event.hpp"

class ClassifiedPointProcessObjectAgent: public ObjectAgent {
private:
    StatisticProxy& m_statProxy;

    PointProcessStat& m_stat;

public:
    ClassifiedPointProcessObjectAgent(const std::string& t_id);

    ~ClassifiedPointProcessObjectAgent() = default;

    virtual std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime) const override;

    virtual std::vector<std::unique_ptr<Event>> simulate(time_t t_currentTime, time_t t_endTime) const override;

    virtual uint64_t getCommunityTag() const;
};

#endif

