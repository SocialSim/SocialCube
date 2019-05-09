#include "PostInfo.hpp"

using namespace std;

PostInfo::PostInfo() {
    return;
}

PostInfo::PostInfo(string t_postID, string t_userId, time_t t_timestamp) {
    m_postId = t_postID;
    m_userId = t_userId;
    m_timestamp = t_timestamp;

    return;
}

PostInfo::~PostInfo() {
    return;
}

void PostInfo::pushCommentAfterPost(string t_commentType, time_t t_timestamp) {
    m_commentSequence.push_back(std::make_pair(t_commentType, t_timestamp));
}

string PostInfo::getPostId() {
    return m_postId;
}

string PostInfo::getUserId() {
    return m_userId;
}

time_t PostInfo::getPostTimestamp() {
    return m_timestamp;
}

vector<pair<string, time_t>> PostInfo::getCommentSequence() {
    return m_commentSequence;
};

void PostInfo::show() {
    cout << m_postId << ", " << m_userId << ", " << m_timestamp << ", " << m_commentSequence.size() << endl;
}