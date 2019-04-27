#include "PostLifespanDistribution.hpp"

using namespace std;

PostLifespanDistribution::PostLifespanDistribution(std::string t_userID) : m_userID(t_userID) {
    return;
}

PostLifespanDistribution::~PostLifespanDistribution() {
    return;
}

void PostLifespanDistribution::pushLifespanDist(int lifespan, double prob) {
    m_lifespan_dists.push_back(std::pair<int, double>(lifespan, prob));
}

std::vector<std::pair<int, double>> PostLifespanDistribution::getLifespanDist() {
    return m_lifespan_dists;
};

void PostLifespanDistribution::show() {
    cout << "userID: " << m_userID << endl;
    for(auto& iter : m_lifespan_dists) {
        cout << iter.first << ", " << iter.second << endl;
    }
    cout << endl;
}
