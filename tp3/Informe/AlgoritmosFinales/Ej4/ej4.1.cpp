
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
        int j, h, p;
        cin >> j;
        cin >> h;
        cin >> p;
        matriz_de_adyacencias[j - 1][h - 1] = p;
        matriz_de_adyacencias[h - 1][j - 1] = p;
    }
    srand (0);
    for (int i = 0; i < n; i++) {
        int conjuntoRandom = rand() % k;
        en_que_subconjunto_esta_cada_nodo.push_back(conjuntoRandom);
    }
    //esta estructura es mas comoda para revisar las sumas
    for (int i = 0; i < n; i++) {
        subconjuntos[en_que_subconjunto_esta_cada_nodo[i]].push_back(i);
    }
    en_que_subconjunto_esta_cada_nodo = busqueda_local(matriz_de_adyacencias, subconjuntos, k, n, en_que_subconjunto_esta_cada_nodo);
    for (int i = 0; i < n; i++)
        cout << en_que_subconjunto_esta_cada_nodo[i] + 1 << " ";
    cout << endl;
    return 0;
}

vector<int> busqueda_local(vector< vector< int> > & matriz_de_adyacencias, vector< vector< int> > & subconjuntos, int k, int n, vector <int> en_que_subconjunto_esta_cada_nodo) {
    //aca tengo que empezar a buscar localmente
    bool SeEncontroMejorSol = true;
    while (SeEncontroMejorSol) {
        SeEncontroMejorSol = false;
        for (int i = 0; i < n; i++) {
            int conjuntoActualDe_i = en_que_subconjunto_esta_cada_nodo[i];
            int sumaDelConjuntoDe_i = 0;
            //Calculo cuanto suma el nodo i en el conjunto donde esta viviendo
            for (int j = 0; j < subconjuntos[conjuntoActualDe_i].size(); j++) {
                sumaDelConjuntoDe_i += matriz_de_adyacencias[i][subconjuntos[conjuntoActualDe_i][j]];
            }
            //Ok, ahora se cuanto peso agrega tener a i en este conjunto en particular
            //hay un conjunto donde i agregue menos peso?
            // busco en mi vecindad, donde meter el nodo i para que sea minimo el peso
            int conjunto_candidato;
            int suma_conjunto_candidato = INFINITO;
            for (int j = 0; j < k; j++) {
                //evito el subconjunto de i
                if (j == conjuntoActualDe_i)
                    continue;
                //para cada conjunto hago la suma
                int sumaPoniendoA_i_enOtroConjunto = 0;
                for (int w = 0; w < subconjuntos[j].size(); w++) {
                    sumaPoniendoA_i_enOtroConjunto += matriz_de_adyacencias[i][subconjuntos[j][w]];
                }
                //y me quedo con el minimo que es el candidato
                if (sumaPoniendoA_i_enOtroConjunto < suma_conjunto_candidato) {
                    suma_conjunto_candidato = sumaPoniendoA_i_enOtroConjunto;
                    conjunto_candidato = j;
                }
            }
            //si mejore algo, muevo el nodo i al candidato
            if (suma_conjunto_candidato < sumaDelConjuntoDe_i) {
                //cambio a i de conjunto
                en_que_subconjunto_esta_cada_nodo[i] = conjunto_candidato;
                //lo pongo en el conjunto nuevo...
                subconjuntos[conjunto_candidato].push_back(i);
                //lo saco del conjunto viejo...
                for (int aux = 0; aux < subconjuntos[conjuntoActualDe_i].size(); aux++) {
                    if (subconjuntos[conjuntoActualDe_i][aux] == i) {
                        subconjuntos[conjuntoActualDe_i].erase(subconjuntos[conjuntoActualDe_i].begin() + aux);
                        break;
                    }
                }
                //Como mejore, reinicio la busqueda local con el nodo i mudado
                SeEncontroMejorSol = true;
                break;
            }
        }
    }
    return en_que_subconjunto_esta_cada_nodo;
}