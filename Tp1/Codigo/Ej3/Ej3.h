#include <iostream>     // std::cout, std::cin
#include <algorithm>    // std::sort
#include <vector>       // std::vector

//#include <chrono>

using namespace std;

/*class TablaDePeligrosidad{
public:
  int  n,m;
  vector<vector <int> > peligrosidad;
  TablaDePeligrosidad();
  ~TablaDePeligrosidad()
  {
    cout << "mama mia" << endl;
    for(int i = 0; i < peligrosidad.size(); i++) 
      cout << "mama mia!!! : " << i << endl;
      peligrosidad[i].clear(); 
    peligrosidad.clear();
  };
}; 
*/
struct tablaDePeligrosidad
{
  int  n,m;
  vector<vector <int> > peligrosidad;
};

void imprimirResultado(vector<int> camiones);
int check(tablaDePeligrosidad &tab, vector<int> &solParcialCamiones ,vector <int> &solFinalCamiones);
bool backtracking(tablaDePeligrosidad &tab, vector<int> &camiones,vector <int> &solFinalCamiones);