#include <vector>
#include <math>

using namespace std;

int AlgoMatrix(int n)
{
  vector<vector<int> > AlgoID;
///////////
  vector<vector<int> > AlgoId(n, vector<int>(n,0));
  for( int i = 0; i < n; ++i )
    AlgoID[i][i] = 1;
  return AlgoID;
}

int main(int n, int m)
{
  return AlgoID[ceil(m/2)][ceil(n/2)];
}
