#include "CascadeSequence.hpp"

using namespace std;

CascadeSequence::CascadeSequence(std::string t_infoId) : m_scoreMatrix() {
    m_infoId = t_infoId;
    return;
}

CascadeSequence::~CascadeSequence() {
    return;
}

void CascadeSequence::pushPost(string t_postId, string t_userId, time_t t_timestamp) {
    m_posts.insert(make_pair(t_postId, PostInfo(t_postId, t_userId, t_timestamp)));
}

void CascadeSequence::pushCommentAfterPost(string t_postId, string t_commentType, time_t t_timestamp) {
    std::unordered_map<string, PostInfo>::iterator it = m_posts.find(t_postId);
    if (it != m_posts.end()) {
        it->second.pushCommentAfterPost(t_commentType, t_timestamp);
    } else {
        cout << "postID: " << t_postId << " doesn't exist!" << endl;
    }
}

void CascadeSequence::setScoreMatrix(ScoreMatrix t_scoreMatrix) {
    m_scoreMatrix = t_scoreMatrix;
}

unordered_map<string, PostInfo> CascadeSequence::getPosts() {
    return m_posts;
}

ScoreMatrix& CascadeSequence::getScoreMatrix() {
    return m_scoreMatrix;
}

void CascadeSequence::show() {
    cout << "InfoID: " << m_infoId << ", number of posts: " << m_posts.size() << endl;
}