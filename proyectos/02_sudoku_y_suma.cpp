#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct EstadisticasSudoku {
    long long intentos = 0;
    long long retrocesos = 0;
};

void explicarAplicacionSudoku() {
    cout << "\nComo se aplica FUERZA BRUTA en Sudoku 4x4:\n";
    cout << "1) Se busca la primera casilla vacia.\n";
    cout << "2) Se prueban valores del 1 al 4 en esa casilla.\n";
    cout << "3) Solo se acepta un valor si cumple fila, columna y subcuadro 2x2.\n";
    cout << "4) Si el valor funciona, se avanza a la siguiente casilla vacia.\n";
    cout << "5) Si en algun punto no hay valor valido, se retrocede (backtracking).\n";
    cout << "6) El proceso termina cuando no quedan casillas vacias.\n";
}

void explicarAplicacionSuma() {
    cout << "\nComo se aplica DIVIDE Y VENCERAS en suma subsecuente maxima:\n";
    cout << "1) Se divide el arreglo en dos mitades.\n";
    cout << "2) Se resuelve recursivamente la mejor suma en la mitad izquierda.\n";
    cout << "3) Se resuelve recursivamente la mejor suma en la mitad derecha.\n";
    cout << "4) Se calcula la mejor suma que cruza el punto medio.\n";
    cout << "5) Se compara izquierda, derecha y cruzada para elegir la maxima.\n";
    cout << "6) Al combinar resultados se obtiene la solucion global.\n";
}

void imprimirSudoku(const vector<vector<int>>& tablero) {
    cout << "\n+-------+-------+\n";
    for (int i = 0; i < 4; i++) {
        cout << "| ";
        for (int j = 0; j < 4; j++) {
            if (tablero[i][j] == 0) cout << ". ";
            else cout << tablero[i][j] << " ";

            if (j == 1) cout << "| ";
        }
        cout << "|\n";
        if (i == 1) cout << "+-------+-------+\n";
    }
    cout << "+-------+-------+\n";
}

bool esValidoSudoku(const vector<vector<int>>& tablero, int fila, int col, int valor) {
    for (int i = 0; i < 4; i++) {
        if (tablero[fila][i] == valor) return false;
        if (tablero[i][col] == valor) return false;
    }

    int filaInicio = (fila / 2) * 2;
    int colInicio = (col / 2) * 2;

    for (int i = filaInicio; i < filaInicio + 2; i++) {
        for (int j = colInicio; j < colInicio + 2; j++) {
            if (tablero[i][j] == valor) return false;
        }
    }

    return true;
}

bool buscarVacio(const vector<vector<int>>& tablero, int& fila, int& col) {
    for (fila = 0; fila < 4; fila++) {
        for (col = 0; col < 4; col++) {
            if (tablero[fila][col] == 0) return true;
        }
    }
    return false;
}

bool resolverSudokuBruta(vector<vector<int>>& tablero, EstadisticasSudoku& estadisticas) {
    int fila = 0;
    int col = 0;

    if (!buscarVacio(tablero, fila, col)) {
        return true;
    }

    for (int valor = 1; valor <= 4; valor++) {
        estadisticas.intentos++;

        if (esValidoSudoku(tablero, fila, col, valor)) {
            tablero[fila][col] = valor;

            if (resolverSudokuBruta(tablero, estadisticas)) {
                return true;
            }

            tablero[fila][col] = 0;
            estadisticas.retrocesos++;
        }
    }

    return false;
}

bool tableroInicialValido(const vector<vector<int>>& tablero) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tablero[i][j] != 0) {
                int valor = tablero[i][j];
                vector<vector<int>> copia = tablero;
                copia[i][j] = 0;
                if (!esValidoSudoku(copia, i, j, valor)) {
                    return false;
                }
            }
        }
    }
    return true;
}

void intercambiarFilas(vector<vector<int>>& tablero, int f1, int f2) {
    vector<int> temp = tablero[f1];
    tablero[f1] = tablero[f2];
    tablero[f2] = temp;
}

