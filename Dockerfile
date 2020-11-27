# Downlaod base image ubuntu 18.04
from ubuntu:18.04

LABEL description="This is a custom image for advent of code"

RUN apt-get update && \
    apt-get install -y cmake g++ make git build-essential python3 python3-pip \
    libncurses5-dev libboost-dev && \
    pip3 install pytest
RUN echo "alias python='python3'" >> ~/.bashrc


WORKDIR ~/
