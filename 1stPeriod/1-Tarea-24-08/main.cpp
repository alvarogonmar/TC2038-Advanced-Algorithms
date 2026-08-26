#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// You have to run nine jobs, with running times of 3,5,6,10,11,14,15,18 and 20 minutes. You have three processors on which you can run these jobs.
// You decide to do the longest-running jobs first on whatever processor is available

void minimumPossible(int N, vector<int> minutes)
{
    int suma = 0;
    for (int i = 0; i < minutes.size(); i++)
    {
        suma = suma + minutes[i];
    }

    int minimum = suma / N;
    vector<int> processors(N, 0);

    sort(minutes.begin(), minutes.end());

    int i = minutes.size() - 1;

    // Colocar los N trabajos más grandes
    for (int j = 0; j < N; j++)
    {
        processors[j] = minutes[i];
        i--;
    }

    // Colocar los trabajos restantes
    for (; i >= 0; i--)
    {
        for (int j = 0; j < N; j++)
        {
            if (processors[j] + minutes[i] <= minimum)
            {
                processors[j] += minutes[i];
                break;
            }
        }
    }

    cout << "Minimo posible: " << minimum << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "Procesador " << i + 1
             << ": " << processors[i] << " minutos" << endl;
    }
}

int main()
{
    vector<int> minutes = {3, 5, 6, 10, 11, 14, 15, 18, 20};

    minimumPossible(3, minutes);
    return 0;
}