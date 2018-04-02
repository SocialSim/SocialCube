#include "ClusteredUserIDProxy.hpp"

using namespace std;

DBG(static const string tag="ClusteredUserIDProxy";)

ClusteredUserIDProxy::ClusteredUserIDProxy(const string& file) throw() : UserIDProxy(file) {
    return;
}

ClusteredUserIDProxy::~ClusteredUserIDProxy() {
    return;
}

void ClusteredUserIDProxy::parse() {
    string userID;
    uint64_t communityID;
    while (m_userIDStatisticsFile >> userID >> communityID) {
        m_userIDs.push_back(userID);
        m_userIDToCommunity[userID] = communityID;
    }
    DBG(LOGD(TAG, "User ID has "+stringfy(m_userIDs.size()));)
}

void ClusteredUserIDProxy::show() {
    for(auto id : m_userIDs)
        cout << id << " " << m_userIDToCommunity[id] << "\n";
    cout << m_userIDs.size() << endl;
}

uint64_t ClusteredUserIDProxy::getCommunityTag(const string& t_userID) {
    assert(m_userIDToCommunity.find(t_userID) != m_userIDToCommunity.end());
    return m_userIDToCommunity[t_userID];
}
