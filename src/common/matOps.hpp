#ifndef __MATOPS__
#define __MATOPS__

#include <vector>
#include <algorithm>

namespace matops {

	std::vector<double> ones(int k);
	std::vector<double> mul(const std::vector<double>& in, double m);
	std::vector<double> mul(double m, const std::vector<double>& in);
	std::vector<double> inv(const std::vector<double>& in);
	std::vector<double> exp(const std::vector<double>& in);
	std::vector<double> add(const std::vector<double>& s, const std::vector<double>& t);
	std::vector<double> minus(const std::vector<double>& s, const std::vector<double>& t);
	std::vector<double> mul(const std::vector<double>& s, const std::vector<double>& t);
	double min(const std::vector<double>& in);
	int minargs(const std::vector<double>& in);

}

#endif
