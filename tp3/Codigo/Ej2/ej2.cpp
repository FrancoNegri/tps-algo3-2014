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
void imprimirResultado(Solucion& solParcial);

bool backtracking(Solucion& solParcial,Solucion& solFinal,int cajaActual,int k,vector < vector< int> > &adyacencias)
{
	int resultCheck;

	resultCheck = check(adyacencias,solParcial,solFinal);
	//cout << "resultado " << resultCheck << endl;
	if(resultCheck == 2)
	{
		solFinal= solParcial;
	        return true;	
	}else{
		if(resultCheck == 0 ){
			return false;
		}else{
			int length = solParcial.conjuntos[cajaActual].size()-1;	
			Solucion nueva = solParcial;
			//cout << "length " << length << endl;
			//para cada uno de los vertices
			for(int i = 0 ; i < length;i++ ){
				//guardo el vertice a mover
				int vertice = nueva.conjuntos[cajaActual].front();	
				//popeo el vertice	
				nueva.conjuntos[cajaActual].pop();
				//me guardo la pila de vertices para no pisar la original 
				queue<int> proximo = nueva.conjuntos[cajaActual+1];
				nueva.conjuntos[cajaActual+1].push(vertice);
				
				int nuevaCaja = cajaActual + 1;
				//cout << "llego a llamar a la recursiva " << cajaActual << endl;
				//llamado recursivo con el vertice movido hacia adelante
				//solFinal  es la solucion que teni antes 
				//cout << "nueva sol ";	
				imprimirResultado(nueva);
				backtracking(nueva,solFinal,nuevaCaja,k,adyacencias);
				//cout << "solFinal ";
				//imprimirResultado(solFinal);
				//restablezco las pilas
				nueva.conjuntos[cajaActual+1] = proximo;	
				nueva.conjuntos[cajaActual].push(vertice);
			}
			return true;
		}
	}
	return false; // solo para completar casos, es imposible que se llegue a este punto.
}

// check:
// si retorna 0 es una solucion ya calculada
// si retorna 1, es valida pero falta completar cajas
// si retorna 3 la solucion no es mejor tengo q seguir calculando
// si retorna 2 es solucion valida
int check(vector < vector<int> > &adyacencias, Solucion &solParcial,Solucion &solFinal)
{
	//mi resultado final sigue siendo mejor
	int peso = calcularPeso(solParcial ,adyacencias);
	solParcial.peso = peso;
	//Podas, si tiene cajas vacias no voy a generar una solucion mejor si no una ya generada al igual que mover bolitas entre cajas sucesoras, abort!
	if(tieneMasBolitasElPredecesor(solParcial))
		return 0;
	if(tieneCajasVacias(solParcial))
		return 1;
	if(peso<solFinal.peso){
		return 2;
	}else{
		return 3;
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
void imprimirResultado(Solucion& solParcial){
cout << "peso " << solParcial.peso << endl;
 for(int i = 0; i < solParcial.conjuntos.size(); i++){
		cout << "[";
		queue<int> copia = solParcial.conjuntos[i];
	 while(!copia.empty()){
	 	cout << copia.front()<< ",";
                copia.pop();
   	 }
 	cout << "]";
 }
	cout << endl;
}
int calcularPeso(Solucion &sol , vector< vector <int> > &adyacencias ){
	int peso = 0;
	for(int k = 0; k < sol.conjuntos.size() ; k++){
		//agarro una caja
		queue <int> cajaActual = sol.conjuntos[k];
		while(!cajaActual.empty()){
			queue <int> resto = cajaActual;
			while(!resto.empty()){
				 //cout << cajaActual.front() << "," << resto.front() << endl;
				  peso += adyacencias[cajaActual.front()][resto.front()]; 
				  //cout << "peso " << peso<< endl;
				  resto.pop();	
			}
			cajaActual.pop();
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
		inicializarPeorSol(solParcial,n,adyacencias);
		Solucion solFinal = solParcial;
		Solucion x;
		imprimirAdyacencias(adyacencias);
		//imprimirResultado(solFinal);	
		bool sol = backtracking(solParcial,solFinal,0,k,adyacencias);
		//return sol;
		//imprimirResultado(solFinal);
		//[>solParcial.clear();<]
		//[>solFinal.clear();<]
	//break;
	//}

	return 0;
}
