using namespace std;

void CumulantFromCK()
{
  TFile* file = TFile::Open("FileOne.root");
  //Definitions of <<2>>
  TProfile* hm_0 = (TProfile*)file->Get("hmult_recursion_0_0");
  cout << hm_0 << endl;
  TH1D* hm_2_new = (TH1D*)hm_0->ProjectionX("hm_0_new", "B");
  TH1D* H2_0 = (TH1D*)hm_2_new->Clone("H2_0"); // Copy for math operations for <<4>>
  TH1D* H2_1 = (TH1D*)hm_2_new->Clone("H2_1"); // Copy for math operations for <<6>>
  TH1D* H2_2 = (TH1D*)hm_2_new->Clone("H2_2"); // Copy for math operations for <<8>>

  //Definitions of <<4>>
  TProfile* hm_2 = (TProfile*)file->Get("hmult_recursion_0_2");
  cout << hm_2 << endl;
  TH1D* hm_4_new = (TH1D*)hm_2->ProjectionX("hm_2_new", "B");
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
  TH1D* hm_6_new = (TH1D*)hm_4->ProjectionX("hm_4_new", "B");
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
  TH1D* hm_8_new = (TH1D*)hm_6->ProjectionX("hm_6_new", "B");

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


  // Getting rid of the garbage from this junkpile
  delete H2_0;
  delete H2_1;
  delete H2_2;
  delete H4_0;
  delete H4_1;
  delete H4_2;
  delete H6_0;
  // Garbage collection is important to prevent memory leaks, and I just made a whole shitload
  // of extra memory addresses up there, so I had to fix it



  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // Finding v{n} from c{n}
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // Useable cumulants: hm_2_new, hm_4_new, hm_6_new, hm_8_new
  /////////////////////////////////////////////////////////////////////////////////////////////////////


  //v{2}
  TH1D* vm_2 = (TH1D*)hm_2_new->Clone("vm_2"); // I found out how to loop over the length below
  TH1D* vm_4 = (TH1D*)hm_4_new->Clone("vm_4");
  TH1D* vm_6 = (TH1D*)hm_6_new->Clone("vm_6");
  TH1D* vm_8 = (TH1D*)hm_8_new->Clone("vm_8");

  //lengths of old histograms
  int t = (vm_2->GetSize()) - 2; // h1->GetSize() inherits from TArray
  int u = (vm_4->GetSize()) - 2; // Thank you Rene Brun, I would never have found this
  int v = (vm_6->GetSize()) - 2;
  int w = (vm_8->GetSize()) - 2;

  int i = 0; // for looping



  //loop over the old histogram to fill the new one

  // v{2}
  for(i=1; i<=t; ++i){
    double val = hm_2_new->GetBinContent(i);
    double origErr = hm_2_new->GetBinError(i);
    double op = pow((val), (1/2));
    double newErr = (origErr)/(2*op);
    vm_2->SetBinContent(i, op); // arguments are an integer and a double
    vm_2->SetBinError(i, newErr);
  }// v{2} w/error

  //v{4}
  for(i=1; i<=u; ++i){
    double val = hm_4_new->GetBinContent(i);
    double valTwo = hm_2_new->GetBinContent(i);
    double origErr = hm_4_new->GetBinError(i);
    double origErrTwo = hm_2_new->GetBinError(i);
    double op = pow((-val), (1/4));
    double dWRTTwo = valTwo*(-val + (2*valTwo*valTwo))*origErr;
    double dWRTFour = (-val + (2*valTwo*valTwo))*origErr/16;
    double newErr = pow((dWRTTwo + dWRTFour)*(origErr*origErr), .5);
    double ev24 = (1.0/pow(-val,0.75))*sqrt((valTwo*valTwo*origErrTwo*origErrTwo)+(0.0625*origErr*origErr));
    //The original line is the following:   ev24 = (1.0/pow(-c24,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
    vm_4->SetBinContent(i, op);
    vm_4->SetBinError(i, newErr);
  }// v{4} w/error

  // v{6}
  for(i=1; i<=v; ++i){
    double val = hm_6_new->GetBinContent(i);
    double valTwo = hm_2_new->GetBinContent(i);
    double valFour = hm_4_new->GetBinContent(i);
    double origErr = hm_6_new->GetBinError(i);
    double innerTerm = pow((val-(9*valTwo*valFour)+12*(valTwo*valTwo*valTwo)), (-5/6));
    double outerTerm = pow((1/6), 2) + pow((9*valTwo/6), 2) + pow(((9*valFour)/6 + 24*(valTwo*valTwo)/6),2);
    double newErr = pow((innerTerm*innerTerm)*(outerTerm)*(origErr*origErr), .5);
    double op = pow((val/4), (1/6));
    vm_6->SetBinContent(i, op);
    vm_6->SetBinError(i, newErr);
  }// v{6} w/error

  //v{8}
  for(i=1; i<=w; ++i){
    double val = hm_8_new->GetBinContent(i);
    double valTwo = hm_2_new->GetBinContent(i);
    double valFour = hm_4_new->GetBinContent(i);
    double valSix = hm_6_new->GetBinContent(i);
    double origErr = hm_8_new->GetBinError(i);
    double innerTerm = pow(((-val/33) + ((16*valSix*valTwo)/33) + ((18*valFour*valFour)/33) - ((144*valFour*valTwo*valTwo)/33) + ((144*valTwo*valTwo))/33), (-7/8));
    double outerTerm = pow((1/8), 2) + pow((16*valTwo), 2) + pow(((36*valFour)-(144*valTwo*valTwo)), 2) + pow((16*valSix), 2);
    double newErr = pow((innerTerm*innerTerm)*(outerTerm)*(origErr*origErr), .5);
    double op = pow((-val/33), (1/8));
    vm_8->SetBinContent(i, op);
    vm_8->SetBinError(i, newErr);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Error calculation testing
  TH1D* vm_4_test = (TH1D*)vm_4->Clone("vm_4_test");

  //v{4}_test
  for(i=1; i<=u; ++i){
    double val = hm_4_new->GetBinContent(i);
    double valTwo = hm_2_new->GetBinContent(i);
    double origErr = hm_4_new->GetBinError(i);
    double origErrTwo = hm_2_new->GetBinError(i);
    double op = pow((-val), (1/4));
    double newErr = (1.0/pow(-val,0.75))*sqrt((valTwo*valTwo*origErrTwo*origErrTwo)+(0.0625*origErr*origErr));
    //The original line is the following:   ev24 = (1.0/pow(-c24,0.75))*sqrt((two*two*etwo*etwo)+(0.0625*efour*efour));
    vm_4_test->SetBinContent(i, op);
    vm_4_test->SetBinError(i, newErr);
  }// v{4}_test w/error

    // TCanvas to print objects to
  TCanvas *c1 = new TCanvas("c1", "c1");
  hm_2_new->Draw();
  c1->Print("chmult2.png");

  hm_4_new->Draw();
  c1->Print("chmult4.png");

  hm_6_new->Draw();
  c1->Print("chmult6.png");

  hm_8_new->Draw();
  c1->Print("chmult8.png");

  vm_4->Draw();
  c1->Print("vOfCOf4.png");

  vm_4_test->Draw();
  c1->Print("vOfCOf4_test.png");







  TF1* N2 = new TF1("N2","[0]*1/(x-1)",2,500);
  TF1* N4 = new TF1("N4","[0]*6/((x-1)*(x-2)*(x-3))",4,500);
  TF1* N6 = new TF1("N6","[0]*120/((x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6))",6,500);
  TF1* N8 = new TF1("N8","[0]*5040/((x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6)*(x-7)*(x-8)",8,500);

  // Sample class for TF1 --> TF1* function = new TF1(“function”,“1/(x-1)“,2,500)

  cout << hm_2_new << endl;
  hm_2_new->Fit(N2,"","",2,100);
  hm_2_new->Draw();

  cout << hm_4_new << endl;
  hm_4_new->Fit(N4,"","",4,100);
  hm_4_new->Draw();

  cout << hm_6_new << endl;
  hm_6_new->Fit(N6,"","",6,100);
  hm_6_new->Draw();

  cout << hm_8_new << endl;
  hm_8_new->Fit(N8,"","",8,100);
  hm_8_new->Draw();


  return;

}
