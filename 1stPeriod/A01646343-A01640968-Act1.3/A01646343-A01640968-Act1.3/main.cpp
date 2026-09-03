// Programa que resuelve un laberinto usando backtracking y ramificacion y poda.
// Alvaro Gonzalez Martinez A01646343 | Valeria Fernanda Hernandez Avilan A01640968
// Miercoles 03 de Septiembre 2026

#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

// Imprime una matriz de enteros con espacios entre columnas.
// Parametros: matriz contiene los valores a imprimir.
// Retorno: no regresa valor, imprime la matriz recibida.
// Complejidad: O(mn), donde m es la cantidad de filas y n de columnas.
void imprimirMatriz(const vector<vector<int>> &matriz) {
    int M = matriz.size();
    int N = matriz[0].size();

    // Recorre cada posicion para imprimir la matriz completa.
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriz[i][j];

            if (j < N - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

// Encuentra un camino en el laberinto usando backtracking.
// Parametros: laberinto es la matriz original; res guarda el camino encontrado;
// coordenada contiene la casilla actual.
// Retorno: true si existe un camino desde coordenada hasta la meta, false si no.
// Complejidad: O(4^(mn)), donde m es la cantidad de filas y n de columnas.
bool backtracking(vector<vector<int>> &laberinto, vector<vector<int>> &res, tuple<int, int> coordenada) {
    int x = get<0>(coordenada);
    int y = get<1>(coordenada);
    int M = laberinto.size();
    int N = laberinto[0].size();

    res[x][y] = 1;

    // Caso base: si llego a la meta, el camino ya esta completo.
    if (x == M - 1 && y == N - 1) {
        return true;
    }

    // Intenta avanzar a la izquierda si la casilla es valida.
    if (y - 1 >= 0 && laberinto[x][y - 1] == 1 && res[x][y - 1] == 0) {
        if (backtracking(laberinto, res, make_tuple(x, y - 1))) {
            return true;
        }
    }

    // Intenta avanzar hacia abajo.
    if (x + 1 < M && laberinto[x + 1][y] == 1 && res[x + 1][y] == 0) {
        if (backtracking(laberinto, res, make_tuple(x + 1, y))) {
            return true;
        }
    }

    // Intenta avanzar hacia arriba.
    if (x - 1 >= 0 && laberinto[x - 1][y] == 1 && res[x - 1][y] == 0) {
        if (backtracking(laberinto, res, make_tuple(x - 1, y))) {
            return true;
        }
    }

    // Intenta avanzar a la derecha.
    if (y + 1 < N && laberinto[x][y + 1] == 1 && res[x][y + 1] == 0) {
        if (backtracking(laberinto, res, make_tuple(x, y + 1))) {
            return true;
        }
    }

    // Si ningun vecino sirve, se desmarca la casilla y se regresa.
    res[x][y] = 0;
    return false;
}

// Explora caminos posibles y poda ramas que ya no pueden mejorar la solucion.
// Parametros: laberinto es la matriz original; camino guarda la ruta actual;
// mejorCamino guarda la mejor ruta encontrada; coordenada contiene la casilla actual;
// pasos indica la longitud actual; mejorLongitud guarda la menor longitud encontrada.
// Retorno: true si encontro al menos un camino hacia la meta, false si no.
// Complejidad: O(4^(mn)), donde m es la cantidad de filas y n de columnas.
bool ramificacionPodaAux(vector<vector<int>> &laberinto, vector<vector<int>> &camino,
                         vector<vector<int>> &mejorCamino, tuple<int, int> coordenada,
                         int pasos, int &mejorLongitud) {
    int M = laberinto.size();
    int N = laberinto[0].size();
    int x = get<0>(coordenada);
    int y = get<1>(coordenada);
    bool encontroCamino = false;

    // Poda: si esta rama ya es igual o peor que la mejor, se corta.
    if (pasos >= mejorLongitud) {
        return false;
    }

    camino[x][y] = 1;

    // Si llega a la meta, actualiza el mejor camino encontrado.
    if (x == M - 1 && y == N - 1) {
        mejorLongitud = pasos;
        mejorCamino = camino;
        camino[x][y] = 0;
        return true;
    }

    // izquierda
    if (y - 1 >= 0 && laberinto[x][y - 1] == 1 && camino[x][y - 1] == 0) {
        if (ramificacionPodaAux(laberinto, camino, mejorCamino, make_tuple(x, y - 1),
                                pasos + 1, mejorLongitud)) {
            encontroCamino = true;
        }
    }

    // abajo
    if (x + 1 < M && laberinto[x + 1][y] == 1 && camino[x + 1][y] == 0) {
        if (ramificacionPodaAux(laberinto, camino, mejorCamino, make_tuple(x + 1, y),
                                pasos + 1, mejorLongitud)) {
            encontroCamino = true;
        }
    }

    // arriba
    if (x - 1 >= 0 && laberinto[x - 1][y] == 1 && camino[x - 1][y] == 0) {
        if (ramificacionPodaAux(laberinto, camino, mejorCamino, make_tuple(x - 1, y),
                                pasos + 1, mejorLongitud)) {
            encontroCamino = true;
        }
    }

    // derecha
    if (y + 1 < N && laberinto[x][y + 1] == 1 && camino[x][y + 1] == 0) {
        if (ramificacionPodaAux(laberinto, camino, mejorCamino, make_tuple(x, y + 1),
                                pasos + 1, mejorLongitud)) {
            encontroCamino = true;
        }
    }

    camino[x][y] = 0;
    return encontroCamino;
}

// Encuentra el camino mas corto usando ramificacion y poda.
// Parametros: laberinto es la matriz original; res guarda el mejor camino encontrado.
// Retorno: true si existe un camino desde el origen hasta la meta, false si no.
// Complejidad: O(4^(mn)), donde m es la cantidad de filas y n de columnas.
bool ramificacionPoda(vector<vector<int>> &laberinto, vector<vector<int>> &res) {
    int M = laberinto.size();
    int N = laberinto[0].size();
    int mejorLongitud = M * N + 1;
    vector<vector<int>> camino(M, vector<int>(N, 0));

    // Si inicio o meta son pared, no existe solucion.
    if (laberinto[0][0] == 0 || laberinto[M - 1][N - 1] == 0) {
        return false;
    }

    return ramificacionPodaAux(laberinto, camino, res, make_tuple(0, 0), 1, mejorLongitud);
}

// Lee el laberinto, obtiene soluciones con ambas tecnicas e imprime los resultados.
// Parametros: no recibe parametros.
// Retorno: regresa 0 si el programa termina correctamente.
// Complejidad: O(4^(mn)), por la llamada a backtracking.
int main() {
    int M = 0;
    int N = 0;

    cin >> M;
    cin >> N;

    // Crear laberinto M x N
    vector<vector<int>> laberinto(M, vector<int>(N));

    // Leer laberinto
    // Guarda cada 0 o 1 en su fila y columna correspondiente.
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> laberinto[i][j];
        }
    }

    // Matrices resultado inicialmente llenas de 0
    vector<vector<int>> resBacktracking(M, vector<int>(N, 0));
    vector<vector<int>> resPoda(M, vector<int>(N, 0));

    // Coordenada inicial
    tuple<int, int> inicio = make_tuple(0, 0);

    // Ejecutar backtracking
    if (laberinto[0][0] == 1 && laberinto[M - 1][N - 1] == 1) {
        backtracking(laberinto, resBacktracking, inicio);
    }

    // Ejecutar ramificacion y poda
    ramificacionPoda(laberinto, resPoda);

    // Imprimir solución de backtracking
    imprimirMatriz(resBacktracking);
    cout << endl;

    // Imprimir solución de ramificacion y poda
    imprimirMatriz(resPoda);

    return 0;
}
