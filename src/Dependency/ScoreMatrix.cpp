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
//    cout << "getUserScore, t_id: " << t_id << endl;
//    cout << "t_id.substr(0, 5) = " << t_id.substr(0, 5) << endl;
//    cout << "m_out_users.size() = " << m_out_users.size() << endl;

    for (auto& iter : m_out_users) {
        cout << iter << endl;
    }

    if (t_id.substr(0, 5).compare("root-") == 0 && m_score_table.find(t_id) == m_score_table.end()) {
//        cout << "UNK_ROOT" << endl;
        return m_score_table["UNK_ROOT"];
    } else if (m_score_table.find(t_id) == m_score_table.end()) {
//        cout << "UNK_COMM" << endl;
        return m_score_table["UNK_COMM"];
    } else {
//        cout << "m_score_table[t_id]" << endl;
//        for (auto& iter : m_score_table[t_id]) {
//            cout << iter << endl;
//        }
        return m_score_table[t_id];
    }
}

std::string ScoreMatrix::getOutUser(std::vector<string> t_v) {
    assert(t_v.size() == 4);

    vector<double> sum;

//    cout << "in getOutUser, t_v:" << endl;
    for (auto& iter : t_v) {
        cout << iter << endl;
    }

    for (auto& iter : t_v) {
        if (sum.size() == 0) {
//            sum = getUserScore("root-" + iter);
        } else {
            vector<double> user_embedding = getUserScore(iter);
            transform(sum.begin(), sum.end(), user_embedding.begin(), sum.begin(), std::plus<double>());
        }
//        cout << "======sum========" << endl;
//        for (auto& iter : sum) {
//            cout << iter << endl;
//        }
    }

    int max_index = distance(sum.begin(), max_element(sum.begin(), sum.end()));

//    cout << "max_index = " << max_index << endl;
//    cout << "m_out_users[max_index] = " << m_out_users[max_index] << endl;
    return m_out_users[max_index];
}

std::string ScoreMatrix::randomlyGetInactiveUser() {
    int randnum = rand() % m_inactive_users.size();
    return m_inactive_users[randnum];
}