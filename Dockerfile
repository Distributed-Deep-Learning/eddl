FROM ubuntu:18.04

# Update software repository
RUN apt-get update

# Install dependencies
RUN apt-get install -y build-essential ca-certificates apt-utils # Essentials
RUN apt-get install -y cmake wget graphviz zlib1g-dev # Utilities
RUN apt-get install -y libblas-dev liblapack-dev  # BLAS + LAPACK
RUN apt-get install -y libeigen3-dev  # Eigen3
RUN apt-get install -y libprotobuf-dev protobuf-compiler protobuf-c-compiler  # Protobuf
RUN apt-get install -y libgtest-dev  # Google tests

# Set working directory
ENV EDDL_ROOT /eddl
WORKDIR $EDDL_ROOT

# Copy repo
COPY . .

# All together
RUN mkdir build && \
    cd build && \
    cmake -D BUILD_SHARED_LIB=ON -D BUILD_EXAMPLES=ON .. && \
    make -j$(grep -c ^processor /proc/cpuinfo) && \
    make install


# Make build folder
#RUN mkdir build

# Set working directory
#WORKDIR $EDDL_ROOT/build

## Build EDDL
#RUN cmake .. -DBUILD_TARGET=CPU  # {CPU, GPU, FPGA}
#RUN make -j$(nproc)