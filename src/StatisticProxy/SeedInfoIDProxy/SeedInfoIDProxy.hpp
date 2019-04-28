#ifndef __SEED_INFO_ID_PROXY__
#define __SEED_INFO_ID_PROXY__

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

class SeedInfoIDProxy : public ProxyModule {
private:

    std::vector<std::string> seed_infoIDs;

    std::ifstream m_seedInfoIDStatisticFile;

public:
    SeedInfoIDProxy(const std::string& file) throw();

    virtual ~SeedInfoIDProxy();

    virtual void parse();

    virtual void show();

    std::vector<std::string> get();

};

#endif
