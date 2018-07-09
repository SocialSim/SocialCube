#include <memory>
#include "AgentBuilder/AgentBuilder.hpp"
#include "Simulator/Simulator.hpp"
#include "Simulator/EventBasedSimulator.hpp"
#include "Simulator/CacheAwareSimulator.hpp"
#include "Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp"
#include "Agent/UserAgent/GithubAgent/DailySimpleGithubUserAgent.hpp"
#include "Agent/ObjectAgent/ObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/SimpleGithubObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/PointProcessObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/IntegratedPointProcessObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/IntegratedPoissonProcessObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/PoissonProcessObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/ClassifiedPointProcessObjectAgent.hpp"
#include "Agent/ObjectAgent/GithubAgent/ClassifiedPoissonProcessObjectAgent.hpp"
#include "Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp"
#include "Agent/UserAgent/GithubAgent/ClusteredGithubUserAgent.hpp"
#include "ArgParser/ArgParser.hpp"

int main(int argc, const char* argv[]) {
    ArgParser args(argc, argv);

    /**
     * Read config file
     */

    std::ifstream infile(args.getProxyConfigFileName());
    std::string line;
    std::string delimiter = "=";

    std::string builderType;

    std::map <std::string, std::string> filePaths;

    while (std::getline(infile, line)) {
        if (line.length() > 0 && line.at(0) == '#') {
            builderType = line.substr(line.find('#') + 1, line.length());
            // Initialize AgentBuilder
        } else if (line.length() > 0) {
            int pos = line.find(delimiter);
            if (pos != std::string::npos) {
                std::string fileName = line.substr(0, pos);
                std::string path = line.substr(pos + delimiter.length(), line.length());
                filePaths.insert(std::pair <std::string, std::string> (fileName, path));
            } else {
                cout << "Format Error!" << endl;
            }
        }

        if (line.length() == 0 or infile.peek() == EOF) {
            // Initialize SimulatorProfiler
            SimulatorProfiler& sp = SimulatorProfiler::getInstance();
            sp.setProfileShow(args.getSimulationShowProfileStatus());

            // Initialize EventManager
            EventManager& em = EventManager::getInstance();
            em.setCenter(args.getSimulationCenter());
            em.setEventShow(args.getSimulationShowEventStatus());
            em.setEventFileName(args.getSimulationEventFileName());
            em.setEventBufferSize(args.getSimulationEventBufferSize());

            if (builderType == "PointProcess") {
                // Initialize Simulator
                EventBasedSimulator s;
                s.setStartTime(args.getSimulationStartTime());
                s.setEndTime(args.getSimulationEndTime());
                s.setUnitTime(args.getSimulationUnitTime());

                AgentBuilder<SimpleGithubUserAgent, PointProcessObjectAgent> builder(args.getDefaultFilePath());
                for (auto& iter : filePaths) {
                    builder.setFilePath(iter.first, iter.second);
                }
                filePaths.clear();
                std::vector<std::shared_ptr<PointProcessObjectAgent>> agentList;
                builder.build();
                agentList = builder.getObjectAgentList();
                for(auto& iter : agentList)
                    s.addUserAgent(iter.get());
                s.simulate();
            } else if (builderType == "ClassifiedPointProcess") {
                // Initialize Simulator
                EventBasedSimulator s;
                s.setStartTime(args.getSimulationStartTime());
                s.setEndTime(args.getSimulationEndTime());
                s.setUnitTime(args.getSimulationUnitTime());

                AgentBuilder<SimpleGithubUserAgent, ClassifiedPointProcessObjectAgent> builder(args.getDefaultFilePath());

                for (auto& iter : filePaths) {
                    builder.setFilePath(iter.first, iter.second);
                }
                filePaths.clear();
                std::vector<std::shared_ptr<ClassifiedPointProcessObjectAgent>> agentList;
                builder.build();
                agentList = builder.getObjectAgentList();
                for(auto& iter : agentList)
                    s.addUserAgent(iter.get());
                s.simulate();
            } else if (builderType == "PoissonProcess") {
                // Initialize Simulator
                EventBasedSimulator s;
                s.setStartTime(args.getSimulationStartTime());
                s.setEndTime(args.getSimulationEndTime());
                s.setUnitTime(args.getSimulationUnitTime());

                AgentBuilder<SimpleGithubUserAgent, PoissonProcessObjectAgent> builder(args.getDefaultFilePath());
                for (auto& iter : filePaths)
                    builder.setFilePath(iter.first, iter.second);
                filePaths.clear();
                std::vector<std::shared_ptr<PoissonProcessObjectAgent>> agentList;
                builder.build();
                agentList = builder.getObjectAgentList();
                for(auto& iter : agentList)
                    s.addUserAgent(iter.get());
                s.simulate();
            } else if (builderType == "ClassifiedPoissonProcess") {
                // Initialize Simulator
                EventBasedSimulator s;
                s.setStartTime(args.getSimulationStartTime());
                s.setEndTime(args.getSimulationEndTime());
                s.setUnitTime(args.getSimulationUnitTime());

                AgentBuilder<SimpleGithubUserAgent, ClassifiedPoissonProcessObjectAgent> builder(args.getDefaultFilePath());
                for (auto& iter : filePaths) {
                    builder.setFilePath(iter.first, iter.second);
                }
                filePaths.clear();
                std::vector<std::shared_ptr<ClassifiedPoissonProcessObjectAgent>> agentList;
                builder.build();
                agentList = builder.getObjectAgentList();
                for(auto& iter : agentList)
                    s.addUserAgent(iter.get());
                s.simulate();
            } else if (builderType == "SimpleBehavior") {
                // Initialize Simulator
                Simulator s;
                s.setStartTime(args.getSimulationStartTime());
                s.setEndTime(args.getSimulationEndTime());
                s.setUnitTime(args.getSimulationUnitTime());

                AgentBuilder<SimpleGithubUserAgent, SimpleGithubObjectAgent> builder(args.getDefaultFilePath());
                for (auto& iter : filePaths)
                    builder.setFilePath(iter.first, iter.second);
                filePaths.clear();
                std::vector<std::shared_ptr<SimpleGithubUserAgent>> agentList;
                builder.build();
                agentList = builder.getUserAgentList();
                for(auto& iter : agentList) {
                    s.addUserAgent(iter.get());
                }
                s.simulate();
            } else if (builderType == "DailySimpleBehavior") {
                EventBasedSimulator s;
                s.setStartTime(args.getSimulationStartTime());
                s.setEndTime(args.getSimulationEndTime());
                s.setUnitTime(args.getSimulationUnitTime());

                AgentBuilder<DailySimpleGithubUserAgent, SimpleGithubObjectAgent> builder(args.getDefaultFilePath());
                for (auto& iter : filePaths)
                    builder.setFilePath(iter.first, iter.second);
                filePaths.clear();
                std::vector<std::shared_ptr<DailySimpleGithubUserAgent>> agentList;
                builder.build();
                agentList = builder.getUserAgentList();
                for(auto& iter : agentList) {
                    s.addUserAgent(iter.get());
                }
                s.simulate();
            } else if (builderType == "IntegratedPointProcess") {
                EventBasedSimulator s;
                s.setStartTime(args.getSimulationStartTime());
                s.setEndTime(args.getSimulationEndTime());
                s.setUnitTime(args.getSimulationUnitTime());

                AgentBuilder<SimpleGithubUserAgent, IntegratedPointProcessObjectAgent> builder(args.getDefaultFilePath());
                for (auto& iter : filePaths) {
                    builder.setFilePath(iter.first, iter.second);
                }
                filePaths.clear();
                std::vector<std::shared_ptr<IntegratedPointProcessObjectAgent>> agentList;
                builder.build();
                agentList = builder.getObjectAgentList();
                for(auto& iter : agentList)
                    s.addUserAgent(iter.get());
                s.simulate();
            } else if (builderType == "IntegratedPoissonProcess") {
                EventBasedSimulator s;
                s.setStartTime(args.getSimulationStartTime());
                s.setEndTime(args.getSimulationEndTime());
                s.setUnitTime(args.getSimulationUnitTime());

                AgentBuilder<SimpleGithubUserAgent, IntegratedPoissonProcessObjectAgent> builder(args.getDefaultFilePath());
                for (auto &iter : filePaths) {
                    builder.setFilePath(iter.first, iter.second);
                }
                filePaths.clear();
                std::vector <std::shared_ptr<IntegratedPoissonProcessObjectAgent>> agentList;
                builder.build();
                cout << "finish build" <<endl;
                agentList = builder.getObjectAgentList();
                for (auto &iter : agentList)
                    s.addUserAgent(iter.get());
                cout << "start simulate" << endl;
                s.simulate();
            } else {
                std::cout << "Unsupported model type" << std::endl;
            }
        }
    }
}
