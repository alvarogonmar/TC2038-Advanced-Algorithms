// Programa que ordena una lista de numeros de mayor a menor usando merge sort.
// Alvaro Gonzalez Martinez A01646343 | Valeria Fernanda Hernandez Avilan A01640968
// Miercoles 19 de Agosto 2026

#include <vector>
#include <iostream>
using namespace std;

// Une dos secciones ordenadas del vector list entre left y right.
// Parametros: list es el vector a ordenar; left, mid y right delimitan las secciones.
// Retorno: no regresa valor, modifica el vector recibido.
// Complejidad: O(n), donde n es la cantidad de elementos entre left y right.
void merge(vector<double> &list, int left, int mid, int right)
{

	vector<double> temp(right - left + 1);

	int i = left;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= right)
	{
		if (list[i] > list[j])
		{
			temp[k] = list[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = list[j];
			k++;
			j++;
		}
	}
	while (i <= mid)
	{
		temp[k] = list[i];
		k++;
		i++;
	}
	while (j <= right)
	{
		temp[k] = list[j];
		k++;
		j++;
	}
	for (int x = 0; x < temp.size(); x++)
	{
		list[left + x] = temp[x];
	}
}

// Ordena el vector list de mayor a menor usando el algoritmo merge sort.
// Parametros: list es el vector a ordenar; left y right son los limites del segmento.
// Retorno: no regresa valor, modifica el vector recibido.
// Complejidad: O(n log n), donde n es la cantidad de elementos entre left y right.
void mergeSort(vector<double> &list, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int mid = (left + right) / 2;
	mergeSort(list, left, mid);
	mergeSort(list, mid + 1, right);

	merge(list, left, mid, right);
}

// Lee los datos, ordena la lista e imprime el resultado.
// Parametros: no recibe parametros.
// Retorno: regresa 0 si el programa termina correctamente.
// Complejidad: O(n log n), por la llamada a mergeSort.
int main()
{
	int n;
	cin >> n;
	vector<double> list(n);
	for (int i = 0; i < n; i++)
	{
		cin >> list[i];
	}
	mergeSort(list, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		cout << list[i] << endl;
	}
	return 0;
}
