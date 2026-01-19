FROM ubuntu:latest

# Install build-essential package which includes g++
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    software-properties-common \
    gnupg2 \
    && \
    add-apt-repository ppa:ubuntu-toolchain-r/test \
    && \
    apt-get update \
    && \
    apt-get install -y \
    clang-18 \
    libclang-18-dev \
    g++-14 \
    cmake \
    build-essential \
    libzmq3-dev \
    git \
    clang-format \
    pkg-config \
    vim


RUN git clone https://github.com/google/flatbuffers.git /flatbuffers
WORKDIR /flatbuffers
RUN cmake -G "Unix Makefiles" && \
    make && \
    make install


RUN flatc --version

# Copy your C++ source code to the container
WORKDIR /app
# COPY . .

# Build your C++ program
# RUN g++-15 -o main main.cpp 

# Expose a port if your program uses one (optional)
# EXPOSE 8080

# Command to run your program (optional)
# CMD ["./my_program"]

# podman build -t ng .
# podman run --userns=keep-id --user 1000:1021 -v /home/dawid/Coding/NG:/home/hao/Coding/NG:Z,U -it ng
# CLion options: --entrypoint= --rm --security-opt label=disable --userns=keep-id --user 1000:1000 -v /home/dawid/Coding/NG:/home/ubuntu/Coding/NG:U,Z

USER ubuntu
