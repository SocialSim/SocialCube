#ifndef __OBJECT_PREFERENCE_PROXY__
#define __OBJECT_PREFERENCE_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <cstdlib>
#include "Dependency/ObjectPreference.hpp"
#include "StatisticProxy/ProxyModule.hpp"

class ObjectPreferenceProxy : public ProxyModule {
private:
    std::unordered_map<std::string, std::unique_ptr<ObjectPreference>> m_objectPreference;

    std::ifstream m_objectPreferenceStatisticsFile;

public:
    ObjectPreferenceProxy();

    virtual ~ObjectPreferenceProxy();

    virtual void parse();

    virtual void show();
    
    ObjectPreference& get(const std::string& userID);
};

#endif
