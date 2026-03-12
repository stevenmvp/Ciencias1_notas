#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct SudokuStats {
    long long intentos = 0;
    long long asignaciones = 0;
    long long retrocesos = 0;
    long long podas = 0;
};

int leerEnteroEnRango(const string &mensaje, int minimo, int maximo) {
    while (true) {
        try {
            cout << mensaje;
            string linea;
            if (!getline(cin, linea)) {
                throw runtime_error("No se pudo leer la entrada.");
            }

            size_t idx = 0;
            int valor = stoi(linea, &idx);
            if (idx != linea.size()) {
                throw invalid_argument("La entrada contiene caracteres no validos.");
            }
            if (valor < minimo || valor > maximo) {
                throw out_of_range("Valor fuera de rango permitido.");
            }
            return valor;
        } catch (const invalid_argument &) {
            cout << "Entrada invalida. Debes escribir un numero entero." << endl;
        } catch (const out_of_range &) {
            cout << "Entrada fuera de rango. Debe estar entre " << minimo
                 << " y " << maximo << "." << endl;
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cout << "Intenta nuevamente." << endl;
        }
    }
}

vector<int> leerFilaSudoku(int fila) {
    while (true) {
        try {
            cout << "Fila " << (fila + 1)
                 << " (9 numeros entre 0 y 9, separados por espacio): ";
            string linea;
            if (!getline(cin, linea)) {
                throw runtime_error("No se pudo leer la fila.");
            }

            stringstream ss(linea);
            vector<int> numeros;
            int valor;
            while (ss >> valor) {
                if (valor < 0 || valor > 9) {
                    throw out_of_range("Cada valor debe estar entre 0 y 9.");
                }
                numeros.push_back(valor);
            }

            if (numeros.size() != 9) {
                throw invalid_argument("Debes ingresar exactamente 9 valores.");
            }

            return numeros;
        } catch (const exception &e) {
            cout << "Entrada invalida: " << e.what() << endl;
        }
    }
}

void mostrarTitulo(const string &titulo) {
    cout << "\n" << string(78, '=') << endl;
    cout << titulo << endl;
    cout << string(78, '=') << endl;
}

void mostrarSudoku(const vector<vector<int>> &tablero) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            cout << "+-------+-------+-------+" << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                cout << "| ";
            }
            if (tablero[i][j] == 0) {
                cout << ". ";
            } else {
                cout << tablero[i][j] << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "+-------+-------+-------+" << endl;
}

bool esMovimientoValido(const vector<vector<int>> &tablero, int fila, int col,
                       int valor) {
    for (int j = 0; j < 9; j++) {
        if (tablero[fila][j] == valor) {
            return false;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (tablero[i][col] == valor) {
            return false;
        }
    }

    int inicioFila = (fila / 3) * 3;
    int inicioCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[inicioFila + i][inicioCol + j] == valor) {
                return false;
            }
        }
    }

    return true;
}

bool tableroInicialValido(const vector<vector<int>> &tablero) {
    for (int i = 0; i < 9; i++) {
        set<int> vistos;
        for (int j = 0; j < 9; j++) {
            int v = tablero[i][j];
            if (v != 0) {
                if (vistos.count(v)) {
                    return false;
                }
                vistos.insert(v);
            }
        }
    }

    for (int j = 0; j < 9; j++) {
        set<int> vistos;
        for (int i = 0; i < 9; i++) {
            int v = tablero[i][j];
            if (v != 0) {
                if (vistos.count(v)) {
                    return false;
                }
                vistos.insert(v);
            }
        }
    }

    for (int bloqueFila = 0; bloqueFila < 3; bloqueFila++) {
        for (int bloqueCol = 0; bloqueCol < 3; bloqueCol++) {
            set<int> vistos;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int v = tablero[bloqueFila * 3 + i][bloqueCol * 3 + j];
                    if (v != 0) {
                        if (vistos.count(v)) {
                            return false;
                        }
                        vistos.insert(v);
                    }
                }
            }
        }
    }

    return true;
}

