const int nRuns = 1000000;
void ToyMonteCarlo()

{
  // gRandom = new TRandom3();
  // cout<<gRandom<<endl;
  gStyle->SetOptStat(0);

  TCanvas* c1 = new TCanvas();
  TF1* funx = new TF1("funx","gaus",-10,10);
  TF1* funy = new TF1("funy","gaus",-10,10);
  TH1D* histx = new TH1D("histx","",200,-10,10);
  TH1D* histy = new TH1D("histy","",200,-10,10);
  TH1D* histr = new TH1D("histr","",100,0,10);

  funx->SetParameter(0,1.0);
  funy->SetParameter(0,1.0);

  funx->SetParameter(1,0.0);
  funy->SetParameter(1,0.0);

  funx->SetParameter(2,1.0);
  funy->SetParameter(2,1.0);



  for (int i = 0; i<nRuns; ++i)
    {
      double x = funx->GetRandom();
      double y = funy->GetRandom();
      double r = sqrt(x*x+y*y);
      histx->Fill(x);
      histy->Fill(y);
      histr->Fill(r);
    }

  histx->Draw();
  c1->Print("bg_histx.png");
  histy->Draw();
  c1->Print("bg_histy.png");

   histr->Draw();
   double meanr = histr->GetMean();
   double sigmar = histr->GetRMS();
   double skewr = histr->GetSkewness();
   double kurtr = histr->GetKurtosis();
   double SigDivMeanr = sigmar/meanr;
  TLatex* Tex_mean = new TLatex(0.6,0.8,Form("mean = %f",meanr));
   Tex_mean->SetNDC();
   Tex_mean->Draw();
  TLatex* Tex_sigma = new TLatex(0.6,0.75,Form("sigma = %f",sigmar));
   Tex_sigma->SetNDC();
   Tex_sigma->Draw();
  TLatex* Tex_skew = new TLatex(0.6,0.7,Form("skew = %f",skewr));
   Tex_skew->SetNDC();
   Tex_skew->Draw();
  TLatex* Tex_kurt = new TLatex(0.6,0.65,Form("kurt = %f",kurtr));
   Tex_kurt->SetNDC();
   Tex_kurt->Draw();
  TLatex* Tex_SigDivMean = new TLatex(0.6,0.6,Form("SigDivMean = %f",SigDivMeanr));
   Tex_SigDivMean->SetNDC();
   Tex_SigDivMean->Draw();

     
  c1->Print("bg_histr.png");
}
