#ifndef SOCIALCUBE_POISSORPROCESSSTAT_HPP
#define SOCIALCUBE_POISSORPROCESSSTAT_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <cstdint>
#include <iostream>
#include <cassert>
#include "EventHourlyActionRate.hpp"
#include "common/util.hpp"

class PoissonProcessStat {
private:

    std::double mu;
    std::string type;
    std::string m_userID;

public:

    PoissonProcessStat(const std::string &t_userID);

    ~PoissonProcessStat() = default;

    void setMu(const std::vector<double>& in);

    void setType(const std::string in);

    std::double getMu() const;

    std::string getType() const;

    std::string getUserID() const;

    void show() const;
};

#endif //SOCIALCUBE_POISSORPROCESSSTAT_HPP
