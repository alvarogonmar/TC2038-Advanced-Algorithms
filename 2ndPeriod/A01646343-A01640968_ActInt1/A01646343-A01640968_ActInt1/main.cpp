// Programa que busca codigos maliciosos, palindromos y coincidencias en transmisiones.
// Alvaro Gonzalez Martinez A01646343 | Valeria Fernanda Hernandez Avilan A01640968
// Jueves 1 de Octubre 2026

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// Lee todo el contenido de un archivo de texto.
// Parametros: nombreArchivo indica el archivo a leer y contenido guarda sus caracteres.
// Retorno: true si el archivo se pudo leer y contiene datos; false en caso contrario.
// Complejidad: O(n), donde n es la cantidad de caracteres del archivo.
bool leerArchivo(const string &nombreArchivo, string &contenido) {
	ifstream archivo(nombreArchivo);

	if (!archivo.is_open()) {
		cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
		return false;
	}

	contenido = "";
	char caracter = '\0';

	while (archivo.get(caracter)) {
		contenido += caracter;
	}

	if (contenido.empty()) {
		cerr << "El archivo esta vacio: " << nombreArchivo << endl;
		return false;
	}

	return true;
}

// Construye el arreglo de prefijos y sufijos utilizado por el algoritmo KMP.
// Parametros: codigo contiene la secuencia cuyo arreglo LPS se construye.
// Retorno: vector con la longitud del prefijo valido para cada posicion del codigo.
// Complejidad: O(m), donde m es la longitud del codigo.
vector<size_t> construirLps(const string &codigo) {
	vector<size_t> lps(codigo.length(), 0);
	size_t longitud = 0;
	size_t indice = 1;

	while (indice < codigo.length()) {
		if (codigo[indice] == codigo[longitud]) {
			longitud++;
			lps[indice] = longitud;
			indice++;
		} else {
			if (longitud == 0) {
				lps[indice] = 0;
				indice++;
			} else {
				longitud = lps[longitud - 1];
			}
		}
	}

	return lps;
}

// Busca la primera aparicion de un codigo dentro de una transmision mediante KMP.
// Parametros: transmision contiene los datos y codigo contiene la secuencia buscada.
// Retorno: indice inicial del codigo o string::npos cuando no existe coincidencia.
// Complejidad: O(n + m), donde n y m son las longitudes de la transmision y el codigo.
size_t buscarKmp(const string &transmision, const string &codigo) {
	vector<size_t> lps = construirLps(codigo);
	size_t indiceTransmision = 0;
	size_t indiceCodigo = 0;

	while (indiceTransmision < transmision.length()) {
		if (transmision[indiceTransmision] == codigo[indiceCodigo]) {
			indiceTransmision++;
			indiceCodigo++;

			if (indiceCodigo == codigo.length()) {
				return indiceTransmision - codigo.length();
			}
		} else {
			if (indiceCodigo > 0) {
				indiceCodigo = lps[indiceCodigo - 1];
			} else {
				indiceTransmision++;
			}
		}
	}

	return string::npos;
}

// Verifica si un codigo esta contenido en una transmision e imprime el resultado.
// Parametros: transmision contiene los datos y codigo contiene la secuencia buscada.
// Retorno: no regresa valor; imprime false o true seguido de la posicion inicial.
// Complejidad: O(n + m), por la llamada al algoritmo KMP.
void verificarCodigo(const string &transmision, const string &codigo) {
	size_t posicion = buscarKmp(transmision, codigo);

	if (posicion == string::npos) {
		cout << "false" << endl;
	} else {
		cout << "true " << posicion + 1 << endl;
	}
}

