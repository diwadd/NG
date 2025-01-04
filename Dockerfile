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
    libzmq3-dev

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
# sudo docker run -v /home/dawid/Coding/NG:/app -it ng_main
