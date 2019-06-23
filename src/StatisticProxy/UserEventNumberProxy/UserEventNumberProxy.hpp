#ifndef __USER_EVENT_NUMBER_PROXY__
#define __USER_EVENT_NUMBER_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iomanip>

#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class UserEventNumberProxy : public ProxyModule {
private:

    std::unordered_map<std::string, int> m_userEventNumber;

    std::ifstream m_userEventNumberFile;

public:
    UserEventNumberProxy(const std::string& file) throw();

    virtual ~UserEventNumberProxy();

    virtual void parse();

    int getEventNumber(const std::string& userID);

    std::string randomlyChooseUser();

    bool chooseThisUser(const std::string& userID);

    virtual void show();

};

#endif
