#include "ObjectPreferenceProxy.hpp"

using namespace std;

DBG(static const string tag="ObjectPreferenceProxy";)

ObjectPreferenceProxy::ObjectPreferenceProxy(const string& file) throw() {
    try{
        m_objectPreferenceStatisticsFile.open(file);
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
        double aggrPreference = 0.0;
        for(int i = 0; i < stoi(preferenceCount); ++i) {
            getline(m_objectPreferenceStatisticsFile, tmp);
            string objectID = tmp.substr(0, tmp.find(" "));
            double preference = stod(tmp.substr(tmp.find(" ") + 1));
            aggrPreference += preference;
            objectPreference->set(objectID, aggrPreference);
        }
        m_objectPreference[userID] = move(objectPreference);
    }
    DBG(LOGD(TAG, "Object Preference has "+stringfy(m_objectPreference.size()));)
}

void ObjectPreferenceProxy::show() {
    for(auto& iter : m_objectPreference) {
        iter.second->show();
    }
}

ObjectPreference& ObjectPreferenceProxy::get(const string& userID) {
    return *(m_objectPreference[userID]);
}
