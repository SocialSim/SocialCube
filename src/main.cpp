#include <memory>
#include "AgentBuilder/AgentBuilder.hpp"
#include "Simulator/Simulator.hpp"
#include "Simulator/CacheAwareSimulator.hpp"
#include "Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/SimpleGithubObjectAgent.hpp"
#include "Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp"
#include "ArgParser/ArgParser.hpp"


int main(int argc, const char* argv[]) {
    ArgParser args(argc, argv);

    AgentBuilder<SimpleGithubUserAgent, SimpleGithubObjectAgent> builder;
    builder.build();
    
    CacheAwareSimulator s;
    s.setCurrentTime(args.getSimulationCurrentTime());
    s.setStartTime(args.getSimulationStartTime());
    s.setEndTime(args.getSimulationEndTime());
    s.setUnitTime(args.getSimulationUnitTime());
    s.setProfileShow(args.getSimulationShowProfileStatus());
    s.setEventShow(args.getSimulationShowEventStatus());
    s.setEventFileName(args.getSimulationEventFileName());

    std::vector<std::unique_ptr<SimpleGithubUserAgent>>& agentList = builder.getUserAgentList();
    for(auto& iter : agentList)
        s.addUserAgent(move(iter));

    s.simulate();
}
