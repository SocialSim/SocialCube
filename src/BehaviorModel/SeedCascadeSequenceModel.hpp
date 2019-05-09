#ifndef __SEED_CASCADE_SEQUENCE_MODEL__
#define __SEED_CASCADE_SEQUENCE_MODEL__

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
#include "Dependency/PostInfo.hpp"
#include "Dependency/CascadeSequence.hpp"
#include "Dependency/PostInfo.hpp"

class SeedCascadeSequenceModel {
private:

    SeedCascadeSequenceModel();

    ~SeedCascadeSequenceModel();

    static std::string generateNodeId();

    static int randomlyRoundDouble(double num);

    static int convertISOtoDay(time_t t_currentTime);

    static double generateGaussianRandom();

    static const int LOOK_BACK = 3;

public:

    static std::vector<std::unique_ptr<Event>> evaluate(const std::string t_infoId,
                                                        ScoreMatrix& t_scoreMatrix,
                                                        time_t t_startTime,
                                                        time_t t_endTime
    );

};

#endif
