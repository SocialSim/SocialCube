#include "ObjectIDProxy.hpp"

using namespace std;

DBG(static const string tag="ObjectIDProxy";)

ObjectIDProxy::ObjectIDProxy(const string& file) throw() {
    try{
        m_objectIDStatisticsFile.open (file);
    } catch(exception& e) {
        ObjectIDProxyException o_e;
        throw o_e;
    }
    assert(m_objectIDStatisticsFile.is_open());
    return;
}

ObjectIDProxy::~ObjectIDProxy() {
    m_objectIDStatisticsFile.close();
    return;
}

void ObjectIDProxy::parse() {
    string objectID;
    while (m_objectIDStatisticsFile >> objectID)
        m_objectIDs.push_back(objectID);

    DBG(LOGD(TAG, "Object ID has "+stringfy(m_objectIDs.size()));)
}

vector<string>& ObjectIDProxy::get() {
    return m_objectIDs;
}

void ObjectIDProxy::show() {
    for(auto id : m_objectIDs)
        cout << id << "\n";

    cout << m_objectIDs.size() << endl;
}
