// Plotter to test combinatorics directly against predicted collision geometries/cumulants
void CosinePlotterTFileOne()
{

  //histogram->Fit(function,“R”);
  TF1* N2 = new TF1("N2","1/(x-1)",2,500);
  TF1* N4 = new TF1("N4","6/((x-1)*(x-2)*(x-3))",4,500);
  //TF1* N6 = new TF1("N6","12/((x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6))",6,500);
  //TF1* N8 = new TF1("N8","

  // Sample class for TF1 --> TF1* function = new TF1(“function”,“1/(x-1)“,2,500)

  TFile* file = TFile::Open("FileOne.root");

  TProfile* hm_0 = (TProfile*)file->Get("hmult_recursion_0_0");
  cout << hm_0 << endl;
  hm_0->Draw();

  TProfile* hm_2 = (TProfile*)file->Get("hmult_recursion_0_2");
  cout << hm_2 << endl;
  hm_2->Draw();

  TProfile* hm_4 = (TProfile*)file->Get("hmult_recursion_0_4");
  cout << hm_4 << endl;
  hm_4->Draw();

  TProfile* hm_6 = (TProfile*)file->Get("hmult_recursion_0_6");
  cout << hm_6 << endl;
  hm_6->Draw();

  return;

}
