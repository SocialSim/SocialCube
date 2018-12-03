#ifndef __RESPONSE_TYPE_PROBABILITY__
#define __RESPONSE_TYPE_PROBABILITY__

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>

class ResponseTypeProbability {

private:

    std::vector<std::string> m_response_type_prob;

    std::string m_userID;

public:

    ResponseTypeProbability(std::string t_userID);

    ~ResponseTypeProbability();

    void pushResponseType(std::string t_input);

    std::vector<std::string> getResponseTypeProb();

    void show();
};

#endif
