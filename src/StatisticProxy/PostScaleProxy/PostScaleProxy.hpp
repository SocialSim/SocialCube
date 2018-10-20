#ifndef __TYPE_DISTRIBUTION_PROXY__
#define __TYPE_DISTRIBUTION_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/TypeDistribution.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class PostScaleProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<PostScale>> m_postScale;

    std::ifstream m_postScaleFile;

public:
    PostScaleProxy(const std::string& file) throw();

    virtual ~PostScaleProxy();

    virtual void parse();

    virtual void show();

    PostScale& get(const std::string& userID);

};

#endif
