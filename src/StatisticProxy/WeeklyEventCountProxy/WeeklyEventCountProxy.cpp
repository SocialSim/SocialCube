#include "WeeklyEventCountProxy.hpp"

DBG(static const string tag="WeeklyEventCountProxy";)

using namespace std;

WeeklyEventCountProxy::WeeklyEventCountProxy(const string& file) throw() {
    try {
        m_weeklyEventCountStatisticFile.open (file);
    } catch (exception &e) {
        DailyActivityLevelProxyException h_e;
        throw h_e;
    }
    assert(m_weeklyEventCountStatisticFile.is_open());

    return;
}

WeeklyEventCountProxy::~WeeklyEventCountProxy() {
    m_weeklyEventCountStatisticFile.close();
    return;
}

void WeeklyEventCountProxy::parse() {
    string tmp;
    while (getline(m_weeklyEventCountStatisticFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));

        // m_weeklyEventCounts[userID] = new WeeklyEventCount(userID);

        m_weeklyEventCounts.insert(std::pair<string, unique_ptr<WeeklyEventCount>>(userID,
                unique_ptr<WeeklyEventCount>(new WeeklyEventCount(userID))));

        string str_activityLevels = tmp.substr(tmp.find(" "));
        stringstream ss(str_activityLevels);
        string item;
        while (ss >> item) {
            m_weeklyEventCounts[userID]->addEventCount(stod(item));
        }
    }
    // show();
    DBG(LOGD(TAG, "Weekly Event Count has "+stringfy(m_weeklyEventCounts.size()));)
}

void WeeklyEventCountProxy::show() {
    cout << m_weeklyEventCounts.size() << endl;
    for(auto const& iter : m_weeklyEventCounts) {
        iter.second->show();
    }
}

WeeklyEventCount& WeeklyEventCountProxy::get(const std::string& userID) {
    if(m_weeklyEventCounts.find(userID) == m_weeklyEventCounts.end()) {
        return *(m_weeklyEventCounts["-1"]);
    } else {
        assert(m_weeklyEventCounts.find(userID) != m_weeklyEventCounts.end());
        return *(m_weeklyEventCounts[userID]);
    }
}
