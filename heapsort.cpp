#include <iostream>
using namespace std;

#define PAI(x) (((x) - 1) / 2)
#define ESQ(x) (2 * (x) + 1)
#define DIR(x) (2 * (x) + 2)

// Função heapify padrão do heapsort 
// TODO: Implementar versão k-way 
template <typename T>
void heapify(T arr[], int n, int i) {
    int largest = i;
    int left = ESQ(i);
    int right = DIR(i);

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

int main() {
    const int MAX_SIZE = 100;
    double arr[MAX_SIZE]; 
    int n = 0;

    cout << "Digite os elementos:" << endl;

    while (cin >> arr[n] && n < MAX_SIZE) {
        n++;
    }

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Estrutura base do heapsort
    // Checar se ta funcionando corretamente
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

    cout << "\nVetor:" << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;
    return 0;
}
