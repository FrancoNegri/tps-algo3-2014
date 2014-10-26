#include <sys/time.h>
#include <iostream>
#include <sys/timeb.h>
#include <vector>
#include <queue>
using namespace std;


struct Solucion{
	int peso;
	vector< queue <int> > conjuntos;
};


int check(vector < vector<int> > adyacencias, Solucion &solParcial,Solucion &solFinal);
bool solucionTieneMenosPeso(vector < vector<int> > *adyacencias, Solucion solParcial,Solucion solFinal);
bool tieneCajasVacias(Solucion& sol);
bool tieneMasBolitasElPredecesor(Solucion& sol);
void inicializarPeorSol(Solucion sol,int n);
bool SolucionCompletaMejor(vector < vector<int> > *adyacencias, Solucion solParcial,Solucion solFinal);

bool backtracking(Solucion& solParcial,Solucion& solFinal,int cajaActual,int k,vector < vector< int> > adyacencias)
{
  int resultCheck;


    resultCheck = check(adyacencias,solParcial,solFinal);
    if(resultCheck == 2)
    {
	    solFinal= solParcial;
	    return true;
    }else{
	    if(resultCheck == 3 ){
		return false;
	    }else{
		int length = solParcial.conjuntos[cajaActual].size();	
		Solucion nueva = solParcial;
		for(int i = 0 ; i < length;i++ ){
			//Busco una nueva solucion en el arbol de soluciones
			queue<int> conjunto = solParcial.conjuntos[cajaActual];
			//muevo un vertice para adelante 
			int vertice = conjunto.front();		
			conjunto.pop();
			nueva.conjuntos[cajaActual+1].push(vertice);
			nueva.conjuntos[cajaActual] = conjunto;
			backtracking(nueva,solFinal,cajaActual+1,k,adyacencias);
		}
	}
    }
  return false; // solo para completar casos, es imposible que se llegue a este punto.
}



// check:
// si retorna 0 no es sol valida
// si retorna 1, es valida pero falta agregar vertices
// si retorna 3 la solucion tiene cajas vacias o entonces es porque el de la posicicon i+1 tiene mas bolitas que el actual y ya fue generada esa solucion
// si retorna 2 es solucion valida
int check(vector < vector<int> > *adyacencias, Solucion &solParcial,Solucion &solFinal)
{
  //mi resultado final sigue siendo mejor
  //if(solucionTieneMenosPeso(solParcial,solFinal,adyacencias))
    //return 3;
  //Podas, si tiene cajas vacias no voy a generar una solucion mejor si no una ya generada al igual que mover bolitas entre cajas sucesoras, abort!
  if(tieneCajasVacias(solParcial)&& tieneMasBolitasElPredecesor(solParcial))
    return 0;

  //
  if(SolucionCompletaMejor(adyacencias,solParcial,solFinal))
    return 2;


  return 1;
}
bool solucionTieneMenosPeso(vector < vector<int> > *adyacencias, Solucion solParcial,Solucion solFinal){

	bool res = true;
	int peso = 0;
	for(int i = 0 ; i < solParcial.conjuntos.size();i++){
		vector<int> conjunto;
		while(!solParcial.conjuntos[i].empty()){
			conjunto.push_back(solParcial.conjuntos[i].front());
			solParcial.conjuntos[i].pop();	
		}
		//calcular el peso del conjunto
	
	}	
	

	return res;
}

//Reviso si mi solucion tiene cajas vacias
bool tieneCajasVacias(Solucion& sol){
	bool res = false;
	for(int i = 0; i < sol.conjuntos.size();i++ ){
		if(sol.conjuntos[i].size() == 0){
			res = true;
			break;
		} 	
	}
	return res;
}

//Reviso si en algun caso estoy teniendo dos cajas seguidas donde la segunda tiene mas bolitas
bool tieneMasBolitasElPredecesor(Solucion& sol){
	bool res = false;
	int cantidadAnterior = sol.conjuntos[0].size();
	for(int i = 1; i < sol.conjuntos.size();i++ ){
		if(sol.conjuntos[i].size()>cantidadAnterior  ){
			res = true;
			break;
		}else{
			cantidadAnterior = sol.conjuntos[i].size();
		}	
	}
	return res;
}
bool SolucionCompletaMejor(vector < vector<int> > *adyacencias, Solucion solParcial,Solucion solFinal){
	bool res = true;




	return res;


}
/*void imprimirResultado(vector<int> solParcial)*/
//{
 //int max = solParcial[0];
 //for(int i = 1; i < solParcial.size(); i++)
   //if(solParcial[i] > max)
     //max = solParcial[i];
 //cout << max + 1<< " ";
 //for(int i = 0; i < solParcial.size(); i++)
   //cout << solParcial[i] + 1 << " ";
 //cout << endl;
//}



void inicializarPeorSol(Solucion sol,int n){
  queue<int> inicial;
  for(int i = 0; i < n; i++)
      inicial.push(i);

	
}


int main()
{
  
	int n,m,k;
	cin >> n;
	cin >> m;
	cin >> k;

	vector< vector< int> >adyacencias  = vector< vector< int> >(n, vector<int> (n, 0));
	vector< vector< int> > subconjuntos;

	for(int i = 0; i < k; i++)
	{
		vector< int> aux;
		subconjuntos.push_back(aux);
	}


	for(int i = 0; i < m; i++)
	{
		int j,k,p;
		cin >> j;
		cin >> k;
		cin >> p;
		adyacencias[j-1][k-1] = p;
		adyacencias[k-1][j-1] = p;
	}

	timeval tm1, tm2;
	gettimeofday(&tm1, NULL);
	while(true){
		Solucion solParcial;
		Solucion solFinal;

		inicializarPeorSol(solFinal,n);

		bool sol = backtracking(solParcial,solFinal,0,k,adyacencias);

		//imprimirResultado(solFinal);
		/*solParcial.clear();*/
		/*solFinal.clear();*/
	}

	return 0;
}
