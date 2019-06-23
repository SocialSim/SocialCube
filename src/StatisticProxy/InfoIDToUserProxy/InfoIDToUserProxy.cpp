#include "InfoIDToUserProxy.hpp"

DBG(static const string tag="InfoIDToUserProxy";)

using namespace std;

InfoIDToUserProxy::InfoIDToUserProxy(const string& file) throw() {
    try {
        m_infoIDToUserStatisticFile.open (file);
    } catch (exception &e) {
        InfoIDToUserProxyException h_e;
        throw h_e;
    }
    assert(m_infoIDToUserStatisticFile.is_open());

    return;
}

InfoIDToUserProxy::~InfoIDToUserProxy() {
    m_infoIDToUserStatisticFile.close();
    return;
}

void InfoIDToUserProxy::parse() {
    string tmp;
    while (getline(m_infoIDToUserStatisticFile, tmp)) {
        string infoID = tmp.substr(0, tmp.find(","));
        string preferenceCount = tmp.substr(tmp.find(",") + 1);
        unordered_map<string, double> infoIDToUserDistribution;

        for(int i = 0; i < stoi(preferenceCount); ++i) {
            getline(m_infoIDToUserStatisticFile, tmp);
            string user_id = tmp.substr(0, tmp.find(","));
            string prob = tmp.substr(tmp.find(",") + 1);
            infoIDToUserDistribution.insert(std::make_pair<string, double>((string)user_id, stod(prob)));
        }

        if(stoi(preferenceCount) != 0)
            m_infoIDToUser[infoID] = infoIDToUserDistribution;
    }
}

void InfoIDToUserProxy::show() {
    cout << m_infoIDToUser.size() << endl;
}

unordered_map<string, double> InfoIDToUserProxy::get(const std::string& infoID) {
    return m_infoIDToUser[infoID];
}

string InfoIDToUserProxy::getUserByInfoID(const std::string &infoID) {
    string selected_user;

    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    double sum = 0;
    for (auto &iter : m_infoIDToUser[infoID]) {
        sum += iter.second;
        if (randnum <= sum) {
            selected_user = iter.first;
            break;
        }
    }
    return selected_user;
}

