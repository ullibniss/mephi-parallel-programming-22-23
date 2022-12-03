#!/bin/bash

info() {
  echo "[INFO] $1"
}

warn() {
  echo "[WARN] $1"
}

crit() {
  echo "[CRIT] $1"
}

echo "RUNNING $0"
echo "----------------------------------------"
ARRAYS_GEN_DIR=arrays_dir
info "CHECK IF ARRAYS CREATED"
if ! ls -l | grep $ARRAYS_GEN_DIR > /dev/null
then
  warn "ARRAYS NOT FOUND"
  info "CREATE NEW ARRAYS IN DIRECTORY $ARRAYS_GEN_DIR"
  mkdir $ARRAYS_GEN_DIR
  /bin/python3 array_gen.py
  info "CREATED NEW ARRAYS SUCCESFULLY"
else
  info "ARRAYS SEEM CREATED"
fi

ARG=$1
TREADS=${ARG:-4}
MPI_DEBUG_DIR=mpi_debug
MPI_CFILE_NAME=lab5_x10.cpp
MPI_BINFILE_NAME=lab5

info "CREATE DIRECTORY FOR MPI BIN FILES $MPI_DEBUG_DIR"
mkdir $MPI_DEBUG_DIR 2> /dev/null
cd $MPI_DEBUG_DIR
info "COMPILE MPI PROGRAMM $MPI_CFILE_NAME INTO BINARY FILE $MPI_BINFILE_NAME"
mpicc ../$MPI_CFILE_NAME -o $MPI_BINFILE_NAME

if [ $ARG = "--all" ]
then
  for (( i = 1; i < 13; i++ ))
  do
    mpirun -np $i ./$MPI_BINFILE_NAME
  done
else
  info "RUN MPI BINARY FILE $MPI_BINFILE_NAME with $TREADS treads"
  mpirun -np $TREADS ./$MPI_BINFILE_NAME
fi

