#include "Ej3.h"


// de la manera en que esta creado el algoritmo,
// busca la solucion de abajo para arriba
// esto signigica, al principio intenta meter todos los productos en el camion 1
// si no, mete uno en el camion 2, y asi...
// todavía tengo que justificar, que en el momento de parar, entrega la mejor solo
// pero a simple vista me parece que falta algo.

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
  if(n == 0)
    exit(0);
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
    
    if(resultadoCheck == 2)
      return true;
    if(resultadoCheck == 1)
      backtracking(tab,camiones);
    
    camiones.pop_back();
  }
  return false; // solo para completar casos, es imposible que se llegue a este punto.
}

// check si retorna 2 es solucion valida
// si retorna 1, es valida pero falta agregar camiones
// si retorna 0 no es sol valida

int check(TablaDePeligrosidad &tab, vector<int> &camiones)
{
  vector<int> peligrosidad;
  for(int i = 0; i < camiones.size(); i++) //seteo los n valores del vector en 0.
    peligrosidad.push_back(0);

  for(int i = 0; i < camiones.size(); i++) //determino la peligrosidad por camion.
    for(int j = i + 1; j< camiones.size() ; j++)
      if(camiones[i] == camiones[j])
	peligrosidad[camiones[i]] =+ tab.peligrosidad[i][j];
  
  for(int i = 0; i < camiones.size(); i++)
    if(tab.m < peligrosidad[i])
      return 0;
  if(tab.n == camiones.size())
    return 2;
  return 1;
}

void imprimirResultado(vector<int> camiones)
{
 int max = camiones[0];
 for(int i = 1; i < camiones.size(); i++)
   if(camiones[i] > max)
     max = camiones[i];
 cout << max + 1<< " ";
 for(int i = 0; i < camiones.size(); i++)
   cout << camiones[i] + 1 << " ";
 cout << endl;
}

int main()
{
  while(cin.peek() != 48) 
  {
    TablaDePeligrosidad tab = TablaDePeligrosidad();
    vector<int> camiones;
    
    //auto start = chrono::high_resolution_clock::now();
    bool sol = backtracking(tab, camiones);
    //auto finish = chrono::high_resolution_clock::now();
    //cout << chrono::duration_cast<chrono::microseconds>(finish - start).count() << endl;
    imprimirResultado(camiones);
    cin.get();
  }
  return 0;
}