#ifndef __SPECIFIC_CASCADE_MODEL__
#define __SPECIFIC_CASCADE_MODEL__

#include <vector>
#include <iostream>
#include <memory>
#include <random>
#include <algorithm> 
#include "common/Event.hpp"
#include "common/Exception.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "Dependency/PostScale.hpp"
#include "Dependency/ResponseTypeProbability.hpp"
#include "Dependency/PostBreadthDistribution.hpp"
#include "Dependency/SpecificResponseDistribution.hpp"

class SpecificCascadeModel {
private:

    SpecificCascadeModel();

    ~SpecificCascadeModel();

    static int generateBreadth(PostBreadthDistribution& t_postBreadthDistribution);

    static int generateLifespan(PostLifespanDistribution& t_postLifespanDistribution);

    static std::string generateSpecificResponse(SpecificResponseDistribution& t_specificResponseDistribution);

    static std::string chooseResponseType(std::vector <std::string> &responseTypes, std::vector <double> &responseProbabilities);

    static std::string generateNodeId();

    static int randomlyRoundDouble(double num);

    static int convertISOtoDay(time_t t_currentTime);

public:

    static std::vector<std::unique_ptr<Event>> evaluate(const std::string t_id,
                                                        PostScale& t_postScale,
                                                        PostBreadthDistribution& t_postBreadthDistribution,
                                                        std::unordered_map<std::string, double> t_communityDistribution,
                                                        time_t t_startTime,
                                                        time_t t_endTime
    );

};

#endif
