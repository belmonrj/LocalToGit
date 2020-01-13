#include pythia

int main(){
// Generator. Process selection. LHC initialization.
  Pythia pythia;
  pythia.readString("Beams:eCM = 8000.");
  pythia.readString("HardQCD:all = on");
  pythia.readString("PhaseSpace:pTHatMin = 20.");
  pythia.init();

  for (int iEvent = 0; iEvent < 10000; ++iEvent)
    {
      // --- for the generic formulas ---------
      for(int h=0;h<maxHarmonic;h++)
        {
          for(int w=0;w<maxPower;w++)
            {
              Qvector[h][w] = TComplex(0.,0.);
            } //  for(int p=0;p<maxPower;p++)
        } // for(int h=0;h<maxHarmonic;h++)
      // --------------------------------------

      if (!pythia.next()) continue;
      // Find number of all final charged particles and fill histogram.

}
