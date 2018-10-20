#include "PostLifespanDistribution.hpp"

using namespace std;

PostLifespanDistribution::PostLifespanDistribution(std::string t_userID) : m_userID(t_userID) {
    return;
}

PostLifespanDistribution::~PostLifespanDistribution() {
    return;
}

void PostLifespanDistribution::insertLifespanDist(int lifespan, double prob) {
    m_lifespans_dists.insert(std::pair<int, double>(lifespan, prob));
}

std::unordered_map<int, double> getLifespanDists() {
    return std::unordered_map<int, double>(m_lifespans_dists);
};

void PostScale::show() {
    cout << "userID: " << m_userID << end;
    for(auto& iter : m_lifespans_dists) {
        cout << iter[0] << ", " << iter[1] << endl;
    }
    cout << endl;
}
