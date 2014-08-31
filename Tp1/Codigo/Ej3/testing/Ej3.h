#include <iostream>     // std::cout, std::cin
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <chrono>

using namespace std;

struct tablaDePeligrosidad
{
  int  n,m;
  vector<vector <int> > peligrosidad;
};

void imprimirResultado(vector<int> camiones);
int check(tablaDePeligrosidad *tab, vector<int> &solParcialCamiones ,vector <int> &solFinalCamiones);
bool backtracking(tablaDePeligrosidad *tab, vector<int> &camiones,vector <int> &solFinalCamiones);
