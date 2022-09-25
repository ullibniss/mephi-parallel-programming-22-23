#!/bin/bash

mkdir cmake-build-debug 2> /dev/null
if [[ $1 == "-10" ]]
then
  if ! ls -l | grep arrays_dir > /dev/null
  then
    mkdir arrays_dir
    echo "Created dir 'arrays_dir'"
    echo "Generating arrays:"
    /bin/python3 array_gen.py
  fi
  gcc -fopenmp -o cmake-build-debug/lab2 lab2_parallel.c
else
  gcc -fopenmp -o cmake-build-debug/lab2 lab2.c
fi

./cmake-build-debug/lab2


