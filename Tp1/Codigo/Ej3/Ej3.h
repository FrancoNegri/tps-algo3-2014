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
  ~TablaDePeligrosidad()
  {
    cout << "mama mia" << endl;
    for(int i = 0; i < peligrosidad.size(); i++) 
	peligrosidad[i].clear(); 
    peligrosidad.clear();
  };
}; 

void imprimirResultado(vector<int> camiones);
int check(TablaDePeligrosidad &tab, vector<int> &solParcialCamiones ,vector <int> &solFinalCamiones);
bool backtracking(TablaDePeligrosidad &tab, vector<int> &camiones,vector <int> &solFinalCamiones);