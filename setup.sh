#!/usr/bin/env bash

# setup environment variable
echo "export SOCIALCUBEPATH=$(pwd)" >> ~/.profile
echo "export CPATH=${CPATH}:$(pwd)/src" >> ~/.profile

