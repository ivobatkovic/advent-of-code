# Solutions to advent of code
<p align="center">
    <img src="https://img.shields.io/badge/Developed%20and%20tested%20for-macOS%2011.0%7C%20Ubuntu%2018.04-informational"/>
    <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-informational"/></a>
</p>
<p align="center">
    <img src="https://github.com/ivobatkovic/advent-of-code/workflows/2019:Python/badge.svg"/>
    <img src="https://img.shields.io/badge/versions-3.6%20%7C%203.9-informational"/>
    <a href="https://github.com/psf/black">
    <img src="https://img.shields.io/badge/code%20style-black-000000.svg"/></a>    
    <img src="https://github.com/ivobatkovic/advent-of-code/workflows/2019:C++/badge.svg"/>
    <img src="https://img.shields.io/badge/standard-c++14-informational"/>
    <img src="https://img.shields.io/badge/clang%20format-google-000000.svg"/>
</p>
<p align="center">
    <img src="https://github.com/ivobatkovic/advent-of-code/workflows/2020:Python/badge.svg"/>
    <img src="https://img.shields.io/badge/versions-3.6%20%7C%203.9-informational"/>
    <a href="https://github.com/psf/black">
    <img src="https://img.shields.io/badge/code%20style-black-000000.svg"/></a>    
    <img src="https://github.com/ivobatkovic/advent-of-code/workflows/2020:C++/badge.svg"/>
    <img src="https://img.shields.io/badge/standard-c++17-informational"/>
    <img src="https://img.shields.io/badge/clang%20format-google-000000.svg"/>
</p>

Each folder contains solutions to different years of [advent of code](https://adventofcode.com), which has the following structure
```bash
year                   # Advent of code year
├──day1
│   ├── cpp            # Containing c++ source files
│   │    ├── src
│   │    └── inlclude
│   ├── python         # Contains python source files
│   ├── data           # Contains input data
│   └── CMakeLists.txt # Build configuraiton
.
.
├──day25
│   ├── cpp         
│   │    ├── src
│   │    └── include
│   ├── python      
│   ├── data        
│   └── CMakeLists.txt
└──CMakeLists.txt      # cmake settings for the project
```
## Python
### Dependencies (Ubuntu/MacOS)
To install the needed dependencies, run:
```bash
virtualenv venv            # (optional)
source venv/bin/activate   # (optional)
pip install --upgrade pip
pip install -r requirements.txt
```
### Installation (Ubuntu/MacOS)
To run the solution for year X day Y, run:
```bash
python X/dayY/python/dayY.py 
# E.g., python 2020/day1/python/day1.py
```



## C++
### Dependencies
#### Ubuntu
```bash
apt-get update
apt-get install -y libboost-dev # clang-format optional)
``` 
#### MacOS
```bash
brew install boost clang-format # clang-format optional)
```
### Installation (Ubuntu/MacOS)
To build the solution of year X day Y, run:
```bash
cd X                    # Move into directory of year X
mkdir build && cd build # Make a build directory
cmake ..                # Setup the cmake project
make dayY               # Build dayX
./dayY/day/             # Run dayY
```
To build all days, all tests, and running all tests in parallel, run:
```bash
make all build_tests test -j$(nproc)
```

## Using Docker to run the examples
You can build a [Docker](https://www.docker.com/) image with the provided ``Dockerfile``, which will make sure that all necessary libraries, dependencies, etc, are installed.

### Building the docker file and running
The following command builds a Docker image `adventofcode`
```bash
docker build -f Dockerfile -t adventofcode .
```

### Run the docker file and mount the advent of code repository
You can run the built docker image with the following command:
```bash
docker run -v $(pwd):/adventofcode -ti adventofcode bash
```
This will open up a bash shell for the docker image, and mount the current folder to the running container.

### Bootstraping
To generate a project structure for a given year and day, run the following:
```bash
python bootstrap.py -y <year> -d <day> 
```

#### Download input 
You can also download the input during the bootstrapping using [aocd](https://github.com/wimglenn/advent-of-code-data). For this you need to export the [session ID](https://github.com/wimglenn/advent-of-code-wim/issues/1):
```bash
export AOC_SESSION=<session_id>
```
and run
```bash
python bootstrap.py -y <year> -d <day> -input 1
```
