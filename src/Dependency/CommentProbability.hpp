#ifndef __COMMENT_PROBABILITY__
#define __COMMENT_PROBABILITY__

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>

class CommentProbability {

private:

    std::vector<std::pair<std::string, double>> m_comment_prob;

    std::string m_userID;

public:

    CommentProbability(std::string t_userID);

    ~CommentProbability();

    void pushProb(std::string t_userID, double t_prob);

    std::vector<std::pair<std::string, double>> getCommentProb();

    void show();
};

#endif
