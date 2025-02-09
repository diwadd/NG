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
    pkg-config


RUN git clone https://github.com/google/flatbuffers.git /flatbuffers
WORKDIR /flatbuffers
RUN cmake -G "Unix Makefiles" && \
    make && \
    make install


RUN flatc --version

# Replace dawid with custom user
RUN useradd -m hao
USER hao

# Copy your C++ source code to the container
WORKDIR /app
# COPY . .

# Build your C++ program
# RUN g++-15 -o main main.cpp 

# Expose a port if your program uses one (optional)
# EXPOSE 8080

# Command to run your program (optional)
# CMD ["./my_program"]

# sudo docker build -t ng_main .
# docker run -u 1000:1000 -v /home/user/Coding/NG:/home/dawid -it ng_main
