#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
using namespace std;

void HistArrayMaker(int pairs, int events, TH1D* tha[])
{
  double pi = 3.14159;
  for(int i = 0; i < pairs; ++i)
    {
        tha[i] = new TH1D(Form("phi_for_monty_%d",i),"",100,0,pi);
        for(int m = 0; m <= events; ++m)
          {
            double phi = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/pi));
            tha[i]->Fill(phi,1.0);
            tha[i]->SetMinimum(0);
          }
      }
  return;
}

void RandomPhi()
{
  srand (static_cast <unsigned> (time(0)));
  double pi = 3.1415926;


  // Objects for printing/filling
  //TH1D* phi_for_monty = new TH1D("phi_for_monty", "", 100, 0, pi); // can label axes with "Title; XAxisTitle; YAxisTitle"
  TCanvas* c1 = new TCanvas("c1", "samples",200, 10 , 600, 400);
  //phi_for_monty->SetMinimum(0);

  //important typecasting
  const int pairs = 50; //put number of pairs per event here
  int events = 1000;

  TH1D* phi_for_monty_array[pairs];

  HistArrayMaker(pairs,events,phi_for_monty_array);

  return;
}

  //loop of events and pairs
    //  for(int m = 0; m <= events; ++m){

    //for(int i = 0; i <= pairs; ++i)
    //{
    //  double phi = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/pi));
    //  double j = phi;
    //  double k = phi + pi;
    //  phi_for_monty->Fill(j,1.0);
    //}
    //}

  //  phi_for_monty->GetXaxis()->SetTitle("XAxis");
  //  phi_for_monty->GetYaxis()->SetTitle("Yaxis");
  //  phi_for_monty->Draw();
  //  c1->Print("phiForMrBurns.png");

      //phi_for_monty->FillN(events, *j, 1.0, 1.0) // here is where the error is

//return;

//}