// Encuentra el palindromo mas largo de un texto mediante el algoritmo de Manacher.
// Parametros: contenido es el texto donde se busca el palindromo.
// Retorno: posiciones inicial y final del palindromo, numeradas desde uno.
// Complejidad: O(n), donde n es la longitud del contenido.
tuple<int, int> encontrarPalindromo(const string &contenido) {
	string transformado = "#";

	for (char caracter : contenido) {
		transformado += caracter;
		transformado += '#';
	}

	int longitudTransformada = transformado.size();
	vector<int> radios(longitudTransformada, 0);
	int centro = -1;
	int limiteDerecho = -1;
	int mejorLongitud = 0;
	int mejorCentro = -1;

	for (int indice = 0; indice < longitudTransformada; indice++) {
		if (indice < limiteDerecho) {
			int espejo = 2 * centro - indice;
			radios[indice] = min(radios[espejo], limiteDerecho - indice);
		} else {
			radios[indice] = 0;
		}

		while (indice - radios[indice] - 1 >= 0 &&
			   indice + radios[indice] + 1 < longitudTransformada &&
			   transformado[indice - radios[indice] - 1] ==
			   transformado[indice + radios[indice] + 1]) {
			radios[indice]++;
		}

		if (radios[indice] > mejorLongitud) {
			mejorLongitud = radios[indice];
			mejorCentro = indice;
		}

		if (indice + radios[indice] > limiteDerecho) {
			limiteDerecho = indice + radios[indice];
			centro = indice;
		}
	}

	int inicioTransformado = mejorCentro - mejorLongitud;
	if (transformado[inicioTransformado] == '#') {
		inicioTransformado++;
	}

	int finTransformado = mejorCentro + mejorLongitud;
	if (transformado[finTransformado] == '#') {
		finTransformado--;
	}

	int inicio = (inicioTransformado + 1) / 2;
	int fin = (finTransformado + 1) / 2;
	return make_tuple(inicio, fin);
}

// Encuentra el substring comun mas largo entre dos transmisiones.
// Parametros: primera y segunda contienen las transmisiones que se comparan.
// Retorno: posiciones inicial y final del substring en la primera transmision.
// Complejidad: O(nm), donde n y m son las longitudes de las transmisiones.
tuple<int, int> encontrarSubstringComun(const string &primera, const string &segunda) {
	int filas = primera.size() + 1;
	int columnas = segunda.size() + 1;
	int mejorLongitud = 0;
	int mejorFinal = 0;
	vector<vector<int>> tabla(filas, vector<int>(columnas, 0));

	for (int fila = 1; fila < filas; fila++) {
		for (int columna = 1; columna < columnas; columna++) {
			if (primera[fila - 1] == segunda[columna - 1]) {
				tabla[fila][columna] = tabla[fila - 1][columna - 1] + 1;

				if (tabla[fila][columna] > mejorLongitud) {
					mejorLongitud = tabla[fila][columna];
					mejorFinal = fila;
				}
			} else {
				tabla[fila][columna] = 0;
			}
		}
	}

	int inicio = mejorFinal - mejorLongitud + 1;
	return make_tuple(inicio, mejorFinal);
}

// Lee los archivos, ejecuta los tres analisis solicitados e imprime sus resultados.
// Parametros: no recibe parametros.
// Retorno: 0 si termina correctamente y 1 si algun archivo no se puede leer.
// Complejidad: O(nm), por la busqueda del substring comun mas largo.
int main() {
	string transmision1 = "";
	string transmision2 = "";
	string codigo1 = "";
	string codigo2 = "";
	string codigo3 = "";
	bool archivosCorrectos = true;

	if (!leerArchivo("transmission1.txt", transmision1)) {
		archivosCorrectos = false;
	}
	if (!leerArchivo("transmission2.txt", transmision2)) {
		archivosCorrectos = false;
	}
	if (!leerArchivo("mcode1.txt", codigo1)) {
		archivosCorrectos = false;
	}
	if (!leerArchivo("mcode2.txt", codigo2)) {
		archivosCorrectos = false;
	}
	if (!leerArchivo("mcode3.txt", codigo3)) {
		archivosCorrectos = false;
	}

	if (!archivosCorrectos) {
		return 1;
	}

	verificarCodigo(transmision1, codigo1);
	verificarCodigo(transmision1, codigo2);
	verificarCodigo(transmision1, codigo3);
	verificarCodigo(transmision2, codigo1);
	verificarCodigo(transmision2, codigo2);
	verificarCodigo(transmision2, codigo3);

	tuple<int, int> resultadoPalindromo1 = encontrarPalindromo(transmision1);
	tuple<int, int> resultadoPalindromo2 = encontrarPalindromo(transmision2);

	cout << get<0>(resultadoPalindromo1) << " " << get<1>(resultadoPalindromo1) << endl;
	cout << get<0>(resultadoPalindromo2) << " " << get<1>(resultadoPalindromo2) << endl;

	tuple<int, int> resultadoComun = encontrarSubstringComun(transmision1, transmision2);
	cout << get<0>(resultadoComun) << " " << get<1>(resultadoComun) << endl;

	return 0;
}
