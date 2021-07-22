# Downlaod base image ubuntu 18.04
from ubuntu:18.04

LABEL description="This is a custom image for advent of code"

COPY ./requirements.txt ./requirements.txt

RUN apt-get update && \
    apt-get -y install \
    g++ \
    make \
    curl \
    git \
    build-essential \
    python3 \
    python3-pip \
    libncurses5-dev \
    libboost-dev \
    libboost-regex-dev \
    clang-format &&\
    
    # Install Bazel
    apt-get -y install openjdk-8-jdk && \
    echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list && \
    curl https://bazel.build/bazel-release.pub.gpg | apt-key add - && \
    apt-get update && \
    apt-get -y install bazel && \
    
    # Python reqs
    pip3 install --upgrade pip && pip3 install -r requirements.txt && \
    pip3 install cmake --upgrade
RUN echo "alias python='python3'" >> ~/.bashrc

WORKDIR ~/
