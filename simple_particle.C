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

#include "Pythia8/Pythia.h"

using namespace Pythia8;

const double pi = 3.1415926;

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

  TH1D* heta_vec = new TH1D("heta w/counter", "eta distribution", 100, -3, 3);//This should work but idk
  TH1D* hPhi_vec = new TH1D("hPhi w/counter", "phi distribution", 100, -pi, pi);
  // Begin event loop. Generate event. Skip if error. List first one.

  TProfile* tp1f_c22mult = new TProfile("tp1f_c22mult","c22 vs mult",100,-0.5,499.5,-1e10,1e10);

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
              if ( p.isFinal() && p.isCharged() ) heta_vec->Fill(p.eta()); // this is correct
              //eta filler

              if ( p.isFinal() && p.isCharged() ) hPhi_vec->Fill(p.phi());
              // fill hPhi

              if(p.pT() > 1.0 && p.pT() < 3.0) parts.push_back(&p);
            }

          Q2x += cos(2*p.phi());
          // Qx
          Q2y += sin(2*p.phi());
          // Qy

        } // end loop over particles

      double c22 = ((Q2x * Q2y) - mult)/(mult*(mult-1));
      tp1f_c22mult->Fill(mult,c22);
      // cumulant

      // in a second loop over the selected particles, we'll do more stuff...

      hmult->Fill( nCharged );
      hmult_selected->Fill( mult );
      //hmult_eta->Fill( eta ); // this is extremely bad
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


  // we'll make a file to output some histograms...

  return 0;

}
