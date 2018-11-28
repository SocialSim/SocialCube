#ifndef __SEED_CASCADE_MODEL__
#define __SEED_CASCADE_MODEL__

#include <vector>
#include <iostream>
#include <memory>
#include <random>
#include "common/Event.hpp"
#include "common/Exception.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "Dependency/PostScale.hpp"
#include "Dependency/CommentProbability.hpp"
#include "Dependency/PostLifespanDistribution.hpp"

class SeedCascadeModel {
private:

    SeedCascadeModel();

    ~SeedCascadeModel();

    static int generateLifespan(PostLifespanDistribution& t_postLifespanDistribution);

    static std::string generateNodeId();

    static int randomlyRoundDouble(double num);

    static int convertISOtoDay(time_t t_currentTime);

public:

    static std::vector<std::unique_ptr<Event>> evaluate(const std::string t_id,
                                                        PostScale& t_postScale,
                                                        PostLifespanDistribution& t_postLifespanDistribution,
                                                        std::unordered_map<std::string, double> t_communityDistribution,
                                                        time_t t_startTime,
                                                        time_t t_endTime
    );

};

#endif
