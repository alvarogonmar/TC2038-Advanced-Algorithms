#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dpChange(int change, const vector<int> &coins, vector<int> &quantities)
{
    int N = coins.size();
    vector<int> dp(change + 1, change + 1);
    vector<int> selectedCoin(change + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= change; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i >= coins[j])
            {
                int candidate = dp[i - coins[j]] + 1;

                if (candidate < dp[i])
                {
                    dp[i] = candidate;
                    selectedCoin[i] = j;
                }
            }
        }
    }
    int remaining = change;

    while (remaining > 0)
    {
        int coinIndex = selectedCoin[remaining];

        if (coinIndex == -1)
        {
            cout << "No es posible dar el cambio exacto." << endl;
            return;
        }

        quantities[coinIndex]++;
        remaining = remaining - coins[coinIndex];
    }
    for (int i = N - 1; i >= 0; i--)
    {
        cout << "Monedas de " << coins[i] << ": "
             << quantities[i] << endl;
    }
}

void avaroChange(int change, const vector<int> &coins, vector<int> &quantities)
{
    int N = coins.size();
    int remaining = change;

    for (int i = N - 1; i >= 0; i--)
    {
        if (coins[i] <= remaining)
        {
            quantities[i] = remaining / coins[i];
            remaining = remaining % coins[i];
        }
    }
    for (int i = N - 1; i >= 0; i--)
    {
        cout << "Monedas de " << coins[i] << ": " << quantities[i] << endl;
    }
}

int main()
{
    int N;
    int P;
    int Q;
    cout << "Introduzca la cantidad de monedas que tiene:" << endl;
    cin >> N;
    vector<int> coins(N);
    cout << "Introduzca las denominaciones de las monedas que tiene:" << endl;
    for (int i = 0; i < N; i++)
    {
        cin >> coins[i];
    }
    sort(coins.begin(), coins.end());
    cout << "Introduzca el precio del producto:" << endl;
    cin >> P;
    cout << "Introduzca el dinero que recibio del cliente:" << endl;
    cin >> Q;
    int change = Q - P;
    vector<int> avaroResult(N, 0);
    vector<int> dpResult(N, 0);

    cout << "DP" << endl;
    dpChange(change, coins, dpResult);

    cout << "Avaro" << endl;
    avaroChange(change, coins, avaroResult);
    return 0;
}