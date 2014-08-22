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


void imprimir_tab(tablaDePeligrosidad &tab)
{
 for (int i = 0; i < tab.peligrosidad.size(); ++i)
 {
   vector<int> v = tab.peligrosidad[i];
   for (int j = 0; j < v.size(); ++j)
   {
     cout << tab.peligrosidad[i][j] << " " ;
   }
   cout << endl;
 }
 cout << endl;
}



void InicializarTablaDePeligrosidad(tablaDePeligrosidad *tab)
{
  cin >> tab->n;
  if(tab->n == 0)
    exit(0);
  cin >> tab->m;
  //tab->peligrosidad.resize(tab->n-1);


  for (int i = 0; i < tab->n-1; i++)
  {
    vector<int> acum; 
    
    /*tab->peligrosidad[i].resize( (tab->n) - i);*/
    for(int j = 0; j < tab->n-i-1; j++) {
      int valor;
      cin >> valor;
      acum.push_back(valor);
/*      cin >> tab->peligrosidad[i][j];*/
    }
    tab->peligrosidad.push_back(acum);
  }
}




bool backtracking(tablaDePeligrosidad &tab, vector <int> &solParcialCamiones,vector <int> &solFinalCamiones)
{
  int resultadoCheck;
  resultadoCheck = check(tab,solParcialCamiones,solFinalCamiones);
  imprimirResultado(solParcialCamiones);
  imprimir_tab(tab);

  //es una olucion
  if(resultadoCheck == 2)
  {
      solFinalCamiones = solParcialCamiones;
      return true;
  }
  // solParcial usa mas camiones que solFinal
  if(resultadoCheck == 3) {
    return false;
  }

  //Me faltan asignar un producto a un camion
  for(int i = 0; i < tab.n; i++)
  {
    solParcialCamiones.push_back(i);
    backtracking(tab,solParcialCamiones,solFinalCamiones);
    solParcialCamiones.pop_back();
  }
  return false; // solo para completar casos, es imposible que se llegue a este punto.
}


//Si la solucion parcial usa mas camiones que la mejor solucion, podo.

bool solucionFinalUsaMenosCamiones(vector<int> &solParcialCamiones ,vector <int> &solFinalCamiones)
{
  int maxSolPar = solParcialCamiones[0];
  int maxSolFin = solFinalCamiones[0];
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

bool cotaDePeligrosidadSobrepasada(tablaDePeligrosidad &tab, vector<int> &solParcialCamiones)
{
  
  vector<int> peligrosidad;
  for(int k = 0; k < solParcialCamiones.size(); k++) {//seteo los n valores del vector en 0.
    peligrosidad.push_back(0);
  }
  
  for(int i = 0; i < solParcialCamiones.size(); i++) //determino la peligrosidad por camion.
  { 
    for(int j = 0; j< solParcialCamiones.size() - i; j++) {
      if(solParcialCamiones[i] == solParcialCamiones[j]) {
        peligrosidad[solParcialCamiones[i]] += tab.peligrosidad[i][j];
      }
    }    
  }

  for(int h = 0; h < solParcialCamiones.size(); h++)
  {

    if(tab.m < peligrosidad[h])
      return true;
  }
  return false;
}

// check:
// si retorna 0 no es sol valida
// si retorna 1, es valida pero falta agregar camiones
// si retorna 3 la solucion anterior usa menos camiones
// si retorna 2 es solucion valida
int check(tablaDePeligrosidad &tab, vector<int> &solParcialCamiones ,vector <int> &solFinalCamiones)
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
  while(true) 
  {
    tablaDePeligrosidad tab;

    InicializarTablaDePeligrosidad(&tab);
    vector<int> solParcialCamiones;
    vector<int> solFinalCamiones;

    inicializarPeorSol(solFinalCamiones,tab.n);

    //auto start = chrono::high_resolution_clock::now();
    solParcialCamiones.push_back(0);
    bool sol = backtracking(tab, solParcialCamiones,solFinalCamiones);
    //auto finish = chrono::high_resolution_clock::now();
    //cout << chrono::duration_cast<chrono::microseconds>(finish - start).count() << endl;
    
    imprimirResultado(solFinalCamiones);
    solParcialCamiones.clear();
    solFinalCamiones.clear();
  }
  return 0;
}
