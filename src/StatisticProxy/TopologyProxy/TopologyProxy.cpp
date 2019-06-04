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
//    string tmp;
//    while (getline(m_topologyStatisticFile, tmp)) {
//        string userID = tmp.substr(0, tmp.find(","));
//        string probabilities = tmp.substr(tmp.find(",") + 1);
//        unordered_map<string, double> userCommentProbs;
//
//        string user_id;
//        string prob;
//
//        istringstream in(probabilities);
////        while (in >> user_id) {
////            in >> prob;
////            userCommentProbs.insert(std::make_pair<string, double>((string)user_id, stod(prob)));
////        }
//
//        while (in.good()) {
//            getline(in, user_id, ',');
//            getline(in, prob, ',');
//            userCommentProbs.insert(std::make_pair<string, double>((string)user_id, stod(prob)));
//        }
//
//        m_userCommentProbs[userID] = userCommentProbs;
//    }
    string tmp;
    while (getline(m_topologyStatisticFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(","));
        string preferenceCount = tmp.substr(tmp.find(",") + 1);
        unordered_map<string, double> userCommentProbs;

        for(int i = 0; i < stoi(preferenceCount); ++i) {
            getline(m_topologyStatisticFile, tmp);
            string user_id = tmp.substr(0, tmp.find(","));
            string prob = tmp.substr(tmp.find(",") + 1);
            userCommentProbs.insert(std::make_pair<string, double>((string)user_id, stod(prob)));
        }

        if(stoi(preferenceCount) != 0)
            m_userCommentProbs[userID] = userCommentProbs;
    }
}

void TopologyProxy::show() {
    cout << m_userCommentProbs.size() << endl;
}

unordered_map<string, double> TopologyProxy::get(const std::string& userID) {
    return m_userCommentProbs[userID];
}

string TopologyProxy::getUserByTopology(const std::string &userID) {
    string selected_user;

    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    double sum = 0;
    for (auto &iter : m_userCommentProbs[userID]) {
        sum += iter.second;
        if (randnum <= sum) {
            selected_user = iter.first;
            break;
        }
    }
    return selected_user;
}