void intercambiarColumnas(vector<vector<int>>& tablero, int c1, int c2) {
    for (int i = 0; i < 4; i++) {
        int temp = tablero[i][c1];
        tablero[i][c1] = tablero[i][c2];
        tablero[i][c2] = temp;
    }
}

vector<vector<int>> generarSudokuAleatorio(int vacias) {
    vector<vector<int>> solucionBase = {
        {1, 2, 3, 4},
        {3, 4, 1, 2},
        {2, 1, 4, 3},
        {4, 3, 2, 1}
    };

    for (int i = 0; i < 10; i++) {
        int operacion = rand() % 4;
        if (operacion == 0) {
            int banda = (rand() % 2) * 2;
            intercambiarFilas(solucionBase, banda, banda + 1);
        } else if (operacion == 1) {
            int pila = (rand() % 2) * 2;
            intercambiarColumnas(solucionBase, pila, pila + 1);
        } else if (operacion == 2) {
            intercambiarFilas(solucionBase, 0, 2);
            intercambiarFilas(solucionBase, 1, 3);
        } else {
            intercambiarColumnas(solucionBase, 0, 2);
            intercambiarColumnas(solucionBase, 1, 3);
        }
    }

    vector<int> mapeo = {1, 2, 3, 4};
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = mapeo[i];
        mapeo[i] = mapeo[j];
        mapeo[j] = temp;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            solucionBase[i][j] = mapeo[solucionBase[i][j] - 1];
        }
    }

    vector<vector<int>> tablero = solucionBase;
    int eliminadas = 0;
    while (eliminadas < vacias) {
        int fila = rand() % 4;
        int col = rand() % 4;
        if (tablero[fila][col] != 0) {
            tablero[fila][col] = 0;
            eliminadas++;
        }
    }

    return tablero;
}

struct ResultadoSubsecuencia {
    int suma;
    int inicio;
    int fin;
};

ResultadoSubsecuencia mejorCruzada(const vector<int>& arreglo, int izquierda, int medio, int derecha, long long& comparaciones) {
    int sumaIzquierda = numeric_limits<int>::min();
    int suma = 0;
    int mejorInicio = medio;

    for (int i = medio; i >= izquierda; i--) {
        suma += arreglo[i];
        comparaciones++;
        if (suma > sumaIzquierda) {
            sumaIzquierda = suma;
            mejorInicio = i;
        }
    }

    int sumaDerecha = numeric_limits<int>::min();
    suma = 0;
    int mejorFin = medio + 1;

    for (int j = medio + 1; j <= derecha; j++) {
        suma += arreglo[j];
        comparaciones++;
        if (suma > sumaDerecha) {
            sumaDerecha = suma;
            mejorFin = j;
        }
    }

    ResultadoSubsecuencia resultado;
    resultado.suma = sumaIzquierda + sumaDerecha;
    resultado.inicio = mejorInicio;
    resultado.fin = mejorFin;
    return resultado;
}

ResultadoSubsecuencia maxSubArregloDyV(const vector<int>& arreglo, int izquierda, int derecha, long long& llamadas, long long& comparaciones) {
    llamadas++;

    if (izquierda == derecha) {
        return {arreglo[izquierda], izquierda, derecha};
    }

    int medio = izquierda + (derecha - izquierda) / 2;

    ResultadoSubsecuencia izquierdaRes = maxSubArregloDyV(arreglo, izquierda, medio, llamadas, comparaciones);
    ResultadoSubsecuencia derechaRes = maxSubArregloDyV(arreglo, medio + 1, derecha, llamadas, comparaciones);
    ResultadoSubsecuencia cruzadaRes = mejorCruzada(arreglo, izquierda, medio, derecha, comparaciones);

    comparaciones += 2;
    if (izquierdaRes.suma >= derechaRes.suma && izquierdaRes.suma >= cruzadaRes.suma) {
        return izquierdaRes;
    }
    if (derechaRes.suma >= izquierdaRes.suma && derechaRes.suma >= cruzadaRes.suma) {
        return derechaRes;
    }
    return cruzadaRes;
}

