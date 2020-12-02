# 2019 Solutions

The solutions for [advent of code 2019](https://adventofcode.com/2019/) are structured in different folders called day1, day2, ..., day25, which have the following structure:
```bash
.
├──day1
|   ├── cpp            # Containing c++ source files
│   |    ├── src
│   |    ├── include
│   |    └── tests
|   ├── python         # Contains python source files
|   ├── data           # Contains input data
|   └── CMakeLists.txt # Build configuraiton
.
.
├──day25
|   ├── cpp         
│   |    ├── src
│   |    └── include
│   |    └── tests
|   ├── python      
|   ├── data        
|   └── CMakeLists.txt
├──utils               # Input/output C++ library
|   ├── src            
|   ├── include
|   └── CMakeLists.txt # python functions
├──cmake               # cmake settings
└──CMakeLists.txt      # cmake settings for the project
```

## Installation (Linux/MacOS)
### C++
To configure the build for c++ run the following commands (uses c++14):
```bash
mkdir build        # create a build folder
cd build           # move into the build folder
cmake ..           # configure build files
```
To compile the code for all days, including the test cases, run:
```bash
make all           # compiles all days
make build_tests   # compiles all tests
make test          # runs all tests
````
To build everything and run the tests in parallel
```bash
make all build_tests test -j$(nproc)
```
To compile dayX (where X=[1,...,25]), run:
```bash
make dayX         # replace X with the desired day
make dayX_test    # compiles the test suite for dayX
```
Then to run the built program simply type:
```bash
./dayX/dayX       # to run the program solving dayX
./dayX/dayX_test  # to run the tests for dayX
```
### Python
To run the python scripts, move to the dayXX/python directory:
```bash
cd dayXX/python   # Move to folder dayXX/python
python dayXX.py   # Run python script
```