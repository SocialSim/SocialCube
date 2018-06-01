#ifndef __COUNTRY_CODES_PROXY__
#define __COUNTRY_CODES_PROXY__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class CountryCodesProxy : public ProxyModule {
protected:
    std::vector<std::string> m_countryCodes;

    std::ifstream m_countryCodesStatisticsFile;
public:
    CountryCodesProxy(const std::string& file) throw();

    virtual ~CountryCodesProxy();

    virtual void parse();

    std::vector<std::string>& get();

    virtual uint64_t getCommunityTag(const std::string& t_userID);

    virtual void show();
};

#endif
