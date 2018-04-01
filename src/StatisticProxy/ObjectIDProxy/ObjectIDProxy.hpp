#ifndef __OBJECT_ID_PROXY__
#define __OBJECT_ID_PROXY__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdlib>
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class ObjectIDProxy : public ProxyModule {
private:
    std::vector<std::string> m_objectIDs;

    std::ifstream m_objectIDStatisticsFile;
public:
    ObjectIDProxy(const std::string& file) throw();

    virtual ~ObjectIDProxy();

    virtual void parse();

    std::vector<std::string>& get();

    virtual void show();
};

#endif
