# Solutions to advent of code
<p align="center">
    <img src="https://img.shields.io/badge/Developed%20and%20tested%20Ubuntu%2020.04-informational"/>
    <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-informational"/></a>
</p>
<p align="center">
    <img src="https://github.com/ivobatkovic/advent-of-code/workflows/Python/badge.svg"/>
    <img src="https://img.shields.io/badge/versions-3.8-informational"/>
    <a href="https://github.com/psf/black">
    <img src="https://img.shields.io/badge/code%20style-black-000000.svg"/></a>    
    <img src="https://github.com/ivobatkovic/advent-of-code/workflows/C++/badge.svg"/>
    <img src="https://img.shields.io/badge/standard-c++17-informational"/>
    <img src="https://img.shields.io/badge/clang%20format-google-000000.svg"/>
</p>

Each folder contains solutions to different years of [advent of code](https://adventofcode.com), which has the following structure
```bash
year                   # Advent of code year
├── day1
│   ├── cpp            # C++ solution
│   │    ├── main.cpp
│   │    ├── solutions.cpp
│   │    ├── solutions.hpp
│   │    └── test.cpp
│   ├── data           # Input data
│   ├── __init__.py    # Python directory module
│   ├── BUILD.bazel    # Bazel configuration
│   ├── CMakeLists.txt # Cmake configuration
│   └── solutions.py   # Python solution
.
.
├── day25
│   ├── cpp            
│   │    ├── main.cpp
│   │    ├── solutions.cpp
│   │    ├── solutions.hpp
│   │    └── test.cpp
│   ├── data           
│   ├── __init__.py    
│   ├── BUILD.bazel    
│   ├── CMakeLists.txt 
│   └── solutions.py   
├── __init__.py
└── CMakeLists.txt 
```
## Python
### Dependencies (Ubuntu)
To install the needed dependencies, run:
```bash
pip install --upgrade pip
pip install -r requirements.txt
```
### Installation (Ubuntu/MacOS)
To run the solution for year X day Y, run:
```bash
python yearX/dayY/python/solutions.py 
# E.g., python year2020/day1/python/solutions.py
```

To run the python tests:
```bash
python -m pytest yearX/dayY/solutions.py # Run year X day Y tests
python -m pytest year*/**/solutions.py   # To run all test
```



## C++
### Dependencies
#### Ubuntu
```bash
apt-get update
apt-get install -y libncurses5-dev libboost-dev libboost-regex-dev
apt-get install -y clang-format # optional - used for formatting
``` 
### Installation (Ubuntu)
**Cmake**

To build the solution of year X day Y, run:
```bash
mkdir build && cd build   # Make a build directory
cmake ..                  # Setup the cmake project
make yearX-dayY-cpp-main  # Build year X day Y
./yearX/dayY/cpp-main      # Run year X day Y
```
To build all tests, and running them in parallel, run:
```bash
make build_tests test -j$(nproc)
```

**Bazel** 

To build the solution of day X year Y, run:
```bash
bazel build //yearX/dayY/...     # Build all targets of year X day Y
./bazel-bin/yearX/dayY/main-cpp  # Run year X day Y
```
To build and run all tests, run:
```bash
bazel test //...
```

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
python bootstrap.py -y <year> -d <day> -input -i
```
