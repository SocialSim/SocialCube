#include "ResponseTypeProbabilityProxy.hpp"

using namespace std;

DBG(static const string tag="ResponseTypeProbabilityProxy";)

ResponseTypeProbabilityProxy::ResponseTypeProbabilityProxy(const string& file) throw() {
    try {
        m_commentProbabilityFile.open(file);
    } catch (exception &e) {
        CommentProbabilityProxyException t_e;
        throw t_e;
    }
    assert(m_commentProbabilityFile.is_open());
    return;
}

ResponseTypeProbabilityProxy::~ResponseTypeProbabilityProxy() {
    m_commentProbabilityFile.close();
    return;
}

void ResponseTypeProbabilityProxy::parse() {
    string tmp;
    while (getline(m_commentProbabilityFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string probabilities = tmp.substr(tmp.find(" ") + 1);
        unique_ptr<ResponseTypeProbability> commentProb(new ResponseTypeProbability(userID));

        string user;
        string prob;
        
        // cout << "Scanning user " << userID << endl;

        vector<string> result;
        istringstream iss(probabilities);
        for (string probabilities; iss >> probabilities; )
            result.push_back(probabilities);

        for (auto & element : result) {
            commentProb->pushResponseType(element);
        }
        m_commentProbability[userID] = move(commentProb);
    }
    DBG(LOGD(TAG, "Comment Probability has "+stringfy(m_commentProbability.size()));)
}

// void ResponseTypeProbabilityProxy::parse() {
//     string tmp;
//     while (getline(m_commentProbabilityFile, tmp)) {
//         string userID = tmp.substr(0, tmp.find(" "));
//         string probabilities = tmp.substr(tmp.find(" ") + 1);
//         unique_ptr<ResponseTypeProbability> commentProb(new ResponseTypeProbability(userID));

//         string user;
//         string prob;
        
//         // cout << "Scanning user " << userID << endl;

//         istringstream in(probabilities);
//         while (in >> user) {
//             in >> prob;
//             // cout << user << " " << prob << endl;
//             commentProb->pushResponseType(user);
//             commentProb->pushResponseType(prob);
//         }
//         m_commentProbability[userID] = move(commentProb);
//     }
//     DBG(LOGD(TAG, "Comment Probability has "+stringfy(m_commentProbability.size()));)
// }

void ResponseTypeProbabilityProxy::show() {
    cout << m_commentProbability.size() << endl;
    for(auto& iter : m_commentProbability) {
        iter.second->show();
    }
}

ResponseTypeProbability& ResponseTypeProbabilityProxy::get(const std::string& userID) {
    if(m_commentProbability.find(userID) == m_commentProbability.end()) {
        throw;
    } else {
        assert(m_commentProbability.find(userID) != m_commentProbability.end());
        return *(m_commentProbability[userID]);
    }
}
