#include "Ej3.h"

using namespace std;

// n-> cantidad de productos a transportar
// m-> nivel de peligrosidad
// n-1 lineas:
// 	h1,2 h1,3 h1,4 ... h1, n
//	h2,3 h2,4 h1,5 ... h2, n
//	...
//	h(n-1),n


TablaDePeligrosidad::TablaDePeligrosidad()
{
  cin >> n;
  cin >> m;
  peligrosidad.resize(n-1);
  for (int i = 0; i < n; i++)
  {
    peligrosidad[i].resize(n-i);
    for(int j = 0; j < n-i; j++)
      cin >> peligrosidad[i][j];
  }
}






bool backtracking(TablaDePeligrosidad &tab, vector <int> &camiones)
{
  int resultadoCheck;
  for(int i = 0; i < tab.n; i++)
  {
    
    camiones.push_back(i);
    resultadoCheck = check(tab,camiones);
    if(resultadoCheck = 2)
      return true;
    if(resultadoCheck = 1)
      backtracking(tab,camiones);
  }
  return false; // solo para completar casos, es imposible que se llegue a este punto.
}

// check si retorna 2 es solucion valida
// si retorna 1, es valida pero falta agregar camiones
// si retorna 0 no es sol valida

int check(TablaDePeligrosidad &tab, vector<int> &camiones)
{
  
  // esta funcion es la muelte.
  vector<int> peligrosidad;
  peligrosidad.resize(tab.n);
  vector<vector<int> > productosQueVanEnMismoCamion;
  productosQueVanEnMismoCamion.resize(tab.n);
  for(int w = 0; w < camiones.size(); w++)
  {
      productosQueVanEnMismoCamion[camiones[w]].push_back(w);
  }
  // 	   p1 p2 p3 p4
  //camion 1  2  1  3
  for(int i = 0;  i < productosQueVanEnMismoCamion.size(); i++)
    for(int j = 0;j < productosQueVanEnMismoCamion[i].size()-1; j++)
    {
      cout << i << endl;
      //cout << j << endl;
      peligrosidad[i] = tab.peligrosidad[productosQueVanEnMismoCamion[i][j]] [productosQueVanEnMismoCamion[i][j+1]];
    }
  for(int i = 0; i < tab.n; i++)
    if(tab.m < peligrosidad[i])
      return 0;
  if(tab.n == camiones.size())
    return 2;
  return 1;
  
  //	   	c1 	c2 	c3 	c4
  //producto	1  	2  	4  	-
  //		3
  //peligr:	h1,3
  
}

void imprimirResultado(vector<int> camiones)
{
 int max = camiones[0];
 for(int i = 1; i < camiones.size(); i++)
   if(camiones[i] > max)
     max = camiones[i];
  cout << max;
 for(int i = 1; i < camiones.size(); i++)
   cout << camiones[i] << endl;
}

int main()
{
  TablaDePeligrosidad tab = TablaDePeligrosidad();
  vector<int> camiones;
  
  cout << "tabla terminada!" << endl;
  //auto start = chrono::high_resolution_clock::now();
  bool sol = backtracking(tab, camiones);
  //auto finish = chrono::high_resolution_clock::now();
  //cout << chrono::duration_cast<chrono::microseconds>(finish - start).count() << endl;
  imprimirResultado(camiones);
  return 0;
}