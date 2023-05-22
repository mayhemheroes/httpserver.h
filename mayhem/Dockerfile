# Build Stage
FROM --platform=linux/amd64 ubuntu:20.04 as builder

## Install build dependencies.
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y cmake clang m4 ragel libc6-dbg

## Add source code to the build stage.
ADD . /httpserver.h
WORKDIR /httpserver.h

## TODO: ADD YOUR BUILD INSTRUCTIONS HERE.
RUN mkdir build
WORKDIR build
RUN CC=clang CXX=clang++ cmake ..
RUN make

# Package Stage
FROM --platform=linux/amd64 ubuntu:20.04

COPY --from=builder /httpserver.h/build/test/unit/fuzz-parser /
