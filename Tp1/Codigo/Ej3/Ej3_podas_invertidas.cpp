#include "Ej3.h"
#include <sys/time.h>
#include <sys/timeb.h>

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


void imprimir_tab(tablaDePeligrosidad tab)
{
 for (int i = 0; i < tab.peligrosidad.size(); i++)
 {
   vector<int> v = tab.peligrosidad[i];
   for (int j = 0; j < v.size(); j++)
   {
     cout << tab.peligrosidad[i][j] << " " ;
   }
   cout << endl;
 }
 cout << endl;
}



tablaDePeligrosidad InicializarTablaDePeligrosidad() {
  tablaDePeligrosidad tab;
  cin >> tab.n;
  if(tab.n == 0)
    exit(0);
  cin >> tab.m;
  //construyo una matriz de n x n inicializada en 0
  vector< vector<int> > vec(tab.n, vector<int>(tab.n));
  tab.peligrosidad = vec;

  //le meto en la matriz los valores de peligrosidad de a pares
  for (int i = 0; i < tab.n; i++) {
    for(int j = i; j < tab.n; j++) {
      //la diagonal no tiene sentido
      if(j == i) {
        tab.peligrosidad[i][j] = 0;
      } else {
        int valor;
        cin >> valor;
        
        tab.peligrosidad[i][j] = valor;
        tab.peligrosidad[j][i] = valor;  
      }
    }
  }
  return tab;
}




bool backtracking(tablaDePeligrosidad &tab, vector <int> &solParcialCamiones,vector <int> &solFinalCamiones)
{
  //imprimirResultado(solParcialCamiones);
  int resultadoCheck;
  if(solParcialCamiones.size() > tab.n) {
    return false;
  }

  resultadoCheck = check(tab,solParcialCamiones,solFinalCamiones);

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

  if(resultadoCheck == 0) {
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
  int cantidad_de_camiones_en_la_solucion_parcial = solParcialCamiones[0];
  int cantidad_de_camiones_en_la_solucion_final = solFinalCamiones[0];

  for(int i = 0; i < solParcialCamiones.size(); i++) {
    if(cantidad_de_camiones_en_la_solucion_parcial < solParcialCamiones[i]) {
      cantidad_de_camiones_en_la_solucion_parcial = solParcialCamiones[i];
    }
  }
    
  for(int i = 0; i < solFinalCamiones.size(); i++) {
    if(cantidad_de_camiones_en_la_solucion_final < solFinalCamiones[i]) {
      cantidad_de_camiones_en_la_solucion_final = solFinalCamiones[i];
    }
  }

  return cantidad_de_camiones_en_la_solucion_final < cantidad_de_camiones_en_la_solucion_parcial;
}

bool cotaDePeligrosidadSobrepasada(tablaDePeligrosidad &tab, vector<int> &solParcialCamiones)
{
  //por cada camion, pongo su peligrosidad en 0
  vector<int> peligrosidad;
  for(int k = 0; k < solParcialCamiones.size(); k++) {//seteo los n valores del vector en 0.
    peligrosidad.push_back(0);
  }
  

  for(int i = 0; i < solParcialCamiones.size(); i++) //determino la peligrosidad por camion.
  { 
    // miramos a partir del elemento i en el camion, cuanto le cuesta combinarse con el elemento j, que j es estrictamente mayor a i
    for(int j = i+1; j< solParcialCamiones.size(); j++) {
      int camion_del_producto_i = solParcialCamiones[i];
      int camion_del_producto_j = solParcialCamiones[j];
      //estan en el mismo camion???
      if(camion_del_producto_j == camion_del_producto_i) {
        peligrosidad[camion_del_producto_i] += tab.peligrosidad[i][j];

      }
    }    
  }

  //reviso si alguna peligrosidad se paso de la cota
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
  //me pase, abort!
  if(cotaDePeligrosidadSobrepasada(tab,solParcialCamiones))
    return 0;
  //mi resultado final sigue siendo mejor
  if(solucionFinalUsaMenosCamiones(solParcialCamiones,solFinalCamiones))
    return 3;

  //
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
  timeval tm1, tm2;
  gettimeofday(&tm1, NULL);
  while(true){
    tablaDePeligrosidad tab = InicializarTablaDePeligrosidad();
    vector<int> solParcialCamiones;
    vector<int> solFinalCamiones;

    inicializarPeorSol(solFinalCamiones,tab.n);

    //auto start = chrono::high_resolution_clock::now();
    //Agrego el primer producto al camion y lanzo la recursion
    solParcialCamiones.push_back(0);
    gettimeofday(&tm1, NULL);
    bool sol = backtracking(tab, solParcialCamiones,solFinalCamiones);
    gettimeofday(&tm2, NULL);
    unsigned long long t = 1000 * (tm2.tv_sec - tm1.tv_sec) + (tm2.tv_usec - tm1.tv_usec) / 1000;
    cout << "tarde tanto: " <<t << endl;
    //auto finish = chrono::high_resolution_clock::now();
    //cout << chrono::duration_cast<chrono::microseconds>(finish - start).count() << endl;
    
    imprimirResultado(solFinalCamiones);
    solParcialCamiones.clear();
    solFinalCamiones.clear();
  }

  return 0;
}
