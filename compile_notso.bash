#!/bin/bash



g++ -o Not_so_simple_particle Not_so_simple_particle.C -std=c++11 -Wall -Wshadow `root-config --libs` -I$ROOTSYS/include -I$PYTHIA8/include  -l Pythia8 -L $PYTHIA8/lib


