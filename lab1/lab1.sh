#!/bin/bash

mkdir cmake-build-debug 2> /dev/null
if [[ $1 == "-10" ]]
then
  if ! ls -l | grep arrays_dir > /dev/null
  then
    mkdir arrays_dir
    /bin/python3 array_gen.py
  fi
  gcc -fopenmp -o cmake-build-debug/lab1 lab1_x10.c
else
  gcc -fopenmp -o cmake-build-debug/lab1 lab1.c
fi

./cmake-build-debug/lab1
