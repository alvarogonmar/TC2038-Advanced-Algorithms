// Programa que calcula el cambio de monedas usando programacion dinamica y algoritmo avaro.
// Alvaro Gonzalez Martinez A01646343 | Valeria Fernanda Hernandez Avilan A01640968
// Miercoles 26 de Agosto 2026

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Calcula la cantidad minima de monedas para dar cambio usando programacion dinamica.
// Parametros: change es el cambio a entregar; coins contiene las denominaciones;
// quantities guarda cuantas monedas de cada denominacion se utilizan.
// Retorno: no regresa valor, imprime y modifica el vector quantities.
// Complejidad: O(nm), donde n es la cantidad de monedas y m es el cambio.
void dpChange(int change, const vector<int> &coins, vector<int> &quantities) {
    int coinCount = coins.size();
    vector<int> dp(change + 1, change + 1);
    vector<int> selectedCoin(change + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= change; i++) {
        for (int j = 0; j < coinCount; j++) {
            if (i >= coins[j]) {
                int candidate = dp[i - coins[j]] + 1;

                if (candidate < dp[i]) {
                    dp[i] = candidate;
                    selectedCoin[i] = j;
                }
            }
        }
    }
    int remaining = change;

    while (remaining > 0) {
        int coinIndex = selectedCoin[remaining];

        if (coinIndex == -1) {
            cout << "No es posible dar el cambio exacto." << endl;
            return;
        }

        quantities[coinIndex]++;
        remaining = remaining - coins[coinIndex];
    }
    for (int i = coinCount - 1; i >= 0; i--) {
        cout << "Monedas de " << coins[i] << ": "
             << quantities[i] << endl;
    }
}

// Calcula el cambio tomando primero las monedas de mayor denominacion disponibles.
// Parametros: change es el cambio a entregar; coins contiene las denominaciones;
// quantities guarda cuantas monedas de cada denominacion se utilizan.
// Retorno: no regresa valor, imprime y modifica el vector quantities.
// Complejidad: O(n), donde n es la cantidad de denominaciones de monedas.
void avaroChange(int change, const vector<int> &coins, vector<int> &quantities) {
    int coinCount = coins.size();
    int remaining = change;

    for (int i = coinCount - 1; i >= 0; i--) {
        if (coins[i] <= remaining) {
            quantities[i] = remaining / coins[i];
            remaining = remaining % coins[i];
        }
    }
    for (int i = coinCount - 1; i >= 0; i--) {
        cout << "Monedas de " << coins[i] << ": " << quantities[i] << endl;
    }
}

// Lee las denominaciones, calcula el cambio e imprime las soluciones con DP y avaro.
// Parametros: no recibe parametros.
// Retorno: regresa 0 si el programa termina correctamente.
// Complejidad: O(nm), por la llamada a dpChange.
int main() {
    int coinCount;
    int price;
    int payment;

    cout << "Introduzca la cantidad de monedas que tiene:" << endl;
    cin >> coinCount;

    vector<int> coins(coinCount);

    cout << "Introduzca las denominaciones de las monedas que tiene:" << endl;
    for (int i = 0; i < coinCount; i++) {
        cin >> coins[i];
    }

    sort(coins.begin(), coins.end());

    cout << "Introduzca el precio del producto:" << endl;
    cin >> price;

    cout << "Introduzca el dinero que recibio del cliente:" << endl;
    cin >> payment;

    int change = payment - price;

    if (change < 0) {
        cout << "El dinero recibido no alcanza para pagar el producto." << endl;
        return 0;
    }

    vector<int> avaroResult(coinCount, 0);
    vector<int> dpResult(coinCount, 0);

    cout << "DP" << endl;
    dpChange(change, coins, dpResult);

    cout << "Avaro" << endl;
    avaroChange(change, coins, avaroResult);
    return 0;
}
