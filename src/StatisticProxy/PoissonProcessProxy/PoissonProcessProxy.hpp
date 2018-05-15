#ifndef SOCIALCUBE_POISSONPROCESSPROXY_HPP
#define SOCIALCUBE_POISSONPROCESSPROXY_HPP

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/PoissonProcessStat.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class PoissonProcessProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<PoissonProcessStat>> m_stats;

    std::ifstream m_poissonProcessStatisticsFile;

public:
    PoissonProcessProxy(const std::string& file) throw();

    virtual ~PoissonProcessProxy();

    virtual void parse();

    virtual void show();

    PoissonProcessStat& get(const std::string& userID);

};

#endif
