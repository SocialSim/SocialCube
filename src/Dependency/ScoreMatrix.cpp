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
    if (t_id.substr(0, 5).compare("root-") == 0 && m_score_table.find(t_id) == m_score_table.end()) {
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

//    cout << "t_v: " << endl;
    for (auto& iter : t_v) {
//        cout << iter << endl;
        if (sum.size() == 0) {
            sum = getUserScore("root-" + iter);
        } else {
            vector<double> user_embedding = getUserScore(iter);
            transform(sum.begin(), sum.end(), user_embedding.begin(), sum.begin(), std::plus<double>());
        }
    }
//    cout << "sum:" << endl;
//    for (auto & iter : sum) {
//        cout << iter << endl;
//    }

//    cout << "sum.size() = " << sum.size() << endl;
    unordered_map<int, double> index_score;

    vector<int> top_k_index = getTopKIndex(sum);

//    cout << "after getTopKIndex, top_k_index.size() = " << top_k_index.size() << endl;

    vector<double> top_k_score;
    double top_k_sum = 0;

    for (auto &iter : top_k_index) {
        top_k_score.push_back(sum[iter]);
        top_k_sum += sum[iter];
//        cout << iter << ", " << sum[iter] << ", top_k_sum = " << top_k_sum << endl;
    }

    double randnum = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);

    double tmp_sum = 0;
    for (int i = 0; i < top_k_score.size(); i++) {
//        cout << "top_k_score[i] = " << top_k_score[i] << ", top_k_sum = " << top_k_sum << endl;
        tmp_sum += top_k_score[i] / top_k_sum;
//        cout << "randnum = " << randnum << ", top_k_score[i] / top_k_sum = " << top_k_score[i] / top_k_sum << ", " << tmp_sum << endl;
        if (randnum <= tmp_sum) {
//            cout << "return " << m_out_users[top_k_index[i]] << endl;
            return m_out_users[top_k_index[i]];
        }
    }
}

vector<int> ScoreMatrix::getTopKIndex(vector<double> t_sum) {
    priority_queue< pair<double, int>, vector<std::pair<double, int>>, greater <pair<double, int>> > q;
    int k = m_top_k;
    for (int i = 0; i < t_sum.size(); ++i) {
        if(q.size()<k)
            q.push(std::pair<double, int>(t_sum[i], i));
        else if(q.top().first < t_sum[i]){
            q.pop();
            q.push(std::pair<double, int>(t_sum[i], i));
        }
    }
    k = q.size();
    vector<int> result(k);
    for (int i = 0; i < k; ++i) {
        result[k - i - 1] = q.top().second;
        q.pop();
    }

    return result;
}

void ScoreMatrix::setTopK(int t_top_k) {
    m_top_k = t_top_k;
}

int ScoreMatrix::getTopK() {
    return m_top_k;
}

std::string ScoreMatrix::randomlyGetInactiveUser() {
    int randnum = rand() % m_inactive_users.size();
    return m_inactive_users[randnum];
}