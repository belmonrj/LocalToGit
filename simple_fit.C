using namespace std;

void simple_fit()
{

  gStyle->SetOptStat(0);

  //TFile* file = TFile::Open("FileTwo.root");
  //TFile* file = TFile::Open("FileComplete20-09-2019.root");
  TFile* file = TFile::Open("FileOne.root");
  //Definitions of <<2>>
  TProfile* hm_0 = (TProfile*)file->Get("hmult_recursion_0_0");
  //Definitions of <<4>>
  TProfile* hm_2 = (TProfile*)file->Get("hmult_recursion_0_2");
  //Definitions of <<6>>
  TProfile* hm_4 = (TProfile*)file->Get("hmult_recursion_0_4");
  //Definitions of <<8>>
  TProfile* hm_6 = (TProfile*)file->Get("hmult_recursion_0_6");


  // TCanvas to print objects to
  TCanvas *c1 = new TCanvas("c1","");


  //return;



  //TF1* N2 = new TF1("N2","[0]/(x-1)",2,500);
  //TF1* N2 = new TF1("N2","[0]/pow(x,[1])",2,500);
  //TF1* N2 = new TF1("N2","[0]/pow(x-1,[0]",2,500);
  TF1* N2 = new TF1("N2","[0]*1/pow(x-[1],[2])",2,500);
  //N2->SetParLimits(1,0,1);
  N2->FixParameter(1,0.0);
  N2->FixParameter(2,1.2);
  //TF1* N4 = new TF1("N4","[0]*6/((x-1)*(x-2)*(x-3))",4,500);
  TF1* N4 = new TF1("N4","[0]/pow(x-[1],[2])",4,500);
  //N4->SetParLimits(1,0,1);
  N4->FixParameter(1,0.0);
  N4->FixParameter(2,2.5);
  //TF1* N6 = new TF1("N6","[0]*120/((x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6))",6,500);
  TF1* N6 = new TF1("N6","[0]/pow(x-[1],[2])",6,500);
  //N6->SetParLimits(1,0,1);
  N6->FixParameter(1,0.0);
  N6->FixParameter(2,4.0);
  //TF1* N8 = new TF1("N8","[0]*5040/((x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6)*(x-7)*(x-8))",8,500);
  TF1* N8 = new TF1("N8","[0]/pow(x-[1],[2])",8,500);
  //N8->SetParLimits(1,0,1);
  N8->FixParameter(1,0.0);
  N8->FixParameter(2,7.0);

  hm_0->GetXaxis()->SetRangeUser(0,100);
  hm_2->GetXaxis()->SetRangeUser(0,100);
  hm_4->GetXaxis()->SetRangeUser(0,100);
  hm_6->GetXaxis()->SetRangeUser(0,100);


  cout << hm_0 << endl;
  hm_0->Fit(N2,"","",20,50);
  hm_0->Draw();
  c1->SetLogy(1);
  c1->Print("PythiaFigures/modfit_chmult2_log.png");
  c1->SetLogx(1);
  c1->SetLogy(1);
  c1->Print("PythiaFigures/modfit_chmult2_loglog.png");

  //return;

  c1->SetLogx(0);
  //c1->SetLogy(0);
  cout << hm_2 << endl;
  hm_2->Fit(N4,"","",25,70);
  hm_2->Draw();
  c1->Print("PythiaFigures/modfit_chmult4_log.png");
  c1->SetLogx(1);
  c1->SetLogy(1);
  c1->Print("PythiaFigures/modfit_chmult4_loglog.png");

  //return;

  c1->SetLogx(0);
  //c1->SetLogy(0);
  cout << hm_4 << endl;
  hm_4->Fit(N6,"","",30,70);
  hm_4->Draw();
  c1->Print("PythiaFigures/modfit_chmult6_log.png");
  c1->SetLogx(1);
  c1->SetLogy(1);
  c1->Print("PythiaFigures/modfit_chmult6_loglog.png");

  //return;

  c1->SetLogx(0);
  //c1->SetLogy(0);
  cout << hm_6 << endl;
  hm_6->Fit(N8,"","",50,100);
  hm_6->Draw();
  N8->Draw("same");
  c1->Print("PythiaFigures/modfit_chmult8_log.png");
  c1->SetLogx(1);
  c1->SetLogy(1);
  c1->Print("PythiaFigures/modfit_chmult8_loglog.png");

  return;


}
