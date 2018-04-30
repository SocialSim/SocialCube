#ifndef __SIMPLE_BEHAVIOR_MODEL__
#define __SIMPLE_BEHAVIOR_MODEL__

#include <vector>
#include <cmath>
#include <iostream>
#include <memory>
#include "common/Event.hpp"
#include "common/matOps.hpp"

class PointProcessModel {
    private:

        PointProcessModel() = default;

        ~PointProcessModel() = default;

		static std::string generateUserID();

    public:

	static std::vector<std::unique_ptr<Event>> evaluate(
		const std::string objectID,
		const std::vector<double>& mu,
		const std::vector<std::vector<double>>& alpha,
		const std::vector<double>& beta,
		const std::vector<std::string>& typeList,
		int k,
        time_t t_startTime,
        time_t t_endTime
        );

};

#endif
