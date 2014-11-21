#include <sys/time.h>
#include <iostream>
#include <sys/timeb.h>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <cstdlib>


using namespace std;


struct Solucion{
	int peso;
	vector< stack <int> > conjuntos;
};

//definiciones de las funciones q usa el backtracking
int check(vector < vector<int> > & adyacencias, Solucion &solParcial,Solucion &solFinal,int numeroVertice);
void inicializarPeorSol(Solucion& sol,int n, vector < vector<int> > & adyacencias,int k);
int calcularPeso(Solucion &sol , vector< vector <int> > &adyacencias );
void imprimirResultado(Solucion& solParcial, int n);
void calcularNuevoPeso(Solucion &sol ,int index, int vertice,int signo, vector< vector <int> > &adyacencias );


bool backtracking(Solucion& solParcial,Solucion& solFinal,int numeroVertice,int k,vector < vector< int> > &adyacencias)
{
	int resultCheck;

	resultCheck = check(adyacencias,solParcial,solFinal,numeroVertice);
	//cout << "resultado " << resultCheck << endl;
	//cout << "verticeNumero " << numeroVertice << endl;
	if(resultCheck == 0)
	{
		int peso = calcularPeso(solParcial ,adyacencias);
		solParcial.peso = peso;
		if(solParcial.peso < solFinal.peso){
			solFinal= solParcial;
		        return true;	
		}
		return false;
	}
	if (resultCheck == 2)
		return false;

	for(int i = 0; i < k ;i++){
		calcularNuevoPeso(solParcial,i,numeroVertice,1,adyacencias);
		solParcial.conjuntos[i].push(numeroVertice);
		//imprimirResultado(solParcial);
		backtracking(solParcial,solFinal,numeroVertice+1,k,adyacencias);
		calcularNuevoPeso(solParcial,i,numeroVertice,-1,adyacencias);
		solParcial.conjuntos[i].pop();
	} 
	return false; 
}

int cantidadCajasVacias(Solucion& sol){
	int cantidad = 0;
	for(int i = 0;i<sol.conjuntos.size();i++){
		if(sol.conjuntos[i].size()==0)
			cantidad++;
	}
	return cantidad;
}

// check:
// si retorna 0 llegue al final 
// si retorna 1, tengo que seguir insertando vertices 
// si retorna 2 la solucion parcial tiene mas peso q la final con lo que descarto esta rama o 
//la cantidad de vertices que me quedan para ubicar es menor a la cantidad de cajas vacias
int check(vector < vector<int> > &adyacencias, Solucion &solParcial,Solucion &solFinal,int numeroVertice)
{
	//no termine de agregar vetices sigo
	if(solParcial.peso > solFinal.peso){
		return 2;
	}

	if(adyacencias.size()==numeroVertice){
		return 0;	
	}	
	
	//si tiene cajas vacias no voy a generar una solucion mejor si no una ya generada al igual que mover bolitas entre cajas sucesoras, abort!
	if(cantidadCajasVacias(solParcial)>=numeroVertice){
		return 2;
	}

	
	return 1;
}


void imprimirResultado(Solucion& solParcial, int n){
	// cout << "peso " << solParcial.peso << endl;
 // 	for(int i = 0; i < solParcial.conjuntos.size(); i++)
 // 	{
	// 	cout << "[";
	// 	stack<int> copia = solParcial.conjuntos[i];
	//  	while(!copia.empty())
	// 	{
	// 	 	cout << copia.top()<< ",";
	//                 copia.pop();
	//    	}
 // 		cout << "]";
 // 	}
	// cout << endl;

	//int n = 10;


	//Version modificada que muestra el resultado acorde a lo que se pide

	vector<int> aux;
	aux.resize(n);

	cout << "peso " << solParcial.peso << endl;
 	for(int i = 0; i < solParcial.conjuntos.size(); i++)
 	{
		stack<int> copia = solParcial.conjuntos[i];
	 	while(!copia.empty())
		{
			aux[copia.top()] = i;
			copia.pop();
	   	}
 	}

 	for(int i = 0; i < aux.size(); i++)
 		cout << aux[i] + 1 << " ";
 	cout << endl;

}

