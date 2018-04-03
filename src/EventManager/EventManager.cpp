#include "EventManager.hpp"

using namespace std;

DBG(static const string tag="EventManager";)

EventManager::EventManager() : m_eventCount(0), m_bufferSize(1<<20),
    m_eventFile(""), m_eventOn(false) {
    return;    
}


EventManager& EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

void EventManager::emitEventOnBufferFull() {

    if(m_events.size() > m_bufferSize) {
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
    DBG(LOGP(TAG, "\n\n*************************** Event Manager Configuration ***************************", false);)
    DBG(LOGP(TAG, "Event Buffer Size: "+stringfy(m_bufferSize));)
    DBG(LOGP(TAG, "Event Storage: "+m_eventFileName);)
    DBG(LOGP(TAG, "Event Show Status: "+stringfy(m_eventOn));)
    DBG(LOGP(TAG, "*************************** Simulator Configuration ***************************\n\n", false);)

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

void EventManager::setEventBufferSize(uint64_t t_bufferSize) {
    m_bufferSize = t_bufferSize;
}
