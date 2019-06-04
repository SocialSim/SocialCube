#ifndef __INFOID_TO_USER_PROXY__
#define __INFOID_TO_USER_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class InfoIDToUserProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unordered_map<std::string, double>> m_infoIDToUser;

    std::ifstream m_infoIDToUserStatisticFile;

public:
    InfoIDToUserProxy(const std::string& file) throw();

    virtual ~InfoIDToUserProxy();

    virtual void parse();

    virtual void show();

    std::unordered_map<std::string, double> get(const std::string& infoID);

};

#endif
