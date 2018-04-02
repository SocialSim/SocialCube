#ifndef __CLUSTERED_USER_ID_PROXY__
#define __CLUSTERED_USER_ID_PROXY__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <unordered_map>
#include "UserIDProxy.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class ClusteredUserIDProxy: public UserIDProxy {
private:
    std::unordered_map<std::string, uint64_t> m_userIDToCommunity;
public:
    ClusteredUserIDProxy(const std::string& file) throw();

    virtual ~ClusteredUserIDProxy();

    virtual void parse() override;

    uint64_t getCommunityTag(const std::string& t_userID);

    virtual void show() override;
};

#endif
