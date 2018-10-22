#include "CommentProbability.hpp"

using namespace std;

CommentProbability::CommentProbability(std::string t_userID) : m_userID(t_userID) {
    return;
}

CommentProbability::~CommentProbability() {
    return;
}

void CommentProbability::pushProb(std::string t_userID, double t_prob) {
    m_comment_prob.push_back(std::pair<std::string, double>(t_userID, t_prob));
}

std::vector<std::pair<std::string, double>> CommentProbability::getCommentProb() {
    return m_comment_prob;
};

void CommentProbability::show() {
    cout << "userID: " << m_userID << endl;
    for(auto& iter : m_comment_prob) {
        cout << iter.first << ", " << iter.second << endl;
    }
    cout << endl;
}