bool encontrarVacio(const vector<vector<int>> &tablero, int &fila, int &col) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (tablero[i][j] == 0) {
                fila = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

bool resolverSudoku(vector<vector<int>> &tablero, SudokuStats &stats,
                    bool mostrarPasos, int limitePasosVisibles,
                    int &pasosImpresos) {
    int fila = 0;
    int col = 0;
    if (!encontrarVacio(tablero, fila, col)) {
        return true;
    }

    for (int valor = 1; valor <= 9; valor++) {
        stats.intentos++;
        if (esMovimientoValido(tablero, fila, col, valor)) {
            tablero[fila][col] = valor;
            stats.asignaciones++;

            if (mostrarPasos && pasosImpresos < limitePasosVisibles) {
                cout << "[Paso " << (pasosImpresos + 1) << "] Colocar " << valor
                     << " en (fila " << (fila + 1) << ", col " << (col + 1)
                     << ")" << endl;
                pasosImpresos++;
            }

            if (resolverSudoku(tablero, stats, mostrarPasos, limitePasosVisibles,
                              pasosImpresos)) {
                return true;
            }

            tablero[fila][col] = 0;
            stats.retrocesos++;

            if (mostrarPasos && pasosImpresos < limitePasosVisibles) {
                cout << "[Paso " << (pasosImpresos + 1) << "] Retroceder en (fila "
                     << (fila + 1) << ", col " << (col + 1) << ")" << endl;
                pasosImpresos++;
            }
        } else {
            stats.podas++;
        }
    }

    return false;
}

vector<vector<int>> generarSudokuAleatorio(int vacias) {
    vector<vector<int>> base = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9},
    };

    vector<int> perm = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    random_shuffle(perm.begin(), perm.end());
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            base[i][j] = perm[base[i][j] - 1];
        }
    }

    vector<int> filas;
    for (int banda = 0; banda < 3; banda++) {
        vector<int> grupo = {banda * 3, banda * 3 + 1, banda * 3 + 2};
        random_shuffle(grupo.begin(), grupo.end());
        filas.insert(filas.end(), grupo.begin(), grupo.end());
    }
    vector<vector<int>> tmp(9, vector<int>(9, 0));
    for (int i = 0; i < 9; i++) {
        tmp[i] = base[filas[i]];
    }
    base = tmp;

    vector<int> cols;
    for (int stack = 0; stack < 3; stack++) {
        vector<int> grupo = {stack * 3, stack * 3 + 1, stack * 3 + 2};
        random_shuffle(grupo.begin(), grupo.end());
        cols.insert(cols.end(), grupo.begin(), grupo.end());
    }
    tmp.assign(9, vector<int>(9, 0));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tmp[i][j] = base[i][cols[j]];
        }
    }
    base = tmp;

    vector<pair<int, int>> celdas;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            celdas.push_back(make_pair(i, j));
        }
    }
    random_shuffle(celdas.begin(), celdas.end());

    vacias = min(vacias, 81);
    for (int k = 0; k < vacias; k++) {
        int i = celdas[k].first;
        int j = celdas[k].second;
        base[i][j] = 0;
    }

    return base;
}

void ejecutarMonedasVoraz() {
    mostrarTitulo("EJERCICIO 1: CAMBIO DE MONEDAS CON TECNICA VORAZ (GREEDY)");

    cout << "\nEste modulo toma siempre la moneda de mayor valor posible"
         << " para reducir rapido la cantidad restante." << endl;

    vector<int> monedas = {1000, 500, 200, 100, 50};
    cout << "\nDenominaciones fijas en pesos colombianos (COP): 50, 100, 200, 500, 1000"
         << endl;

    cout << "\nModo de cantidad objetivo:" << endl;
    cout << "1 - Ingresar cantidad manualmente" << endl;
    cout << "2 - Generar cantidad aleatoria" << endl;
    int modoCantidad = leerEnteroEnRango("Opcion: ", 1, 2);

    int cantidad = 0;
    if (modoCantidad == 1) {
        cantidad = leerEnteroEnRango("Cantidad objetivo a cambiar (0 a 100000000): ",
                                     0, 100000000);
    } else {
        int minimo = leerEnteroEnRango("Minimo aleatorio (0 a 100000000): ", 0,
                                       100000000);
        int maximo = leerEnteroEnRango(
            "Maximo aleatorio (debe ser >= minimo y <= 100000000): ", minimo,
            100000000);
        cantidad = minimo + rand() % (maximo - minimo + 1);
        cout << "Cantidad generada aleatoriamente: " << cantidad << endl;
    }

    if (cantidad == 0) {
        cout << "\nNo se necesitan monedas para cambiar 0." << endl;
        return;
    }

    cout << "\nMonedas ordenadas de mayor a menor para aplicar voraz: ";
    for (size_t i = 0; i < monedas.size(); i++) {
        cout << monedas[i] << (i + 1 < monedas.size() ? ", " : "\n");
    }

    vector<int> usadasPorTipo(monedas.size(), 0);
    int restante = cantidad;

    mostrarTitulo("PROCESO VORAZ PASO A PASO");

    for (size_t i = 0; i < monedas.size(); i++) {
        int moneda = monedas[i];
        if (restante >= moneda) {
            int cantidadMonedas = restante / moneda;
            usadasPorTipo[i] = cantidadMonedas;
            restante -= cantidadMonedas * moneda;
            cout << "Tomar " << cantidadMonedas << " moneda(s) de " << moneda
                 << ". Restante: " << restante << endl;
        } else {
            cout << "Moneda " << moneda
                 << " descartada en este paso (es mayor que el restante: "
                 << restante << ")." << endl;
        }
    }

    mostrarTitulo("RESULTADO DEL CAMBIO");

    if (restante != 0) {
        cout << "No se puede formar exactamente la cantidad " << cantidad
             << " con los tipos de moneda ingresados." << endl;
        cout << "Residuo sin cubrir: " << restante << endl;
        return;
    }

    int totalMonedas = 0;
    cout << "Cambio encontrado por estrategia voraz:" << endl;
    for (size_t i = 0; i < monedas.size(); i++) {
        if (usadasPorTipo[i] > 0) {
            cout << "- " << usadasPorTipo[i] << " x " << monedas[i] << endl;
            totalMonedas += usadasPorTipo[i];
        }
    }
    cout << "Total de monedas usadas: " << totalMonedas << endl;
    cout << "Cantidad objetivo cubierta al 100%." << endl;
}

