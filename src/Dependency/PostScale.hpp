#ifndef __POST_SCALE__
#define __POST_SCALE__

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>

class PostScale {

private:

    std::vector<std::pair<double, double>> m_scales;

    std::string m_userID;

public:

    PostScale(std::string t_userID);

    ~PostScale();

    void pushScale(double t_number, double t_scale);

    std::vector<std::pair<double, double>> getScale();

    void show();
};

#endif
