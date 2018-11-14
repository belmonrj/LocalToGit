const int maxn =10;

void generate();
int NCK(int,int);
int NDK(int,int);
long long NFAC(int,int);
long long KFAC(int,int);
long long NMINKFAC(int,int);
long long OPERTOT(long long, long long, long long);



void generate()
{

  ofstream fout("list_of_numbers");
  for ( int i = 0; i < maxn; ++i )
    {
      fout << i << " " << 2*i << endl;
    }

} // void generate


//void Function2()
//{
// printf();
//}//void function2
//-----------------------------------------------------

int NDK(int n, int k)
{
  if (k == 0) return 1;

  else return n/k;
}// NDK
//--------------------------------------------------------
long long NFAC(int n, int k)
{

  unsigned long long factorialn = 1;

  for(int i = 1; i <=n; ++i)
    {
      factorialn *= i;
    }
  return factorialn;
}//N!
//----------------------------------------------------------

long long KFAC(int n, int k)
{
  unsigned long long factorialk = 1;
  for(int i = 1; i <= n; ++i)
    {
      factorialk *= i;
    }
  return factorialk;
}//K!
//-----------------------------------------------------

long long NMINKFAC(int n, int k)
{
  unsigned long long factorialj = 1;
  int j = n - k;
  for(int i = 1; i <= j; ++i)
    {
      factorialj *= i;
    }
  return factorialj;
}//J!
//-----------------------------------------------------

long long OPERTTOT(long long factorialn, long long factorialk, long long factorialj)
{
  return factorialn/( factorialk * factorialj);
}//f(n,k) = N! / K!(N-K)!

void Function2Gra()

{

  TCanvas* c2 = new TCanvas();

  generate();  // RB - calls function above to make list_of_numbers

  ifstream fin("list_of_numbers");
  int var1 [maxn] , var2 [maxn];
  int NDK[maxn];// defined as dividing array
  long long NFAC[maxn];// defined as dividing array
  long long KFAC[maxn];// double makes this a float
  long long OPERTOT[maxn];
  int num[maxn];
  //  int NC4[maxn];// defined as choosing array
  // int ND4[maxn];// defined as dividing array
  // double OPER4[maxn];// output array for the operation d     \
  //efined below
  // int NC6[maxn];// defined as choosing array
  // int ND6[maxn];// defined as dividing array
  // double OPER6[maxn];// output array for the operation d     \
  //efined below
  //} // matches Function2Gra
  for ( int l = 0; l < maxn; ++l ) // defines the loop as
    // repeating until we reach maxn
    {

      num[l] = l;// assigned number of total particles

      // choose 2 to start

      NDK[l] = NDK(l,2);

      NFAC[l] = NFAC(l,2);

      KFAC[l] = KFAC(l,2);

      NMINKFAC[l] = NMINKFAC(l,2);

      OPERTOT[l] = OPERTOT(l,2);

      cout << l << " " << NDK[l] << " " << NFAC[l] << " " << KFAC[l] << " " << NMINKFAC[l] << " " << OPERTOT[l] << " " <<endl;

    } // for loop
  fin.close();
} // function2gra


