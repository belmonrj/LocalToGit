#!/bin/bash



g++ -o simple_particle simple_particle.C -std=c++11 -Wall -Wshadow `root-config --libs` -I$ROOTSYS/include -I$PYTHIA8/include  -l Pythia8 -L $PYTHIA8/lib


