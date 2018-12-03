#include "PostBreadthDistributionProxy.hpp"

using namespace std;

DBG(static const string tag="PostBreadthDistributionProxy";)

PostBreadthDistributionProxy::PostBreadthDistributionProxy(const string& file) throw() {
    try {
        m_postBreadthDistributionFile.open(file);
    } catch (exception &e) {
        PostLifespanDistributionProxyException t_e;
        throw t_e;
    }
    assert(m_postBreadthDistributionFile.is_open());
    return;
}

PostBreadthDistributionProxy::~PostBreadthDistributionProxy() {
    m_postBreadthDistributionFile.close();
    return;
}

void PostBreadthDistributionProxy::parse() {
    string tmp;
    while (getline(m_postBreadthDistributionFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string distribution = tmp.substr(tmp.find(" ") + 1);

        unique_ptr<PostBreadthDistribution> postBreadthDistribution(new PostBreadthDistribution(userID));
        int breadth;
        double prob;
        istringstream in(distribution);
        while (in >> breadth) {
            in >> prob;
            postBreadthDistribution->pushBreadthDist(breadth, prob);
        }
        m_postBreadthDistribution[userID] = move(postBreadthDistribution);
    }
    DBG(LOGD(TAG, "Post Breadth Distribution has "+stringfy(m_postBreadthDistribution.size()));)
}

void PostBreadthDistributionProxy::show() {
    cout << m_postBreadthDistribution.size() << endl;
    for(auto& iter : m_postBreadthDistribution) {
        iter.second->show();
    }
}

PostBreadthDistribution& PostBreadthDistributionProxy::get(const std::string& userID) {
    if(m_postBreadthDistribution.find(userID) == m_postBreadthDistribution.end()) {
        throw;
    } else {
        assert(m_postBreadthDistribution.find(userID) != m_postBreadthDistribution.end());
        return *(m_postBreadthDistribution[userID]);
    }
}
