#ifndef __EVENT_MANAGER__
#define __EVENT_MANAGER__

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>

#include "SimulatorProfiler/SimulatorProfiler.hpp"
#include "common/Event.hpp"
#include "Log/Log.hpp"

class EventManager {
    private:
        // Private member variables
        std::string m_center = "user-centric";

        std::string m_platform;

        std::string m_scenario;

        std::string m_domain;

        std::vector<std::unique_ptr<Event>> m_events;

        uint64_t m_eventCount;

        uint64_t m_bufferSize;

        std::string m_eventFileName;

        std::ofstream m_eventFile; 

        bool m_eventOn;

        // Private member functions

        void emitEventOnBufferFull();

        void emitEvent();

        void _emitGithubUserCentricEvent();

        void _emitGithubRepoCentricEvent();

        void _emitRedditUserCentricEvent();

        void _emitRedditRepoCentricEvent();

        void _emitTwitterUserCentricEvent();

        void _emitTwitterRepoCentricEvent();

        EventManager();

    public:
        static EventManager& getInstance();

        ~EventManager() = default;

        void setCenter(const std::string& center);

        void setPlatform(const std::string& platform);

        void setScenario(const std::string& scenario);

        void setDomain(const std::string& domain);

        void setEventShow(bool t_eventOn); 

        void setEventFileName(const std::string& t_file);

        void setEventBufferSize(uint64_t t_bufferSize);

        void start();

        void end();

        uint64_t getEventCount();

        void storeEvent(std::vector<std::unique_ptr<Event>>& events);
};

#endif
