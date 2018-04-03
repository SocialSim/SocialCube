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

    // Initialize Simulator
    Simulator s;
    s.setStartTime(args.getSimulationStartTime());
    s.setEndTime(args.getSimulationEndTime());
    s.setUnitTime(args.getSimulationUnitTime());

    // Initialize SimulatorProfiler
    SimulatorProfiler& sp = SimulatorProfiler::getInstance();
    sp.setProfileShow(args.getSimulationShowProfileStatus());

    // Initialize EventManager
    EventManager& em = EventManager::getInstance();
    em.setEventShow(args.getSimulationShowEventStatus());
    em.setEventFileName(args.getSimulationEventFileName());
    em.setEventBufferSize(args.getSimulationEventBufferSize());

    // Initialize AgentBuilder
    AgentBuilder<ClusteredGithubUserAgent, SimpleGithubObjectAgent> builder;
    builder.build();
    std::vector<std::shared_ptr<ClusteredGithubUserAgent>>& agentList = builder.getUserAgentList();
    for(auto& iter : agentList)
        s.addUserAgent(iter.get());

    s.simulate();
}
