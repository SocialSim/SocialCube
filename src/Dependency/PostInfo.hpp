#ifndef __POST_INFO__
#define __POST_INFO__

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>

class PostInfo {

private:

    std::string m_postId;

    std::string m_userId;

    time_t m_timestamp;

    std::vector<std::pair<std::string, time_t>> m_commentSequence;

public:

    PostInfo();

    PostInfo(std::string t_postID, std::string t_userId, time_t t_timestamp);

    ~PostInfo();

    void pushCommentAfterPost(std::string t_commentType, time_t t_timestamp);

    std::string getUserId();

    time_t getPostTimestamp();

    std::vector<std::pair<std::string, time_t>> getCommentSequence();

    void show();
};

#endif
