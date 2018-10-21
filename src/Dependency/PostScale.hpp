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

    std::vector<std::pair<int, int>> m_scales;

    std::string m_userID;

public:

    PostScale(std::string t_userID);

    ~PostScale();

    void pushScale(int t_number, int t_scale);

    int getScale(int t_index);

    void show();
};

#endif
