using namespace std;

double * tGrapherX(int a)
{
  static double x[1000];
  int n = 1000;

// loop for maths
   for (int i = 0; i<n; ++i)
     {
       x[i] = i+1.0;
     }


   return x;
}

double NTop(int n, int minus)
{
  double x = 1.0;
  for(int i = 1; i <= minus; ++i)
    {
      x = x * (n - i);
    }
  return x;
}

double * tGrapherY(int a)
{
  static double y[1000];
  Int_t n = 1000;

// loop for maths
  for (int i = 0; i<n; ++i)
    {
      y[i] = NTop(i,a)/pow((i+1),a);
    }

  return y;
}


void NGrapher()
{
  // Objects : TCanvas, TGraph array
  TCanvas *c1 = new TCanvas("c1","example");
  TGraph* arr[4];
  TGraph* arrTwo[4];

  // array lengths and constant declarations
  int j[4] = {1, 3, 5, 7};
  int n = 1000;

  //loop for the outputs in the array
  for (int i = 0; i < 4; ++i)
    {
      arr[i] = new TGraph(n, tGrapherX(j[i]), tGrapherY(j[i]));
      //      arrTwo[i] = new TGraph(n, tGrapherX(j[i])/((double *)(j[i]+1)), tGrapherY(j[i]));
    }


  //Coloring and storage style
  EColor z[4] = {kBlue, kGreen, kRed, kOrange};
  for (int q = 0; q<4; ++q)
    {
      c1->Clear();
      arr[q]->SetLineWidth(2);
      arr[q]->SetLineStyle(2);
      arr[q]->SetLineColor(z[q]);
      arr[q]->GetXaxis()->SetTitle("Multiplicity");
      arr[q]->GetYaxis()->SetTitle("Ratio");
      arr[q]->GetXaxis()->SetLimits(0.0,1000.0);
      arr[q]->SetMinimum(0.0);
      arr[q]->SetMaximum(1.1);
      arr[q]->Draw();
      c1->Print(Form("CombinatoricFigures/ngrapher_single_%d.png",q));
    }

  for (int i = 0; i < 4; ++i)
    {
      arr[i]->Draw();
    }
  TLegend* leg = new TLegend(0.68,0.18,0.88,0.38);
  leg->AddEntry(arr[0],"arr0","l");
  leg->AddEntry(arr[1],"arr1","l");
  leg->AddEntry(arr[2],"arr2","l");
  leg->AddEntry(arr[3],"arr3","l");
  leg->Draw();

  c1->Print("CombinatoricFigures/ngrapher_all.png");

  return;
}

