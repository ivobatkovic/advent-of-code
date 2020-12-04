# 2020 Solutions

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
To download the input using [aocd](https://github.com/wimglenn/advent-of-code-data), you need to export the session ID:
```bash
export AOC_SESSION=<session_id>
```