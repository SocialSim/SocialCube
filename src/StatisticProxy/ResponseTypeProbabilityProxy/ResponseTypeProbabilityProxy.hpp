#ifndef __RESPONSE_TYPE_PROBABILITY_PROXY__
#define __RESPONSE_TYPE_PROBABILITY_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/ResponseTypeProbability.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class ResponseTypeProbabilityProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<ResponseTypeProbability>> m_commentProbability;

    std::ifstream m_commentProbabilityFile;

public:
    ResponseTypeProbabilityProxy(const std::string& file) throw();

    virtual ~ResponseTypeProbabilityProxy();

    virtual void parse();

    virtual void show();

    ResponseTypeProbability& get(const std::string& userID);

};

#endif
