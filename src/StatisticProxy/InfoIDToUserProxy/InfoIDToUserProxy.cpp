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
        string infoID = tmp.substr(0, tmp.find(" "));
        string probabilities = tmp.substr(tmp.find(" ") + 1);
        unordered_map<string, double> infoIDToUserDistribution;

        string user_id;
        string prob;

        istringstream in(probabilities);
        while (in >> user_id) {
            in >> prob;
            infoIDToUserDistribution.insert(std::make_pair<string, double>((string)user_id, stod(prob)));
        }
        m_infoIDToUser[infoID] = infoIDToUserDistribution;
    }
}

void InfoIDToUserProxy::show() {
    cout << m_infoIDToUser.size() << endl;
}

unordered_map<string, double> InfoIDToUserProxy::get(const std::string& infoID) {
    return m_infoIDToUser[infoID];
}

