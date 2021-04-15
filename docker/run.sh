#!/bin/bash

echo "Building..."

docker build -t cub3d .

echo "Running..."

docker run -ti --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v $PWD/..:/tmp cub3d 