void ejecutarSudoku() {
    vector<vector<int>> tablero(4, vector<int>(4, 0));
    int modoEntrada = 0;

    cout << "\n=== SUDOKU 4x4 - FUERZA BRUTA ===\n";
    explicarAplicacionSudoku();
    cout << "1 - Ingresar valores manualmente\n";
    cout << "2 - Generar Sudoku aleatorio\n";
    cout << "Opcion: ";
    cin >> modoEntrada;

    if (modoEntrada == 1) {
        cout << "Ingresa el tablero (0 para casilla vacia):\n";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << "Celda [" << i + 1 << "," << j + 1 << "]: ";
                cin >> tablero[i][j];
                if (tablero[i][j] < 0 || tablero[i][j] > 4) {
                    cout << "Valor invalido. Debe ser de 0 a 4.\n";
                    return;
                }
            }
        }
    } else if (modoEntrada == 2) {
        int vacias = 8;
        cout << "Cantidad de casillas vacias (1 a 14): ";
        cin >> vacias;
        if (vacias < 1 || vacias > 14) {
            cout << "Valor invalido. Se usara 8 por defecto.\n";
            vacias = 8;
        }
        tablero = generarSudokuAleatorio(vacias);
    } else {
        cout << "Opcion no valida.\n";
        return;
    }

    if (!tableroInicialValido(tablero)) {
        cout << "\nEl tablero inicial viola las reglas del Sudoku 4x4.\n";
        return;
    }

    cout << "\nTablero inicial:";
    imprimirSudoku(tablero);

    EstadisticasSudoku estadisticas;
    bool resuelto = resolverSudokuBruta(tablero, estadisticas);

    if (resuelto) {
        cout << "\nSudoku resuelto:";
        imprimirSudoku(tablero);
        cout << "Intentos de asignacion: " << estadisticas.intentos << "\n";
        cout << "Retrocesos (backtracking): " << estadisticas.retrocesos << "\n";
        cout << "Complejidad teorica aproximada: O(4^k), donde k es el numero de casillas vacias.\n";
    } else {
        cout << "\nNo existe solucion para el tablero dado.\n";
        cout << "Intentos de asignacion: " << estadisticas.intentos << "\n";
    }
}

void imprimirSubsecuencia(const vector<int>& arreglo, int inicio, int fin) {
    cout << "Subsecuencia maxima: [ ";
    for (int i = inicio; i <= fin; i++) {
        cout << arreglo[i] << " ";
    }
    cout << "]\n";
}

void ejecutarSumaSubsecuente() {
    cout << "\n=== SUMA SUBSECUENTE MAXIMA - DIVIDE Y VENCERAS ===\n";
    explicarAplicacionSuma();

    int n;
    cout << "Cantidad de elementos: ";
    cin >> n;

    if (n <= 0) {
        cout << "La cantidad debe ser mayor a 0.\n";
        return;
    }

    vector<int> arreglo(n);
    cout << "Ingresa los " << n << " elementos (pueden ser negativos):\n";
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "]: ";
        cin >> arreglo[i];
    }

    long long llamadas = 0;
    long long comparaciones = 0;

    ResultadoSubsecuencia resultado = maxSubArregloDyV(arreglo, 0, n - 1, llamadas, comparaciones);

    cout << "\nSuma maxima: " << resultado.suma << "\n";
    cout << "Indice inicio: " << resultado.inicio << "\n";
    cout << "Indice fin: " << resultado.fin << "\n";
    imprimirSubsecuencia(arreglo, resultado.inicio, resultado.fin);

    cout << "Llamadas recursivas: " << llamadas << "\n";
    cout << "Comparaciones aproximadas: " << comparaciones << "\n";
    cout << "Complejidad teorica: O(n log n).\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int opcion = 0;

    do {
        cout << "\n" << string(60, '=') << "\n";
        cout << "PROYECTO 2: SUDOKU 4x4 Y SUMA SUBSECUENTE MAXIMA\n";
        cout << string(60, '=') << "\n";
        cout << "1 - Resolver Sudoku 4x4 (Fuerza Bruta)\n";
        cout << "2 - Suma Subsecuente Maxima (Divide y Venceras)\n";
        cout << "0 - Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                ejecutarSudoku();
                break;
            case 2:
                ejecutarSumaSubsecuente();
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}
