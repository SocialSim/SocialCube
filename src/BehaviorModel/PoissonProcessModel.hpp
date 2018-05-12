#ifndef SOCIALCUBE_POISSONPROCESSMODEL_HPP
#define SOCIALCUBE_POISSONPROCESSMODEL_HPP

#include <vector>
#include <cmath>
#include <iostream>
#include <memory>
#include "common/Event.hpp"
#include "common/matOps.hpp"

class PoissonProcessModel {
private:

    PoissonProcessModel() = default;

    ~PoissonProcessModel() = default;

    static std::string generateUserID();

public:

    static std::vector<std::unique_ptr<Event>> evaluate(
            const std::string objectID,
            const std::vector<double>& mu,
            const std::vector<std::string>& typeList,
            int k,
            time_t t_startTime,
            time_t t_endTime
    );

};

#endif //SOCIALCUBE_POISSONPROCESSMODEL_HPP
