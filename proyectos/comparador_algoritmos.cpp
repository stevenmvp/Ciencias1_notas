#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>

struct DetallePasos {
    long long ciclos = 0;
    long long organizacion = 0;
    long long otros = 0;

    void mostrar(std::string nombre) {
        std::cout << "\n================================";
        std::cout << "\n  RESULTADOS: " << nombre;
        std::cout << "\n================================";
        std::cout << "\nPasos de Ciclo:        " << ciclos;
        std::cout << "\nPasos de Organizacion: " << organizacion;
        std::cout << "\nOtros (Comparaciones): " << otros;
        std::cout << "\n--------------------------------";
        std::cout << "\nTOTAL DE PASOS:        " << (ciclos + organizacion + otros) << "\n";
    }
};

// --- Algoritmo de Burbuja ---
DetallePasos burbuja(std::vector<int>& arr) {
    DetallePasos dp;
    int n = arr.size();
    dp.otros++; 
    for (int i = 0; i < n - 1; i++) {
        dp.ciclos++; 
        for (int j = 0; j < n - i - 1; j++) {
            dp.ciclos++; 
            dp.otros++; 
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                dp.organizacion += 3; 
            }
            dp.ciclos++; 
        }
        dp.ciclos++; 
        dp.ciclos++; 
    }
    dp.ciclos++; 
    return dp;
}

// --- Algoritmo de Inserción ---
DetallePasos insercion(std::vector<int>& arr) {
    DetallePasos dp;
    int n = arr.size();
    dp.otros++; 
    for (int i = 1; i < n; i++) {
        dp.ciclos++; 
        int clave = arr[i];
        int j = i - 1;
        dp.organizacion += 2; 
        while (j >= 0 && arr[j] > clave) {
            dp.ciclos++; 
            dp.otros += 2; 
            arr[j + 1] = arr[j];
            j--;
            dp.organizacion += 2; 
        }
        dp.otros++; 
        arr[j + 1] = clave;
        dp.organizacion++; 
        dp.ciclos++; 
    }
    dp.ciclos++; 
    return dp;
}

void imprimirArreglo(const std::vector<int>& arr) {
    std::cout << "[ ";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << (i == arr.size() - 1 ? "" : ", ");
    }
    std::cout << " ]\n";
}

int main() {
    srand(time(0));
    int tam;
    char permitirRepetidos;
    
    std::cout << "--- CONFIGURACION DEL EXPERIMENTO ---\n";
    std::cout << "Ingrese el tamano del arreglo: ";
    std::cin >> tam;
    std::cout << "Permitir numeros repetidos? (s/n): ";
    std::cin >> permitirRepetidos;

    std::vector<int> original;
    
    if (permitirRepetidos == 'n' || permitirRepetidos == 'N') {
        std::set<int> sinDuplicados;
        // Rango amplio para asegurar que encontremos suficientes números únicos
        while (sinDuplicados.size() < tam) {
            sinDuplicados.insert(rand() % (tam * 10)); 
        }
        for (int x : sinDuplicados) original.push_back(x);
        
        // Mezclamos el conjunto porque 'set' lo guarda ordenado
        for (int i = 0; i < tam; i++) {
            int swapIdx = rand() % tam;
            std::swap(original[i], original[swapIdx]);
        }
    } else {
        for (int i = 0; i < tam; i++) {
            original.push_back(rand() % 100);
        }
    }

    std::cout << "\nArreglo Inicial: ";
    imprimirArreglo(original);

    std::vector<int> datosB = original;
    std::vector<int> datosI = original;

    DetallePasos dpB = burbuja(datosB);
    std::cout << "\nArreglo Ordenado (Burbuja): ";
    imprimirArreglo(datosB);
    dpB.mostrar("BURBUJA");

    DetallePasos dpI = insercion(datosI);
    std::cout << "\nArreglo Ordenado (Insercion): ";
    imprimirArreglo(datosI);
    dpI.mostrar("INSERCION");

    return 0;
}
