#ifndef __CASCADE_SEQUENCE_PROXY__
#define __CASCADE_SEQUENCE_PROXY__

#include <unordered_map>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Dependency/CascadeSequence.hpp"
#include "Dependency/PostInfo.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class CascadeSequenceProxy : public ProxyModule {
private:

    std::unordered_map<std::string, CascadeSequence> m_cascadeSequences;

    std::ifstream m_cascadeSequenceFile;

public:
    CascadeSequenceProxy(const std::string& file) throw();

    virtual ~CascadeSequenceProxy();

    virtual void parse();

    virtual void show();

    time_t parseTime(std::string& str_time);

    CascadeSequence& getCascadeSequence(std::string info_id);

};

#endif
