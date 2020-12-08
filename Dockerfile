# Downlaod base image ubuntu 18.04
from ubuntu:18.04

LABEL description="This is a custom image for advent of code"

COPY ./requirements.txt ./requirements.txt

RUN apt-get update && \
    apt-get install -y g++ make git build-essential python3 python3-pip libncurses5-dev libboost-dev clang-format &&\
    pip3 install --upgrade pip && pip3 install -r requirements.txt && \
    pip3 install cmake --upgrade
RUN echo "alias python='python3'" >> ~/.bashrc

WORKDIR ~/
