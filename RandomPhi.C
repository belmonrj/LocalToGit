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
  int pairs = 50; //put number of pairs per event here

  int events = 1000;

  //loop of events and
  for(int m = 0; m <= events; ++m){

    for(int i = 0; i <= pairs; ++i)
      {
        double phi = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/pi));
        double j = phi;
        double k = phi + pi;
        phi_for_monty->Fill(j,1.0);
      }
  }
    phi_for_monty->Draw();
    c1->Print("phiForMrBurns.png");

      //phi_for_monty->FillN(events, *j, 1.0, 1.0) // here is where the error is

  return;

}

