// Plotter to test combinatorics directly against predicted collision geometries/cumulants

void CosinePlotterTFileOne()
{

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
