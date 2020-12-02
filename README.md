# Solutions to advent of code
Each folder here contains solutions to different years of advent of code.

The solutions have only been tested on MacOS/Linux.

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

## Dependencies
To install dependencies run
```bash
virtualenv venv            # (optional)
source venv/bin/activate   # (optional)
pip install --upgrade pip
pip install -r requirements.txt
```

## License
[MIT](https://choosealicense.com/licenses/mit/)