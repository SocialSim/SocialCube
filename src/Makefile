BASEDIR := $(SOCIALCUBEPATH)
SRCDIR := $(BASEDIR)/src

TARGET := socialcube

CXX := g++
CXX_FLAGS := -O0 -g -DDEBUG
#CXX_FLAGS := -g3 -pthread
CXX_FLAGS := $(CXX_FLAGS) -Wall -W -Wmissing-declarations -Wredundant-decls -Wdisabled-optimization
CXX_FLAGS := $(CXX_FLAGS) -Wpointer-arith -Wsign-compare -Wendif-labels
CXX_FLAGS := $(CXX_FLAGS) -std=c++14
CXX_FLAGS := $(CXX_FLAGS) -I $(SRCDIR)

OBJS := Simulator.o
OBJS := $(OBJS) CacheAwareSimulator.o
OBJS := $(OBJS) EventBasedSimulator.o
OBJS := $(OBJS) SimpleGithubUserAgent.o 
OBJS := $(OBJS) ClusteredGithubUserAgent.o 
OBJS := $(OBJS) Community.o 
OBJS := $(OBJS) CommunityManager.o 
OBJS := $(OBJS) SimpleGithubObjectAgent.o 
OBJS := $(OBJS) PointProcessObjectAgent.o
OBJS := $(OBJS) IntegratedPointProcessObjectAgent.o
OBJS := $(OBJS) IntegratedPoissonProcessObjectAgent.o
OBJS := $(OBJS) PoissonProcessObjectAgent.o
OBJS := $(OBJS) BehaviorModel.o
OBJS := $(OBJS) PointProcessModel.o
OBJS := $(OBJS) IntegratedPointProcessModel.o
OBJS := $(OBJS) IntegratedPoissonProcessModel.o
OBJS := $(OBJS) PoissonProcessModel.o
OBJS := $(OBJS) EventHourlyActionRate.o
OBJS := $(OBJS) HourlyActionRate.o
OBJS := $(OBJS) ObjectPreference.o
OBJS := $(OBJS) TypeDistribution.o
OBJS := $(OBJS) UserDistribution.o
OBJS := $(OBJS) PointProcessStat.o
OBJS := $(OBJS) PoissonProcessStat.o
OBJS := $(OBJS) StatisticProxy.o
OBJS := $(OBJS) HourlyActionRateProxy.o
OBJS := $(OBJS) ObjectPreferenceProxy.o
OBJS := $(OBJS) TypeDistributionProxy.o
OBJS := $(OBJS) UserDistributionProxy.o
OBJS := $(OBJS) PointProcessProxy.o
OBJS := $(OBJS) PoissonProcessProxy.o
OBJS := $(OBJS) CountryCodesProxy.o
OBJS := $(OBJS) ActivityLevelProxy.o
OBJS := $(OBJS) ObjectIDProxy.o
OBJS := $(OBJS) UserIDProxy.o
OBJS := $(OBJS) ClusteredUserIDProxy.o
OBJS := $(OBJS) Event.o
OBJS := $(OBJS) EventManager.o
OBJS := $(OBJS) DependentEventLogger.o
OBJS := $(OBJS) ArgParser.o
OBJS := $(OBJS) Log.o
OBJS := $(OBJS) SimulatorProfiler.o
OBJS := $(OBJS) matOps.o
OBJS := $(OBJS) main.o

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CXX) $(CXX_FLAGS) $^ -o $@

Simulator.o:	./Simulator/Simulator.cpp ./Simulator/Simulator.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

CacheAwareSimulator.o:	./Simulator/CacheAwareSimulator.cpp ./Simulator/CacheAwareSimulator.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

EventBasedSimulator.o:	./Simulator/EventBasedSimulator.cpp ./Simulator/EventBasedSimulator.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

SimpleGithubUserAgent.o:	./Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.cpp ./Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

SimpleGithubObjectAgent.o:	./Agent/ObjectAgent/GithubAgent/SimpleGithubObjectAgent.cpp ./Agent/ObjectAgent/GithubAgent/SimpleGithubObjectAgent.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

PointProcessObjectAgent.o:	./Agent/ObjectAgent/GithubAgent/PointProcessObjectAgent.cpp ./Agent/ObjectAgent/GithubAgent/PointProcessObjectAgent.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

IntegratedPointProcessObjectAgent.o:	./Agent/ObjectAgent/GithubAgent/IntegratedPointProcessObjectAgent.cpp ./Agent/ObjectAgent/GithubAgent/IntegratedPointProcessObjectAgent.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

IntegratedPoissonProcessObjectAgent.o:	./Agent/ObjectAgent/GithubAgent/IntegratedPoissonProcessObjectAgent.cpp ./Agent/ObjectAgent/GithubAgent/IntegratedPoissonProcessObjectAgent.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

PoissonProcessObjectAgent.o:	./Agent/ObjectAgent/GithubAgent/PoissonProcessObjectAgent.cpp ./Agent/ObjectAgent/GithubAgent/PoissonProcessObjectAgent.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

