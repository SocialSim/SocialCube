#ifndef __POINT_PROCESS_PROXY__
#define __POINT_PROCESS_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/PointProcessStat.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class PointProcessProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<PointProcessStat>> m_stats;

    std::ifstream m_pointProcessStatisticsFile;

public:
    PointProcessProxy(const std::string& file) throw();

    virtual ~PointProcessProxy();

    virtual void parse();

    virtual void show();

    PointProcessStat& get(const std::string& userID);

};

#endif
