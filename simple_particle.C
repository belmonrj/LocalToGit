// main01.cc is a part of the PYTHIA event generator.
// Copyright (C) 2018 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program. It fits on one slide in a talk.
// It studies the charged multiplicity distribution at the LHC.

// this is a copy with very minor modification by Ron Belmont
// Also edited to by Aidan Lytle to produce an eta distribution

#include "TROOT.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TComplex.h"

#include "Pythia8/Pythia.h"

using namespace Pythia8;

const double pi = 3.1415926;

// Stuff for cumulants greater than 2
static const int maxCorrelator = 12; // Somewhat abusing the setup as it is...
static const int maxHarmonic = 10; // Need to assess on case-by-case basis, but this gets you v2{8} and v3{6}
static const int maxPower = 9;
TComplex Qvector[maxHarmonic][maxPower]; // All needed Q-vector components
TComplex Q(int, int);
TComplex Recursion(int, int*);
TComplex Recursion(int, int*, int, int);

int main()
{

  // Generator. Process selection. LHC initialization.
  Pythia pythia;
  pythia.readString("Beams:eCM = 8000.");
  pythia.readString("HardQCD:all = on");
  pythia.readString("PhaseSpace:pTHatMin = 20.");
  pythia.init();

  // --- histograms
  TH1D* hmult = new TH1D("hmult","charged multiplicity", 100, -0.5, 499.5);
  TH1D* hmult_selected = new TH1D("hmult_selected","charged multiplicity for selected particles", 100, -0.5, 499.5);
  //TH1D* hmult_eta = new TH1D( "Eta particle", "-3 to 3", 100, -0.5, 499.5); // this is extremely bad

  TH1D* heta = new TH1D("heta", "eta distribution", 100, -3, 3); // this is correct
  TH1D* hPhi = new TH1D("hPhi", "phi distribution", 100, -pi, pi);//This should work but idk

  //looped histograms

  // --- the first argument in the constructor is the object name
  // --- it must not have spaces, special characters, etc.
  // TH1D* heta_vec = new TH1D("heta w/counter", "eta distribution", 100, -3, 3);//This should work but idk
  // TH1D* hPhi_vec = new TH1D("hPhi w/counter", "phi distribution", 100, -pi, pi);
  TH1D* heta_vec = new TH1D("heta_vec", "eta distribution", 100, -3, 3);
  TH1D* hPhi_vec = new TH1D("hPhi_vec", "phi distribution", 100, -pi, pi);

  // Begin event loop. Generate event. Skip if error. List first one.
  // Particle correlation as a function of charged multiplicity.

  TProfile* tp1f_c22mult = new TProfile("tp1f_c22mult","c22 vs mult",100,-0.5,499.5,-1e10,1e10);
  TProfile* tp1f_c24mult = new TProfile("tp1f_c24mult","c24 vs mult",100,-0.5,499.5,-1e10,1e10);
  TProfile* tp1f_c26mult = new TProfile("tp1f_c26mult","c26 vs mult",100,-0.5,499.5,-1e10,1e10);
  TProfile* tp1f_c28mult = new TProfile("tp1f_c28mult","c28 vs mult",100,-0.5,499.5,-1e10,1e10);
  //TComplex* BoulderCumulants = new TComplex(//stuff here to fill defintion of TComplex
  TProfile* nfvtxt_recursion[2][maxCorrelator];

  for ( int cs = 0; cs < 2; ++cs )
    {
      for(int c = 0; c < maxCorrelator; ++c )
        {
          nfvtxt_recursion[cs][c] = new TProfile(Form("nfvtxt_recursion_%d_%d",cs,c),"",700,-0.5,699.5,-1.1,1.1);
        }
    }

  ////
  //Recursion Function from BoulderCumulantsFunction.C
  ////

  // --- from generic forumulas ----------------------------------------------------

  ////
  //Main event loop
  ////

  for (int iEvent = 0; iEvent < 10000; ++iEvent)
    {

      if (!pythia.next()) continue;
      // Find number of all final charged particles and fill histogram.

      Event& event = pythia.event;
      // First we find the particles we need for the analysis,
      // as well as event multiplicity.
      vector<Particle*> parts;
      int mult = 0;
      int nCharged = 0;
      double Q2x = 0;
      double Q2y = 0;
      //int heta = 0; // this is extremely bad

      for (int i = 0; i < event.size(); ++i)
        {
          // Particle short notation
          Particle& p = event[i];

          // count all charged particles
          if (p.isFinal() && p.isCharged()) ++nCharged;

          // Apply simple, particle level, cuts.

          if ( p.isFinal() && p.isCharged() ) heta->Fill(p.eta()); // this is correct
          //eta filler

          if ( p.isFinal() && p.isCharged() ) hPhi->Fill(p.phi());
          // fill hPhi

          if(p.isFinal() && p.isCharged() && abs(p.eta()) < 2.5 && p.pT() > 0.5)
            {
              ++mult;
              //if ( p.isFinal() && p.isCharged() ) heta_vec->Fill(p.eta()); // this is redundant
              heta_vec->Fill(p.eta()); // this is correct
              //eta filler

              //if ( p.isFinal() && p.isCharged() ) hPhi_vec->Fill(p.phi());
              hPhi_vec->Fill(p.phi());
              // fill hPhi

              if(p.pT() > 1.0 && p.pT() < 3.0) parts.push_back(&p);
            }

          Q2x += cos(2*p.phi());
          // Qx
          Q2y += sin(2*p.phi());
          // Qy

        } // end loop over particles

      ////Defining usage and objects necessary for Recursion and 
      ////higher cumulants after particle loop, but over 
      ////event loop

      int harmonics_Two_Num[2] = {2,-2}; // 2, -2
      int harmonics_Two_Den[2] = {0,0}; // recursion gives right combinatorics
      TComplex twoRecursion = Recursion(2,harmonics_Two_Num)/Recursion(2,harmonics_Two_Den).Re();
      double spwTwoRecursion = Recursion(2,harmonics_Two_Den).Re();
      double wTwoRecursion = 1.0;
      nfvtxt_recursion[0][0]->Fill(mult,twoRecursion.Re(),wTwoRecursion); // <<cos(h1*phi1+h2*phi2)>>
      nfvtxt_recursion[1][0]->Fill(mult,twoRecursion.Im(),wTwoRecursion); // <<sin(h1*phi1+h2*phi2)>>
      //  4-p correlations:
      //cout<<” => Calculating 4-p correlations (using recursion)...       \r”<<flush;
      int harmonics_Four_Num[4] = {2,2,-2,-2};
      int harmonics_Four_Den[4] = {0,0,0,0}; // recursion gives right combinatorics
      TComplex fourRecursion = Recursion(4,harmonics_Four_Num)/Recursion(4,harmonics_Four_Den).Re();
      double spwFourRecursion = Recursion(4,harmonics_Four_Den).Re();
      double wFourRecursion = 1.0;
      nfvtxt_recursion[0][2]->Fill(mult,fourRecursion.Re(),wFourRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>
      nfvtxt_recursion[1][2]->Fill(mult,fourRecursion.Im(),wFourRecursion); // <<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4)>>
      //  6-p correlations:
      //cout<<” => Calculating 6-p correlations (using recursion)...       \r”<<flush;
      int harmonics_Six_Num[6] = {2,2,2,-2,-2,-2};
      int harmonics_Six_Den[6] = {0,0,0,0,0,0};
      TComplex sixRecursion = Recursion(6,harmonics_Six_Num)/Recursion(6,harmonics_Six_Den).Re();
      double spwSixRecursion = Recursion(6,harmonics_Six_Den).Re();
      double wSixRecursion = 1.0;
      nfvtxt_recursion[0][4]->Fill(mult,sixRecursion.Re(),wSixRecursion); // <<cos(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>>
      nfvtxt_recursion[1][4]->Fill(mult,sixRecursion.Im(),wSixRecursion); // <<sin(h1*phi1+h2*phi2+h3*phi3+h4*phi4+h5*phi5+h6*phi6)>>
      //  8-p correlations:
      //cout<<” => Calculating 8-p correlations (using recursion)...       \r”<<flush;
      int harmonics_Eight_Num[8] = {2,2,2,2,-2,-2,-2,-2};
      int harmonics_Eight_Den[8] = {0,0,0,0,0,0,0,0};
      TComplex eightRecursion = Recursion(8,harmonics_Eight_Num)/Recursion(8,harmonics_Eight_Den).Re();
      double spwEightRecursion = Recursion(8,harmonics_Eight_Den).Re();
      double wEightRecursion = 1.0;
      nfvtxt_recursion[0][6]->Fill(mult,eightRecursion.Re(),wEightRecursion);
      nfvtxt_recursion[1][6]->Fill(mult,eightRecursion.Im(),wEightRecursion);
      ////End of ripped codes from 'Boulder' codes


      // calculate the 2 cumulant
      double c22 = ((Q2x * Q2y) - mult)/(mult*(mult-1));
      // fill TProfile to compute average cumulant vs multiplicity
      tp1f_c22mult->Fill(mult,c22);

      // multiplicity distributions
      hmult->Fill( nCharged );
      hmult_selected->Fill( mult );
    } // end of loop over events

  pythia.stat(); // tell about some statistics for this run

  TCanvas* c1 = new TCanvas("c1","");

  hmult->Draw();
  c1->Print("p8_hmult.png");

  hmult_selected->Draw();
  c1->Print("p8_hmult_sel.png");

  // fixed name in accordance with above
  heta->Draw();
  heta->SetMinimum(0); // root zero suppresses by default
  c1->Print("p8_eta.png");

  hPhi->Draw();
  hPhi->SetMinimum(0);
  c1->Print("p8_phi.png");

  heta_vec->Draw();
  heta_vec->SetMinimum(0); // root zero suppresses by default
  c1->Print("p8_eta_vec.png");

  hPhi_vec->Draw();
  hPhi_vec->SetMinimum(0);
  c1->Print("p8_phi_vec.png");

  tp1f_c22mult->Draw();
  c1->Print("p8_c22mult.png");

  //Tfile for I/O stuff
  TFile* HistFile = new TFile("FileOne.root","recreate");
  HistFile->cd();
  heta->Write();
  heta_vec->Write();
  hPhi->Write();
  hPhi_vec->Write();
  tp1f_c22mult->Write();
  HistFile->Close();

  // we'll make a file to output some histograms...

  return 0;

}
// --- from generic forumulas ----------------------------------------------------
TComplex Recursion(int n, int* harmonic)
{
  return Recursion(n,harmonic,1,0); // 1 and 0 are defaults from above
}

TComplex Recursion(int n, int* harmonic, int mult, int skip)
{
  // Calculate multi-particle correlators by using recursion (an improved faster version) originally developed by
  // Kristjan Gulbrandsen (gulbrand@nbi.dk).

  int nm1 = n-1;
  TComplex c(Q(harmonic[nm1], mult));
  if (nm1 == 0) return c;
  c *= Recursion(nm1, harmonic);
  if (nm1 == skip) return c;

  int multp1 = mult+1;
  int nm2 = n-2;
  int counter1 = 0;
  int hhold = harmonic[counter1];
  harmonic[counter1] = harmonic[nm2];
  harmonic[nm2] = hhold + harmonic[nm1];
  TComplex c2(Recursion(nm1, harmonic, multp1, nm2));
  int counter2 = n-3;
  while (counter2 >= skip) {
    harmonic[nm2] = harmonic[counter1];
    harmonic[counter1] = hhold;
    ++counter1;
    hhold = harmonic[counter1];
    harmonic[counter1] = harmonic[nm2];
    harmonic[nm2] = hhold + harmonic[nm1];
    c2 += Recursion(nm1, harmonic, multp1, counter2);
    --counter2;
  }
  harmonic[nm2] = harmonic[counter1];
  harmonic[counter1] = hhold;

  if (mult == 1) return c-c2;
  return c-double(mult)*c2;

}
TComplex Q(int n, int p)
{
  // Using the fact that Q{-n,p} = Q{n,p}^*.
  if(n>=0){return Qvector[n][p];}
  return TComplex::Conjugate(Qvector[-n][p]);
} // TComplex Q(int n, int p)
// ------------------------
