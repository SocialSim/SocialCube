#ifndef __OBJECT_ID_PROXY__
#define __OBJECT_ID_PROXY__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "StatisticProxy/ProxyModule.hpp"

class ObjectIDProxy : public ProxyModule {
private:
    std::vector<std::string> m_objectIDs;

    std::ifstream m_objectIDStatisticsFile;
public:
    ObjectIDProxy();

    virtual ~ObjectIDProxy();

    virtual void parse();

    std::vector<std::string>& get();

    virtual void show();
};

#endif
