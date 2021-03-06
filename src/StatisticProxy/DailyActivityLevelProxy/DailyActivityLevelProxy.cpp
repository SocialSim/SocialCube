#include "DailyActivityLevelProxy.hpp"

DBG(static const string tag="DailyActivityLevelProxy";)

using namespace std;

DailyActivityLevelProxy::DailyActivityLevelProxy(const string& file) throw() {
    try {
        m_dailyActivityLevelStatisticFile.open (file);
    } catch (exception &e) {
        DailyActivityLevelProxyException h_e;
        throw h_e;
    }
    assert(m_dailyActivityLevelStatisticFile.is_open());

    return;
}

DailyActivityLevelProxy::~DailyActivityLevelProxy() {
    m_dailyActivityLevelStatisticFile.close();
    return;
}

void DailyActivityLevelProxy::parse() {
    string tmp;
    while (getline(m_dailyActivityLevelStatisticFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));

        // m_dailyActivityLevels[userID] = new DailyActivityLevel(userID);

        m_dailyActivityLevels.insert(std::pair<string, unique_ptr<DailyActivityLevel>>(userID,
                unique_ptr<DailyActivityLevel>(new DailyActivityLevel(userID))));

        string str_activityLevels = tmp.substr(tmp.find(" "));
        stringstream ss(str_activityLevels);
        string item;
        while (ss >> item) {
            m_dailyActivityLevels[userID]->addActivityLevel(stod(item));
        }
    }
    // show();
    DBG(LOGD(TAG, "Daily Activity Level has "+stringfy(m_dailyActivityLevels.size()));)
}

void DailyActivityLevelProxy::show() {
    cout << m_dailyActivityLevels.size() << endl;
    for(auto const& iter : m_dailyActivityLevels) {
        iter.second->show();
    }
}

DailyActivityLevel& DailyActivityLevelProxy::get(const std::string& userID) {
    if(m_dailyActivityLevels.find(userID) == m_dailyActivityLevels.end()) {
        return *(m_dailyActivityLevels["-1"]);
    } else {
        assert(m_dailyActivityLevels.find(userID) != m_dailyActivityLevels.end());
        return *(m_dailyActivityLevels[userID]);
    }
}
