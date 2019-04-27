#ifndef __SEED_EVENTS_PROXY__
#define __SEED_EVENTS_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Event.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class SeedEventsProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::vector<Event>> seed_events;

    std::ifstream m_seedEventsStatisticFile;

public:
    SeedEventsProxy(const std::string& file) throw();

    virtual ~SeedEventsProxy();

    virtual void parse();

    virtual void show();

    std::vector<Event> get(std::string t_user_id);

};

#endif
