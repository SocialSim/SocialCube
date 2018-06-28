#include "WeeklyEventCount.hpp"

using namespace std;

WeeklyEventCount::WeeklyEventCount(const std::string &t_userID) :
        m_eventCountList(),
        m_userID(t_userID) {
    return;
}

WeeklyEventCount::~WeeklyEventCount() {
    return;
}

double WeeklyEventCount::getEventCount(int t_day) {
    return m_eventCountList[t_day];
}

int WeeklyEventCount::getEventCountSize() {
    return m_eventCountList.size();
}

int WeeklyEventCount::getEventCountSum() {
    int initial_sum  = 0;
    return accumulate(m_eventCountList.begin(), m_eventCountList.end(), initial_sum);
}


void WeeklyEventCount::addEventCount(double t_activityLevel) {
    m_eventCountList.push_back(t_activityLevel);
}

void WeeklyEventCount::show() const {
    cout << "User " << m_userID << endl;
    for (int i = 0; i < m_eventCountList.size(); i++) {
        cout << "day: " << i << ", " << m_eventCountList[i] << endl;
    }
}

string WeeklyEventCount::getUserID() const {
    string result = m_userID;
    return result;
}
