const int maxn =25;

void generate();
long long NFAC(int);
long long NDIVKFAC(long long, long long);


void generate()
{
  ofstream fout("list_of_numbers");
  for ( int i = 0; i < maxn; ++i )
    {
      fout << i << " " << 2*i << endl;
    }

} // void generate



long long NFAC(int n)
{

  long long factorialn = 1;

  for (int i = 1; i <=n; ++i)
    {
      factorialn *= i;
    }
  return factorialn;
} // N!
//---------------------------------------------------------

long long NFACDIVKFAC(long long NFAC, long long KFAC)
{
  return NFAC/KFAC;
}// N!/K!

void Function3()
{

  TCanvas* c3 = new TCanvas();

  generate();

  ifstream fin("list_of_numbers");
  long long NFACa[maxn];
  long long NFACDIVKFACa[maxn];



  for ( int j = 0; j < maxn; ++j)
    {

      NFACa[j] = NFAC(j);
      KFACa[j] = KFAC(2);
      NFACDIVKFACa[j] = NFACDIVKFAC(NFACa[j], KFACa[j]);

      cout << j << " " << NFACa[j] << " " << KFACa[j] << " " << NFACDIVKFACa[j] << " " << endl;

    }
  // for loop
  fin.close();
}//Fucntion3Gra
