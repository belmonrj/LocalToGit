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
float LeeYangRoughDraft();
float ZeroesLoop(float);

//main function
float LeeYangRoughDraft()
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

float sum = LeeYangRoughDraft();


float ZeroesLoop(float m)
{

  TCanvas *c2 = new TCanvas("c2","r vs mag(ir)",200,10,500,300);
  Double_t x[10], y[10];
  Int_t n = 10; // the z part of our code
  for (Int_t i=0;i<n;i++) {
    x[i] = (float(i)/10);
    y[i] = (float(i)/10)*(m);
  }
  TGraph* gr = new TGraph(n,x,y);
  gr->Draw("AC*");
  return 0;
}

int main()
{
  ZeroesLoop(sum);
  return 0;
}
