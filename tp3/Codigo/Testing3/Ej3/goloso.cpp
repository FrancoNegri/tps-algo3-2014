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

//#include <chrono>

using namespace std;

#ifndef INFINITO
#define INFINITO INT_MAX
#endif

//idea: en cada paso, tomo un vertice, me fijo en que subconjunto minimiza la suma, y lo agrego ahí.

Solucion goloso(vector< vector< int> > &matriz_de_adyacencias, vector< vector< int> > &noseusa, int k, int n)
{
    //hasta aca cree todos las estructuras de datos que voy a necesitar.
    vector< vector< int> > subconjuntos;

    for (int i = 0; i < k; i++)
    {
        vector< int> aux;
        subconjuntos.push_back(aux);
    }

    vector<int> en_que_subconjunto_esta_cada_nodo;


    vector<int> nodos;
    for (int i = 0; i < n; i++)
    {
        nodos.push_back(i);
    }

    /*random_shuffle(nodos.begin(),nodos.end());*/

    //meto el nodo 1 en cualquiera de los conjuntos, por ahora son todos iguales.

    en_que_subconjunto_esta_cada_nodo.push_back(nodos[0]);

    //del punto de arriba, el nodo 1 va a ir en el subconjunto 1, asi que tambien digo eso.

    en_que_subconjunto_esta_cada_nodo.resize(n);

    subconjuntos[0].push_back(nodos[0]);

    int menorSuma = INFINITO;

    for (int i = 1; i < n; i++ )
    {
        //tomo el vertice i

        int menorConjunto = 0;

        for (int j = 0; j < k; j++)
        {
            //para cada conjunto
            int aux = 0;
            for (int w = 0; w < subconjuntos[j].size(); w++)
            {
                //veo cuanto "peso" suma agregar este vertice a este conjunto determinado
                int candidato = subconjuntos[j][w];
                aux += matriz_de_adyacencias[nodos[i]][candidato];
            }

            //me guardo el conjunto que minimiza la suma
            if (aux < menorSuma)
            {
                menorSuma = aux;
                menorConjunto = j;
            }
        }

        //agrego el verice i al conjunto que minimiza la suma
        subconjuntos[menorConjunto].push_back(nodos[i]);
        //esto es para dar la respuesta de una y no tener que andar buscando los valores despues
        en_que_subconjunto_esta_cada_nodo[nodos[i]] = menorConjunto;
    }
    noseusa = subconjuntos;
    //complejidad O(kn^2) creo.
    Solucion sol;
    sol.conjuntos = en_que_subconjunto_esta_cada_nodo;
    sol.peso = menorSuma;
    return sol;
}