#ifndef __SCORE_MATRIX__
#define __SCORE_MATRIX__

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>
#include <numeric>

class ScoreMatrix {

private:

    std::unordered_map<std::string, std::vector<double>> m_score_table;

    std::vector<std::string> m_out_users;

    std::vector<std::string> m_inactive_users;

public:

    ScoreMatrix();

    ~ScoreMatrix();

    void insertUserScore(std::pair<std::string, std::vector<double>> t_p);

    void addOutUser(std::string t_id);

    void addInactiveUser(std::string t_id);

    std::vector<double> getUserScore(std::string t_id);

    std::string getOutUser(std::vector<std::string> t_v);

    std::string randomlyGetInactiveUser();
};

#endif
