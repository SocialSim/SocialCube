#include "ActivityLevelProxy.hpp"

using namespace std;

DBG(static const string tag="ActivityLevelProxy";)

ActivityLevelProxy::ActivityLevelProxy(const string& file) throw() {
    try{
        m_activityLevelStatisticsFile.open(file.c_str());
    } catch(exception& e) {
        CountryCodesProxyException u_e;
        throw u_e;
    }
    assert(m_activityLevelStatisticsFile.is_open());
    return;
}

ActivityLevelProxy::~ActivityLevelProxy() {
    m_activityLevelStatisticsFile.close();
    return;
}

void ActivityLevelProxy::parse() {
    string countryCode;
    while (m_activityLevelStatisticsFile >> countryCode)
        m_activityLevels.push_back(countryCode);
    DBG(LOGD(TAG, "Activity Level has "+stringfy(m_activityLevels.size()));)
}

vector<string>& ActivityLevelProxy::get() {
    return m_activityLevels;
}

void ActivityLevelProxy::show() {
    for(auto cc : m_activityLevels)
        cout << cc << "\n";
    cout << m_activityLevels.size() << endl;
}

uint64_t ActivityLevelProxy::getCommunityTag(const string& t_userID) {
    UserIDProxyNoMethodException u_e;
    throw u_e;
}