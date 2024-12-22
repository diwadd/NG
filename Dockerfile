FROM ubuntu:latest

# Install build-essential package which includes g++
RUN apt-get update && apt-get install -y build-essential
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    software-properties-common \
    gnupg2 \
    && \
    # Add the Ubuntu Toolchain PPA (for older g++ versions)
    add-apt-repository ppa:ubuntu-toolchain-r/test \
    && \
    apt-get update \
    && \
    # Install the desired g++ version (replace with your target version)
    apt-get install -y g++-14
    # Example: g++-9 for GCC 9, g++-10 for GCC 10, etc.

# Copy your C++ source code to the container
WORKDIR /app
COPY . .

# Build your C++ program
# RUN g++-15 -o main main.cpp 

# Expose a port if your program uses one (optional)
# EXPOSE 8080

# Command to run your program (optional)
# CMD ["./my_program"]


