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

list<arista> solucion(vector<arista> enlaces,int cantEquipos,int cantEnlaces ){
	//matriz de adyacencias
	vector< vector<int> > adyacencias (cantEquipos);

	//pongo la matriz de adyacencias en -1 que indica que no hay conexion
	for(int i=0;i<cantEquipos;i++){
		adyacencias[i].resize(cantEquipos);
		for(int j=0;j<cantEquipos;j++){
			adyacencias[i][j] = -1;
		}
	}
	//Completo con las adyacencias del vector que viene como entrada			
	for(int i=0;i<cantEquipos;i++){
		adyacencias[enlaces[i].e1][enlaces[i].e2] = enlaces[i].costo;
		adyacencias[enlaces[i].e2][enlaces[i].e1] = enlaces[i].costo;

	}

	vector< distancia > distancias (cantEquipos);
	int posActual=0;
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
	lista <arista> restoEnlaces;
	vector < arista > agm;
	int iteraciones =0;
	while(iteraciones < cantEquipos -1){

		int min=-1;
		int nodoMin;
		//busco el minimo en el arreglo
		for(int i =0;i<cantEquipos;i++){
			if(min == -1 || ( 0 < distancias[i].costo && distancias[i].costo< min)){
				min = distancias[i].costo;
				nodoMin = i;
			}
		}
		distancias[nodoMin].costo = -1;
		arista nueva = {distancias[nodoMin].nodoOrigen,nodoMin,min};
		agm.push_back(nueva);

		// actualizo mi arreglo de distancias 
		for(int i=0;i<cantEquipos;i++){
			if(adyacencias[nodoMin][i]>=0 && adyacencias[nodoMin][i]< distancias[i].costo){
				distancias[i].costo = adyacencias[nodoMin][i];
				distancias[i].nodoOrigen =nodoMin;
			}else{
				if(adyacencias[nodoMin][i]!=-1){ //agrego el resto de los enlaces a una lista
					arista nuevaArista = {nodoMin,i,adyacencias[nodoMin][i]};
					restoEnlaces.push_back(nuevaArista);	
				}
			}
		}
		iteraciones++;


	}
	arista aristaMin = restoEnlaces.first();
	for (iterator::list<arista> it = restoEnlaces.begin(); it!=restoEnlaces.end(); it++){
		if(aristaMin.costo<it->costo){
			aristaMin = (*it);
		}
	}

	for(int i = 0; i<cantEquipos; i++){
		for(j = 0; j<cantEquipos; j++){
			adyacencias[i][j] = -1;
		}
	}

	for(int i = 0; i<agm.size(); i++){
		adyacencias[agm[i].e1][agm[i].e2] = agm[i].costo;
		adyacencias[agm[i].e2][agm[i].e1] = agm[i].costo;
	}

	stack<int> caminoActual;
	caminoActual.push(aristaMin.e1);

	while (caminoActual.top() != aristaMin.e2){
		int topAnt = caminoActual.top();
		for(int i = 0; i<cantEquipos; i++){
			if(adyacencias[topAnt][i]!=-1){
				caminoActual.push(i);
				adyacencias[topAnt][i] = -1;
				adyacencias[i][topAnt] = -1;
				break;
			}
		}
		if(topAnt == caminoActual.top()){
			caminoActual.pop(topAnt);
		}
	}

	//falta reconstruir el camino

}


int main(int argc, char *argv[])
{
	// para detectar cuando estoy leyendo la primer linea
	bool primerLinea = true; 
	string line,s_equipos, s_enlaces;
	//e1 y e2 representan el numero de los equipos
    int cantEquipos, cantEnlaces,e1,e2,costo;
 	vector<arista> enlaces;
    //Comienzo la lectura del archivo
    while ( getline (cin,line) ){
    		vector<string> entradaSplit;
	        int fromIndex = 0;//inicio string
	        int length = 0; //longitud string

    		if(line == "0") break;
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
                    //pueblos = new pueblo[cantPueblos];
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
            costo = atoi(entradaSplit[2].c_str());
			
			arista nueva = {e1,e2,costo}; 
			enlaces.push_back(nueva);
    }
    //fin lectura archivo 
	//Para medir tiempos descomentar
	//auto begin = std::chrono::high_resolution_clock::now();
    list<arista> resultado = solucion(enlaces,cantEnlaces,cantEquipos);
   	// cout << cantEdificios << " " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    // cout << endl;


   	//Print resultado
    return 0;
}