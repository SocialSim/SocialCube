#include "ObjectPreference.hpp"

ObjectPreference::ObjectPreference(const std::string &t_userID) :
    m_userID(t_userID) {
    return;
}

ObjectPreference::~ObjectPreference() {
    return;
}

void ObjectPreference::set(const std::string &t_objectID, double t_preference) {
    m_preference[t_objectID] = t_preference;
}

double ObjectPreference::get(const std::string &t_objectID) {
    return m_preference[t_objectID];
}

void ObjectPreference::increment(const std::string &t_objectID, double t_delta) {
    m_preference[t_objectID] += t_delta;
}

bool ObjectPreference::exist(const std::string &t_objectID) {
    return m_preference.find(t_objectID) != m_preference.end();
}

std::vector<std::string> ObjectPreference::getPreferedObjectIDs() {
    std::vector<std::string> objectIDs;

    for(auto iter : m_preference) {
        objectIDs.push_back(iter.first);
    }

    return objectIDs;
}
