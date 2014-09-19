#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sys/time.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <sys/timeb.h>
#include <list>
#include <utility>
#include <stack>
#include <fstream>
#include <vector>

using namespace std;

struct arista
{
	int e1;
	int e2;
	int costo;
};

struct distancia
{
	int nodoOrigen ;
	int costo;
};
struct resultado
{
	int costoTotal;
	list<arista> anillo;
	list<arista> resto;
	bool conexo;

};
void imprimirMatriz(vector< vector < int > > matriz,int tam);
void imprimirArreglo(vector< distancia > vec,int tam);

resultado solucion(vector<arista> enlaces,int cantEnlaces,int cantEquipos ){
	//matriz de adyacencias
	vector< vector<int> > adyacencias (cantEquipos);
	vector< vector<int> > agm (cantEquipos);
	vector< vector<int> > aux (cantEquipos);
	list<arista> anillo;
	list<arista> resto;
	vector< distancia > distancias (cantEquipos);
	vector<bool> estan(cantEquipos);
	list <arista> restoEnlaces;
	int iteraciones =0;
	int costoTotal = 0;
	int posActual=0;

	//pongo la matriz de adyacencias en -1 que indica que no hay conexion
	for(int i=0;i<cantEquipos;i++){
		adyacencias[i].resize(cantEquipos);
		agm[i].resize(cantEquipos);
		for(int j=0;j<cantEquipos;j++){
			adyacencias[i][j] = -1;
			agm[i][j] = -1;

		}
	}

	//Completo con las adyacencias del vector que viene como entrada			
	for(int i=0;i<cantEnlaces;i++){
		adyacencias[enlaces[i].e1][enlaces[i].e2] = enlaces[i].costo;
		adyacencias[enlaces[i].e2][enlaces[i].e1] = enlaces[i].costo;

	}

	aux = adyacencias;
	stack<int> esConexo;
	esConexo.push(0);
	int contador = 1;

	for(int i = 0;i<cantEquipos;i++){
		estan[i]=false;
	}
	estan[0]=true;

	while (!esConexo.empty()){
		int topAnt = esConexo.top();
		for (int i = 0; i<cantEquipos; i++){
			if (aux[topAnt][i]!=-1 && !estan[i]){
				esConexo.push(i);
				contador++;
				estan[i]=true;
				aux[topAnt][i] = -1;
				aux[i][topAnt] = -1;
				break;
			}
		}
		if (topAnt == esConexo.top()){
			esConexo.pop();
		} 
	}

	if (contador != cantEquipos || cantEnlaces< cantEquipos){
		resultado res;
		res.conexo = false;
		return res;
	}

	//inicializo el arreglo de distancias
	for(int i = 0;i<cantEquipos;i++){
		if(adyacencias[0][i] != -1){
			distancias[i].costo = adyacencias[0][i];
			distancias[i].nodoOrigen = 0;
		}else{
			distancias[i].costo = -1; //si no son adyacentes seteo -1
			distancias[i].nodoOrigen = -1;
		}
	}

	for(int i = 0;i<cantEquipos;i++){
		estan[i]=false;
	}
	estan[0]=true;

	while(iteraciones < cantEquipos -1){

		int min=-1;
		int nodoMin;
		//busco el minimo en el arreglo de distancias
		for(int i =0;i<cantEquipos;i++){
			if(min == -1 || ( 0 < distancias[i].costo && distancias[i].costo< min && !estan[i])){
				min = distancias[i].costo;
				nodoMin = i;
			}
		}
		distancias[nodoMin].costo = -1;

		//Actualizamos la matriz de adyacencias de agm
		agm[distancias[nodoMin].nodoOrigen][nodoMin] = min;
		agm[nodoMin][distancias[nodoMin].nodoOrigen] = min;
		adyacencias[nodoMin][distancias[nodoMin].nodoOrigen] = -1;
		adyacencias[distancias[nodoMin].nodoOrigen][nodoMin] = -1;

		costoTotal += min;
		estan[nodoMin]=true;

		// actualizo mi arreglo de distancias 
		for(int i=0;i<cantEquipos;i++){
			if(adyacencias[nodoMin][i]>=0)
			{
				if(!estan[i] && 
					(distancias[i].costo == -1  || 
						adyacencias[nodoMin][i]< distancias[i].costo
					)){

					distancias[i].costo = adyacencias[nodoMin][i];
					distancias[i].nodoOrigen =nodoMin;	
				
				}
				
			}
		}
		iteraciones++;
	}
	//Busco del resto de aristas q no pertecen al agm la minima para generar un circuito
	
	 arista aristaMin = {-1,-1,-1};
	

	for(int i=0;i<cantEquipos;i++){
		for(int j=i+1;j<cantEquipos;j++){
			if(	aristaMin.costo == -1 || 
				(adyacencias[i][j]!=-1 && adyacencias[i][j] < aristaMin.costo)
			  )
			{
				aristaMin.costo = adyacencias[i][j];
				aristaMin.e1 = i;
				aristaMin.e2 = j;
			}
		}
	}



	costoTotal += aristaMin.costo;
	//BUSCO EL CAMINO 
	stack<int> caminoActual;
	caminoActual.push(aristaMin.e1);

	aux = agm;
	while (caminoActual.top() != aristaMin.e2){
		int topAnt = caminoActual.top();
		for(int i = 0; i<cantEquipos; i++){
			if(aux[topAnt][i]!=-1){
				caminoActual.push(i);
				aux[topAnt][i] = -1;
				aux[i][topAnt] = -1;
				break;
			}
		}
		if(topAnt == caminoActual.top()){
			caminoActual.pop();
		}
	}
	
	// CONSTRUYO EL CIRCUITO 

	while(!caminoActual.empty()){
		int topAnt = caminoActual.top();
		caminoActual.pop();
		if(caminoActual.empty()) break;
		arista nueva = {topAnt,caminoActual.top(),0};
		anillo.push_back(nueva);
		//limpio en la matriz del agm aquellas aristas que pertenecen al anillo
		agm[topAnt][caminoActual.top()] = -1;
		agm[caminoActual.top()][topAnt] = -1;
	}
	//agrego el arista que cierra el circuito
	anillo.push_back(aristaMin);

	//CONSTRUYO LA LISTA DE LAS ARISTAS QUE QUEDAN FUERA DEL ANILLO 
	for(int i =0;i<cantEquipos;i++){
		for(int j=i+1;j<cantEquipos;j++){
			if(agm[i][j]!=-1){
				arista nueva = {i,j,0};
				resto.push_back(nueva);
			}
		}
	}

	resultado res = {costoTotal,anillo,resto,true};
	return res;
}

