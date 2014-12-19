//idea: en cada paso, tomo un vertice, me fijo en que subconjunto minimiza la suma, y lo agrego ahi.

vector<int> goloso(vector< vector< int> > & matriz_de_adyacencias, vector< vector< int> > & noseusa, int k, int n) {
    //hasta aca cree todos las estructuras de datos que voy a necesitar.
    vector< vector< int> > subconjuntos;
    for (int i = 0; i < k; i++) {
        vector< int> aux;
        subconjuntos.push_back(aux);
    }
    vector<int> en_que_subconjunto_esta_cada_nodo;
    vector<int> nodos;
    for (int i = 0; i < n; i++) {
        nodos.push_back(i);
    }
    //meto el nodo 1 en cualquiera de los conjuntos, por ahora son todos iguales.
    en_que_subconjunto_esta_cada_nodo.push_back(nodos[0]);
    //del punto de arriba, el nodo 1 va a ir en el subconjunto 1, asi que tambien digo eso.
    en_que_subconjunto_esta_cada_nodo.resize(n);
    subconjuntos[0].push_back(nodos[0]);
    for (int i = 1; i < n; i++ ) {
        //tomo el vertice i
        int menorSuma = INFINITO;
        int menorConjunto = 0;
        for (int j = 0; j < k; j++) {
            //para cada conjunto
            int aux = 0;
            for (int w = 0; w < subconjuntos[j].size(); w++) {
                //veo cuanto "peso" suma agregar este vertice a este conjunto determinado
                int candidato = subconjuntos[j][w];
                aux += matriz_de_adyacencias[nodos[i]][candidato];
            }
            //me guardo el conjunto que minimiza la suma
            if (aux < menorSuma) {
                menorSuma = aux;
                menorConjunto = j;
            }
        }
        //agrego el verice i al conjunto que minimiza la suma
        subconjuntos[menorConjunto].push_back(nodos[i]);
        en_que_subconjunto_esta_cada_nodo[nodos[i]] = menorConjunto;
    }
    noseusa = subconjuntos;
    return en_que_subconjunto_esta_cada_nodo;;
}



int main() {
    int n, m, k;
    cin >> n;
    cin >> m;
    cin >> k;
    vector< vector< int> > matriz_de_adyacencias  = vector< vector< int> >(n, vector<int> (n, 0));
    vector< vector< int> > subconjuntos;
    vector<int> en_que_subconjunto_esta_cada_nodo;
    for (int i = 0; i < k; i++) {
        vector< int> aux;
        subconjuntos.push_back(aux);
    }
    for (int i = 0; i < m; i++) {
        int j, h, p;
        cin >> j;
        cin >> h;
        cin >> p;
        matriz_de_adyacencias[j - 1][h - 1] = p;
        matriz_de_adyacencias[h - 1][j - 1] = p;
    }
    en_que_subconjunto_esta_cada_nodo = goloso(matriz_de_adyacencias, subconjuntos, k, n);
    for (int i = 0; i < n; i++)
        cout << en_que_subconjunto_esta_cada_nodo[i] + 1 << " ";
    cout << endl;
    return 0;
}