# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Set environment variables to avoid prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gcc \
    g++ \
    git \
    libstdc++-12-dev \
    ninja-build \
    python3 \
    python3-pip \
    python3-yaml \
    libaio-dev \
    libboost-all-dev \
    libfmt-dev \
    libcrypto++-dev \
    xfslibs-dev \
    ragel \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Clone and build Seastar
RUN git clone --recursive https://github.com/scylladb/seastar.git /opt/seastar && \
    cd /opt/seastar && \
    ./configure.py --compiler=g++ --cflags="-O2" --cxxflags="-std=gnu++20" --optimize && \
    ninja -C build/release

# Set environment variables for Seastar
ENV SEASTAR_DIR=/opt/seastar
ENV PATH=$PATH:/opt/seastar/build/release

# Create a workspace directory for developing your application
WORKDIR /workspace

# Expose a default working port (e.g., for Seastar apps)
EXPOSE 10000

# Command to keep the container running or enable immediate development
CMD ["/bin/bash"]
