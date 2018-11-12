const int maxn =25;


// RB - we haven't talked about this yet but you need function protoypes at the top
void generate();
int NCK(int,int);
int NDK(int,int);



// RB - I added this function so I could test the code with the number list
void generate()
{

  ofstream fout("list_of_numbers");
  for ( int i = 0; i < maxn; ++i )
    {
      fout << i << " " << 2*i << endl;
    }

} // void generate



int NCK(int n, int r)
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
} // int NCK // RB - always make a comment indicating the end of a function, it makes the code much more readable



// RB - always put several blank lines in between functions, it makes the code much more readable
int NDK(int n, int r)
{
  return n/r;
} // int NDK



// RB - you didn't name this and it needs a name (that matches the filename) to be able to be executed
void nchoosek_var1_var2()
{

  TCanvas* c1 = new TCanvas();

  generate();  // RB - calls function above to make list_of_numbers

  ifstream fin("list_of_numbers");
  //int var1 ["numberofn"] , var2 ["numberofr"]; // RB - you can't do this, see comments above
  int var1 [maxn] , var2 [maxn];

  int NC2[maxn];// defined as choosing array
  int ND2[maxn];// defined as dividing array
  double OPER2[maxn];// output array for the operation defined below // double makes this a float and not an integer
  int NC4[maxn];// defined as choosing array
  int ND4[maxn];// defined as dividing array
  double OPER4[maxn];// output array for the operation defined below
  int NC6[maxn];// defined as choosing array
  int ND6[maxn];// defined as dividing array
  double OPER6[maxn];// output array for the operation defined below
  int NC8[maxn];// defined as choosing array
  int ND8[maxn];// defined as dividing array
  double OPER8[maxn];// output array for the operation defined below
  double num[maxn]; // new array for number of particles for which we are studying the dilution (what we want to prove/disprove)
  for ( int i = 0; i < maxn; ++i )// defines the loop as repeating until we reach maxn
    {
      num[i] = i;// assigned number of total particles
      
      // choose 2 to start

      NC2[i] = NCK(i,2); // assigns element i of array NC2(choosing array) to the function output of NCK of i and 2
      
      ND2[i] = NDK(i,2); // assigns element i of array ND2(dividing array) to the function output of NDK of i and 2

      OPER2[i] =(double)ND2[i]/(double)NC2[i]; // applies divison operation from congruent elements in ND2 and NC2 (the original goal)
     
      cout << i << " " << NC2[i] << " " << ND2[i] << " " << OPER2[i] << endl;
      
      // --- now choose 4
	
      NC4[i] = NCK(i,4); // assigns element i of array NC4(choosing array) to the function output of NCK of i and 4

      ND4[i] = NDK(i,4); // assigns element i of array ND4(dividing array) to the function output of NDK of i and 4

      OPER4[i] = ND4[i]/NC4[i]; // applies divison operation from congruent elements in ND4 and NC4 (the original goal)

      // --- now choose 6

      NC6[i] = NCK(i,6); // assigns element i of array NC6(choosing array) to the function output of NCK of i and 6

      ND6[i] = NDK(i,6); // assigns element i of array ND6(dividing array) to the function output of NDK of i and 6

      OPER6[i] = ND6[i]/NC6[i]; // applies divison operation from congruent elements in ND6 and NC6 (the original goal)

      // --- now choose 8

      NC8[i] = NCK(i,8); // assigns element i of array NC8(choosing array) to the function output of NCK of i and 8

      ND8[i] = NDK(i,8); // assigns element i of array ND8(dividing array) to the function output of NDK of i and 8

      OPER8[i] = ND8[i]/NC8[i]; // applies divison operation from congruent elements in ND8 and NC8 (the original goal)

    }
  fin.close();


  // RB - see comments above; I guess you want to pass "numberofn" as an argument to this function here?
  // RB - but I can't tell why or what you mean by it
  TGraph* tg2 = new TGraph (maxn, num, OPER2);
  tg2->SetLineWidth(4); // RB - added this to make it a bit easier to see under the fit
  tg2->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  tg2->Draw("al");

} // end of nchoosek_var1_var2

