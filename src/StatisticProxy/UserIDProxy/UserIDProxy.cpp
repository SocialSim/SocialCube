#include "UserIDProxy.hpp"

using namespace std;

UserIDProxy::UserIDProxy() {
    string filePath(getenv("SOCIALCUBEPATH"));
    filePath += "/statistics/user_id.json";
    m_userIDStatisticsFile.open(filePath.c_str());
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
    cout << "User ID has " << m_userIDs.size() << endl;
}

vector<string>& UserIDProxy::get() {
    return m_userIDs;
}

void UserIDProxy::show() {
    for(auto id : m_userIDs)
        cout << id << "\n";
    cout << m_userIDs.size() << endl;
}
