#include "matOps.hpp"

using namespace std;

vector<double> matops::ones(int k) {
	vector<double> v(k, 1.0);
	return v;
}

vector<double> matops::mul(const std::vector<double>& in, double m) {
	vector<double> v = in;
	for(auto& ele : v)
		ele *= m;
	return v;
}

vector<double> matops::mul(double m, const std::vector<double>& in) {
	return matops::mul(in, m);
}

vector<double> matops::inv(const std::vector<double>& in) {
	vector<double> v = in;
	for(auto& ele : v)
		ele *= -1;
	return v;
}

vector<double> matops::exp(const std::vector<double>& in) {
	vector<double> v = in;
	for(auto& ele : v)
		ele = std::exp(ele);
	return v;
}

vector<double> matops::add(const std::vector<double>& s, const std::vector<double>& t) {
	if(s.size() != t.size()) {
		throw;
	}

	std::vector<double> v(s.size(), 0.0);
	for(int i = 0; i < s.size(); ++i) {
		v[i] = s[i] + t[i];	
	}

	return v;
}

vector<double> matops::minus(const std::vector<double>& s, const std::vector<double>& t) {
	if(s.size() != t.size()) {
		throw;
	}
	std::vector<double> v(s.size(), 0.0);
	for(int i = 0; i < s.size(); ++i) {
		v[i] = s[i] - t[i];	
	}

	return v;
}

vector<double> matops::mul(const std::vector<double>& s, const std::vector<double>& t) {
	if(s.size() != t.size()) {
		throw;
	}
	std::vector<double> v(s.size(), 0.0);
	for(int i = 0; i < s.size(); ++i) {
		v[i] = s[i] * t[i];	
	}

	return v;
}

double matops::min(const std::vector<double>& in) {
	return *min_element(in.begin(), in.end());
}

int matops::minargs(const std::vector<double>& in) {
	return min_element(in.begin(), in.end()) - in.begin();
}
