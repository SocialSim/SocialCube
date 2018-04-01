BASEDIR := $(SOCIALCUBEPATH)
SRCDIR := $(BASEDIR)/src

TARGET := socialcube

CXX := g++
CXX_FLAGS := -O3 -g -DDEBUG
#CXX_FLAGS := -g3 -pthread
CXX_FLAGS := $(CXX_FLAGS) -Wall -W -Wmissing-declarations -Wredundant-decls -Wdisabled-optimization
CXX_FLAGS := $(CXX_FLAGS) -Wpointer-arith -Wsign-compare -Wendif-labels
CXX_FLAGS := $(CXX_FLAGS) -std=c++11
CXX_FLAGS := $(CXX_FLAGS) -I $(SRCDIR)

OBJS := Simulator.o
OBJS := $(OBJS) CacheAwareSimulator.o
OBJS := $(OBJS) SimpleGithubUserAgent.o 
OBJS := $(OBJS) SimpleGithubObjectAgent.o 
OBJS := $(OBJS) BehaviorModel.o
OBJS := $(OBJS) EventHourlyActionRate.o
OBJS := $(OBJS) HourlyActionRate.o
OBJS := $(OBJS) ObjectPreference.o
OBJS := $(OBJS) TypeDistribution.o
OBJS := $(OBJS) StatisticProxy.o
OBJS := $(OBJS) HourlyActionRateProxy.o
OBJS := $(OBJS) ObjectPreferenceProxy.o
OBJS := $(OBJS) TypeDistributionProxy.o
OBJS := $(OBJS) ObjectIDProxy.o
OBJS := $(OBJS) UserIDProxy.o
OBJS := $(OBJS) Event.o
OBJS := $(OBJS) DependentEventLogger.o
OBJS := $(OBJS) ArgParser.o
OBJS := $(OBJS) Log.o
OBJS := $(OBJS) SimulatorProfiler.o
OBJS := $(OBJS) main.o

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CXX) $(CXX_FLAGS) $^ -o $@

Simulator.o:	./Simulator/Simulator.cpp ./Simulator/Simulator.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

CacheAwareSimulator.o:	./Simulator/CacheAwareSimulator.cpp ./Simulator/CacheAwareSimulator.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

SimpleGithubUserAgent.o:	./Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.cpp ./Agent/UserAgent/GithubAgent/SimpleGithubUserAgent.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

SimpleGithubObjectAgent.o:	./Agent/ObjectAgent/GithubAgent/SimpleGithubObjectAgent.cpp ./Agent/ObjectAgent/GithubAgent/SimpleGithubObjectAgent.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

BehaviorModel.o:	./BehaviorModel/SimpleBehaviorModel.cpp ./BehaviorModel/SimpleBehaviorModel.hpp
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

StatisticProxy.o:	./StatisticProxy/StatisticProxy.cpp ./StatisticProxy/StatisticProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

HourlyActionRateProxy.o:	./StatisticProxy/HourlyActionRateProxy/HourlyActionRateProxy.cpp ./StatisticProxy/HourlyActionRateProxy/HourlyActionRateProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

ObjectPreferenceProxy.o:	./StatisticProxy/ObjectPreferenceProxy/ObjectPreferenceProxy.cpp ./StatisticProxy/ObjectPreferenceProxy/ObjectPreferenceProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

TypeDistributionProxy.o:	./StatisticProxy/TypeDistributionProxy/TypeDistributionProxy.cpp ./StatisticProxy/TypeDistributionProxy/TypeDistributionProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

ObjectIDProxy.o:	./StatisticProxy/ObjectIDProxy/ObjectIDProxy.cpp ./StatisticProxy/ObjectIDProxy/ObjectIDProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

UserIDProxy.o:	./StatisticProxy/UserIDProxy/UserIDProxy.cpp ./StatisticProxy/UserIDProxy/UserIDProxy.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

Event.o:	./common/Event.cpp ./common/Event.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

DependentEventLogger.o:	./DependentEventLogger/DependentEventLogger.cpp ./DependentEventLogger/DependentEventLogger.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

ArgParser.o:	./ArgParser/ArgParser.cpp ./ArgParser/ArgParser.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

Log.o:	./Log/Log.cpp ./Log/Log.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

SimulatorProfiler.o:	./Simulator/SimulatorProfiler.cpp ./Simulator/SimulatorProfiler.hpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

main.o:	./main.cpp
	$(CXX) -c $(CXX_FLAGS) $< -o $@

clean:
	rm -rf *.o $(TARGET)
