using namespace std;

void CumulantFromCK()
{
  TFile* file = TFile::Open("FileOne.root");
  //Definitions of <<2>>
  TProfile* hm_0 = (TProfile*)file->Get("hmult_recursion_0_0");
  cout << hm_0 << endl;
  TH1D* hm_2_new = hm_0->ProjectionX("hm_0_new", "B");
  TH1D* H2_0 = hm_2_new->Clone("H2_0"); // Copy for math operations for <<4>>
  TH1D* H2_1 = hm_2_new->Clone("H2_1"); // Copy for math operations for <<6>>
  TH1D* H2_2 = hm_2_new->Clone("H2_2"); // Copy for math operations for <<8>>


  //Definitions of <<4>>
  TProfile* hm_2 = (TProfile*)file->Get("hmult_recursion_0_2");
  cout << hm_2 << endl;
  TH1D* hm_4_new = hm_2->ProjectionX("hm_2_new", "B");
  TH1D* H4_0 = hm_4_new->Clone("H4_0"); // Copy for math operations for <<6>>
  TH1D* H4_1 = hm_4_new->Clone("H4_1"); // Copy for math operations for <<8>>
  TH1D* H4_2 = hm_4_new->Clone("H4_2"); // Copy for math operations for <<8>> #2
  //Math on <<4>>
  H2_0->Multiply(H2_0); // H2 -> (H2)^2
  H2_0->Scale(2.0); // H2 -> 2(H2)^2
  hm_2_new->Add(H2_0,-1.0); // H4 -> H4 - 2(H2^2)



  //Definitions of <<6>>
  TProfile* hm_4 = (TProfile*)file->Get("hmult_recursion_0_4");
  cout << hm_4 << endl;
  TH1D* hm_6_new = hm_4->ProjectionX("hm_4_new", "B");
  TH1D* H6_0 = hm_6_new->Clone("H6_0"); // Copy for math operations for <<6>>



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
  TH1D* hm_8_new = hm_6->ProjectionX("hm_6_new", "B");

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

  return;

  //c{2} = <2>
  //c{4} = <4> - 2*<2>^2

}

//<2> hmult_recursion_0_0
//hmult_recursion_0_2 is <4>
//hmult_recursion_0_4 is <6>
//hmult_recursion_0_6 is <8>