void imprimirMatriz(vector< vector < int > > matriz,int tam){
	cout << "matriz" << endl;
	for(int i =0; i < tam; i++){
		for(int j =0; j < tam; j++){
			cout << matriz[i][j] << ' ';
		}	
		cout << endl;
	}
	cout << endl;

}
void imprimirArreglo(vector< distancia > vec,int tam){
	for(int i = 0 ; i <tam;i++){
		cout << '[' <<	vec[i].nodoOrigen << ',';
		cout  <<  vec[i].costo << ']';
 	}
 	cout << endl;
}
int main(int argc, char *argv[])
{
	// para detectar cuando estoy leyendo la primer linea
	bool primerLinea = true; 
	string line;
	//e1 y e2 representan el numero de los equipos
    int cantEquipos,e1,e2,costo;
    int cantEnlaces = 0;
 	vector<arista> enlaces;
 	int cantLeidas = -1;
    //Comienzo la lectura del archivo
    while ( getline (cin,line) ){
    		vector<string> entradaSplit;
	        int fromIndex = 0;//inicio string
	        int length = 0; //longitud string

    		
            if(primerLinea){
                     for(int i = 0; i<line.length();i++ ){
		                if(i== line.length()-1){
		                  length++;
		                  entradaSplit.push_back(line.substr(fromIndex, length));
		                }else if(line[i]== ' '){
		                  entradaSplit.push_back(line.substr(fromIndex, length));
		                  fromIndex = i+1;
		                  length = 0;
		                }else{
		                  length++;
		                }
		            }

                    cantEquipos = atoi(entradaSplit[0].c_str());
                    cantEnlaces = atoi(entradaSplit[1].c_str());
                    primerLinea=false;
                    continue;
            }

          
          	for(int i = 0; i<line.length();i++ ){
                if(i== line.length()-1){
                  length++;
                  entradaSplit.push_back(line.substr(fromIndex, length));
                }else if(line[i]== ' '){
                  entradaSplit.push_back(line.substr(fromIndex, length));
                  fromIndex = i+1;
                  length = 0;
                }else{
                  length++;
                }
            }

            e1 = atoi(entradaSplit[0].c_str());
			e2 = atoi(entradaSplit[1].c_str());
			//SOLO PARA EMPROLIJAR INDICES RESTO 1
			e1--;
			e2--;

            costo = atoi(entradaSplit[2].c_str());
			
			arista nueva = {e1,e2,costo}; 
			enlaces.push_back(nueva);
    }
    //FIN LECTURA ARCHIVO 

    // cout << cantEquipos << ' ' << cantEnlaces << endl;
    // for(int i =0;i<cantEnlaces;i++){
    // 	cout << enlaces[i].e1 << ' ' << enlaces[i].e2 ;
    // 	cout << ' ' << enlaces[i].costo << endl;
    // }
    // cout << endl;

	//Para medir tiempos descomentar
	//auto begin = std::chrono::high_resolution_clock::now();

    resultado res = solucion(enlaces,cantEnlaces,cantEquipos);
   	// cout << cantEdificios << " " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    // cout << endl;


    //IMPRIMO LA SALIDA
    if(res.conexo){
    	cout << res.costoTotal << ' ' << res.anillo.size();
	    cout << ' ' << res.resto.size() << endl;

	    for (list<arista>::iterator it = res.anillo.begin(); it!=res.anillo.end(); it++){
	    	int e1 = (*it).e1 +1;
	    	int e2 = (*it).e2 +1;
			cout << e1 << ' ' << e2 << endl; 
		}
		for (list<arista>::iterator it = res.resto.begin(); it!=res.resto.end(); it++){
			int e1 = (*it).e1 +1;
	    	int e2 = (*it).e2 +1;
			cout << e1 << ' ' << e2 << endl;
		}
    }else{
    	cout << "no" << endl;

    }
    
   	return 0;
}