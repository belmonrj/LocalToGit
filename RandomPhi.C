#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
using namespace std;


void RandomPhi()
{
  srand (static_cast <unsigned> (time(0)));
  double pi = 3.1415;
  int events = 20; //put events number here
  double j[events];
  double k[events];
  double l[events];
  int i = 0;
  for(i = 0; i <= events; ++i)
    {
    double phi = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/pi));
    j[i] = phi;
    k[i] = phi + pi;
    l[i] = j[i]-k[i];
    }


  return;

}

