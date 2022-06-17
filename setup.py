from setuptools import setup, find_packages

# List of requirements
with open("requirements.txt","r") as f:
    requirements = f.read().splitlines()
print(requirements)

# Package configuration
setup(
    name="adventofcode",
    version="1.0.0",
    description="Solutions to adventofcode.com",
    packages=find_packages(), 
    install_requires=requirements
)
