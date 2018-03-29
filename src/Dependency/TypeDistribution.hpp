#ifndef __TYPE_DISTRIBUTION__
#define __TYPE_DISTRIBUTION__

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>

class TypeDistribution {

    private:

        // hour -> action rate of that hour
        std::vector<double> m_dist;

        std::string m_userID;

        static const std::unordered_map<std::string, int> m_actions;

    public:

        static size_t getActionCount();

        TypeDistribution(std::string t_userID);

        ~TypeDistribution();

        void pushDist(double t_dist);

        double getDist(int t_actionIndex);

        void show();
};

#endif
