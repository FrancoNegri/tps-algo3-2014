
vector<int> busqueda_local3(vector< vector< int> > & matriz_de_adyacencias, vector< vector< int> > & subconjuntos, int k, int n, vector <int> & en_que_subconjunto_esta_cada_nodo) {
    //aca tengo que empezar a buscar localmente
    bool SeEncontroMejorSol = true;
    while (SeEncontroMejorSol) {
        SeEncontroMejorSol = false;
        for (int i = 0; i < n; i++) {
            int conjuntoActualDe_i = en_que_subconjunto_esta_cada_nodo[i];
            for (int otroNodo = i + 1; otroNodo < subconjuntos[conjuntoActualDe_i].size(); otroNodo++) {
                //Calculo cuanto suma el nodo i en el conjunto donde esta viviendo
                int nodo1, nodo2;
                nodo1 = i;
                nodo2 = subconjuntos[conjuntoActualDe_i][otroNodo];
                int sumaDelConjuntoDe_i = devolverSumaIntraparticion(nodo1, nodo2 , subconjuntos[conjuntoActualDe_i] , matriz_de_adyacencias);
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
                    int sumaPoniendoA_i_enOtroConjunto = devolverSumaIntraparticion(nodo1, nodo2 , subconjuntos[j] , matriz_de_adyacencias);;
                    //y me quedo con el minimo que es el candidato
                    if (sumaPoniendoA_i_enOtroConjunto < suma_conjunto_candidato) {
                        suma_conjunto_candidato = sumaPoniendoA_i_enOtroConjunto;
                        conjunto_candidato = j;
                    }
                }
                //si mejore algo, muevo el nodo i al candidato
                if (suma_conjunto_candidato < sumaDelConjuntoDe_i) {
                    //cout << "pongo el nodo:" << nodo1 << "y el nodo:" << nodo2 << "peso nuevo: " << suma_conjunto_candidato <<  endl;
                    intercambiarNodosDeConjunto(nodo1, nodo2, conjuntoActualDe_i, conjunto_candidato, subconjuntos, en_que_subconjunto_esta_cada_nodo );
                    //Como mejore, reinicio la busqueda local con el nodo i mudado
                    SeEncontroMejorSol = true;
                    break;
                }
            }
        }
    }
    return en_que_subconjunto_esta_cada_nodo;
}


int devolverSumaIntraparticion(int nodo1, int nodo2, vector<int> particion, vector< vector< int> > & matriz_de_adyacencias) {
    int suma = 0;
    for (int j = 0; j < particion.size(); j++) {
        if (particion[j] != nodo1 && particion[j] != nodo2) {
            suma += matriz_de_adyacencias[nodo1][particion[j]];
            suma += matriz_de_adyacencias[nodo2][particion[j]];
        }
    }
    return suma;
}


void intercambiarNodosDeConjunto(int nodo1, int nodo2, int subconjuntoSrs, int subconjuntoDest, vector< vector< int> > & subconjuntos, vector <int> & en_que_subconjunto_esta_cada_nodo) {
    //cambio a i de conjunto
    en_que_subconjunto_esta_cada_nodo[nodo1] = subconjuntoDest;
    en_que_subconjunto_esta_cada_nodo[nodo2] = subconjuntoDest;
    //lo pongo en el conjunto nuevo...
    subconjuntos[subconjuntoDest].push_back(nodo1);
    subconjuntos[subconjuntoDest].push_back(nodo2);
    //lo saco del conjunto viejo...
    for (int aux = 0; aux < subconjuntos[subconjuntoSrs].size(); aux++) {
        if (subconjuntos[subconjuntoSrs][aux] == nodo1) {
            subconjuntos[subconjuntoSrs].erase(subconjuntos[subconjuntoSrs].begin() + aux);
            break;
        }
    }
    for (int aux = 0; aux < subconjuntos[subconjuntoSrs].size(); aux++)
        if (subconjuntos[subconjuntoSrs][aux] == nodo2) {
            subconjuntos[subconjuntoSrs].erase(subconjuntos[subconjuntoSrs].begin() + aux);
            break;
        }
    return;
}