void ejecutarSudokuBacktracking() {
    mostrarTitulo("EJERCICIO 2: SUDOKU 9x9 CON BACKTRACKING");

    cout << "\nBacktracking reduce el espacio de busqueda descartando"
         << " opciones invalidas temprano (poda), en lugar de probar"
         << " ciegamente todas las combinaciones." << endl;

    cout << "\nModo de entrada:" << endl;
    cout << "1 - Cargar tablero de ejemplo" << endl;
    cout << "2 - Ingresar tablero manualmente" << endl;
    cout << "3 - Generar tablero aleatorio" << endl;
    int modo = leerEnteroEnRango("Opcion: ", 1, 3);

    vector<vector<int>> tablero(9, vector<int>(9, 0));

    if (modo == 1) {
        tablero = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
        };
        cout << "\nSe cargo un tablero clasico resoluble." << endl;
    } else if (modo == 2) {
        cout << "\nIngresa las 9 filas del Sudoku. Usa 0 para casillas vacias."
             << endl;
        for (int i = 0; i < 9; i++) {
            tablero[i] = leerFilaSudoku(i);
        }
    } else {
        cout << "\nGeneracion aleatoria de Sudoku (resoluble)." << endl;
        int vacias = leerEnteroEnRango(
            "Cantidad de casillas vacias deseada (20 a 60): ", 20, 60);
        tablero = generarSudokuAleatorio(vacias);
        cout << "Tablero aleatorio generado correctamente." << endl;
    }

    if (!tableroInicialValido(tablero)) {
        cout << "\nError: El tablero inicial tiene conflictos (fila, columna"
             << " o subcuadro repetido)." << endl;
        cout << "Corrige los datos e intenta nuevamente." << endl;
        return;
    }

    mostrarTitulo("TABLERO INICIAL");
    mostrarSudoku(tablero);

    int mostrar = leerEnteroEnRango(
        "\nMostrar explicacion paso a paso? (1=Si, 0=No): ", 0, 1);

    SudokuStats stats;
    int pasosImpresos = 0;
    const int limitePasosVisibles = 60;

    mostrarTitulo("RESOLVIENDO CON BACKTRACKING");
    bool resuelto = resolverSudoku(tablero, stats, mostrar == 1,
                                   limitePasosVisibles, pasosImpresos);

    if (mostrar == 1 && pasosImpresos >= limitePasosVisibles) {
        cout << "... Se ocultaron pasos adicionales para mantener legible la salida."
             << endl;
    }

    mostrarTitulo("RESULTADO FINAL");
    if (!resuelto) {
        cout << "No existe solucion para el tablero dado." << endl;
        cout << "El algoritmo podo " << stats.podas
             << " posibilidades invalidas antes de concluir." << endl;
        return;
    }

    cout << "Sudoku resuelto exitosamente." << endl;
    mostrarSudoku(tablero);

    cout << "\nMetricas del proceso:" << endl;
    cout << "- Intentos de colocacion: " << stats.intentos << endl;
    cout << "- Asignaciones realizadas: " << stats.asignaciones << endl;
    cout << "- Retrocesos (vuelta atras): " << stats.retrocesos << endl;
    cout << "- Podas por invalidez: " << stats.podas << endl;

    cout << "\nInterpretacion:" << endl;
    cout << "Backtracking evita fuerza bruta completa: prueba, valida y"
         << " retrocede solo cuando detecta contradiccion." << endl;
}

int main() {
    try {
        srand(static_cast<unsigned int>(time(nullptr)));
        while (true) {
            mostrarTitulo("MENU PRINCIPAL - GREEDY Y BACKTRACKING");
            cout << "1 - Cambio de monedas (Voraz)" << endl;
            cout << "2 - Sudoku 9x9 (Backtracking)" << endl;
            cout << "0 - Salir" << endl;

            int opcion = leerEnteroEnRango("Selecciona una opcion: ", 0, 2);

            if (opcion == 0) {
                cout << "\nPrograma finalizado." << endl;
                break;
            }

            if (opcion == 1) {
                ejecutarMonedasVoraz();
            } else if (opcion == 2) {
                ejecutarSudokuBacktracking();
            }

            int continuar = leerEnteroEnRango(
                "\nDeseas volver al menu principal? (1=Si, 0=No): ", 0, 1);
            if (continuar == 0) {
                cout << "\nPrograma finalizado." << endl;
                break;
            }
        }
    } catch (const exception &e) {
        cout << "\nError fatal controlado: " << e.what() << endl;
        return 1;
    }

    return 0;
}
