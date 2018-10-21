#ifndef __POST_SCALE_PROXY__
#define __POST_SCALE_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/PostScale.hpp"
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
