### Experimenting with SocialCube

In this page you are going to learn how to run c++ version simulator from end to end. This whole pipeline includes:
* Getting training data for analysis.
* Generating statistic files from Analysis Library.
* Feed the statistics files to simulator and generate outputs.
* Use metrics code provided by DARPA to evaluate the results.

#### Getting training data
Due to the large size of the data files, all the raw data is stored in Apollo5 server. Currently the complete data set is stored under
```
user@apollo5$ /home/morningmoni/socialsim/data/Events
```

The folder contains all the github data from Jan 2015 to Aug 2017. The csv data files contain a lot of extra meta data, which hasn't been used in our analysis. Given the large data set, we recommend you start experimenting with smaller data set. Note that these csv files need to be processed and conform to certain format before training.

The data format used by our simulator follows the following format:
```
Timestamp ObjectID UserID EventType
```

Below is a snippet of the data we used:
```
2015-01-01T00:00:00Z bHgMq3HjZU6IAGndgtg-EQ b7WyUGR5fEHmYLYzd8_53A PushEvent
2015-01-01T00:00:00Z 6fLr_XwvouWV5u0IcchljQ _wRNH2Fiw9W0U0KBe-WIGA PushEvent
2015-01-01T00:00:01Z c4Yo3NMeMt2bHdV0QIIMtQ A6-vMkTGPRlzqxpb1S_XAw CreateEvent
2015-01-01T00:00:01Z THqpDiAa7tPv2kydZw1-7w b-supkbTf9P_2vL9xvDA0w PushEvent
2015-01-01T00:00:03Z LxJUSCIrZ7C-zkIT00t87Q Qj6G_ffNl2VJjKu9Nl77sg PushEvent
2015-01-01T00:00:03Z EqeRZrZg-qVcv9t517zhnA Bn3PuCz4rHEik6lpqs-3Yw PushEvent
2015-01-01T00:00:03Z DIM81D1G9hf8oqlLCNS8pA YLMr4IywRM4ELYqybB6hlA PushEvent
2015-01-01T00:00:03Z vkp5GSE6YJx2bIo-fwretQ laakGDaXe2J8xmXV90QC9g PushEvent
2015-01-01T00:00:03Z zKi6eFnRtlEMaUahkFOsZQ Ui4sBkfZnQe3TkhuN0iOHQ PushEvent
2015-01-01T00:00:04Z Fq6xwig_dtUuCfEEynNZCA n8ybPr7LCtiLPc5Mcv_xCA CreateEvent
```

You can find a preprocessed training data file under
```
user@apollo5$ /home/yifan/SimulatorCore/data/ISO-time-event_2015-01-01.txt
user@apollo5$ /home/yifan/SimulatorCore/data/ISO-time-event_2015-01.txt
```

The first file contains preprocessed data for one day, and the second file contains preprocessed data for one month. You can write your own script to process the raw data files and generate input files with the right format.

#### Generating statistics with Analysis Library

Since the performance of Analysis Library is not a bottleneck, Analysis Library is completely written in Python for faster development and data manipulation. Existing Analysis Library is under __SocialSim/SimulatorCore__ repository, __cppversion__ branch. Clone the repo and check out to _cppversion_ branch.

Before you start analyzing, you need to run setup.sh file in the repo root folder. Go to the repo root folder, and type
```bash
user@apollo5$ sh setup.sh
user@apollo5$ source ~/.profile
```

It will setup relavant environment variables $SOCIALSIMPATH used by analysis library.

They you need to copy the training data into the following folder:
```
user@apollo5$ $ cp ${LOCATION_TO_YOUR_DATA}/ISO-time-event_2015-01-01.txt {SOCIALSIMPATH}/data/
```

Let's assume you put ISO-time-event_2015-01-01.txt file in the right directory. Then you would have:
```
user@apollo5$ ls ${SOCIALSIMPATH}/data/
ISO-time-event_2015-01-01.txt
```

The implementation of analysis library can be found under
```
user@apollo5$ ${SOCIALSIMPATH}/src/AnalysisLib
```

The script to run Analysis Library is located under
```
user@apollo5$ ${SOCIALSIMPATH}/src/analyze.py
```

In order to run analysis library, you need to specify which analysis library you want to use within analyze.py:
```python
analysisLib = ClusIndependentAnalysisLib.getInstance()                      
analysisLib.storeStatistics()
```

In the code snippet, it uses _CluIndependentAnalysisLib_. You can change it to existing analysis library, as long as they are available under /src/AnalysisLib folder.

