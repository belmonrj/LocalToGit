const int maxn = 1000;

//void generate();
double factorial(int);
double factorial(int, int);
double NCK(int, int);
void doAll3(const int);

void All3()
{
  gStyle->SetOptTitle(0); // gets rid of the "Graph" at the top of the graphs when you draw them on a TCanvas
  doAll3(15);
  doAll3(25);
  doAll3(100);
  doAll3(200);
  doAll3(500);
  doAll3(1000);
}

// void generate()
// {
//   ofstream fout("list_of_numbers");
//   for ( int i = 0; i < maxn; ++i )
//     {
//       fout << i << " " << 2*i << endl;
//     }

// } // void generate



double factorial(int n)
{

  double factorialn = 1;

  for (int i = 1; i <=n; ++i)
    {
      factorialn *= i;
    }
  return factorialn;
} // N!

double factorial(int n, int stop)
{

  double factorialn = n;
  int counter = 0;
  for (int i = (n - 1); i >=1 ; --i)
    {
      if ( counter >= (stop - 1) ) break;
      factorialn *= i;
      counter++;
    }
  return factorialn;
} // N!
//---------------------------------------------------------







double NCK(int n, int r)
{
  if (r == 0) return 1;

  if (r > n / 2) return NCK(n, n - r); // save some computation

  long res = 1;

  for (int k = 1; k <= r; ++k)
    {
      res *= n - k + 1;
      res /= k;
    }

  return res;
} // int NCK //






