#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sys/time.h>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
#include <sys/timeb.h>
#include <climits>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

#ifndef INFINITO
#define INFINITO INT_MAX
#endif

//idea: genero una solución al azar (es decir, para cada nodo, lo asigno a un subconjunto cualquiera)
//Vecindad 1: Para cada nodo, pruebo con quitarlo del conjunto y agregarlo a uno que mejore el peso.
//Vecindad 2: para cada nodo, lo mismo que 1, pero ademas intento swapear nodos...? ver

vector<int> busqueda_local(vector< vector< int> > &matriz_de_adyacencias, vector< vector< int> > &subconjuntos, int k, int n, vector <int> en_que_subconjunto_esta_cada_nodo)
{
	//aca tengo que empezar a buscar localmente
	bool SeEncontroMejorSol = true;
	while(SeEncontroMejorSol)
	{
		SeEncontroMejorSol = false;

		int nodo = -1;
		int pesoNodoQueMasPesoGenera = 0;
		int conjuntoDelNodoQueMasPesoGenera = -1;


		for(int i = 0; i < n; i++)
		{
			int conjuntoActualDe_i = en_que_subconjunto_esta_cada_nodo[i];
			int sumaAUX = 0;
			for(int j = 0; j < subconjuntos[conjuntoActualDe_i].size(); j++)
			{
				sumaAUX += matriz_de_adyacencias[i][subconjuntos[conjuntoActualDe_i][j]];
			}
			if(sumaAUX > pesoNodoQueMasPesoGenera)
			{
				pesoNodoQueMasPesoGenera = sumaAUX;
				nodo = i;
				conjuntoDelNodoQueMasPesoGenera = en_que_subconjunto_esta_cada_nodo[i];
			}
		}

		//Ok, ahora se cuanto peso agrega tener a i en este conjunto en particular
		//hay un conjunto donde i agregue menos peso?
		// busco en mi vecindad, donde meter el nodo i para que sea minimo el peso
		int conjunto_candidato; 
		int suma_conjunto_candidato = INFINITO; 
		for(int j = 0; j < k; j++)
		{
			//evito el subconjunto de i
			if (j == conjuntoDelNodoQueMasPesoGenera)
				continue;

			//para cada conjunto hago la suma
			int sumaPoniendoA_i_enOtroConjunto = 0;
			
			for(int w = 0; w < subconjuntos[j].size(); w++)
			{
				sumaPoniendoA_i_enOtroConjunto += matriz_de_adyacencias[nodo][subconjuntos[j][w]];
			}

			//y me quedo con el minimo que es el candidato
			if(sumaPoniendoA_i_enOtroConjunto < suma_conjunto_candidato)
			{
				suma_conjunto_candidato = sumaPoniendoA_i_enOtroConjunto;
				conjunto_candidato = j;
			}
		}

		//si mejore algo, muevo el nodo i al candidato
		if(suma_conjunto_candidato < pesoNodoQueMasPesoGenera)
		{
			//cambio a i de conjunto
			en_que_subconjunto_esta_cada_nodo[nodo] = conjunto_candidato;

			//lo pongo en el conjunto nuevo...
			subconjuntos[conjunto_candidato].push_back(nodo);

			//lo saco del conjunto viejo...
			for(int aux = 0; aux < subconjuntos[conjuntoDelNodoQueMasPesoGenera].size(); aux++)
			{
				if(subconjuntos[conjuntoDelNodoQueMasPesoGenera][aux] == nodo)
				{
					subconjuntos[conjuntoDelNodoQueMasPesoGenera].erase(subconjuntos[conjuntoDelNodoQueMasPesoGenera].begin() + aux);
					break;
				}							
			}
			//Como mejore, reinicio la busqueda local con el nodo i mudado
			SeEncontroMejorSol = true;
			break;
		}
	}
	return en_que_subconjunto_esta_cada_nodo;
}