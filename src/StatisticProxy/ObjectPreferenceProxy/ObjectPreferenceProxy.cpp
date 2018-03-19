#include "ObjectPreferenceProxy.hpp"

using namespace std;

ObjectPreferenceProxy::ObjectPreferenceProxy() {
    m_objectPreferenceStatisticsFile.open ("/home/parallels/Desktop/SocialCube/statistics/object_preference.json");
    assert(m_objectPreferenceStatisticsFile.is_open());
    return;
}

ObjectPreferenceProxy::~ObjectPreferenceProxy() {
    m_objectPreferenceStatisticsFile.close();
    return;
}

void ObjectPreferenceProxy::parse() {
    string tmp;
    while (getline(m_objectPreferenceStatisticsFile, tmp)) {
        string userID = tmp.substr(0, tmp.find(" "));
        string preferenceCount = tmp.substr(tmp.find(" ") + 1);
        unique_ptr<ObjectPreference> objectPreference(new ObjectPreference(userID));
        for(int i = 0; i < stoi(preferenceCount); ++i) {
            getline(m_objectPreferenceStatisticsFile, tmp);
            string objectID = tmp.substr(0, tmp.find(" "));
            string preference = tmp.substr(tmp.find(" ") + 1);
            objectPreference->set(objectID, stod(preference));
        }
        m_objectPreference[userID] = move(objectPreference);
    }
}

void ObjectPreferenceProxy::show() {
    for(auto& iter : m_objectPreference) {
        iter.second->show();
    }
}

ObjectPreference& ObjectPreferenceProxy::get(const string& userID) {
    return *(m_objectPreference[userID]);
}
