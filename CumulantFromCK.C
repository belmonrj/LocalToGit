using namespace std;

void CumulantFromCK()
{
  TFile* file = TFile::Open("FileOne.root");

  TProfile* hm_0 = (TProfile*)file->Get("hmult_recursion_0_0");
  cout << hm_0 << endl;
  TH1D* hm_0_new = hm_0->ProjectionX("hm_0_new", "B");
  TH1D* H2 = hm_0_new; // Copy for math operations

  TProfile* hm_2 = (TProfile*)file->Get("hmult_recursion_0_2");
  cout << hm_2 << endl;
  TH1D* hm_2_new = hm_2->ProjectionX("hm_2_new", "B");
  TH1D* H4 = hm_2_new; // Copy for math operations
  H2->Multiply(H2);
  H2->Scale(2.0);
  H4->Add(H2,-1.0);
  
    //  TProfile* hm_4 = (TProfile*)file->Get("hmult_recursion_0_4");
    //  cout << hm_4 << endl;
    //  TH1D* hm_4_new = hm_4->ProjectionX("hm_4_new", "B");

    //  TProfile* hm_6 = (TProfile*)file->Get("hmult_recursion_0_6");
    //  cout << hm_6 << endl;
    //  TH1D* hm_6_new = hm_6->ProjectionX("hm_6_new", "B");

  return;

  //c{2} = <2>
  //c{4} = <4> - 2*<2>^2

}

//<2> hmult_recursion_0_0
//hmult_recursion_0_2 is <4>
//hmult_recursion_0_4 is <6>
//hmult_recursion_0_6 is <8>