BehaviorModel.o:	./BehaviorModel/SimpleBehaviorModel.cpp ./BehaviorModel/SimpleBehaviorModel.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

PointProcessModel.o:	./BehaviorModel/PointProcessModel.cpp ./BehaviorModel/PointProcessModel.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

IntegratedPointProcessModel.o:	./BehaviorModel/IntegratedPointProcessModel.cpp ./BehaviorModel/IntegratedPointProcessModel.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

IntegratedPoissonProcessModel.o:	./BehaviorModel/IntegratedPoissonProcessModel.cpp ./BehaviorModel/IntegratedPoissonProcessModel.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

PoissonProcessModel.o:	./BehaviorModel/PoissonProcessModel.cpp ./BehaviorModel/PoissonProcessModel.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

EventHourlyActionRate.o:	./Dependency/EventHourlyActionRate.cpp ./Dependency/EventHourlyActionRate.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

HourlyActionRate.o:	./Dependency/HourlyActionRate.cpp ./Dependency/HourlyActionRate.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

ObjectPreference.o:	./Dependency/ObjectPreference.cpp ./Dependency/ObjectPreference.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

UserDependency.o:	./Dependency/UserDependency.cpp ./Dependency/UserDependency.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

TypeDistribution.o:	./Dependency/TypeDistribution.cpp ./Dependency/TypeDistribution.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

UserDistribution.o: ./Dependency/UserDistribution.cpp ./Dependency/UserDistribution.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

PointProcessStat.o:	./Dependency/PointProcessStat.cpp ./Dependency/PointProcessStat.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

PoissonProcessStat.o:	./Dependency/PoissonProcessStat.cpp ./Dependency/PoissonProcessStat.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

StatisticProxy.o:	./StatisticProxy/StatisticProxy.cpp ./StatisticProxy/StatisticProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

HourlyActionRateProxy.o:	./StatisticProxy/HourlyActionRateProxy/HourlyActionRateProxy.cpp ./StatisticProxy/HourlyActionRateProxy/HourlyActionRateProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

ObjectPreferenceProxy.o:	./StatisticProxy/ObjectPreferenceProxy/ObjectPreferenceProxy.cpp ./StatisticProxy/ObjectPreferenceProxy/ObjectPreferenceProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

TypeDistributionProxy.o:	./StatisticProxy/TypeDistributionProxy/TypeDistributionProxy.cpp ./StatisticProxy/TypeDistributionProxy/TypeDistributionProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

UserDistributionProxy.o:	./StatisticProxy/UserDistributionProxy/UserDistributionProxy.cpp ./StatisticProxy/UserDistributionProxy/UserDistributionProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

ObjectIDProxy.o:	./StatisticProxy/ObjectIDProxy/ObjectIDProxy.cpp ./StatisticProxy/ObjectIDProxy/ObjectIDProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

UserIDProxy.o:	./StatisticProxy/UserIDProxy/UserIDProxy.cpp ./StatisticProxy/UserIDProxy/UserIDProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

ClusteredUserIDProxy.o:	./StatisticProxy/UserIDProxy/ClusteredUserIDProxy.cpp ./StatisticProxy/UserIDProxy/ClusteredUserIDProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

PointProcessProxy.o:	./StatisticProxy/PointProcessProxy/PointProcessProxy.cpp ./StatisticProxy/PointProcessProxy/PointProcessProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

PoissonProcessProxy.o:	./StatisticProxy/PoissonProcessProxy/PoissonProcessProxy.cpp ./StatisticProxy/PoissonProcessProxy/PoissonProcessProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

CountryCodesProxy.o:	./StatisticProxy/CountryCodesProxy/CountryCodesProxy.cpp ./StatisticProxy/CountryCodesProxy/CountryCodesProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

ActivityLevelProxy.o:	./StatisticProxy/ActivityLevelProxy/ActivityLevelProxy.cpp ./StatisticProxy/ActivityLevelProxy/ActivityLevelProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

Event.o:	./common/Event.cpp ./common/Event.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

EventManager.o:	./EventManager/EventManager.cpp ./EventManager/EventManager.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

DependentEventLogger.o:	./DependentEventLogger/DependentEventLogger.cpp ./DependentEventLogger/DependentEventLogger.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

ArgParser.o:	./ArgParser/ArgParser.cpp ./ArgParser/ArgParser.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

Log.o:	./Log/Log.cpp ./Log/Log.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

SimulatorProfiler.o:	./SimulatorProfiler/SimulatorProfiler.cpp ./SimulatorProfiler/SimulatorProfiler.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

ClusteredGithubUserAgent.o:	./Agent/UserAgent/GithubAgent/ClusteredGithubUserAgent.cpp ./Agent/UserAgent/GithubAgent/ClusteredGithubUserAgent.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

Community.o:	./Simulator/Community.cpp ./Simulator/Community.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

CommunityManager.o:	./Simulator/CommunityManager.cpp ./Simulator/CommunityManager.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

matOps.o:	./common/matOps.cpp ./common/matOps.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

main.o:	./main.cpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

clean:
	rm -rf *.o $(TARGET)
