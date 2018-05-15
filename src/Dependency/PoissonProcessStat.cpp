#include "PoissonProcessStat.hpp"

using namespace std;

PoissonProcessStat::PoissonProcessStat(const std::string &t_userID) :
        m_userID(t_userID) {
    return;
}

void PoissonProcessStat::setMu(const vector<double>& in) {
    mu = in;
}

void PoissonProcessStat::setTypeList(const vector<string>& in) {
    typeList = in;
}

void PoissonProcessStat::setK(int t_k) {
    k = t_k;
}

vector<double> PoissonProcessStat::getMu() const {
    return mu;
}

vector<string> PoissonProcessStat::getTypeList() const {
    return typeList;
}

int PoissonProcessStat::getK() const {
    return k;
}

void PoissonProcessStat::show() const {
    cout << "User " << m_userID << endl;
    cout << "K: " << k << endl;

    cout << "type list " << endl;
    socialcube::print_vec(typeList);

    cout << "mu " << endl;
    socialcube::print_vec(mu);

    cout << "\n\n";
}

string PoissonProcessStat::getUserID() const {
    return m_userID;
}
