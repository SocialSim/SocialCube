#include "ScoreMatrix.hpp"

using namespace std;

ScoreMatrix::ScoreMatrix() {
    return;
}

ScoreMatrix::~ScoreMatrix() {
    return;
}

void ScoreMatrix::insertUserScore(std::pair<std::string, std::vector<double>> t_p) {
    m_score_table.insert((std::pair<std::string, std::vector<double>>) t_p);
}

void ScoreMatrix::addOutUser(std::string t_id) {
    m_out_users.push_back(t_id);
}

void ScoreMatrix::addInactiveUser(std::string t_id) {
    m_inactive_users.push_back(t_id);
}

std::vector<double> ScoreMatrix::getUserScore(std::string t_id) {
    if (t_id.substr(0, 5) == "root-" && m_score_table.find(t_id) == m_score_table.end()) {
        return m_score_table["UNK_ROOT"];
    } else if (m_score_table.find(t_id) == m_score_table.end()) {
        return m_score_table["UNK_COMM"];
    } else {
        return m_score_table[t_id];
    }
}

std::string ScoreMatrix::getOutUser(std::vector<string> t_v) {
    assert(t_v.size() == 4);

    vector<double> sum;

    for (auto& iter : t_v) {
        if (sum.size() == 0) {
            sum = getUserScore("root-" + iter);
        } else {
            vector<double> user_embedding = getUserScore(iter);
            transform(sum.begin(), sum.end(), user_embedding.begin(), sum.begin(), std::plus<double>());
        }
    }

    int max_index = distance(sum.begin(), max_element(sum.begin(), sum.end()));

    if (max_index == 0) {
        int randnum = rand() % m_inactive_users.size();
        return m_inactive_users[randnum];
    } else {
        return m_out_users[max_index];
    }
}