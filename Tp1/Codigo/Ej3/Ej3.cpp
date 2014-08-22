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






bool backtracking(TablaDePeligrosidad &tab, vector <int> &solParcialCamiones,vector <int> &solFinalCamiones)
{
  int resultadoCheck;
  for(int i = 0; i < tab.n; i++)
  {
    solParcialCamiones.push_back(i);
    resultadoCheck = check(tab,solParcialCamiones,solFinalCamiones);
    
    
    if(resultadoCheck == 1)
      backtracking(tab,solParcialCamiones,solFinalCamiones);
    if(resultadoCheck == 2)
    {
      solFinalCamiones = solParcialCamiones;
      return true;
    }
    if(resultadoCheck == 3)
      return false;
    
    
    solParcialCamiones.pop_back();
  }
  return false; // solo para completar casos, es imposible que se llegue a este punto.
}


//Si la solucion parcial usa mas camiones que la mejor solucion, podo.

bool solucionFinalUsaMenosCamiones(vector<int> &solParcialCamiones ,vector <int> &solFinalCamiones)
{
  int maxSolPar = solParcialCamiones[1];
  int maxSolFin = solFinalCamiones[1];
  for(int i = 0; i < solParcialCamiones.size(); i++)
    if(maxSolPar < solParcialCamiones[i])
      maxSolPar = solParcialCamiones[i];
    
  for(int i = 0; i < solFinalCamiones.size(); i++)
    if(maxSolFin < solFinalCamiones[i])
      maxSolFin = solFinalCamiones[i];
    
  if(maxSolFin < maxSolPar)
    return true;
  return false;
}

bool cotaDePeligrosidadSobrepasada(TablaDePeligrosidad &tab, vector<int> &solParcialCamiones)
{
  vector<int> peligrosidad;
  for(int i = 0; i < solParcialCamiones.size(); i++) //seteo los n valores del vector en 0.
    peligrosidad.push_back(0);

  for(int i = 0; i < solParcialCamiones.size(); i++) //determino la peligrosidad por camion.
    for(int j = i + 1; j< solParcialCamiones.size() ; j++)
      if(solParcialCamiones[i] == solParcialCamiones[j])
	peligrosidad[solParcialCamiones[i]] =+ tab.peligrosidad[i][j];
  
  for(int i = 0; i < solParcialCamiones.size(); i++)
    if(tab.m < peligrosidad[i])
      return true;
  return false;
}

// check:
// si retorna 0 no es sol valida
// si retorna 1, es valida pero falta agregar camiones
// si retorna 3 la solucion anterior usa menos camiones
// si retorna 2 es solucion valida
int check(TablaDePeligrosidad &tab, vector<int> &solParcialCamiones ,vector <int> &solFinalCamiones)
{
  
  if(solucionFinalUsaMenosCamiones(solParcialCamiones,solFinalCamiones))
    return 3;
  
  if(cotaDePeligrosidadSobrepasada(tab,solParcialCamiones))
    return 0;
  
  if(tab.n == solParcialCamiones.size())
    return 2;
  
  return 1;
}

void imprimirResultado(vector<int> solParcialCamiones)
{
 int max = solParcialCamiones[0];
 for(int i = 1; i < solParcialCamiones.size(); i++)
   if(solParcialCamiones[i] > max)
     max = solParcialCamiones[i];
 cout << max + 1<< " ";
 for(int i = 0; i < solParcialCamiones.size(); i++)
   cout << solParcialCamiones[i] + 1 << " ";
 cout << endl;
}

void inicializarPeorSol(vector<int> &sol,int n)
{
  sol.clear();
  for(int i = 0; i < n; i++)
      sol.push_back(i);
}


int main()
{
  while(cin.peek() != 48) 
  {
    TablaDePeligrosidad tab = TablaDePeligrosidad();
    vector<int> solParcialCamiones;
    vector<int> solFinalCamiones;
    inicializarPeorSol(solFinalCamiones,tab.n);
    
    
    //auto start = chrono::high_resolution_clock::now();
    bool sol = backtracking(tab, solParcialCamiones,solFinalCamiones);
    //auto finish = chrono::high_resolution_clock::now();
    //cout << chrono::duration_cast<chrono::microseconds>(finish - start).count() << endl;
    solParcialCamiones.clear();
    imprimirResultado(solFinalCamiones);
    cin.get();
  }
  return 0;
}