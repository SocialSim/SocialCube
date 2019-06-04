#ifndef __TOPOLOGY_PROXY__
#define __TOPOLOGY_PROXY__

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

class TopologyProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unordered_map<std::string, double>> m_userCommentProbs;

    std::ifstream m_topologyStatisticFile;

public:
    TopologyProxy(const std::string& file) throw();

    virtual ~TopologyProxy();

    virtual void parse();

    virtual void show();

    std::unordered_map<std::string, double> get(const std::string& userID);

    std::string getUserByTopology(const std::string& userID);

};

#endif
