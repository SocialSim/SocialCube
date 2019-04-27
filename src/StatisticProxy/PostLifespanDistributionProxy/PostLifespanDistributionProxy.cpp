#include "PostLifespanDistributionProxy.hpp"

using namespace std;

DBG(static const string tag="PostLifespanDistributionProxy";)

PostLifespanDistributionProxy::PostLifespanDistributionProxy(const string& file) throw() {
    try {
        m_postLifespanDistributionFile.open(file);
    } catch (exception &e) {
        PostLifespanDistributionProxyException t_e;
        throw t_e;
    }
    assert(m_postLifespanDistributionFile.is_open());
    return;
}

PostLifespanDistributionProxy::~PostLifespanDistributionProxy() {
    m_postLifespanDistributionFile.close();
    return;
}

void PostLifespanDistributionProxy::parse() {
    string tmp;
    while (getline(m_postLifespanDistributionFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string distribution = tmp.substr(tmp.find(" ") + 1);

        unique_ptr<PostLifespanDistribution> postLifespanDistribution(new PostLifespanDistribution(userID));
        int lifespan;
        double prob;
        istringstream in(distribution);
        while (in >> lifespan) {
            in >> prob;
            postLifespanDistribution->pushLifespanDist(lifespan, prob);
        }
        m_postLifespanDistribution[userID] = move(postLifespanDistribution);
    }
    DBG(LOGD(TAG, "Post Lifespan Distribution has "+stringfy(m_postLifespanDistribution.size()));)
}

void PostLifespanDistributionProxy::show() {
    cout << m_postLifespanDistribution.size() << endl;
    for(auto& iter : m_postLifespanDistribution) {
        iter.second->show();
    }
}

PostLifespanDistribution& PostLifespanDistributionProxy::get(const std::string& userID) {
    if(m_postLifespanDistribution.find(userID) == m_postLifespanDistribution.end()) {
        return *(m_postLifespanDistribution["[global]"]);
    } else {
        assert(m_postLifespanDistribution.find(userID) != m_postLifespanDistribution.end());
        return *(m_postLifespanDistribution[userID]);
    }
}
