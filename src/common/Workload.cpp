#include "Workload.hpp"

using namespace std;

Workload::Workload() : m_startTime(0), m_endTime(1), m_unitTime(1) {
    return;
}

Workload::Workload(time_t t_startTime, time_t t_endTime, time_t t_unitTime) :
    m_startTime(t_startTime), m_endTime(t_endTime), m_unitTime(t_unitTime) {
        return;
}

std::vector<std::unique_ptr<Community>> Workload::transferWorkload() {
    return move(m_community);
}

time_t Workload::getStartTime() {
    return m_startTime;
}

time_t Workload::getEndTime() {
    return m_endTime;
}

time_t Workload::getUnitTime() {
    return m_unitTime;
}

void Workload::addCommunity(unique_ptr<Community>&& t_community) {
    m_community.push_back(move(t_community));
}
