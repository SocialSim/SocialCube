import os
import datetime
from termcolor import colored
import json

PROXY_FILE_DIR = "/data/final_challenge_stats/"
PROXY_FILE_CONFIG_DIR = "./proxy_files_final_challenge/"
RESULTS_DIR = "./results_final_challenge/"
LOG_DIR = "./log/"

# Change date range here:
GITHUB_START_DATE = "2017-12-01T00:00:00Z"
GITHUB_END_DATE = "2017-12-14T00:00:00Z"

REDDIT_START_DATE = "2017-12-15T00:00:00Z"
REDDIT_END_DATE = "2017-12-31T00:00:00Z"

TWITTER_START_DATE = "2017-01-01T00:00:00Z"
TWITTER_END_DATE = "2017-01-15T00:00:00Z"

# Knobs
RUN_SCENARIO_1 = True
RUN_SCENARIO_2 = False

RUN_GITHUB = False
RUN_REDDIT = True
RUN_TWITTER = False

RUN_CRYPTO = True
RUN_CVE = True
RUN_CYBER = True

scenarios = next(os.walk(PROXY_FILE_DIR))[1]

def generateCommand(proxy_config_file, scenario, platform, domain):
    model_name = proxy_config_file[proxy_config_file.find("_"):proxy_config_file.rfind(".")]
    start_time = "" 
    end_time = ""
    if platform == "github":
        start_time = GITHUB_START_DATE
        end_time = GITHUB_END_DATE
    elif platform == "reddit":
        start_time = REDDIT_START_DATE
        end_time = REDDIT_END_DATE
    elif platform == "twitter":
        start_time = TWITTER_START_DATE
        end_time = TWITTER_END_DATE

    command = "./src/socialcube --show_profile --show_event -s " + start_time + " -e " + end_time + " --proxy_config_file " + PROXY_FILE_CONFIG_DIR + proxy_config_file + " --event_file " + RESULTS_DIR + "events" + model_name + ".json --center user-centric --platform " + platform + " --domain " + domain + " --scenario " + scenario.split("_")[-1] + " 2>&1 | tee " + LOG_DIR + "log" + model_name + ".txt"
    return command

# Remove all result files if confirmed
if len(os.listdir(RESULTS_DIR)) > 0:
    print(colored(RESULTS_DIR + " is not empty, remove all? (y/n)", "cyan"))
    answer = raw_input()
    if answer == "y":
        print(colored("Are you sure? (y/n)", "cyan"))
        answer = raw_input()
        if answer == "y":
            os.system("rm " + RESULTS_DIR + "*")

# All the finished simulation result 
# [event_file_name, scenario, platform, domain]
result_files = []

