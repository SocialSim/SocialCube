#ifndef __EMBEDDING_CASCADE_MODEL__
#define __EMBEDDING_CASCADE_MODEL__

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

class EmbeddingCascadeModel {
private:

    EmbeddingCascadeModel();

    ~EmbeddingCascadeModel();

    static int generateLifespan(PostLifespanDistribution& t_postLifespanDistribution);

    static std::string generateNodeId();

    static int randomlyRoundDouble(double num);

    static int convertISOtoDay(time_t t_currentTime);

    static double generateGaussianRandom();

    static const int LOOK_BACK = 3;

public:

    static std::vector<std::unique_ptr<Event>> evaluate(const std::string t_id,
                                                        PostScale& t_postScale,
                                                        PostLifespanDistribution& t_postLifespanDistribution,
                                                        unordered_map<string, double> t_communityDistribution,
                                                        ScoreMatrix& t_scoreMatrix,
                                                        time_t t_startTime,
                                                        time_t t_endTime
    );

};

#endif
