#include <cstdint>
#include <memory>
#include "AgentBuilder/AgentBuilder.hpp"
#include "Simulator/Simulator.hpp"
#include "Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/SimpleGithubObjectAgent.hpp"
#include "Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp"


int main() {
    srand(time(NULL));

    AgentBuilder<SimpleGithubUserAgent, SimpleGithubObjectAgent> builder;
    builder.build();
    
    Simulator s;
    s.setCurrentTime(0);
    s.setStartTime(0);
    s.setEndTime(24);
    s.setUnitTime(1);

    std::vector<std::unique_ptr<SimpleGithubUserAgent>>& agentList = builder.getUserAgentList();
    for(auto& iter : agentList)
        s.addUserAgent(move(iter));

    s.simulate();
    // s.showEvent();
}
