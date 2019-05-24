// Plotter to test combinatorics directly against predicted collision geometries/cumulants
void CosinePlotterTFileOne()
{

  TCanvas* c1 = new TCanvas("c1","");

  //histogram->Fit(function,“R”);
  TF1* N2 = new TF1("N2","[0]*1/(x-1)",2,500);
  TF1* N4 = new TF1("N4","[0]*6/((x-1)*(x-2)*(x-3))",4,500);
  TF1* N6 = new TF1("N6","[0]*120/((x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6))",6,500);
  TF1* N8 = new TF1("N8","[0]*5040/((x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6)*(x-7)*(x-8))",8,500);

  // Sample class for TF1 --> TF1* function = new TF1(“function”,“1/(x-1)“,2,500)

  TFile* file = TFile::Open("FileOne.root");

  TProfile* hm_0 = (TProfile*)file->Get("hmult_recursion_0_0");
  cout << hm_0 << endl;
  hm_0->Fit(N2,"","",2,100);
  hm_0->SetMaximum(0.5);
  hm_0->SetMinimum(-0.1);
  hm_0->GetXaxis()->SetRangeUser(0,100);
  hm_0->Draw();
  c1->Print("test_fit_2.png");

  TProfile* hm_2 = (TProfile*)file->Get("hmult_recursion_0_2");
  cout << hm_2 << endl;
  hm_2->Fit(N4,"","",4,100);
  hm_2->SetMaximum(0.1);
  hm_2->SetMinimum(-0.01);
  hm_2->GetXaxis()->SetRangeUser(0,100);
  hm_2->Draw();
  c1->Print("test_fit_4.png");

  TProfile* hm_4 = (TProfile*)file->Get("hmult_recursion_0_4");
  cout << hm_4 << endl;
  hm_4->Fit(N6,"","",6,100);
  hm_4->SetMaximum(0.01);
  hm_4->SetMinimum(-0.001);
  hm_4->GetXaxis()->SetRangeUser(0,100);
  hm_4->Draw();
  c1->Print("test_fit_6.png");

  TProfile* hm_6 = (TProfile*)file->Get("hmult_recursion_0_6");
  cout << hm_6 << endl;
  hm_6->Fit(N8,"","",8,100);
  hm_6->SetMaximum(0.001);
  hm_6->SetMinimum(-0.0001);
  hm_6->GetXaxis()->SetRangeUser(0,100);
  hm_6->Draw();
  c1->Print("test_fit_8.png");

  return;

}
