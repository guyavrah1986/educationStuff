# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Set a label for the image
LABEL description="Ubuntu 22.04 with Redis and Hiredis for C++ development"

# Update the package list and install Redis server, Hiredis, and build tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gcc \
    g++ \
    redis-server \
    libhiredis-dev \
    && rm -rf /var/lib/apt/lists/*


# Copy a custom Redis config file that runs Redis in the foreground
COPY redis.conf /etc/redis/redis.conf

# Start the Redis server in the background to enable interaction
RUN redis-server --daemonize yes

# Verify installations
RUN redis-server --version && ldconfig -p | grep hiredis

# Start Redis using the custom config file
# CMD redis-server /etc/redis/redis.conf

# Set the default command to open a shell for development
CMD ["/bin/bash"]
