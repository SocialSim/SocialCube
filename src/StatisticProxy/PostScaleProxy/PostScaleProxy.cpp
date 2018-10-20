#include "PostScaleProxy.hpp"

using namespace std;

DBG(static const string tag="TypeDistributionProxy";)

TypeDistributionProxy::TypeDistributionProxy(const string& file) throw() {
    try {
        m_typeDistributionFile.open(file);
    } catch (exception &e) {
        TypeDistributionProxyException t_e;
        throw t_e;
    }
    assert(m_typeDistributionFile.is_open());
    return;
}

TypeDistributionProxy::~TypeDistributionProxy() {
    m_typeDistributionFile.close();
    return;
}

void TypeDistributionProxy::parse() {
    string tmp;
    while (getline(m_typeDistributionFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string distribution = tmp.substr(tmp.find(" ") + 1);
        unique_ptr<TypeDistribution> typeDistribution(new TypeDistribution(userID));

        istringstream in(distribution);
        for(size_t j = 0; j < TypeDistribution::getActionCount(); ++j) {
            double dist;
            in >> dist;
            typeDistribution->pushDist(dist);
        }
        m_typeDistribution[userID] = move(typeDistribution);
    }
    DBG(LOGD(TAG, "Type Distribution Rate has "+stringfy(m_typeDistribution.size()));)
}

void TypeDistributionProxy::show() {
    cout << m_typeDistribution.size() << endl; 
    for(auto& iter : m_typeDistribution) {
        iter.second->show();
    }
}

TypeDistribution& TypeDistributionProxy::get(const std::string& userID) {
    if(m_typeDistribution.find(userID) == m_typeDistribution.end()) {
        return *(m_typeDistribution["-1"]);
    } else {
        assert(m_typeDistribution.find(userID) != m_typeDistribution.end());
        return *(m_typeDistribution[userID]);
    }
}