void calcularNuevoPeso(Solucion &sol ,int index, int vertice,int signo, vector< vector <int> > &adyacencias ){
	int peso = 0;
	int pesoVertice = 0;
	//agarro el conjunto donde voy a agregar el vertice.
	stack <int> cajaActual = sol.conjuntos[index];
	//calculo el peso del conjunto que deberia restarle al total	
	while(!cajaActual.empty()){
		stack <int> resto = cajaActual;
		pesoVertice += adyacencias[vertice][cajaActual.top()];		
		cajaActual.pop();
	}
	sol.peso += signo * pesoVertice;
}

int calcularPeso(Solucion &sol , vector< vector <int> > &adyacencias ){
	int peso = 0;
	for(int k = 0; k < sol.conjuntos.size() ; k++){
		//agarro una caja
		stack <int> cajaActual = sol.conjuntos[k];
		while(!cajaActual.empty()){
			stack <int> resto = cajaActual;
			while(!resto.empty()){
				 //cout << cajaActual.top() << "," << resto.top() << endl;
				  peso += adyacencias[cajaActual.top()][resto.top()]; 
				  //cout << "peso " << peso<< endl;
				  resto.pop();	
			}
			
			cajaActual.pop();
		}
	}
	return peso;
}
void inicializarPeorSol(Solucion &sol,int n, vector < vector<int> > & adyacencias,int k){
	// inicio una solucion con todos los nodos en un solo conjunto 
	stack<int> inicial;

		cout << "pase" << endl;
	for(int i = 0; i < n; i++)
		inicial.push(i);

	sol.conjuntos[0] = inicial;

	sol.peso =  calcularPeso(sol,adyacencias);

		cout << "pase" << endl;
	// Busco una segunda alternativa para ver si tengo menor peso total y podar mas soluciones 
	Solucion alternativa1; 
	vector< stack< int> > subconjuntos;

		cout << "pase" << endl;
	for(int i = 0; i < k; i++)
	{
		stack< int> aux;
		subconjuntos.push_back(aux);
	}

		cout << "pase" << endl;
	int numeroVertice = 0;
	while(numeroVertice < n){
		
		for(int i = 0; i< k ; i++){
			subconjuntos[i].push(numeroVertice);	
			numeroVertice++;	
		}	
	}
	alternativa1.conjuntos = subconjuntos;
	alternativa1.peso = calcularPeso(alternativa1,adyacencias);
		
	if(alternativa1.peso<= sol.peso){
		sol  = alternativa1;	
	}
 
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

	//while(true){
		int fin;
		cin >> fin;
		//if(fin == 0)
			//break;
		int n,m,k;
		cin >> n;
		cin >> m;
		cin >> k;
		vector< vector< int> >adyacencias  = vector< vector< int> >(n, vector<int> (n, 0));
		vector< stack< int> > subconjuntos;

		for(int i = 0; i < k; i++)
		{
			stack< int> aux;
			subconjuntos.push_back(aux);
		}

		for(int i = 0; i < m; i++)
		{
			int j,l,p;
			cin >> j;
			cin >> l;
			cin >> p;
			adyacencias[j-1][l-1] = p;
			adyacencias[l-1][j-1] = p;
		}

		imprimirAdyacencias(adyacencias);
		cout << "pase" << endl;
		long mtime, seconds, useconds; 
		timeval tm1, tm2;
		gettimeofday(&tm1, NULL);
		Solucion solParcial;
		solParcial.peso = 0;
		solParcial.conjuntos = subconjuntos;	
		Solucion solFinal;
		solFinal.conjuntos = subconjuntos;
		inicializarPeorSol(solFinal,n,adyacencias,k);
		Solucion x;
		bool sol = backtracking(solParcial,solFinal,0,k,adyacencias);
		gettimeofday(&tm2, NULL);	
		//imprimirResultado(solFinal, n);
		seconds  = tm2.tv_sec  - tm1.tv_sec;
		useconds = tm2.tv_usec - tm1.tv_usec;

		mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
		cout << n <<  mtime << endl;
	//}
	return 0;
}
