// Programa que genera y ordena alfabeticamente todos los sufijos de una cadena.
// Alvaro Gonzalez Martinez A01646343 | Valeria Fernanda Hernandez Avilan A01640968
// Lunes 21 de Septiembre 2026

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Genera todos los sufijos de una cadena y los ordena alfabeticamente.
// Parametros: cadena es la palabra original y sufijos almacena los resultados.
// Retorno: no regresa valor, modifica el vector de sufijos.
// Complejidad: O(n^2 log n), considerando la creacion y el ordenamiento de los sufijos.
void generarSufijos(const string &cadena, vector<string> &sufijos) {
	if (cadena.empty()) {
		return;
	}

	string sufijo = "";
	int cantidadCaracteres = cadena.length();

	for (int indice = cantidadCaracteres - 1; indice >= 0; indice--) {
		sufijo = cadena[indice] + sufijo;
		sufijos.push_back(sufijo);
	}

	sort(sufijos.begin(), sufijos.end());
}

// Lee una cadena, valida que exista entrada y muestra sus sufijos ordenados.
// Parametros: no recibe parametros.
// Retorno: regresa 0 si el programa termina correctamente.
// Complejidad: O(n^2 log n), por la generacion y el ordenamiento de los sufijos.
int main() {
	string cadena = "";

	cout << "Introduce una palabra: ";

	if (!(cin >> cadena)) {
		cout << "No se ingreso ninguna palabra." << endl;
		return 0;
	}

	vector<string> sufijos;
	generarSufijos(cadena, sufijos);

	for (const string &sufijo : sufijos) {
		cout << sufijo << endl;
	}

	return 0;
}
