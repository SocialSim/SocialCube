#include "SpecificResponseDistributionProxy.hpp"

using namespace std;

DBG(static const string tag="SpecificResponseDistributionProxy";)

SpecificResponseDistributionProxy::SpecificResponseDistributionProxy(const string& file) throw() {
    try {
        m_specificResponseDistributionFile.open(file);
    } catch (exception &e) {
        PostLifespanDistributionProxyException t_e;
        throw t_e;
    }
    assert(m_specificResponseDistributionFile.is_open());
    return;
}

SpecificResponseDistributionProxy::~SpecificResponseDistributionProxy() {
    m_specificResponseDistributionFile.close();
    return;
}

void SpecificResponseDistributionProxy::parse() {
    string tmp;
    while (getline(m_specificResponseDistributionFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string distribution = tmp.substr(tmp.find(" ") + 1);

        unique_ptr<SpecificResponseDistribution> specificResponseDistribution(new SpecificResponseDistribution(userID));
        string response;
        double prob;
        istringstream in(distribution);
        while (in >> response) {
            in >> prob;
            specificResponseDistribution->pushResponseDist(response, prob);
        }
        m_specificResponseDistribution[userID] = move(specificResponseDistribution);
    }
    DBG(LOGD(TAG, "Post Response Distribution has "+stringfy(m_specificResponseDistribution.size()));)
}

void SpecificResponseDistributionProxy::show() {
    cout << m_specificResponseDistribution.size() << endl;
    for(auto& iter : m_specificResponseDistribution) {
        iter.second->show();
    }
}

SpecificResponseDistribution& SpecificResponseDistributionProxy::get(const std::string& userID) {
    if(m_specificResponseDistribution.find(userID) == m_specificResponseDistribution.end()) {
        cout << "No response distribution found for user " << userID << endl;
        throw;
    } else {
        assert(m_specificResponseDistribution.find(userID) != m_specificResponseDistribution.end());
        return *(m_specificResponseDistribution[userID]);
    }
}
