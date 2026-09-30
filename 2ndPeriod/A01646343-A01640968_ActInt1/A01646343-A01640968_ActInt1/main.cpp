#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

// Lee todo el contenido de un archivo.
// Regresa true si pudo abrirlo y false si no pudo.
bool leerArchivo(string nombreArchivo, string &contenido) {

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return false;
    }

    contenido = "";
    char caracter;

    while (archivo.get(caracter)) {
        contenido += caracter;
    }

    if (contenido.empty()) {
        cerr << "El archivo esta vacio: " << nombreArchivo << endl;
        return false;
    }

    return true;
}


// Construye el arreglo LPS que utiliza KMP
vector<int> construirLPS(string mcode) {

    vector<int> lps(mcode.length(), 0);

    int longitud = 0;
    int i = 1;

    while (i < mcode.length()) {

        if (mcode[i] == mcode[longitud]) {

            longitud++;
            lps[i] = longitud;
            i++;

        } else {

            if (longitud == 0) {
                lps[i] = 0;
                i++;
            } else {
                longitud = lps[longitud - 1];
            }
        }
    }

    return lps;
}


// Busca el mcode dentro de una transmission utilizando KMP
// Regresa el indice donde comienza o -1 si no lo encuentra
int buscarKMP(string transmission, string mcode) {

    vector<int> lps = construirLPS(mcode);

    int i = 0;
    int j = 0;

    while (i < transmission.length()) {

        if (transmission[i] == mcode[j]) {

            i++;
            j++;

            if (j == mcode.length()) {
                return i - mcode.length();
            }

        } else {

            if (j > 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return -1;
}


// Imprime si el mcode fue encontrado y su posicion
void verificarMcode(string transmission, string mcode) {

    int posicion = buscarKMP(transmission, mcode);

    if (posicion == -1) {
        cout << "false" << endl;
    } else {
        // +1 porque el problema pide posiciones comenzando desde 1
        cout << "true " << posicion + 1 << endl;
    }
}

tuple<int,int> palindromo(string contenido){
    string transformado = "#";

    for (char c : contenido){
        transformado += c;
        transformado += '#';
    }

    int n = transformado.size(); //tamaño de contenido
    vector<int>P(n,0); //llenar de ceros

    int C = -1; //centro cuando la derecha ya avanzó
    int R = -1; //derecha mas avanzada
    int best = 0; //mejor largo de palindromo
    int indexBest = -1; //centro del mejor palindromo

    for(int i = 0; i < n; i++){
        if(i < R){ //cuando i si esta en el rango de R
            int mirror = 2*C - i;
            P[i] = min(P[mirror],R - i );
        }
        else{
            P[i] = 0;
        }
        
        while((i - P[i] - 1) >= 0 && (i + P[i] + 1) < n &&  transformado[i - P[i] - 1] == transformado[i + P[i] + 1]){
            P[i] = P[i] + 1;
        }

        if (best < P[i]){
            best = P[i];
            indexBest = i;
        }

        if(R < i + P[i]){
            R = i + P[i];
            C = i;
        }
    }

    int inicioTransformado = indexBest - best;
    if (transformado[inicioTransformado] == '#'){
        inicioTransformado++;
    }

    int finTransformado = indexBest + best;
    if (transformado[finTransformado] == '#'){
        finTransformado--;
    }

    return make_tuple((inicioTransformado + 1) / 2, (finTransformado + 1) / 2);
}

// Parte 3: encuentra el substring comun mas largo entre las dos transmisiones
tuple<int,int> LCS(string a1, string a2) {

    int filas = a1.size() + 1;
    int columnas = a2.size() + 1;

    int bestL = 0;
    int bestI = 0;

    vector<vector<int>> DP(
        filas, vector<int>(columnas, 0)
    );

    DP[0][0] = 0;

    for (int i = 1; i < filas; i++) {

        for (int j = 1; j < columnas; j++) {

            if (a1[i - 1] == a2[j - 1]) {

                DP[i][j] = DP[i - 1][j - 1] + 1;

                if (DP[i][j] > bestL) {
                    bestL = DP[i][j];
                    bestI = i;
                }

            } else {

                DP[i][j] = 0;

            }
        }
    }

    int inicio = bestI - bestL + 1;

    return make_tuple(inicio, bestI);
}

int main() {

    string transmission1;
    string transmission2;
    string mcode1;
    string mcode2;
    string mcode3;

    bool archivosCorrectos = true;

    // Leer las dos transmisiones
    if (!leerArchivo("transmission1.txt", transmission1)) {
        archivosCorrectos = false;
    }
    if (!leerArchivo("transmission2.txt", transmission2)) {
        archivosCorrectos = false;
    }

    // Leer los tres codigos maliciosos
    if (!leerArchivo("mcode1.txt", mcode1)) {
        archivosCorrectos = false;
    }
    if (!leerArchivo("mcode2.txt", mcode2)) {
        archivosCorrectos = false;
    }
    if (!leerArchivo("mcode3.txt", mcode3)) {
        archivosCorrectos = false;
    }

    // Terminar el programa si falto algun archivo
    if (!archivosCorrectos) {
        return 1;
    }

    // Parte 1: buscar cada mcode en cada transmission
    verificarMcode(transmission1, mcode1);
    verificarMcode(transmission1, mcode2);
    verificarMcode(transmission1, mcode3);

    verificarMcode(transmission2, mcode1);
    verificarMcode(transmission2, mcode2);
    verificarMcode(transmission2, mcode3);

    // Parte 2: palindromo mas largo de cada transmission
    tuple<int, int> resultado1 = palindromo(transmission1);
    tuple<int, int> resultado2 = palindromo(transmission2);

    cout << get<0>(resultado1) << " " << get<1>(resultado1) << endl;
    cout << get<0>(resultado2) << " " << get<1>(resultado2) << endl;

    // Parte 3: substring comun mas largo entre las dos transmisiones
    tuple<int, int> resultado3 = LCS(transmission1, transmission2);

    cout << get<0>(resultado3) << " " << get<1>(resultado3) << endl;

    return 0;
}
