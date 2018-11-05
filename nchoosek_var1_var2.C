const int maxn = 10;


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
  if (r == 0) return 0; // RB - very smart to have safety checks like this
  // avoiding a collapse
  //{ // RB - I don't know why you have a brace here

  ifstream fin("list_of_numbers");
  // printing from a file

  //int var1 ["numberofn"] , var2 ["numberofr"];
  // RB - you can't use quotes to indicate a variable name, nor can you use a variable you haven't yet defined
  // RB - and why would you want var1 and var2 to have different sizes?
  int var1[maxn], var2[maxn];
  //setting the number of array items to the inputs; need to write something to detect this
  for ( int i = 0; i < maxn; ++i ) // RB - I guess you want to have a for loop here?
    {
      fin >> var1[i] >> var2[i];
      cout << var1[i] << " " << var2[i] << "\n";
    }
  fin.close();

  //} RB - I don't know why you have a brace here

  // RB - you don't do a return here, but ROOT allows it to run and just issues a warning
  // RB - however, I suspect you intended to return a value

} // int NDK



// RB - you didn't name this and it needs a name (that matches the filename) to be able to be executed
void nchoosek_var1_var2()
{

  TCanvas* c1 = new TCanvas();

  generate();  // RB - calls function above to make list_of_numbers

  ifstream fin("list_of_numbers");
  //int var1 ["numberofn"] , var2 ["numberofr"]; // RB - you can't do this, see comments above
  int var1 [maxn] , var2 [maxn];
  for ( int i = 0; i < maxn; ++i )
    // RB - don't put blank lines in between the for statement and the brackets
    {
      fin >> var1[i] >> var2[i];
      cout << var1[i] << " " << var2[i] << "\n";
    }
  fin.close();


  // RB - see comments above; I guess you want to pass "numberofn" as an argument to this function here?
  // RB - but I can't tell why or what you mean by it
  TGraph* tg = new TGraph (maxn, var1, var2);
  tg->SetLineWidth(4); // RB - added this to make it a bit easier to see under the fit
  tg->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit
  tg->Draw("al");

  TF1* f1 = new TF1("f1","pol1");
  // RB - I can't tell what you're trying to do here; I guess you want to pass numberofn and numberofr
  // RB - as function arguments.  I don't know what these are supposed to mean, but I doubt that's actually
  // RB - the fit range you want to use...
  //tg->Fit("f1","","",0,("numberofn"*"numberofr");
  double fitmax = (double)maxn;
  tg->Fit("f1","","",0,fitmax);
  c1->Print("patharray1.png");



  // RB - just an FYI, I'll show you how to call your function, assign variables with it, etc.
  // RB - you can initialize variables using the function like this:
  int b5c1 = NCK(5,1);
  int b5c2 = NCK(5,2);
  cout << "5 choose 1 is " << b5c1 << endl;
  cout << "5 choose 2 is " << b5c2 << endl;
  // RB - you can also call the fucntion directly like this
  cout << "5 choose 3 is " << NCK(5,3) << endl;
  cout << "5 choose 4 is " << NCK(5,4) << endl;
  cout << "5 choose 5 is " << NCK(5,5) << endl;
  // RB - you can also put it in a loop if you like
  cout << "-------------------------" << endl;
  cout << "Now doing nested for loop" << endl;
  for ( int i = 0; i < 7; ++i )
    {
      for ( int j = 0; j <= i; ++j )
        {
          cout << i << " choose " << j << " is " << NCK(i,j) << endl;
        }
    }
  cout << "-------------------------------" << endl;
  cout << "Now doing nested for loop again" << endl;
  for ( int i = 0; i < 7; ++i )
    {
      for ( int j = 0; j <= i; ++j )
        {
          cout << NCK(i,j) << " ";
        }
      cout << endl;
    }

} // end of nchoosek_var1_var2

