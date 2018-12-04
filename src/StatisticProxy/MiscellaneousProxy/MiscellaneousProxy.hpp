#ifndef __MISCELLANEOUS_PROXY__
#define __MISCELLANEOUS_PROXY__

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

class MiscellaneousProxy : public ProxyModule {
private:

    std::unordered_map<std::string, double> m_actionTypeDistribution;

    double m_quartile[3];

    std::unordered_map<std::string, double> m_embeddingParams;

    std::ifstream m_miscellaneousStatisticFile;

public:
    MiscellaneousProxy(const std::string& file) throw();

    virtual ~MiscellaneousProxy();

    virtual void parse();

    virtual void show();

    std::unordered_map<std::string, double> getActionTypeDistribution();

    double* getQuartile();

    std::unordered_map<std::string, double> getEmbeddingParams();
};

#endif
