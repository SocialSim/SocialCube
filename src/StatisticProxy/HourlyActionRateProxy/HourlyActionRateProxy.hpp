#ifndef __HOURLY_ACTION_RATE_PROXY__
#define __HOURLY_ACTION_RATE_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/HourlyActionRate.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"

class HourlyActionRateProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<HourlyActionRate>> m_hourlyActionRate;

    std::ifstream m_hourlyActionRateStatisticFile;

public:
    HourlyActionRateProxy() throw();

    virtual ~HourlyActionRateProxy();

    virtual void parse();

    virtual void show();

    HourlyActionRate& get(const std::string& userID);

};

#endif
