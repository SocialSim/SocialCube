#include "CommentProbabilityProxy.hpp"

using namespace std;

DBG(static const string tag="CommentProbabilityProxy";)

CommentProbabilityProxy::CommentProbabilityProxy(const string& file) throw() {
    try {
        m_commentProbabilityFile.open(file);
    } catch (exception &e) {
        CommentProbabilityProxyException t_e;
        throw t_e;
    }
    assert(m_commentProbabilityFile.is_open());
    return;
}

CommentProbabilityProxy::~CommentProbabilityProxy() {
    m_commentProbabilityFile.close();
    return;
}

void CommentProbabilityProxy::parse() {
    string tmp;
    while (getline(m_commentProbabilityFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string probabilities = tmp.substr(tmp.find(" ") + 1);
        unique_ptr<CommentProbability> commentProb(new CommentProbability(userID));

        string user;
        double prob;
        istringstream in(probabilities);
        while (in >> user) {
            in >> prob;
            commentProb->pushProb(user, prob);
        }
        m_commentProbability[userID] = move(commentProb);
    }
    for (auto& iter : m_commentProbability) {
        iter.second->show();
    }
    DBG(LOGD(TAG, "Comment Probability has "+stringfy(m_commentProbability.size()));)
}

void CommentProbabilityProxy::show() {
    cout << m_commentProbability.size() << endl;
    for(auto& iter : m_commentProbability) {
        iter.second->show();
    }
}

CommentProbability& CommentProbabilityProxy::get(const std::string& userID) {
    if(m_commentProbability.find(userID) == m_commentProbability.end()) {
        throw;
    } else {
        assert(m_commentProbability.find(userID) != m_commentProbability.end());
        return *(m_commentProbability[userID]);
    }
}