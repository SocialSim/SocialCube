#ifndef __CASCADE_MODEL__
#define __CASCADE_MODEL__

#include <vector>
#include <iostream>
#include <memory>
#include "common/Event.hpp"
#include "common/Exception.hpp"
#include "StatisticProxy/StatisticProxy.hpp"
#include "Dependency/PostScale.hpp"
#include "Dependency/CommentProbability.hpp"
#include "Dependency/PostLifespanDistribution.hpp"

class CascadeModel {
private:

    CascadeModel();

    ~CascadeModel();

//    StatisticProxy& m_statProxy;

    static int generateLifespan(PostLifespanDistribution& t_postLifespanDistribution);

    static std::string generateCommentUser(CommentProbability& t_commentProbability);

    static std::string generateNodeId();

    static int convertISOtoDay(time_t t_currentTime);

public:

    static std::vector<std::unique_ptr<Event>> evaluate(const std::string t_id,
                                                        PostScale& t_postScale,
                                                        PostLifespanDistribution& t_postLifespanDistribution,
                                                        time_t t_startTime,
                                                        time_t t_endTime
    );

};

#endif
