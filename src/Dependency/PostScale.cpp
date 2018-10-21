#include "PostScale.hpp"

using namespace std;

PostScale::PostScale(std::string t_userID) : m_userID(t_userID) {
    return;
}

PostScale::~PostScale() {
    return;
}

void PostScale::pushScale(int t_number, int t_scale) {
    m_scales.push_back(std::pair<int, int>(t_number, t_scale));
}

std::vector<std::pair<int, int>> PostScale::getScale(int t_index) {
    return m_scales;
}

void PostScale::show() {
    cout << "userID: " << m_userID << end;
    for(auto& iter : m_scales) {
        cout << iter[0] << ", " << iter[1] << endl;
    }
}