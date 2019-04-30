// FileOne.root opener

void TFileOneReader()
{

  TFile* file = TFile::Open("FileOne.root");

  TProfile* hm_0 = (TProfile*)file->Get("hmult_recursion_0_0");
  cout << hm_0 << endl;
  hm_0->Draw();

  return;

  TProfile* hm_1 = (TProfile*)file->Get("hmult_recursion_0_1");
  cout << hm_1 << endl;
  hm_1->Draw();

  TProfile* hm_2 = (TProfile*)file->Get("hmult_recursion_0_2");
  cout << hm_2 << endl;
  hm_2->Draw();

  TProfile* hm_3 = (TProfile*)file->Get("hmult_recursion_0_3");
  cout << hm_3 << endl;
  hm_3->Draw();

  TProfile* hm_4 = (TProfile*)file->Get("hmult_recursion_0_4");
  cout << hm_4 << endl;
  hm_4->Draw();

  TProfile* hm_5 = (TProfile*)file->Get("hmult_recursion_0_5");
  cout << hm_5 << endl;
  hm_5->Draw();

  TProfile* hm_6 = (TProfile*)file->Get("hmult_recursion_0_6");
  cout << hm_6 << endl;
  hm_6->Draw();

  TProfile* hm_7 = (TProfile*)file->Get("hmult_recursion_0_7");
  cout << hm_7 << endl;
  hm_7->Draw();

  TProfile* hm_8 = (TProfile*)file->Get("hmult_recursion_0_8");
  cout << hm_8 << endl;
  hm_8->Draw();

  TProfile* hm_9 = (TProfile*)file->Get("hmult_recursion_0_9");
  cout << hm_9 << endl;
  hm_9->Draw();

  TProfile* hm_10 = (TProfile*)file->Get("hmult_recursion_0_10");
  cout << hm_10 << endl;
  hm_10->Draw();

  TProfile* hm_11 = (TProfile*)file->Get("hmult_recursion_0_11");
  cout << hm_11 << endl;
  hm_11->Draw();

  TProfile* hm_1_0 = (TProfile*)file->Get("hmult_recursion_1_0");
  cout << hm_1_0 << endl;
  hm_1_0->Draw();


  TProfile* hm_1_1 = (TProfile*)file->Get("hmult_recursion_1_1");
  cout << hm_1_1 << endl;
  hm_1_1->Draw();

  TProfile* hm_1_2 = (TProfile*)file->Get("hmult_recursion_1_2");
  cout << hm_1_2 << endl;
  hm_1_2->Draw();

  TProfile* hm_1_3 = (TProfile*)file->Get("hmult_recursion_1_3");
  cout << hm_1_3 << endl;
  hm_1_3->Draw();

  TProfile* hm_1_4 = (TProfile*)file->Get("hmult_recursion_1_4");
  cout << hm_1_4 << endl;
  hm_1_4->Draw();

  TProfile* hm_1_5 = (TProfile*)file->Get("hmult_recursion_1_5");
  cout << hm_1_5 << endl;
  hm_1_5->Draw();

  TProfile* hm_1_6 = (TProfile*)file->Get("hmult_recursion_1_6");
  cout << hm_1_6 << endl;
  hm_1_6->Draw();

  TProfile* hm_1_7 = (TProfile*)file->Get("hmult_recursion_1_7");
  cout << hm_1_7 << endl;
  hm_1_7->Draw();

  TProfile* hm_1_8 = (TProfile*)file->Get("hmult_recursion_1_8");
  cout << hm_1_8 << endl;
  hm_1_8->Draw();

  TProfile* hm_1_9 = (TProfile*)file->Get("hmult_recursion_1_9");
  cout << hm_1_9 << endl;
  hm_1_9->Draw();

  TProfile* hm_1_10 = (TProfile*)file->Get("hmult_recursion_1_10");
  cout << hm_1_10 << endl;
  hm_1_10->Draw();

  TProfile* hm_1_11 = (TProfile*)file->Get("hmult_recursion_1_11");
  cout << hm_1_11 << endl;
  hm_1_11->Draw();

}
