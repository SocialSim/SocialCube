#include "PoissonProcessProxy.hpp"

DBG(static const string tag="PoissonProcessProxy";)

using namespace std;

PoissonProcessProxy::PoissonProcessProxy(const string& file) throw() {
    try {
        m_poissonProcessStatisticsFile.open (file);
    } catch (exception &e) {
        PoissonProcessProxyException p_e;
        throw p_e;
    }
    assert(m_poissonProcessStatisticsFile.is_open());
    return;
}

PoissonProcessProxy::~PoissonProcessProxy() {
    m_poissonProcessStatisticsFile.close();
    return;
}

void PoissonProcessProxy::parse() {

    string tmp;
    while (getline(m_poissonProcessStatisticsFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        int k = stoi(tmp.substr(tmp.find(" ") + 1));
        unique_ptr<PoissonProcessStat> poissonProcessStat(new PoissonProcessStat(userID));
        poissonProcessStat->setK(k);

        // parse typeList
        getline(m_poissonProcessStatisticsFile, tmp);
        istringstream in(tmp);
        string type;
        vector<string> typeList;
        while(in >> type) {
            typeList.push_back(type);
        }
        poissonProcessStat->setTypeList(typeList);
        // parse mu
        getline(m_poissonProcessStatisticsFile, tmp);
        istringstream mu_in(tmp);
        string mu_ele;
        vector<double> mu;
        for(int i = 0; i < k; ++i) {
            mu_in >> mu_ele;
            mu.push_back(stod(mu_ele));
        }
        poissonProcessStat->setMu(mu);

        m_stats[userID] = move(poissonProcessStat);
    }
    DBG(LOGD(TAG, "Poisson Process Stat has "+stringfy(m_stats.size()));)
}

void PoissonProcessProxy::show() {
    cout << m_stats.size() << endl;
    for(auto& iter : m_stats) {
        iter.second->show();
    }
}

PoissonProcessStat& PoissonProcessProxy::get(const std::string& userID) {
    if(m_stats.find(userID) == m_stats.end()) {
        throw;
    } else {
        assert(m_stats.find(userID) != m_stats.end());
        return *(m_stats[userID]);
    }
}