Then you should be able to run analysis library with command:
```bash
user@apollo5$ python analyze.py --dataset ISO-time-event_2015-01-01.txt
```

The argument __--dataset__ specifies which file contains the traininng data. analyze.py will search the file under ${SOCIALSIMPATH}/data. Therefore, the file name should match with the real file name under the data folder.

Then you should get a statistics folder under ${SOCIALSIMPATH}:
```bash
user@apollo5$ cd ${SOCIALSIMPATH}/statistics
user@apollo5$ ls .
cluster_action_rate.json  cluster_type_distribution.json  user_id.json
cluster_id.json           obj_id.json                     user_object_preference.json
cluster_member.json       user_action_rate.json           user_type_distribution.json
```

All the json files under this folder are outputs from analsys library, and will be used by online simulator.

Note that depending on the analysis library you used, you might not get the same statistics files.

#### Online Simulation
Since the performance of Simulator Core does matter, most up-to-date Simulator Core is implemented using c++. The code is under __SocialSim/SocialCube__ repository, __master__ branch. Clone the repo.

Following the same procedure as SimulatorCore, change working directory to the repo root folder, and run setup.sh:
```bash
user@apollo5$ sh setup.sh
user@apollo5$ source ~/.profile
```

It will setup relavant environment variables $SOCIALCUBEPATH used by Simulator Core.

Copy the __statistics__ folder generated by analysis library, and put it under the repo root folder:
```bash
user@apollo5$ cp -r ${SOCIALSIMPATH}/statistics ${SOCIALCUBEPATH}/
user@apollo5$ ls ${SOCIALCUBEPATH}/statistics
cluster_action_rate.json  cluster_type_distribution.json  user_id.json
cluster_id.json           obj_id.json                     user_object_preference.json
cluster_member.json       user_action_rate.json           user_type_distribution.json
```

Then go to the src folder and build the simulator:
```bash
user@apollo5$ cd ${SOCIALCUBEPATH}/src
user@apollo5$ make
```

It will generate an executable called __socialcube__. Run the following command to start simulation:
```
user@apollo5$ ./socialcube --show_profile --show_event -s 2018-02-01T00:00:00Z -e "2018-02-02T00:00:00Z"
```

Here are the explanation of the arguments:
* --show_profile will show you the performance of this round of simulation including the time elapsed, as well as the total number of events generated.
* --show_event will store the outputs in a file. The ouputs will not be stored if this argument is not specified.
* -s 2018-02-01T00:00:00Z specifies the start timestamp of the simulation.
* -e 2018-02-02T00:00:00Z specifies the end timestamp of the simulation.

When in doubt, you can type the following command to check all the available arguments:
```
user@apollo5$ ./socialcube --help
```

Since we want to compare our simulation results with ground truth, we specify --show_event argument. The simulator will store an __events.txt__ file under ${SOCIALCUBEPATH} upon simulation finishes:
```
user@apollo5$ ls ${SOCIALCUBEPATH}
events.txt  Makefile.config  README.md  setup.sh  src  statistics  statistics_golden  test
```

#### Compare with Groundtruth

Since the evaluation code provided by DARPA was proprietary before, we kept the evaluation code close sourced and only stored it in Apollo5 server. The code pertaining to evalution is stored under
```
user@apollo5$ ls /home/yifan/SimulatorCore/src
...
```

There are three files and directories that are related to evalution:
* evalute.py: It specifies the ground truth data and the simulated events.txt file. Those files should be stored under ${SOCiALSIMPATH}/data
* SocialSimEvaluationEngine: This folder contains metrics code provided by DARPA. They are not implemented by us.
* Evaluator: This folder contains our wrapper class around the DARPA metrics code. The EvaluationEngine.py is a thin layer around metrics code. Evaluator.py specifies what questions we want to evaluate on.

Within evaluate.py, we use offlineEvaluate() function. This function is within Evalutor/Evaluator.py. You simply specify the questions you want to evaluate within Evaluator/Evaluator.py. The Evalutor class already has some comments on what methods work.

In order to evaluate, make sure you have ground truth data and generated events file in the right place, then do:
```bash
user@apollo5$ cd ${SOCIALSIMPATH}/src
user@apollo5$ python evaluate.py
```

This will start evaluation. Depending on the size of ground truth and events file, the time for evaluation may vary.

__NOTE__: When doing evaluation, you should make sure the time duration for the ground truth should match the generated events.txt. Otherwise, some metrics might differ a lot. For example, if you simulate from 2017-01-01 to 2017-01-02, you should use a groundtruth that contains data for only one day. If you use groundtruth that contains data for one month or one hour, the expected count of events will surely differ :)

