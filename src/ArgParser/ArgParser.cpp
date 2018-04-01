#include "ArgParser.hpp"

using namespace std;

ArgParser::ArgParser(int argc, const char* argv[]) {

    initSocialCubeArgFromCLI(argc, argv);

    if(readFromFile)
        initSocialCubeArgFromFile();

}

void ArgParser::initSocialCubeArgFromCLI(int argc, const char* argv[]) {
    try { 
        cxxopts::Options options(argv[0], "Optional Argument for SocialCube");
        options
          .positional_help("[optional args]")
          .show_positional_help();

        options.add_options()
          ("s, start_time", "Simulation Start Time", cxxopts::value<uint64_t>())
          ("e, end_time", "Simulation End Time", cxxopts::value<uint64_t>())
          ("u, unit_time", "Simulation Unit Time", cxxopts::value<uint64_t>())
          ("c, current_time", "Simulation Current Time", cxxopts::value<uint64_t>())
          ("init_file", "Read Configuration from File");

        try 
        { 
            auto result = options.parse(argc, argv);

            if (result.count("help")) { 
                std::cout << options.help({""}) << std::endl;
                exit(0);
            } 
            if (result.count("start_time")) { 
                simulator_startTime = result["start_time"].as<uint64_t>();
            } else {
                simulator_startTime = 0;
            }

            if (result.count("end_time")) { 
                simulator_endTime = result["end_time"].as<uint64_t>();
            } else {
                simulator_endTime = 24;
            }

            if (result.count("unit_time")) { 
                simulator_unitTime = result["unit_time"].as<uint64_t>();
            } else {
                simulator_unitTime = 1;
            }

            if (result.count("current_time")) { 
                simulator_currentTime = result["current_time"].as<uint64_t>();
            } else {
                simulator_currentTime = 0;
            }


            if (result.count("init_file")) { 
                readFromFile = true;
            } else {
                readFromFile = false;
            }
        } catch (const cxxopts::OptionException& e)
        {
            std::cout << "error parsing options: " << e.what() << std::endl;
            exit(1);
        }

    } 
    catch (std::exception& e) 
    { 
        std::cerr << "Unhandled Exception reached the top of main: " 
                  << e.what() << ", application will now exit" << std::endl; 
        exit(2);
    } 

    return; 
}

void ArgParser::initSocialCubeArgFromFile() {
    return;
}

uint64_t ArgParser::getSimulationStartTime() {
    return simulator_startTime;
}

uint64_t ArgParser::getSimulationEndTime() {
    return simulator_endTime;
}

uint64_t ArgParser::getSimulationUnitTime() {
    return simulator_unitTime;
}

uint64_t ArgParser::getSimulationCurrentTime() {
    return simulator_currentTime;
}
