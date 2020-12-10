# Advent of code 2020: Solutions
<p align="center">
    <img src="https://img.shields.io/badge/Developed%20and%20tested%20for-macOS%2011.0%7C%20Ubuntu%2018.04-informational"/>
    <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-informational"/></a>
</p>
<p align="center">
    <img src="https://github.com/ivobatkovic/advent-of-code/workflows/Python/badge.svg"/>
    <img src="https://img.shields.io/badge/versions-3.6%20%7C%203.9-informational"/>
    <a href="https://github.com/psf/black">
    <img src="https://img.shields.io/badge/code%20style-black-000000.svg"/></a>    
    <img src="https://github.com/ivobatkovic/advent-of-code/workflows/C++/badge.svg"/>
    <img src="https://img.shields.io/badge/standard-c++14-informational"/>
    <img src="https://img.shields.io/badge/clang%20format-google-000000.svg"/>
</p>


The solutions for [advent of code 2020](https://adventofcode.com/2020) are structured in different folders called day1, day2, ..., day25, which have the following structure:
```bash
.
├──day1
|   ├── python         # Contains python source files
|   └── data           # Contains input 
.
├──day25
|   ├── python      
|   └── data   
├──templates               
|   ├── python         # Template python project     
|   └── data           # Template data
├──bootstrap.py        # Script to set up new day
├──requirements.txt    # Python dependencies
└──CMakeLists.txt      # cmake settings for the project
```

## Installation (Linux/MacOS)

### Python
To run the python scripts:
```bash
python dayX/python/dayX.py # To run dayX
pytest dayX/python/dayX.py # To run tests for dayX
```
### Bootstraping
To generate the project structure for a given day, run the following:
```bash
python bootstrap.py -d <dayNumber>
```

### Download input
To download the input using [aocd](https://github.com/wimglenn/advent-of-code-data), you need to export the [session ID](https://github.com/wimglenn/advent-of-code-wim/issues/1):
```bash
export AOC_SESSION=<session_id>
```
