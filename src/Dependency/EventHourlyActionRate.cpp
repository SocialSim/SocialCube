#include "EventHourlyActionRate.hpp"

EventHourlyActionRate::EventHourlyActionRate(uint64_t t_activityLevel) :
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

uint64_t EventHourlyActionRate::getActivityLevel() {
    return m_activityLevel;
}
