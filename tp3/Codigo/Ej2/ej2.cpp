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

//definiciones de las funciones q usa el backtracking
int check(vector < vector<int> > & adyacencias, Solucion &solParcial,Solucion &solFinal);
bool tieneCajasVacias(Solucion& sol);
bool tieneMasBolitasElPredecesor(Solucion& sol);
void inicializarPeorSol(Solucion& sol,int n, vector < vector<int> > & adyacencias);
int calcularPeso(Solucion &sol , vector< vector <int> > &adyacencias );


bool backtracking(Solucion& solParcial,Solucion& solFinal,int cajaActual,int k,vector < vector< int> > &adyacencias)
{
	int resultCheck;

	cout << cajaActual << endl;

//	resultCheck = check(adyacencias,solParcial,solFinal);
	if(resultCheck == 2)
	{
		solFinal= solParcial;
		return true;
	}else{
		if(resultCheck == 0 ){
			return false;
		}else{
			int length = solParcial.conjuntos[cajaActual].size();	
			Solucion nueva = solParcial;
			for(int i = 0 ; i < length;i++ ){
				//muevo un vertice para adelante 
				int vertice = nueva.conjuntos[cajaActual].front();		
				nueva.conjuntos[cajaActual+1].pop();
				//me guardo la pila de vertices para no pisar la original 
				queue<int> proximo = nueva.conjuntos[cajaActual+1];
				proximo.push(vertice);
				nueva.conjuntos[cajaActual+1] = proximo;
				int nuevaCaja = cajaActual + 1;
				backtracking(nueva,solFinal,nuevaCaja,k,adyacencias);
				nueva.conjuntos[cajaActual].push(vertice);
			}
		}
	}
	return false; // solo para completar casos, es imposible que se llegue a este punto.
}

// check:
// si retorna 0 es una solucion ya calculada
// si retorna 1, es valida pero falta completar cajas
// si retorna 3 la solucion tiene cajas vacias o entonces es porque el de la posicicon i+1 tiene mas bolitas que el actual y ya fue generada esa solucion
// si retorna 2 es solucion valida
int check(vector < vector<int> > &adyacencias, Solucion &solParcial,Solucion &solFinal)
{
	//mi resultado final sigue siendo mejor
	int peso = calcularPeso(solParcial ,adyacencias);
	if(peso<solFinal.peso)
		return 3;
	//Podas, si tiene cajas vacias no voy a generar una solucion mejor si no una ya generada al igual que mover bolitas entre cajas sucesoras, abort!
	if(tieneMasBolitasElPredecesor(solParcial))
		return 0;
	if(tieneCajasVacias(solParcial))
		return 1;
	if(peso<solFinal.peso){
		return 3;
	}else{
		return 2;
	}

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
int calcularPeso(Solucion &sol , vector< vector <int> > &adyacencias ){
	int peso = 0;
	for(int k = 0; k < sol.conjuntos.size() ; k++){
		//agarro una caja
		for(int i = 0; i<sol.conjuntos[k].size()  ; i++ ){
			//para cada elemento de la caja
			for(int j = i+1; j<sol.conjuntos[k].size() ; j++ ){
				//como la matriz esta inicializada en ceros sumara un mayor a cero cuando tenga un valor mayor a cero 
				peso += adyacencias[i][j];	
			}
		}
	}
	return peso;
}

void inicializarPeorSol(Solucion &sol,int n, vector < vector<int> > & adyacencias){
	queue<int> inicial;
	for(int i = 0; i < n; i++)
		inicial.push(i);
	sol.conjuntos[0] = inicial;
	sol.peso =  calcularPeso(sol,adyacencias); 
}

void imprimirAdyacencias(vector < vector <int> > adyacencias){

	for(int i = 0 ; i < adyacencias[0].size();i++){
		for(int j = 0 ; j < adyacencias[0].size();j++){
			cout << adyacencias[i][j] << " ";
		}
		cout << endl;

	}
}


int main()
{

	int n,m,k;
	cin >> n;
	cin >> m;
	cin >> k;

	vector< vector< int> >adyacencias  = vector< vector< int> >(n, vector<int> (n, 0));
	vector< queue< int> > subconjuntos;

	for(int i = 0; i < k; i++)
	{
		queue< int> aux;
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
	//while(true){
		Solucion solParcial;
		solParcial.peso = 0;
		solParcial.conjuntos = subconjuntos;	
		Solucion solFinal = solParcial;
	
		inicializarPeorSol(solFinal,n,adyacencias);
		imprimirAdyacencias(adyacencias);
		bool sol = backtracking(solParcial,solFinal,0,k,adyacencias);
		return sol;
		//imprimirResultado(solFinal);
		//[>solParcial.clear();<]
		//[>solFinal.clear();<]
	//break;
	//}

	return 0;
}
