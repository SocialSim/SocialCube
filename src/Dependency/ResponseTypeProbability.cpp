#include "ResponseTypeProbability.hpp"

using namespace std;

ResponseTypeProbability::ResponseTypeProbability(std::string t_userID) : m_userID(t_userID) {
    return;
}

ResponseTypeProbability::~ResponseTypeProbability() {
    return;
}

void ResponseTypeProbability::pushResponseType(std::string t_input) {
    m_response_type_prob.push_back(t_input);
}

std::vector<std::string> ResponseTypeProbability::getResponseTypeProb() {
    return m_response_type_prob;
};

void ResponseTypeProbability::show() {
    cout << "userID: " << m_userID << endl;
    cout << endl;
}