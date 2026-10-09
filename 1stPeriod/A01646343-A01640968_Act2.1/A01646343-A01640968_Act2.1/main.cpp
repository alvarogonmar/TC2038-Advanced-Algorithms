// Programa que calcula el hash hexadecimal de un archivo de texto.
// Alvaro Gonzalez Martinez A01646343 | Valeria Fernanda Hernandez Avilan A01640968
// Lunes 21 de Septiembre 2026

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Calcula el hash de un archivo sumando los valores ASCII de cada columna.
// Parametros: nombreArchivo es el archivo de entrada y n es el tamano del hash en bits.
// Retorno: cadena hexadecimal de longitud n/4; regresa una cadena vacia si no abre el archivo.
// Complejidad: O(m + n), donde m es la cantidad de caracteres del archivo.
string calcularHash(const string &nombreArchivo, int n) {
	ifstream archivo(nombreArchivo, ios::binary);

	if (!archivo.is_open()) {
		return "";
	}

	// Cada posicion almacena un byte y genera dos digitos hexadecimales.
	// Por eso n bits necesitan n/8 posiciones y producen n/4 digitos.
	int cantidadColumnas = n / 8;
	vector<int> sumas(cantidadColumnas, 0);

	char caracter;
	int cantidadCaracteres = 0;

	while (archivo.get(caracter)) {
		int columna = cantidadCaracteres % cantidadColumnas;
		sumas[columna] += static_cast<unsigned char>(caracter);
		cantidadCaracteres++;
	}

	// Si el ultimo renglon esta incompleto, sus espacios faltantes valen n.
	int columnasOcupadas = cantidadCaracteres % cantidadColumnas;
	if (columnasOcupadas != 0) {
		for (int columna = columnasOcupadas; columna < cantidadColumnas; columna++) {
			sumas[columna] += n;
		}
	}

	// ostringstream convierte las sumas a hexadecimal y permite agregar
	// automaticamente mayusculas y ceros para completar los dos digitos.
	ostringstream resultado;
	resultado << uppercase << hex << setfill('0');

	for (int suma : sumas) {
		resultado << setw(2) << (suma % 256);
	}

	return resultado.str();
}

// Lee el nombre del archivo y n, valida los datos e imprime el hash.
// Parametros: no recibe parametros.
// Retorno: 0 si termina correctamente y 1 si ocurre un error.
// Complejidad: O(m + n), donde m es la cantidad de caracteres del archivo.
int main() {
	string nombreArchivo;
	int n;

	if (!(cin >> nombreArchivo >> n)) {
		cerr << "Entrada invalida." << endl;
		return 1;
	}

	// El formato de dos digitos por posicion requiere bytes completos.
	if (n < 16 || n > 64 || n % 8 != 0) {
		cerr << "n debe ser multiplo de 8 y estar entre 16 y 64." << endl;
		return 1;
	}

	string hash = calcularHash(nombreArchivo, n);
	if (hash.empty()) {
		cerr << "No se pudo abrir el archivo." << endl;
		return 1;
	}

	cout << hash << endl;
	return 0;
}
