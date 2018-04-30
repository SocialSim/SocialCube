#include "util.hpp"

using namespace std;

template<typename T>
void socialcube::print_vec(const vector<T>& v) {
	for(auto& ele : v) {
		cout << ele << " ";	
	}
	cout << "\n";
}