# For each scenario
for s in scenarios:
    if s == "scenario_1" and not RUN_SCENARIO_1:
        continue
    elif s == "scenario_2" and not RUN_SCENARIO_2:
        continue

    scenario_path = PROXY_FILE_DIR + s
    platforms = next(os.walk(scenario_path))[1]
    
    # For each platform
    for p in platforms:
        if p == "github" and not RUN_GITHUB:
            continue
        elif p == "reddit" and not RUN_REDDIT:
            continue
        elif p == "twitter" and not RUN_TWITTER:
            continue

        platform_path = scenario_path + "/" + p
        domains = next(os.walk(platform_path))[1]

        # For each domain
        for d in domains:
            if d == "crypto" and not RUN_CRYPTO:
                continue
            elif d == "cve" and not RUN_CVE:
                continue
            elif d == "cyber" and not RUN_CYBER:
                continue

            domain_path = platform_path + "/" + d
            items = os.listdir(domain_path)
            miscellaneousProxyFilePath = ""
            
            # miscellaneousProxyFile is only for Reddit and Twitter
            if d != "github":
                miscellaneousProxyFilePath = domain_path + "/miscellaneousProxyFile.txt"

            models = next(os.walk(domain_path))[1]
            for m in models:
                model_path = domain_path + "/" + m
                predictionModel = m[:m.rfind("_")]
                simulatorBehaviorModel = m.split("_")[-1]
                
                now = datetime.datetime.now().strftime("%Y-%m-%d_%H:%M:%S")
                proxy_config_file = "ProxyFilePaths_" + predictionModel + "_" + simulatorBehaviorModel + "_" + s + "_" + p + "_" + d + "_" + now + ".config"  
                # Generate proxy config files
                if simulatorBehaviorModel.lower() == "simpledaily":
                    with open(PROXY_FILE_CONFIG_DIR + proxy_config_file, "w") as file:
                        file.write("#DailySimpleBehavior\n")
                        file.write("userIDProxyFile=" + model_path + "/userIDProxyFile.txt\n")
                        file.write("dailyActivityLevelProxyFile=" + model_path + "/dailyActivityLevelProxyFile.txt\n")
                        file.write("objectPreferenceProxyFile=" + model_path + "/objectPreferenceProxyFile.txt\n")
                        file.write("typeDistributionProxyFile=" + model_path + "/typeDistributionProxyFile.txt\n")
                        # No miscellaneousProxyFile!
                
                elif simulatorBehaviorModel.lower() == "cascade":
                    with open(PROXY_FILE_CONFIG_DIR + proxy_config_file, "w") as file:
                        file.write("#CascadeModel\n")
                        file.write("userIDProxyFile=" + model_path + "/userIDProxyFile.txt\n")
                        file.write("postScaleProxyFile=" + model_path + "/postScaleProxyFile.txt\n")
                        file.write("commentProbabilityProxyFile=" + model_path + "/commentProbabilityProxyFile.txt\n")
                        file.write("postLifespanDistributionProxyFile=" + model_path + "/postLifespanDistributionProxyFile.txt\n")
                        file.write("communityDistributionProxyFile=" + model_path + "/communityDistributionProxyFile.txt\n")
                        # Add miscellaneousProxyFile
                        file.write("miscellaneousProxyFile=" + miscellaneousProxyFilePath)
                elif simulatorBehaviorModel.lower() == "embedding":
                    with open(PROXY_FILE_CONFIG_DIR + proxy_config_file, "w") as file:
                        file.write("#EmbeddingCascadeModel\n")
                        file.write("userIDProxyFile=" + model_path + "/userIDProxyFile.txt\n")
                        file.write("commentProbabilityProxyFile=" + model_path + "/commentProbabilityProxyFile.txt\n")
                        file.write("postScaleProxyFile=" + model_path + "/postScaleProxyFile.txt\n")
                        file.write("postLifespanDistributionProxyFile=" + model_path + "/postLifespanDistributionProxyFile.txt\n")
                        file.write("scoreMatrixProxyFile=" + model_path + "/scoreMatrixProxyFile.txt\n")
                        file.write("inactiveUserProxyFile=" + model_path + "/inactiveUserProxyFile.txt\n")
                        file.write("communityDistributionProxyFile=" + model_path + "/communityDistributionProxyFile.txt\n")
                        # Add miscellaneousProxyFile
                        file.write("miscellaneousProxyFile=" + miscellaneousProxyFilePath)

                # Generate the corresponding terminal command
                command = generateCommand(proxy_config_file, s, p, d) 
                print(command)
                os.system(command)

                result_name = "events" + proxy_config_file[proxy_config_file.find("_"):proxy_config_file.rfind(".")] + ".json"
                result_files.append((result_name, s, p, d))

# Test out the correctness of the simulation results
generated_files = [x for x in os.listdir(RESULTS_DIR) if x.endswith(".json")]

for t in result_files:
    filename = t[0]
    scenario = t[1].split("_")[-1]
    platform = t[2]
    domain = t[3]
    
    is_pass = True
    
    # 1. File Size Test
    # If no such result file produced, fail
    if filename not in generated_files:
        is_pass = False
        print(filename + colored(" File Not Exist, FAIL", "red")) 
    else:
        statinfo = os.stat(RESULTS_DIR + filename)
        # If the size of this result file is zero, fail
        if statinfo.st_size == 0:
            is_pass = False
            print(filename + colored(" File Is Empty, FAIL", "red")) 

    # 2. File Content Test
    try:
        with open(RESULTS_DIR + filename, "r") as file:
            data = json.load(file)
            if data["scenario"] != scenario:
                is_pass = False
                print(filename + colored(" Wrong Scenario, FAIL", "red")) 
            if data["platform"] != platform:
                is_pass = False
                print(filename + colored(" Wrong Platform, FAIL", "red")) 
            if data["domain"] != domain:
                is_pass = False
                print(filename + colored(" Wrong Domain, FAIL", "red")) 
            if len(data["data"]) == 0:
                is_pass = False
                print(filename + colored(" No Event Generated, FAIL", "red")) 
            
            if platform == "github" and "actionSubType" not in data["data"][0]:
                is_pass = False
                print(filename + colored(" Github Output Format Wrong, FAIL", "red")) 
            if platform == "reddit" and "communityID" not in data["data"][0]:
                is_pass = False
                print(filename + colored(" Reddit Output Format Wrong, FAIL", "red")) 
            if platform == "twitter" and not("rootID" in data["data"][0] and "communityID" not in data["data"][0]):
                is_pass = False
                print(filename + colored(" Twitter Output Format Wrong, FAIL", "red")) 
    except Exception as e: 
        is_pass = False
        print(filename + colored(" File Is Not Valid JSON, FAIL", "red")) 
        
    if is_pass:
        print(filename + colored(" PASS", "green"))


