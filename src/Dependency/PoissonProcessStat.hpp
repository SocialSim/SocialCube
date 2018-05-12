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

    std::vector<double> mu;
    std::vector<std::string> typeList;
    int k;
    std::string m_userID;

public:

    PoissonProcessStat(const std::string &t_userID);

    ~PoissonProcessStat() = default;

    void setMu(const std::vector<double>& in);

    void setTypeList(const std::vector<std::string>& in);

    void setK(int t_k);

    std::vector<double> getMu() const;

    std::vector<std::string> getTypeList() const;

    int getK() const;

    void show() const;

    std::string getUserID() const;
};

#endif //SOCIALCUBE_POISSONPROCESSSTAT_HPP
