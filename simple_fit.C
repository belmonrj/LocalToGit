using namespace std;

void simple_fit()
{

  gStyle->SetOptStat(0);

  TFile* file = TFile::Open("FileOne.root");
  //Definitions of <<2>>
  TProfile* hm_0 = (TProfile*)file->Get("hmult_recursion_0_0");
  cout << hm_0 << endl;
  //TH1D* hm_2_new = (TH1D*)hm_0->ProjectionX("hm_0_new", "B");
  TH1D* hm_2_new = (TH1D*)hm_0->ProjectionX("hm_0_new");
  TH1D* H2_0 = (TH1D*)hm_2_new->Clone("H2_0"); // Copy for math operations for <<4>>
  TH1D* H2_1 = (TH1D*)hm_2_new->Clone("H2_1"); // Copy for math operations for <<6>>
  TH1D* H2_2 = (TH1D*)hm_2_new->Clone("H2_2"); // Copy for math operations for <<8>>

  //Definitions of <<4>>
  TProfile* hm_2 = (TProfile*)file->Get("hmult_recursion_0_2");
  cout << hm_2 << endl;
  //TH1D* hm_4_new = (TH1D*)hm_2->ProjectionX("hm_2_new", "B");
  TH1D* hm_4_new = (TH1D*)hm_2->ProjectionX("hm_2_new");
  TH1D* H4_0 = (TH1D*)hm_4_new->Clone("H4_0"); // Copy for math operations for <<6>>
  TH1D* H4_1 = (TH1D*)hm_4_new->Clone("H4_1"); // Copy for math operations for <<8>>
  TH1D* H4_2 = (TH1D*)hm_4_new->Clone("H4_2"); // Copy for math operations for <<8>> #2
  //Math on <<4>>
  H2_0->Multiply(H2_0); // H2 -> (H2)^2
  H2_0->Scale(2.0); // H2 -> 2(H2)^2
  hm_4_new->Add(H2_0,-1.0); // H4 -> H4 - 2(H2^2)



  //Definitions of <<6>>
  TProfile* hm_4 = (TProfile*)file->Get("hmult_recursion_0_4");
  cout << hm_4 << endl;
  //TH1D* hm_6_new = (TH1D*)hm_4->ProjectionX("hm_4_new", "B");
  TH1D* hm_6_new = (TH1D*)hm_4->ProjectionX("hm_4_new");
  TH1D* H6_0 = (TH1D*)hm_6_new->Clone("H6_0"); // Copy for math operations for <<6>>



  //Math on <<6>>
  H4_0->Multiply(H2_1); // H4 -> (H4)(H2)
  H4_0->Scale(9.0); // H4 -> 9(H4)(H2)

  H2_1->Multiply(H2_1); // H2 -> (H2)^2
  H2_1->Multiply(H2_2); // H2 -> (H2)^3
  H2_1->Scale(12.0); // H2 -> 12(H2)^3

  hm_6_new->Add(H2_1, 1.0); // H6 -> H6 + 12(H2)^2
  hm_6_new->Add(H4_0, -1.0); //H6 -> H6 - 9(H4)(H2) + 12(H2)^2



  //Definitions of <<8>>
  TProfile* hm_6 = (TProfile*)file->Get("hmult_recursion_0_6");
  cout << hm_6 << endl;
  //TH1D* hm_8_new = (TH1D*)hm_6->ProjectionX("hm_6_new", "B");
  TH1D* hm_8_new = (TH1D*)hm_6->ProjectionX("hm_6_new");

  //Math on <<8>>
  H6_0->Multiply(H2_2); // H6 -> (H6)(H2)
  H6_0->Scale(16.0); //H6 -> 16(H6)(H2)

  H2_2->Multiply(H2_2); // H2 -> (H2)^2 ***
  H4_1->Multiply(H2_2); // H4 -> (H4)(H2)^2
  H4_1->Scale(144.0); // H4 -> 144(H4)(H2)^2

  H4_2->Multiply(H4_2); // H4 -> (H4)^2
  H4_2->Scale(18.0); // H4 -> 18(H4)^2

  H2_2->Multiply(H2_2); // H2 -> (H2)^4 *** See above
  H2_2->Scale(144.0); // H2 -> 144(H2)^4

  hm_8_new->Add(H6_0,-1.0); // H8 -> H8 - 16(H6)(H2)
  hm_8_new->Add(H4_1,1.0); // H8 -> H8 - 16(H6)(H2) + 144(H4)(H2)^2
  hm_8_new->Add(H4_2,-1.0); // H8 -> H8 - 16(H6)(H2) - 18(H4)^2 + 144(H4)(H2)^2
  hm_8_new->Add(H2_2,-1.0); // H8 -> H8 - 16(H6)(H2) - 18(H4)^2 + 144(H4)(H2)^2 - 144(H4)^4

  // TCanvas to print objects to
  TCanvas *c1 = new TCanvas("c1", "c1");
  hm_2_new->GetXaxis()->SetRangeUser(0,100);
  hm_2_new->GetXaxis()->SetTitle("Multiplicity");;
  hm_2_new->Draw();
  //c1->Print("PythiaFigures/chmult2.png");

  hm_4_new->GetXaxis()->SetRangeUser(0,100);
  hm_4_new->GetXaxis()->SetTitle("Multiplicity");;
  hm_4_new->Draw();
  //c1->Print("PythiaFigures/chmult4.png");

  hm_6_new->GetXaxis()->SetRangeUser(0,100);
  hm_6_new->GetXaxis()->SetTitle("Multiplicity");;
  hm_6_new->Draw();
  //c1->Print("PythiaFigures/chmult6.png");

  hm_8_new->GetXaxis()->SetRangeUser(0,100);
  hm_8_new->GetXaxis()->SetTitle("Multiplicity");;
  hm_8_new->Draw();
  //c1->Print("PythiaFigures/chmult8.png");

  //return;

  // Getting rid of the garbage from this junkpile
  // delete H2_0;
  // delete H2_1;
  // delete H2_2;
  // delete H4_0;
  // delete H4_1;
  // delete H4_2;
  // delete H6_0;
  // Garbage collection is important to prevent memory leaks, and I just made a whole shitload
  // of extra memory addresses up there, so I had to fix it



  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // Finding v{n} from c{n}
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // Useable cumulants: hm_2_new, hm_4_new, hm_6_new, hm_8_new
  /////////////////////////////////////////////////////////////////////////////////////////////////////



  //return;



  //TF1* N2 = new TF1("N2","[0]/(x-1)",2,500);
  //TF1* N2 = new TF1("N2","[0]/pow(x,[1])",2,500);
  //TF1* N2 = new TF1("N2","[0]/pow(x-1,[0]",2,500);
  TF1* N2 = new TF1("N2","[0]*1/pow(x-[1],[2])",2,500);
  //N2->SetParLimits(1,0,1);
  N2->FixParameter(1,0.0);
  N2->FixParameter(2,1.0);
  //TF1* N4 = new TF1("N4","[0]*6/((x-1)*(x-2)*(x-3))",4,500);
  TF1* N4 = new TF1("N4","[0]/pow(x-[1],[2])",4,500);
  //N4->SetParLimits(1,0,1);
  N4->FixParameter(1,0.0);
  N4->FixParameter(2,2.0);
  //TF1* N6 = new TF1("N6","[0]*120/((x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6))",6,500);
  TF1* N6 = new TF1("N6","[0]/pow(x-[1],[2])",6,500);
  //N6->SetParLimits(1,0,1);
  N6->FixParameter(1,0.0);
  N6->FixParameter(2,3.0);
  //TF1* N8 = new TF1("N8","[0]*5040/((x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6)*(x-7)*(x-8))",8,500);
  TF1* N8 = new TF1("N8","[0]/pow(x-[1],[2])",8,500);
  //N8->SetParLimits(1,0,1);
  N8->FixParameter(1,0.0);
  N8->FixParameter(2,4.0);

  hm_0->GetXaxis()->SetRangeUser(0,100);
  hm_2->GetXaxis()->SetRangeUser(0,100);
  hm_4->GetXaxis()->SetRangeUser(0,100);
  hm_6->GetXaxis()->SetRangeUser(0,100);


  cout << hm_0 << endl;
  hm_0->Fit(N2,"","",10,100);
  hm_0->Draw();
  c1->Print("PythiaFigures/modfit_chmult2.png");
  c1->SetLogx(1);
  c1->SetLogy(1);
  c1->Print("PythiaFigures/modfit_chmult2_loglog.png");

  //return;

  c1->SetLogx(0);
  c1->SetLogy(0);
  cout << hm_2 << endl;
  hm_2->Fit(N4,"","",10,100);
  hm_2->Draw();
  c1->Print("PythiaFigures/modfit_chmult4.png");
  c1->SetLogx(1);
  c1->SetLogy(1);
  c1->Print("PythiaFigures/modfit_chmult4_loglog.png");

  //return;

  c1->SetLogx(0);
  c1->SetLogy(0);
  cout << hm_4 << endl;
  hm_4->Fit(N6,"","",30,100);
  hm_4->Draw();
  c1->Print("PythiaFigures/modfit_chmult6.png");
  c1->SetLogx(1);
  c1->SetLogy(1);
  c1->Print("PythiaFigures/modfit_chmult6_loglog.png");

  //return;

  c1->SetLogx(0);
  c1->SetLogy(0);
  cout << hm_6 << endl;
  hm_6->Fit(N8,"","",30,100);
  hm_6->Draw();
  c1->Print("PythiaFigures/modfit_chmult8.png");
  c1->SetLogx(1);
  c1->SetLogy(1);
  c1->Print("PythiaFigures/modfit_chmult8_loglog.png");

  return;


}
