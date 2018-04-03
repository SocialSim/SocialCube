#include "EventManager.hpp"

using namespace std;

DBG(static const string tag="EventManager";)

EventManager& EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

void EventManager::emitEventOnExceedThreshold() {

    if(m_events.size() > m_threshold) {
        DBG(LOGD(TAG, "Emit " + stringfy(m_events.size()) + " Events");)
        emitEvent();
        m_events.clear();
    }
}

void EventManager::emitEvent() {
    if(m_eventOn)
        _emitEvent();
}

void EventManager::_emitEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
    for(auto& event : m_events) {
        m_eventFile << *event;
    }
}

void EventManager::start() {
    m_eventFile.open(m_eventFileName.c_str()); 
}

void EventManager::end() {
    emitEvent();
    m_eventFile.close(); 

    SimulatorProfiler& sp = SimulatorProfiler::getInstance();
    sp.setEventCount(m_eventCount);
}

uint64_t EventManager::getEventCount() {
    return m_eventCount;
}

void EventManager::storeEvent(std::vector<std::unique_ptr<Event>>& events) {
    m_eventCount += events.size();
    m_events.insert(
        m_events.end(),
        std::make_move_iterator(events.begin()),
        std::make_move_iterator(events.end())
    );
    events.clear();
}

void EventManager::setEventShow(bool t_eventOn) {
    m_eventOn = t_eventOn;
}

void EventManager::setEventFileName(const std::string& t_file) {
    m_eventFileName = t_file;
}

void EventManager::setEventThreshold(uint64_t t_threshold) {
    m_threshold = t_threshold;
}
