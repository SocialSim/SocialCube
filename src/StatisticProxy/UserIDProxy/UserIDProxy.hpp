#ifndef __USER_ID_PROXY__
#define __USER_ID_PROXY__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class UserIDProxy : public ProxyModule {
private:
    std::vector<std::string> m_userIDs;

    std::ifstream m_userIDStatisticsFile;
public:
    UserIDProxy(const std::string& file) throw();

    virtual ~UserIDProxy();

    virtual void parse();

    std::vector<std::string>& get();

    virtual void show();
};

#endif
