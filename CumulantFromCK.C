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
    double op = pow((val), (1/2));
    vm_2->SetBinContent(i, op); // arguments are an integer and a double
  }// v{2}

  //v{4}
  for(i=1; i<=u; ++i){
    double val = hm_4_new->GetBinContent(i);
    double op = pow((-val), (1/4));
    vm_4->SetBinContent(i, op);
  }// v{4} 

  // v{6}
  for(i=1; i<=v; ++i){
    double val = hm_6_new->GetBinContent(i);
    double op = pow((val/4), (1/6));
    vm_6->SetBinContent(i, op);
  }// v{6}

  //v{8}
  for(i=1; i<=w; ++i){
    double val = hm_8_new->GetBinContent(i);
    double op = pow((-val/33), (1/8));
    vm_8->SetBinContent(i, op);
  }



  return;

}
