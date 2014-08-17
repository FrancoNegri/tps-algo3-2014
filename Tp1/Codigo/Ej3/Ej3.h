#include <iostream>     // std::cout, std::cin
#include <algorithm>    // std::sort
#include <vector>       // std::vector

//#include <chrono>

using namespace std;

class TablaDePeligrosidad{
public:
  int  n,m;
  vector<vector <int> > peligrosidad;
  TablaDePeligrosidad();
  ~TablaDePeligrosidad(){};
}; 

void imprimirResultado(vector<int> camiones);
int check(TablaDePeligrosidad &tab, vector<int> &camiones);
bool backtracking(TablaDePeligrosidad &tab, vector<int> &camiones);