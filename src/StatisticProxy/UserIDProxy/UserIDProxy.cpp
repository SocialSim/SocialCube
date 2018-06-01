#include "UserIDProxy.hpp"

using namespace std;

DBG(static const string tag="UserIDProxy";)

UserIDProxy::UserIDProxy(const string& file) throw() {
    try{
        m_userIDStatisticsFile.open(file.c_str());
    } catch(exception& e) {
        UserIDProxyException u_e;
        throw u_e;
    }
    assert(m_userIDStatisticsFile.is_open());
    return;
}

UserIDProxy::~UserIDProxy() {
    m_userIDStatisticsFile.close();
    return;
}

void UserIDProxy::parse() {
    string userID;
    while (m_userIDStatisticsFile >> userID)
        m_userIDs.push_back(userID);
    DBG(LOGD(TAG, "User ID has "+stringfy(m_userIDs.size()));)
}

vector<string>& UserIDProxy::get() {
    return m_userIDs;
}

void UserIDProxy::show() {
    for(auto id : m_userIDs)
        cout << id << "\n";
    cout << m_userIDs.size() << endl;
}

uint64_t UserIDProxy::index(const string& userID) {
    uint64_t count = 0;
    for(auto id : m_userIDs) {
        if (id == userID) {
            break;
        }
        count++;
    }
    return count;
}

uint64_t UserIDProxy::getCommunityTag(const std::string& t_userID) {
    UserIDProxyNoMethodException u_e;
    throw u_e;
}
