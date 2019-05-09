#ifndef __CASCADE_SEQUENCE__
#define __CASCADE_SEQUENCE__

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>
#include "Dependency/PostInfo.hpp"
#include "Dependency/ScoreMatrix.hpp"
#include "common/Exception.hpp"

class CascadeSequence {

private:

    std::string m_infoId;

    std::unordered_map<std::string, PostInfo> m_posts;

    ScoreMatrix m_scoreMatrix;

public:

    CascadeSequence(std::string t_infoId);

    ~CascadeSequence();

    void pushPost(std::string t_postId, std::string t_userId, time_t t_timestamp);

    void pushCommentAfterPost(std::string t_postId, std::string t_commentType, time_t t_timestamp);

    void setScoreMatrix(ScoreMatrix t_scoreMatrix);

    std::vector<PostInfo> getPosts();

    ScoreMatrix& getScoreMatrix();

    void show();
};

#endif
