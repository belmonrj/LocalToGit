using namespace std;

double * tGrapherX(int a)
{
  static double x[1000];
  Int_t n = 1000;

// loop for maths
  for (Int_t i = 0; i<n; ++i)
    {
      x[i] = (i+1.0);
    }

  return x;
}



double * tGrapherY(int a)
{
  static double y[1000];
  Int_t n = 1000;

// loop for maths
  for (Int_t i = 0; i<n; ++i)
    {
      y[i] = pow((i),a)/pow((i+1),a);
    }

  return y;
}


void NGrapher()
{
  // Objects : TCanvas, TGraph array
  TCanvas *c1 = new TCanvas("c1","example");
  TGraph* arr[4];

  // array lengths and constant declarations
  int j[4] = {1, 3, 5, 7};
  int n = 1000;

  //loop for the outputs in the array
  for (int i = 0; i < 4; ++i)
    {
      arr[i] = new TGraph(n, tGrapherX(j[i]), tGrapherY(j[i]));
    }


  //Coloring and storage style
  EColor z[4] = {kBlue, kGreen, kRed, kOrange};
  for (int q = 0; q<4; ++q)
    {
      arr[q]->SetLineWidth(2); // RB - added this to make it a bit easier to see under the fit             
      arr[q]->SetLineStyle(2); // RB - added this to make it a bit easier to see under the fit             
      arr[q]->SetLineColor(z[q]);
      arr[q]->Draw("l");
      arr[q]->Draw();
    }

  for (int i = 0; i < 4; ++i)
    {
      arr[i]->Paint();
    }

  c1->Print();

  return;
}

