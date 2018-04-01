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
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class ObjectPreferenceProxy : public ProxyModule {
private:
    std::unordered_map<std::string, std::unique_ptr<ObjectPreference>> m_objectPreference;

    std::ifstream m_objectPreferenceStatisticsFile;

public:
    ObjectPreferenceProxy(const std::string& file) throw();

    virtual ~ObjectPreferenceProxy();

    virtual void parse();

    virtual void show();
    
    ObjectPreference& get(const std::string& userID);
};

#endif
