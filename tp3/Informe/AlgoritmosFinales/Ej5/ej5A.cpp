#ifndef PORCENTAJEDEMEJORES
#define PORCENTAJEDEMEJORES 10
#endif
#ifndef CANTIDADDEEXITOS
#define CANTIDADDEEXITOS 34
#endif

//complejidad De este algoritmo O(n^3)
vector<int> goloso(vector< vector< int> > & matriz_de_adyacencias, vector< vector< int> > & noseusa, int k, int n) {
    int cuantosMejores = (PORCENTAJEDEMEJORES * k) / 100;
    if (cuantosMejores == 0)
        cuantosMejores = 1;
    int resultados[cuantosMejores];
    int indices[cuantosMejores];
    vector< vector< int> > subconjuntos;
    for (int i = 0; i < k; i++) {
        vector< int> aux;
        subconjuntos.push_back(aux);
    }
    vector<int> en_que_subconjunto_esta_cada_nodo;
    //meto el nodo 1 en cualquiera de los conjuntos, por ahora son todos iguales.
    en_que_subconjunto_esta_cada_nodo.push_back(0);
    //del punto de arriba, el nodo 1 va a ir en el subconjunto 1, asi que tambien digo eso.
    en_que_subconjunto_esta_cada_nodo.resize(n);
    subconjuntos[0].push_back(0);
    for (int i = 1; i < n; i++ ) {
        for (int l = 0; l < cuantosMejores ; l++) {
            resultados[l] = INFINITO;
            indices[l] = -1;
        }
        //tomo el vertice i
        for (int j = 0; j < k; j++) {
            //para cada conjunto
            int aux = 0;
            for (int w = 0; w < subconjuntos[j].size(); w++) {
                //veo cuanto "peso" suma agregar este vertice a este conjunto determinado
                int candidato = subconjuntos[j][w];
                aux += matriz_de_adyacencias[i][candidato];
            }
            //me guardo los x conjuntos que minimizan la suma
            bool encontreNegativo = false;
            bool indiceMax = 0;
            int w = 0;
            //A lo sumo cuantosMejores iteraciones, cada una de O(1)
            //Como cuantosMejores <= k <= n (ya que de otra manera es un caso trivial)
            //no me va a sumar nada a la complegidad.
            while (w < cuantosMejores) {
                if (indices[w] == -1 && ! encontreNegativo) {
                    encontreNegativo = true;
                    resultados[w] = aux;
                    indices[w] = j;
                    break;
                }
                if (resultados[w] > resultados[indiceMax]) {
                    indiceMax = w;
                }
                w++;
            }
            if (!encontreNegativo && aux < resultados[indiceMax]) {
                resultados[indiceMax] = aux;
                indices[indiceMax] = j;
            }
        }
        int valorQueTomo = rand() % cuantosMejores; // tomo un valor Al Azar entre estos valores
        //agrego el verice i al conjunto que minimiza la suma
        int index = indices[valorQueTomo];
        subconjuntos[index].push_back(i);
        en_que_subconjunto_esta_cada_nodo[i] = indices[valorQueTomo];
    }
    noseusa = subconjuntos;
    return en_que_subconjunto_esta_cada_nodo;
}

vector <int> grasp(vector< vector< int> > & matriz_de_adyacencias, vector< vector< int> > & subconjuntos, int k, int n) {
    srand(0);
    int cantidadDeVecesQueSeLlegoAmejorSol = 0;
    int min_total = INFINITO;
    vector <int> mejor_solucion;
    vector <int> en_que_subconjunto_esta_cada_nodo;
    while (cantidadDeVecesQueSeLlegoAmejorSol < CANTIDADDEEXITOS ) {
        en_que_subconjunto_esta_cada_nodo = goloso(matriz_de_adyacencias, subconjuntos, k, n);
        en_que_subconjunto_esta_cada_nodo = busqueda_local(matriz_de_adyacencias, subconjuntos, k, n, en_que_subconjunto_esta_cada_nodo);
        int total = 0;
        for (int j = 0; j < k; j++) {
            int aux = 0;
            for (int i = 0; i < subconjuntos[j].size(); i++)
                for (int w = i; w < subconjuntos[j].size(); w++)
                    aux += matriz_de_adyacencias[subconjuntos[j][i]][subconjuntos[j][w]];
            total += aux;
        }
        if (total < min_total) {
            min_total = total;
            mejor_solucion = en_que_subconjunto_esta_cada_nodo;
            cantidadDeVecesQueSeLlegoAmejorSol = 0;
        } else
            cantidadDeVecesQueSeLlegoAmejorSol++;
    }
    return mejor_solucion;
}

int main() {
    int n, m, k;
    cin >> n;
    cin >> m;
    cin >> k;
    vector< vector< int> > matriz_de_adyacencias  = vector< vector< int> >(n, vector<int> (n, 0));
    vector< vector< int> > subconjuntos;
    vector <int> en_que_subconjunto_esta_cada_nodo;
    for (int i = 0; i < k; i++) {
        vector< int> aux;
        subconjuntos.push_back(aux);
    }
    for (int i = 0; i < m; i++) {
        int j, k, p;
        cin >> j;
        cin >> k;
        cin >> p;
        matriz_de_adyacencias[j - 1][k - 1] = p;
        matriz_de_adyacencias[k - 1][j - 1] = p;
    }
    en_que_subconjunto_esta_cada_nodo = grasp(matriz_de_adyacencias, subconjuntos, k, n);
    for (int i = 0; i < n; i++)
        cout << en_que_subconjunto_esta_cada_nodo[i] + 1 << " ";
    cout << endl;
    return 0;
}


