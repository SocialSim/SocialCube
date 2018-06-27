#include "PointProcessStat.hpp"

using namespace std;

PointProcessStat::PointProcessStat(const std::string &t_userID) :
    m_userID(t_userID) {
    return;
}

void PointProcessStat::setMu(const vector<double>& in) {
	mu = in;
}

void PointProcessStat::setAlpha(const vector<vector<double>>& in) {
	alpha = in;
}

void PointProcessStat::setBeta(const vector<double>& in) {
	beta = in;
}

void PointProcessStat::setTypeList(const vector<string>& in) {
	typeList = in;
}

void PointProcessStat::setK(int t_k) {
	k = t_k;
}

vector<double> PointProcessStat::getMu() const {
	return mu;
}

vector<vector<double>> PointProcessStat::getAlpha() const {
	return alpha;
}

vector<double> PointProcessStat::getBeta() const {
	return beta;
}

vector<string> PointProcessStat::getTypeList() const {
	cout << "=========================" << endl;
	cout << "m_userID = " << m_userID << ", typeList:" << endl;
	socialcube::print_vec(typeList);
	cout << "=========================" << endl;

	return typeList;
}

int PointProcessStat::getK() const {
	return k;
}

void PointProcessStat::show() const {
    cout << "User " << m_userID << endl;
    cout << "K: " << k << endl;

	cout << "type list " << endl;
	socialcube::print_vec(typeList);

	cout << "mu " << endl;
	socialcube::print_vec(mu);

	cout << "alpha " << endl;
	for(auto& v : alpha) {
		socialcube::print_vec(v);
	}

	cout << "beta " << endl;
	socialcube::print_vec(beta);

	cout << "\n\n";
}

string PointProcessStat::getUserID() const {
	return m_userID;
}
