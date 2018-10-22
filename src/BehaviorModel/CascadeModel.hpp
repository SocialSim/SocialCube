#ifndef __CASCADE_MODEL__
#define __CASCADE_MODEL__

#include <vector>
#include <iostream>
#include <memory>
#include "common/Event.hpp"
#include "common/Exception.hpp"
#include "Dependency/PostScale.hpp"
#include "Dependency/CommentProbability.hpp"
#include "Dependency/PostLifespanDistribution.hpp"

class CascadeModel {
private:

    CascadeModel();

    ~CascadeModel();

    static int generateLifespan(const PostLifespanDistribution& t_postLifespanDistribution);

    static std::string generateCommentUser(const CommentProbability& t_commentProbability);

    static std::string generateNodeId();

public:

    static std::vector<std::unique_ptr<Event>> evaluate(const std::string t_id,
                                                        PostScale& t_postScale,
                                                        PostLifespanDistribution& t_postLifespanDistribution,
                                                        CommentProbabilityProxy& t_commentProbabilityProxy,

                                                        time_t t_startTime,
                                                        time_t t_endTime
    );

};

#endif
