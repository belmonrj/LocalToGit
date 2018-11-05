{
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
  }
 int NDK(int n, int r)
  {
   if (r == 0) return 0;
   // avoiding a collapse
   {

     ifstream fin("list_of_numbers");
     // printing from a file
     
     int var1 ["numberofn"] , var2 ["numberofr"];
     //setting the number of array items to the inputs; need to write something to detect this 
     
       {
	 fin >> var1[i] >> var2[i];
	 cout << var1[i] << " " << var2[i] << "\n";
       }
     fin.close();

   }

  }

   {
     TCanvas* c1 = new TCanvas();
     ifstream fin("list_of_numbers");
     int var1 ["numberofn"] , var2 ["numberofr"];
     for ( int i = 0; i < 10; ++i )
   
       {
	 fin >> var1[i] >> var2[i];
	 cout << var1[i] << " " << var2[i] << "\n";
       }
     
     fin.close();
     TGraph* tg = new TGraph ("numberofn", var1, var2);
     tg->Draw("al");
     TF1* f1 = new TF1("f1","pol1");
     tg->Fit("f1","","",0,("numberofn"*"numberofr");
     c1->Print("patharray1.png");
   }

