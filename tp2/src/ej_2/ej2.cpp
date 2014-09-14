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

struct caballo{
	int fila;
	int columna;
};

struct resultado
{
	
	bool tieneSolucion;

};
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
// void imprimirArreglo(vector< distancia > vec,int tam){
// 	for(int i = 0 ; i <tam;i++){
// 		cout << '[' <<	vec[i].nodoOrigen << ',';
// 		cout  <<  vec[i].costo << ']';
//  	}
//  	cout << endl;
// }

resultado solucion(vector<caballo> enlaces,int cantFilas,int cantCaballos ){
	



	//return res;
}


int main(int argc, char *argv[])
{
	// para detectar cuando estoy leyendo la primer linea
	bool primerLinea = true; 
	string line;
	//e1 y e2 representan el numero de los equipos
    int cantFilas,fila,columna,cantCaballos;
 	vector<caballo> fichas;
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

                    cantFilas = atoi(entradaSplit[0].c_str());
                    cantCaballos = atoi(entradaSplit[1].c_str());
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

            fila = atoi(entradaSplit[0].c_str());
			columna = atoi(entradaSplit[1].c_str());
			//SOLO PARA EMPROLIJAR INDICES RESTO 1
			fila--;
			columna--;

			caballo nueva = {fila,columna}; 
			fichas.push_back(nueva);
    }
    //FIN LECTURA ARCHIVO 

    cout << cantFilas << ' ' << cantCaballos << endl;
    for(int i =0;i<cantCaballos;i++){
    	cout << fichas[i].fila << ' ' << fichas[i].columna << endl;
    }
    cout << endl;

	//Para medir tiempos descomentar
	//auto begin = std::chrono::high_resolution_clock::now();

    resultado res = solucion(fichas,cantFilas,cantCaballos);
   	// cout << cantEdificios << " " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    // cout << endl;


    //IMPRIMO LA SALIDA
  //   if(res.conexo){
  //   	cout << res.costoTotal << ' ' << res.anillo.size();
	 //    cout << ' ' << res.resto.size() << endl;

	 //    for (list<arista>::iterator it = res.anillo.begin(); it!=res.anillo.end(); it++){
	 //    	int e1 = (*it).e1 +1;
	 //    	int e2 = (*it).e2 +1;
		// 	cout << e1 << ' ' << e2 << endl; 
		// }
		// for (list<arista>::iterator it = res.resto.begin(); it!=res.resto.end(); it++){
		// 	int e1 = (*it).e1 +1;
	 //    	int e2 = (*it).e2 +1;
		// 	cout << e1 << ' ' << e2 << endl;
		// }
  //   }else{
  //   	cout << "no" << endl;

  //   }
    
   	return 0;
}