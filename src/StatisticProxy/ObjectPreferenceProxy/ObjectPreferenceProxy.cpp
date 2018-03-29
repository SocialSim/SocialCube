#include "ObjectPreferenceProxy.hpp"

using namespace std;

ObjectPreferenceProxy::ObjectPreferenceProxy() throw() {
    try{
        string filePath(getenv("SOCIALCUBEPATH"));
        filePath += "/statistics/user_object_preference.json";
        m_objectPreferenceStatisticsFile.open(filePath);
    } catch (exception& e) {
        ObjectPreferenceProxyException o_e;
        throw o_e;
    }
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
    cout << "Object Preference has " << m_objectPreference.size() << endl;
}

void ObjectPreferenceProxy::show() {
    for(auto& iter : m_objectPreference) {
        iter.second->show();
    }
}

ObjectPreference& ObjectPreferenceProxy::get(const string& userID) {
    return *(m_objectPreference[userID]);
}
