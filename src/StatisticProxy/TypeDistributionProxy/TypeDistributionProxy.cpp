#include "TypeDistributionProxy.hpp"

using namespace std;

TypeDistributionProxy::TypeDistributionProxy() throw() {
    try {
        string filePath(getenv("SOCIALCUBEPATH"));
        filePath += "/statistics/user_type_distribution.json";
        m_typeDistributionFile.open (filePath);
    } catch (exception &e) {
        HourlyActionRateProxyException h_e;
        throw h_e;
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
    cout << "Type Distributions Rate has " << m_typeDistribution.size() << endl;
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

