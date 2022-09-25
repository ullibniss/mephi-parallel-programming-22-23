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
  gcc -fopenmp -o cmake-build-debug/lab3 lab3_parallel.c
else
  gcc -fopenmp -o cmake-build-debug/lab3 lab3.c
fi

if [[ $2 == "--all" ]]
then
  for (( i=1; i <= 12; i++ ))
  do
    echo "For $i threads:"
    ./cmake-build-debug/lab3 $i
  done
else
  ./cmake-build-debug/lab3 $2
fi


