#include "CommunityDistributionProxy.hpp"

DBG(static const string tag="CommunityDistributionProxy";)

using namespace std;

CommunityDistributionProxy::CommunityDistributionProxy(const string& file) throw() {
    try {
        m_communityDistributionStatisticFile.open (file);
    } catch (exception &e) {
        CommunityDistributionProxyException h_e;
        throw h_e;
    }
    assert(m_communityDistributionStatisticFile.is_open());

    return;
}

CommunityDistributionProxy::~CommunityDistributionProxy() {
    m_communityDistributionStatisticFile.close();
    return;
}

void CommunityDistributionProxy::parse() {
    string tmp;
    while (getline(m_communityDistributionStatisticFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string probabilities = tmp.substr(tmp.find(" ") + 1);
        unordered_map<string, double> userCommunityDistribution;

        string community_id;
        string prob;

        istringstream in(probabilities);
        while (in >> community_id) {
            in >> prob;
            userCommunityDistribution.insert(std::make_pair<string, double>((string)community_id, stod(prob)));
        }
        m_userCommunityDistributions[userID] = userCommunityDistribution;
    }
}

void CommunityDistributionProxy::show() {
    cout << m_userCommunityDistributions.size() << endl;
}

unordered_map<string, double> CommunityDistributionProxy::get(const std::string& userID) {
    if(m_userCommunityDistributions.find(userID) == m_userCommunityDistributions.end()) {
        return m_userCommunityDistributions[userID];
    } else {
        assert(m_userCommunityDistributions.find(userID) != m_userCommunityDistributions.end());
        return m_userCommunityDistributions[userID];
    }
}

