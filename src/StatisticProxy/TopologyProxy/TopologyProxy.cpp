#include "TopologyProxy.hpp"

DBG(static const string tag="TopologyProxy";)

using namespace std;

TopologyProxy::TopologyProxy(const string& file) throw() {
    try {
        m_topologyStatisticFile.open (file);
    } catch (exception &e) {
        TopologyProxyException h_e;
        throw h_e;
    }
    assert(m_topologyStatisticFile.is_open());

    return;
}

TopologyProxy::~TopologyProxy() {
    m_topologyStatisticFile.close();
    return;
}

void TopologyProxy::parse() {
    string tmp;
    while (getline(m_topologyStatisticFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string probabilities = tmp.substr(tmp.find(" ") + 1);
        unordered_map<string, double> userCommentProbs;

        string user_id;
        string prob;

        istringstream in(probabilities);
        while (in >> user_id) {
            in >> prob;
            userCommentProbs.insert(std::make_pair<string, double>((string)user_id, stod(prob)));
        }
        m_userCommentProbs[userID] = userCommentProbs;
    }
}

void TopologyProxy::show() {
    cout << m_userCommentProbs.size() << endl;
}

unordered_map<string, double> TopologyProxy::get(const std::string& userID) {
    return m_userCommentProbs[userID];
}

