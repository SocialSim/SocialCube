#include "ObjectIDProxy.hpp"

using namespace std;

ObjectIDProxy::ObjectIDProxy(){
    m_objectIDStatisticsFile.open ("/home/parallels/Desktop/SocialCube/statistics/obj_id.json");
    assert(m_objectIDStatisticsFile.is_open());
    return;
}

ObjectIDProxy::~ObjectIDProxy() {
    m_objectIDStatisticsFile.close();
    return;
    return;
}

void ObjectIDProxy::parse() {
    string objectID;
    while (m_objectIDStatisticsFile >> objectID)
        m_objectIDs.push_back(objectID);
}

vector<string>& ObjectIDProxy::get() {
    return m_objectIDs;
}

void ObjectIDProxy::show() {
    for(auto id : m_objectIDs)
        cout << id << "\n";

    cout << m_objectIDs.size() << endl;
}
