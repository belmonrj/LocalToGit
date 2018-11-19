const int maxn =25;

void generate();
long long factorial(int);
long long factorial(int, int);


void generate()
{
  ofstream fout("list_of_numbers");
  for ( int i = 0; i < maxn; ++i )
    {
      fout << i << " " << 2*i << endl;
    }

} // void generate



long long factorial(int n)
{

  long long factorialn = 1;

  for (int i = 1; i <=n; ++i)
    {
      factorialn *= i;
    }
  return factorialn;
} // N!

long long factorial(int n, int stop)
{

  long long factorialn = n;
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


void FallinFac1()
{

  TCanvas* c4 = new TCanvas();

  generate(); 
  double o[maxn]={0};
  ifstream fin("list_of_numbers");
  long long factoriala[maxn];
  double num[maxn];

  long long NM1F[maxn];
  long long KM1F[maxn];
  long long NM1FTOK[maxn];

  for ( int j = 0; j < maxn; ++j)
    {
      num[j] = j;
      int k = 2;
      if ( j < k ) continue;
      NM1F[j] = factorial( j - 1 );//setting it down to just one line from factorial
      KM1F[j] = factorial( 1 );//for now to test the code
      NM1FTOK[j] = ( pow (j-1, k-1));
      //cout << "NM1FTOK is " << NM1FTOK[j] << endl;
      o[j] = ((float)KM1F[j] /(float)NM1FTOK[j]);
      // cout << j << " " << NFACa[j] << " " << NM1F[j] << " " << NM1FTOK[j] << " "
      //   << " The number of particle correlations is expected to be proportional to the number of particles in the event. thus" <<
      //"K minus one factorial, divided by n to the k minus one, is" <<  o << " " << endl;

    }
  // for loop
  cout << factorial(10,2) << " " << factorial(10,3) << " "  << factorial(10,10) << " "  << factorial(10) << endl;
  fin.close();
 
  TGraph* c3 = new TGraph (maxn, num, o);
  c3->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit                                                                                              
  c3->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit                                                                                              
  c3->SetLineColor(kRed);
  c3->Draw("al");
  c4->Print("FallinFac1.png");
 
  // TGraph* tgm2 = new TGraph (maxn, );
  // tg2->SetMarkerStyle(kOpenCircle); // Set to points and not a line, so that we can see the discrete nature of the function                                                          
  // tg2->SetMarkerColor(kBlack); 
  // tg2->Draw("p");
  // c1->Print("FallinFac1.png");
}//Fucntion3Gra
