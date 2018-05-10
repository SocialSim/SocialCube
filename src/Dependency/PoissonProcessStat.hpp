#ifndef SOCIALCUBE_POISSONPROCESSSTAT_HPP
#define SOCIALCUBE_POISSONPROCESSSTAT_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <cstdint>
#include <iostream>
#include <cassert>
#include "common/util.hpp"

class PoissonProcessStat {
private:

    double mu;
    std::string type;
    std::string m_userID;

public:

    PoissonProcessStat(const std::string &t_userID);

    ~PoissonProcessStat() = default;

    void setMu(const double in);

    void setType(const std::string &in);

    double getMu() const;

    std::string getType() const;

    std::string getUserID() const;

    void show() const;
};

#endif //SOCIALCUBE_POISSONPROCESSSTAT_HPP