//void CompareAllThree()
void doAll3(int limit)
{

  TCanvas* c4 = new TCanvas();

  //generate();
  double o[maxn]={0};
  double falling[maxn]={0};
  ifstream fin("list_of_numbers");
  double factoriala[maxn];
  double num[maxn];

  double NM1F[maxn];
  double KM1F[maxn];
  double NM1FTOK[maxn];
  double NfloorNchooseK[maxn];



  double NM1F2[maxn];
  double KM1F2[maxn];
  double falling2[maxn]={0};
  double o2[maxn]={0};
  double NfloorNchooseK2[maxn];


  double NM1F3[maxn];
  double KM1F3[maxn];
  double falling3[maxn]={0};
  double o3[maxn]={0};
  double NfloorNchooseK3[maxn];


  double NM1F4[maxn];
  double KM1F4[maxn];
  double falling4[maxn]={0};
  double o4[maxn]={0};
  double NfloorNchooseK4[maxn];

  for ( int j = 0; j < maxn; ++j)
    {
      num[j] = j;
      int k = 2;
      if ( j < k ) continue;
      NM1FTOK[j] = ( pow (j-1, k-1));
      //cout << "NM1FTOK is " << NM1FTOK[j] << endl;
      o[j] = ((float)factorial(k-1)/(float)pow(j, k-1));
      falling[j] = (float)factorial(k-1)/(float)factorial(j-1,k-1);
      // cout << j << " " << NFACa[j] << " " << NM1F[j] << " " << NM1FTOK[j] << " "
      //   << " The number of particle correlations is expected to be proportional to the number of particles in the event. thus" <<
      //"K minus one factorial, divided by n to the k minus one, is" <<  o << " " << endl;
      NfloorNchooseK[j] = (j/k)/((factorial(j))/(factorial(k)*factorial(j - k)));

      int m = 4;
      if ( j < m ) continue;
      o2[j] = ((float)factorial( m - 1 )/(float)pow(j, m - 1));
      falling2[j] = (float)factorial(m-1)/(float)factorial(j-1, m-1);

      NfloorNchooseK2[j] = (j/m)/((factorial(j))/(factorial(m)*factorial(j - m)));

      int r = 6;
      if ( j < r ) continue;
      o3[j] = ((float)factorial( r - 1 )/(float)pow(j, r - 1));
      falling3[j] = (float)factorial(r-1)/(float)factorial(j-1, r-1);

      NfloorNchooseK3[j] = (j/r)/((factorial(j))/(factorial(r)*factorial(j - r)));

      int s = 8;
      if ( j < s ) continue;
      o4[j] = ((float)factorial( s - 1 )/(float)pow(j, s - 1));
      falling4[j] = (float)factorial(s-1)/(float)factorial(j-1, s-1);

      NfloorNchooseK4[j] = (j/s)/((factorial(j))/(factorial(s)*factorial(j - s)));
    }   // for loop



  cout << factorial(10,2) << " " << factorial(10,3) << " "  << factorial(10,10) << " "  << factorial(10) << endl;
  fin.close();

  TGraph* c3 = new TGraph (limit, num, o);
  c3->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  c3->SetLineStyle(3); // RB - added this to make it a bit easier to see under the fit
  c3->SetLineColor(kRed);
  c3->Draw("al");
  c3->SetMaximum(1);
  c3->SetMinimum(1e-10);
  TGraph* cfall = new TGraph (limit, num, falling);
  cfall->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  cfall->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  cfall->SetLineColor(kBlue);
  cfall->Draw("l");
  TGraph* cmain = new TGraph (limit, num, NfloorNchooseK);
  cmain->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  cmain->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  cmain->SetLineColor(kGreen);
  cmain->Draw("l");

  TLegend* legend = new TLegend(0.68,0.68,0.88,0.88);
  legend->SetHeader("k = 2"); // copy this as needed
  legend->AddEntry(c3,"power","l");
  legend->AddEntry(cmain,"NKFloor","l");
  legend->AddEntry(cfall,"fall fac","l");
  legend->SetTextSize(0.05);
  legend->Draw();
  //c4->Print("comb_all3k2.png");
  c4->Print(Form("comb_all3k2_ntrk%d.png",limit));

  //---------------------------------------------------------------------------------------------------------

  TGraph* c32 = new TGraph (limit, num, o2);
  c32->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  c32->SetLineStyle(3); // RB - added this to make it a bit easier to see under the fit
  c32->SetLineColor(kRed);
  c32->Draw("al");
  c32->SetMaximum(1);
  c32->SetMinimum(1e-8);
  TGraph* cfall2 = new TGraph (limit, num, falling2);
  cfall2->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  cfall2->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  cfall2->SetLineColor(kBlue);
  cfall2->Draw("l");
  TGraph* cmain2 = new TGraph (limit, num, NfloorNchooseK2);
  cmain2->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  cmain2->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  cmain2->SetLineColor(kGreen);
  cmain2->Draw("l");

  TLegend* legend2 = new TLegend(0.68,0.68,0.88,0.88);
  legend2->SetHeader("k = 4"); // copy this as needed
  legend2->AddEntry(c3,"power","l");
  legend2->AddEntry(cmain,"NKFloor","l");
  legend2->AddEntry(cfall,"fall fac","l");
  legend2->SetTextSize(0.05);
  legend2->Draw();
  //c4->Print("comb_all3k4.png");
  c4->Print(Form("comb_all3k4_ntrk%d.png",limit));

  c32->SetMinimum(1e-10);
  c4->SetLogy();
  //c4->Print("comb_all3k4_log.png");
  c4->Print(Form("comb_all3k4_log_ntrk%d.png",limit));

  //----------------------------------------------------------------------------------------------------------------------


  TGraph* c33 = new TGraph (limit, num, o3);
  c33->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  c33->SetLineStyle(3); // RB - added this to make it a bit easier to see under the fit
  c33->SetLineColor(kRed);
  c33->Draw("al");
  c33->SetMaximum(1);
  c33->SetMinimum(1e-12);
  TGraph* cfall3 = new TGraph (limit, num, falling3);
  cfall3->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  cfall3->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  cfall3->SetLineColor(kBlue);
  cfall3->Draw("l");
  TGraph* cmain3 = new TGraph (limit, num, NfloorNchooseK3);
  cmain3->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  cmain3->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  cmain3->SetLineColor(kGreen);
  cmain3->Draw("l");

  TLegend* legend3 = new TLegend(0.68,0.68,0.88,0.88);
  legend3->SetHeader("k = 6"); // copy this as needed
  legend3->AddEntry(c3,"power","l");
  legend3->AddEntry(cmain,"NKFloor","l");
  legend3->AddEntry(cfall,"fall fac","l");
  legend3->SetTextSize(0.05);
  legend3->Draw();
  //c4->Print("comb_all3k6.png");
  c4->Print(Form("comb_all3k6_ntrk%d.png",limit));

  c33->SetMinimum(1e-12);
  c4->SetLogy();
  //c4->Print("comb_all3k6_log.png");
  c4->Print(Form("comb_all3k6_log_ntrk%d.png",limit));

  //--------------------------------------------------------------------------------------------------------------
  TGraph* c34 = new TGraph (limit, num, o4);
  c34->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  c34->SetLineStyle(3); // RB - added this to make it a bit easier to see under the fit
  c34->SetLineColor(kRed);
  c34->Draw("al");
  c34->SetMaximum(1);
  c34->SetMinimum(1e-14);
  TGraph* cfall4 = new TGraph (limit, num, falling4);
  cfall4->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  cfall4->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  cfall4->SetLineColor(kBlue);
  cfall4->Draw("l");
  TGraph* cmain4 = new TGraph (limit, num, NfloorNchooseK4);
  cmain4->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  cmain4->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  cmain4->SetLineColor(kGreen);
  cmain4->Draw("l");

  TLegend* legend4 = new TLegend(0.68,0.68,0.88,0.88);
  legend4->SetHeader("k = 8"); // copy this as needed
  legend4->AddEntry(c3,"power","l");
  legend4->AddEntry(cmain,"NKFloor","l");
  legend4->AddEntry(cfall,"fall fac","l");
  legend4->SetTextSize(0.05);
  legend4->Draw();
  //c4->Print("comb_all3k8.png");
  c4->Print(Form("comb_all3k8_ntrk%d.png",limit));

  c34->SetMinimum(1e-12);
  c4->SetLogy();
  //c4->Print("comb_all3k8_log.png");
  c4->Print(Form("comb_all3k8_ntrk%dlog.png",limit));

}//Fucntion3Gra
