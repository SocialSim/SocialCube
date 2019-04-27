#include "ScoreMatrixProxy.hpp"

using namespace std;

DBG(static const string tag="ScoreMatrixProxy";)

ScoreMatrixProxy::ScoreMatrixProxy(const std::string& scoreMatrixFile, const std::string& inactiveUserFile) throw() {
    try {
        m_scoreMatrixFile.open(scoreMatrixFile);
        m_inactiveUserFile.open(inactiveUserFile);
    } catch (exception &e) {
        ScoreMatrixProxyException t_e;
        throw t_e;
    }
    assert(m_scoreMatrixFile.is_open());
    assert(m_inactiveUserFile.is_open());
    return;
}

ScoreMatrixProxy::~ScoreMatrixProxy() {
    m_scoreMatrixFile.close();
    m_inactiveUserFile.close();
    return;
}

void ScoreMatrixProxy::parse() {
    // Parse ScoreMatrixFile
    m_scoreMatrix = ScoreMatrix();

    string tmp;

    // Set top-k
    getline(m_scoreMatrixFile, tmp);
    m_scoreMatrix.setTopK(stod(tmp));

    getline(m_scoreMatrixFile, tmp);
    std::istringstream s(tmp.substr(1));
    string user_id;

    while (std::getline(s, user_id, ','))
    {
        m_scoreMatrix.addOutUser(user_id);
    }

    while (getline(m_scoreMatrixFile, tmp)) {
        string user_id = tmp.substr(0, tmp.find(","));
        std::istringstream s(tmp.substr(tmp.find(",")+1));
        vector<double> scores;
        double f;
        while (s >> f) {
            scores.push_back(f);
            if (s.peek() == ',')
                s.ignore();
        }
        m_scoreMatrix.insertUserScore(make_pair(user_id, scores));
    }

    // Parse InactiveUserFile
    while (getline(m_inactiveUserFile, tmp)) {
        m_scoreMatrix.addInactiveUser(tmp);
    }
}

void ScoreMatrixProxy::show() {
    return;
}

ScoreMatrix& ScoreMatrixProxy::get() {
    return m_scoreMatrix;
}
