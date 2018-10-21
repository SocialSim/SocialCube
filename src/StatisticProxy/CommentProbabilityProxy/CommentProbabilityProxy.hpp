#ifndef __COMMENT_PROBABILITY_PROXY__
#define __COMMENT_PROBABILITY_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/CommentProbability.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class CommentProbabilityProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<CommentProbability>> m_commentProbability;

    std::ifstream m_commentProbabilityFile;

public:
    CommentProbabilityProxy(const std::string& file) throw();

    virtual ~CommentProbabilityProxy();

    virtual void parse();

    virtual void show();

    CommentProbability& get(const std::string& userID);

};

#endif
