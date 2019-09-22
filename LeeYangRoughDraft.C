//First attempted implementation of the Lee-Yang Zeroes method for Heavy Ions w/Dr. Ron Belmont.
//Aidan Lytle, Sep. 20 2019


#include "TROOT.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TComplex.h"
#include <stdio.h>
//#inlcude <stdlib.h>
#include <math.h>
//#include "Pythia8/Pythia.h"

using namespace std;

//function declaration and variable declaration
const double pi = 3.1415926;
int M = 100;

//main function
float ZeroesLoop()
{
  TCanvas* c1 = new TCanvas("c1","");
  TH1D *t1 = new TH1D("t1", "angles", 100, -pi, pi);
  TH1D *costheta = new TH1D("costheta", "cosines", 100, 0, 1);
  float sum = 0;

  //generate random angles between negative pi and pi, then take their cosines.
  //Fill histograms with generated data
  for(int i=1; i<=M; i++){
    float r = (pi/2) - (rand()/(RAND_MAX/(pi)));
    t1->Fill(r);
    float csin = cos(r);
    costheta->Fill(csin);
    sum += csin;
  }

  t1->GetXaxis()->SetRangeUser(-pi,pi);
  t1->Draw();
  costheta->GetXaxis()->SetRangeUser(-1,1);
  costheta->Draw();
  // What remains: find value of z for generating fucntion, then take the log and set it equal to the sum
  return sum;
}

float sum = ZeroesLoop();


int LeeYangRoughDraft(float)
{

  TCanvas *c2 = new TCanvas("c2","r vs mag(ir)",200,10,500,300);
  Double_t x[100], y[100];
  Int_t n = 10;
  for (Int_t i=0;i<n;i++) {
    x[i] = (float(n)/10);
    y[i] = (float(n)/10)*(sum);
   }
   TGraph* gr = new TGraph(n,x,y);
   gr->Draw("AC*");
   return 0;
}
