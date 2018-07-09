import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--simulator_settings", help="path of simulator settings file")
parser.add_argument("--output_file", help="path of output file")
args = parser.parse_args()

# Move to simulator path first.
# Set the start and end of simulation date, in format 2017-07-01
file_simulator_settings = args.simulator_settings

main_model_args = {}
new_user_model_args = {"center": "user-centric"}
new_repo_model_args = {"center": "repo-centric"}

with open(file_simulator_settings, 'r') as file:
      lines = file.readlines();
      model_name = ""
      for l in lines:
            if l[0] == '#':
                  model_name = l[1:-1]
            else:
                  l = l[:-1]
                  key_pair = l.split('=')
                  if model_name == "MainModel":
                        main_model_args[key_pair[0]] = key_pair[1]
                  elif model_name == "NewUserModel":
                        new_user_model_args[key_pair[0]] = key_pair[1]
                  elif model_name == "NewRepoModel":
                        new_repo_model_args[key_pair[0]] = key_pair[1]

# Run the model first.
main_model_cmd = "./src/socialcube --show_profile --show_event" + \
      " -s " + main_model_args['start_date'] + \
      " -e " + main_model_args['end_date'] + \
      " -c " + main_model_args['center'] + \
      " --proxy_config_file " + main_model_args['proxy_config_file'] + \
      " --event_file " + main_model_args['event_file'] + \
      " 2>&1 | tee " + main_model_args['log_file']
print('main_model_cmd: ', main_model_cmd)
os.system(main_model_cmd)

# Run the new user part.
new_user_model_cmd = "./src/socialcube --show_profile --show_event" + \
                 " -s " + new_user_model_args['start_date'] + \
                 " -e " + new_user_model_args['end_date'] + \
                 " -c " + new_user_model_args['center'] + \
                 " --proxy_config_file " + new_user_model_args['proxy_config_file'] + \
                 " --event_file " + new_user_model_args['event_file'] + \
                 " 2>&1 | tee " + new_user_model_args['log_file']
print('new_user_model_cmd: ', new_user_model_cmd)
os.system(new_user_model_cmd)

# Run the new repo part.
new_repo_model_cmd = "./src/socialcube --show_profile --show_event" + \
                     " -s " + new_repo_model_args['start_date'] + \
                     " -e " + new_repo_model_args['end_date'] + \
                     " -c " + new_repo_model_args['center'] + \
                     " --proxy_config_file " + new_repo_model_args['proxy_config_file'] + \
                     " --event_file " + new_repo_model_args['event_file'] + \
                     " 2>&1 | tee " + new_repo_model_args['log_file']
print('new_user_model_cmd: ', new_user_model_cmd)
os.system(new_user_model_cmd)

# Combine the simulation results of three parts.
combined_output_file = args['--output_file']
combined_cmd = "cat " + main_model_args['event_file'] + " " + new_user_model_args['event_file'] + " " + new_repo_model_args['event_file'] + " > " + combined_output_file
print(combined_cmd)
os.system(combined_cmd)