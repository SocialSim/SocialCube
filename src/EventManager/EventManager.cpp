#include "EventManager.hpp"

using namespace std;

DBG(static const string tag="EventManager";)

EventManager::EventManager() : m_eventCount(0), m_bufferSize(1<<19),
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
    if (m_platform == "github") {
        if (m_eventOn) {
            if (m_center == "user-centric") {
                _emitGithubUserCentricEvent();
            } else if (m_center == "repo-centric") {
                _emitGithubRepoCentricEvent();
            }
        }
    } else if (m_platform == "reddit") {
        if (m_eventOn) {
            if (m_center == "user-centric") {
                _emitRedditUserCentricEvent();
            } else if (m_center == "repo-centric") {
                _emitRedditRepoCentricEvent();
            }
        }
    }

}

void EventManager::_emitGithubUserCentricEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
    for(auto& event : m_events) {
        m_eventFile << event->getTimestampStr() << "," << event->getEventType() << "," << event->getUserID() << "," <<
                  event->getObjectID() << "," << event->getAction() << "," << event->getMerged() << "\n";
    }
}

void EventManager::_emitGithubRepoCentricEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
    for(auto& event : m_events) {
        m_eventFile << event->getTimestampStr() << "," << event->getEventType() << "," << event->getObjectID() << "," <<
                 event->getUserID() << "," << event->getAction() << "," << event->getMerged() << "\n";
    }
}

void EventManager::_emitRedditUserCentricEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
    for(auto& event : m_events) {
        m_eventFile << _generateRedditNodeId() << ", " << event->getUserID() << ", " << event->getObjectID() << ", " << event->getObjectID()
                    << ", comment, " << event->getTimestampStrInSeconds() << "," << "\n";
    }
}

void EventManager::_emitRedditRepoCentricEvent(){
    DBG(LOGD(TAG, "Store " + stringfy(m_events.size()) + " Events");)
    for(auto& event : m_events) {
        m_eventFile << _generateRedditNodeId() << ", " << event->getObjectID() << ", " << event->getUserID() << ", " << event->getUserID()
                    << ", comment, " << event->getTimestampStrInSeconds() << "," << "\n";
    }
}

string EventManager::_generateRedditNodeId() {
    static const char alphanum[] =
                    "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";

    int len = 25;
    string nodeId = "";

    for (int i = 0; i < len; ++i) {
        nodeId += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return nodeId;
}

void EventManager::start() {
    DBG(LOGP(TAG, "\n\n*************************** Event Manager Configuration ***************************", false);)
    DBG(LOGP(TAG, "Event Buffer Size: "+stringfy(m_bufferSize));)
    DBG(LOGP(TAG, "Event Storage: "+m_eventFileName);)
    DBG(LOGP(TAG, "Event Show Status: "+stringfy(m_eventOn));)
    DBG(LOGP(TAG, "*************************** Simulator Configuration ***************************\n\n", false);)
    m_eventFile.open(m_eventFileName.c_str(), std::ofstream::app);
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

    emitEventOnBufferFull();
}

void EventManager::setCenter(const std::string& center) {
    m_center = center;
}

void EventManager::setPlatform(const std::string& platform) {
    m_platform = platform;
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
