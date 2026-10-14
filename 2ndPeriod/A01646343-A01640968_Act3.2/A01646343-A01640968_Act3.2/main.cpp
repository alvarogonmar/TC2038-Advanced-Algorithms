// Actividad 3.2 - Dijkstra y Floyd
// Matrículas: A01646343 y A01640968

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Valor reservado para indicar que no se conoce un camino.
const int INF = 2147483647;

// Equivale a mindistance(Q, dist) del pseudocodigo.
// Q contiene implicitamente los nodos que todavia no pertenecen a S.
int minDistance(const vector<int>& dist, const vector<bool>& S) {
    int u = -1;
    for (int v = 0; v < static_cast<int>(dist.size()); v++) {
        if (!S[v] && (u == -1 || dist[v] < dist[u])) {
            u = v;
        }
    }
    return u;
}

// Calcula las distancias desde s. Complejidad: O(n^2).
vector<int> dijkstra(const vector<vector<int>>& grafo, int s) {
    int n = grafo.size();
    vector<int> dist(n, INF);
    dist[s] = 0;

    // S empieza vacio: ningun nodo tiene su distancia definitiva.
    vector<bool> S(n, false);
    int pendientes = n; // Inicialmente Q contiene todos los nodos.

    while (pendientes > 0) {
        int u = minDistance(dist, S);

        // No quedan nodos alcanzables; evita sumar pesos a INF.
        if (u == -1 || dist[u] == INF) {
            break;
        }

        S[u] = true; // S = S union {u}; retirar u de Q.
        pendientes--;

        for (int v = 0; v < n; v++) {
            // -1 indica que no hay arco; 0 es un peso valido.
            if (!S[v] && grafo[u][v] != -1) {
                // Relax(u, v, w): mejorar dist[v] pasando por u.
                // Comprobar que la suma cabe en un int antes de realizarla.
                if (dist[u] <= INF - grafo[u][v] &&
                    dist[v] > dist[u] + grafo[u][v]) {
                    dist[v] = dist[u] + grafo[u][v];
                }
            }
        }
    }

    return dist;
}

void Floyd(int nodos, vector<vector<int>> matrix){
    vector<vector<int>>dist(nodos, vector<int>(nodos)); //matriz de distancias
    const int INF = 2147483647; //numero más grande que acepta un int

    //crear matriz cambiando -1 por infinitos
    for(int i = 0; i < nodos; i++){
        for(int j = 0; j < nodos; j ++){
            if (matrix[i][j] == -1){
                dist[i][j] = INF;
            }
            else{
                dist[i][j] = matrix[i][j];
            }
        }
    }

    //recalcular pasos para llegar nodo final, pasando por k como intermedio
    for(int k = 0; k < nodos; k ++){
        for(int i = 0; i < nodos; i ++){
            for(int j = 0; j < nodos; j ++){
                if (dist[i][k] != INF && dist[k][j] != INF) { //evitar error por suma de infinitos
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    //imprimir matriz
    for(int i = 0; i < nodos; i++){
        for(int j = 0; j < nodos; j ++){
            cout<<dist[i][j]<<" ";
        }
        cout<<"\n";
    }
}


int main() {
    int n;
    cin >> n;

    vector<vector<int>> grafo(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grafo[i][j];
        }
    }

    cout << "Dijkstra :\n";
    for (int origen = 0; origen < n; origen++) {
        vector<int> distancia = dijkstra(grafo, origen);

        for (int destino = 0; destino < n; destino++) {
            if (origen != destino) {
                cout << "node " << origen + 1
                     << " to node " << destino + 1 << " : "
                     << (distancia[destino] == INF ? -1 : distancia[destino])
                     << '\n';
            }
        }
    }

    cout << "\nFloyd :\n";
    Floyd(n, grafo);

    return 0;
}
