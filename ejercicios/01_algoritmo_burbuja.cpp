#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int ciclos = 0;
    int pasos = 0;
    int opc = 0;
    int n = 0;
    
    cout << "Ingresa el numero de la opcion:" << endl;
    cout << "0 - Ingresar numeros manualmente" << endl;
    cout << "1 - Generar numeros aleatorios" << endl;
    cout << "Opcion: ";
    cin >> opc;
    
    if (opc == 0) {
        cout << "Ingresa el numero de elementos: ";
        cin >> n;
        int arr[100];
        cout << "Ingresa los " << n << " numeros: ";
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        
        cout << "\nArreglo Original: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        
        for (int i = 0; i < n - 1; i++) {
            ciclos++;
            for (int j = 0; j < n - i - 1; j++) {
                pasos++;
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        
        cout << "Arreglo Ordenado: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    } 
    else if (opc == 1) {
        cout << "Ingresa el numero de elementos: ";
        cin >> n;
        int arr[100];
        srand(time(0));
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100 + 1;
        }
        
        cout << "\nArreglo Original: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        
        for (int i = 0; i < n - 1; i++) {
            ciclos++;
            for (int j = 0; j < n - i - 1; j++) {
                pasos++;
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        
        cout << "Arreglo Ordenado: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    cout << "\n--- ESTADISTICAS ---" << endl;
    cout << "Numero de ciclos (for externo): " << ciclos << endl;
    cout << "Numero de pasos (for interno): " << pasos << endl;
    cout << "Numero de movimientos (swaps): " << (pasos - ciclos) << endl;
    return 0;
}