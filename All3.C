const int maxn =25;

void generate();
double factorial(int);
double factorial(int, int);
double NCK(int, int);

void generate()
{
  ofstream fout("list_of_numbers");
  for ( int i = 0; i < maxn; ++i )
    {
      fout << i << " " << 2*i << endl;
    }

} // void generate



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
void All3()
{

  TCanvas* c4 = new TCanvas();

  generate();
  double o[maxn]={0};
  double falling[maxn]={0};
  ifstream fin("list_of_numbers");
  double factoriala[maxn];
  double num[maxn];

  double NM1F[maxn];
  double KM1F[maxn];
  double NM1FTOK[maxn];
  double NfloorNchooseK[maxn];

  for ( int j = 0; j < maxn; ++j)
    {
      num[j] = j;
      int k = 2;
      if ( j < k ) continue;
      NM1F[j] = factorial( k - 1 );//setting it down to just one line from factorial
      KM1F[j] = factorial( 1 );//for now to test the code
      NM1FTOK[j] = ( pow (j-1, k-1));
      //cout << "NM1FTOK is " << NM1FTOK[j] << endl;
      o[j] = ((float)factorial(k-1)/(float)pow(j, k-1));
      falling[j] = (float)factorial(k-1)/(float)factorial(j-1,k-1);
      // cout << j << " " << NFACa[j] << " " << NM1F[j] << " " << NM1FTOK[j] << " "
      //   << " The number of particle correlations is expected to be proportional to the number of particles in the event. thus" <<
      //"K minus one factorial, divided by n to the k minus one, is" <<  o << " " << endl;



      NfloorNchooseK[j] = (j/k)/((factorial(j))/(factorial(k)*factorial(j - k)));
    }   // for loop



  cout << factorial(10,2) << " " << factorial(10,3) << " "  << factorial(10,10) << " "  << factorial(10) << endl;
  fin.close();

  TGraph* c3 = new TGraph (maxn, num, o);
  c3->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  c3->SetLineStyle(3); // RB - added this to make it a bit easier to see under the fit
  c3->SetLineColor(kRed);
  c3->Draw("al");
  c3->SetMaximum(1);
  c3->SetMinimum(1e-6);
  TGraph* cfall = new TGraph (maxn, num, falling);
  cfall->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  cfall->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  cfall->SetLineColor(kBlue);
  cfall->Draw("l");
  TGraph* cmain = new TGraph (maxn, num, NfloorNchooseK);
  cmain->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit
  cmain->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  cmain->SetLineColor(kGreen);
  cmain->Draw("l");
  TLegend* legend = new TLegend(0.68,0.68,0.88,0.88);
  legend->AddEntry(c3,"power","l");
  legend->AddEntry(cmain,"NKFloor","l");
  legend->AddEntry(cfall,"fall fac","l");
  legend->SetTextSize(0.05);
  legend->Draw();
  c4->Print("comb_all3.png");
  //c4->SetLogy();
  //c4->Print("comb_all3_log.png");

  // TGraph* tgm2 = new TGraph (maxn, );
  // tg2->SetMarkerStyle(kOpenCircle); // Set to points and not a line, so that we can see the discrete nature of the function
  // tg2->SetMarkerColor(kBlack);
  // tg2->Draw("p");
  // c1->Print("FallinFac1.png");
}//Fucntion3Gra
