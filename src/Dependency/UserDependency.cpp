#include "UserDependency.hpp"

UserDependency::UserDependency(uint64_t t_userID) : m_userID(t_userID) {
    return;
}

UserDependency::~UserDependency() {
    return;
}

void UserDependency::set(const std::string &t_dependentID, double t_dependency) {
    m_dependency[t_dependentID] = t_dependency;
}

double UserDependency::get(const std::string &t_dependentID) {
    return m_dependency[t_dependentID];
}
