#include <memory>
#include "AgentBuilder/AgentBuilder.hpp"
#include "Simulator/Simulator.hpp"
#include "Simulator/CacheAwareSimulator.hpp"
#include "Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/SimpleGithubObjectAgent.hpp"
#include "Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp"
#include "Agent/UserAgent/GithubAgent/ClusteredGithubUserAgent.hpp"
#include "ArgParser/ArgParser.hpp"


int main(int argc, const char* argv[]) {
    ArgParser args(argc, argv);

    AgentBuilder<ClusteredGithubUserAgent, SimpleGithubObjectAgent> builder;
    builder.build();
    
    CacheAwareSimulator s;
    s.setCurrentTime(args.getSimulationCurrentTime());
    s.setStartTime(args.getSimulationStartTime());
    s.setEndTime(args.getSimulationEndTime());
    s.setUnitTime(args.getSimulationUnitTime());
    s.setProfileShow(args.getSimulationShowProfileStatus());
    s.setEventShow(args.getSimulationShowEventStatus());
    s.setEventFileName(args.getSimulationEventFileName());

    std::vector<std::unique_ptr<ClusteredGithubUserAgent>>& agentList = builder.getUserAgentList();
    for(auto& iter : agentList)
        s.addUserAgent(move(iter));

    s.simulate();
}
