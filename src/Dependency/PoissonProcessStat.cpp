#include "PoissonProcessStat.hpp"

using namespace std;

PoissonProcessStat::PoissonProcessStat(const std::string &t_userID) :
        m_userID(t_userID) {
    return;
}

void PoissonProcessStat::setMu(const double in) {
    mu = in;
}

void PoissonProcessStat::setType(const string &in) {
    type = in;
}

double PoissonProcessStat::getMu() const {
    return mu;
}

string PoissonProcessStat::getType() const {
    return type;
}

void PoissonProcessStat::show() const {
    cout << "User " << m_userID << endl;

    cout << "type " << type << endl;

    cout << "mu " << mu << endl;

    cout << "\n\n";
}

string PoissonProcessStat::getUserID() const {
    return m_userID;
}
