#include "EventHourlyActionRate.hpp"

using namespace std;

EventHourlyActionRate::EventHourlyActionRate(double t_activityLevel) :
    m_prob(24, 0.0), m_activityLevel(t_activityLevel) {
    return;
}

EventHourlyActionRate::~EventHourlyActionRate() {
    return;
}

void EventHourlyActionRate::setProb(int t_hour, double t_rate) {
    m_prob[t_hour] = t_rate;
}

double EventHourlyActionRate::getProb(int t_hour) {
    return m_prob[t_hour];
}

double EventHourlyActionRate::getActivityLevel() {
    return m_activityLevel;
}

void EventHourlyActionRate::show() {
    assert(m_prob.size() == 24);
    cout << "activity level " << m_activityLevel << endl;
    for(auto iterm : m_prob)
        cout << iterm << " ";
    cout << endl;
}
