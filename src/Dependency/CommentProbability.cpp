#include "CommentProbability.hpp"

using namespace std;

CommentProbability::CommentProbability(std::string t_userID) : m_userID(t_userID) {
    return;
}

CommentProbability::~CommentProbability() {
    return;
}

void CommentProbability::pushProb(std::string t_userID, double t_prob) {
    m_comment_prob.insert(std::pair<std::string, double>(t_userID, t_prob));
}

std::vector<std::pair<std::string, double>> getCommentProb() {
    return m_comment_prob;
};

void PostScale::show() {
    cout << "userID: " << m_userID << end;
    for(auto& iter : m_comment_prob) {
        cout << iter[0] << ", " << iter[1] << endl;
    }
    cout << endl;
}