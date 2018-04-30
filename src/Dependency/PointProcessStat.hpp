#ifndef __POINT_PROCESS_STAT__
#define __POINT_PROCESS_STAT__

#include <unordered_map>
#include <string>
#include <memory>
#include <cstdint>
#include <iostream>
#include <cassert>
#include "EventHourlyActionRate.hpp"
#include "common/util.hpp"

class PointProcessStat {
    private:

		std::vector<double> mu;
		std::vector<std::vector<double>> alpha;
		std::vector<double> beta;
		std::vector<std::string> typeList;
		int k;
        std::string m_userID;

    public:

        PointProcessStat(const std::string &t_userID);

        ~PointProcessStat() = default;

		void setMu(const std::vector<double>& in);

		void setAlpha(const std::vector<std::vector<double>>& in);

		void setBeta(const std::vector<double>& in);

		void setTypeList(const std::vector<std::string>& in);

		void setK(int t_k);

		std::vector<double> getMu() const;

		std::vector<std::vector<double>> getAlpha() const;

		std::vector<double> getBeta() const;

		std::vector<std::string> getTypeList() const;

		int getK() const;

        void show() const;

        std::string getUserID() const;
};

#endif
