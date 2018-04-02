#include "ObjectPreference.hpp"

using namespace std;

ObjectPreference::ObjectPreference(const std::string &t_userID) :
    m_userID(t_userID) {
    return;
}

ObjectPreference::~ObjectPreference() {
    return;
}

void ObjectPreference::set(const std::string &t_objectID, double t_preference) {
    unique_ptr<PreferenceNode> ptr(new PreferenceNode(t_objectID, t_preference));
    m_preference.push_back(move(ptr));
}

void ObjectPreference::show() const {
    cout << m_userID << endl;
    for(auto& iter : m_preference) {
        cout << iter->objID << " " << iter->preference << "\n"; 
    }
}

string ObjectPreference::randomChooseTarget(bool seed, double _d) const {
    double d = seed ? _d : ((double)rand()) / RAND_MAX;
    auto upper = std::upper_bound(m_preference.begin(), m_preference.end(), d, PreferenceNode::Comparator);
    string target = (*upper).get()->objID;
    return target;
}

std::string ObjectPreference::getUserID() const {
    string id = m_userID;
    return id;
}
