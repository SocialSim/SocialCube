#include "UserDistributionProxy.hpp"

using namespace std;

DBG(static const string tag="UserDistributionProxy";)

UserDistributionProxy::UserDistributionProxy(const string& file) throw() {
    try {
        m_userDistributionFile.open(file);
    } catch (exception &e) {
        UserDistributionProxyException t_e;
        throw t_e;
    }
    assert(m_userDistributionFile.is_open());
    return;
}

UserDistributionProxy::~UserDistributionProxy() {
    m_userDistributionFile.close();
    return;
}

void UserDistributionProxy::parse() {
    string tmp;
    time_t date;
    while (getline(m_userDistributionFile, tmp)) {
        if (tmp.at(0) == '#') {
            struct tm tm_date = {0};
            std::istringstream ss(tmp.substr(1));
            ss >> get_time(&tm_date, "%Y-%m-%d");
            // User start date
            tm_date.tm_mday += 6;
            date = mktime(&tm_date);
        } else {
            size_t start = 0;
            size_t end = tmp.find(",");
            string repoID = tmp.substr(start, end-start);
//            unique_ptr<UserDistribution> userDistribution(new UserDistribution(repoID));
            start = end + 1;
            end = tmp.find(",", end+1);

            while(end != string::npos) {
                string userID = tmp.substr(start, end-start);
                start = end + 1;
                end = tmp.find(",", end+1);
                int count;

                if (end != string::npos) {
                    count = stoi(tmp.substr(start, end-start));
                    start = end + 1;
                    end = tmp.find(",", end+1);
                } else {
                    count = stoi(tmp.substr(start));
                }
                if (m_repoUserDistribution.count(repoID) == 0) {
                    m_repoUserDistribution.insert(std::pair<std::string, std::unique_ptr<UserDistribution>>(repoID, \
                     std::make_unique<UserDistribution>(repoID)));
                }
                m_repoUserDistribution[repoID]->insertUserCount(date, userID, count);
            }
            // m_repoUserDistribution[repoID]->show();
        }
    }
    DBG(LOGD(TAG, "Total repo number = "+stringfy(m_repoUserDistribution.size()));)
}

UserDistribution& UserDistributionProxy::get(const std::string& repoID) {
    // cout << "m_repoUserDistribution.count(repoID) = " << m_repoUserDistribution.count(repoID) << endl;
    if (m_repoUserDistribution.count(repoID) == 0) {
        m_repoUserDistribution[repoID] = std::make_unique<UserDistribution>(repoID);
    }
    return *(m_repoUserDistribution[repoID]);
}

void UserDistributionProxy::show() {
    for(auto& iter : m_repoUserDistribution) {
        iter.second->show();
    }
}
