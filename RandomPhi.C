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


  // Objects for printing/filling
  TH1D* phi_for_monty = new TH1D("phi_for_monty", "Test Phi Print", 100, 0, pi);
  TCanvas* c1 = new TCanvas("c1", "samples",200, 10 , 600, 400);


  //important typecasting
  int events = 100; //put events number here
  double j[events];
  double k[events];
  double l[events];
  int i = 0;


  //loop of correlations
  for(i = 0; i <= events; ++i)
    {
    double phi = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/pi));
    j[i] = phi;
    k[i] = phi + pi;
    l[i] = j[i]-k[i];
    phi_for_monty->Fill(j[i],1.0);
    }
  phi_for_monty->Draw();
  c1->Print("phiForMrBurns.png");

      //phi_for_monty->FillN(events, *j, 1.0, 1.0) // here is where the error is

  return;

}

