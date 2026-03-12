#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct EstadisticasBusqueda {
    long long evaluadas = 0;
    long long conflictos = 0;
    long long podas = 0;
    long long colocaciones = 0;
    long long retrocesos = 0;
};

enum TipoPieza {
    PEON = 1,
    CABALLO = 2,
    ALFIL = 3,
    TORRE = 4,
    REINA = 5
};

string nombrePieza(int tipo) {
    if (tipo == PEON) return "Peon";
    if (tipo == CABALLO) return "Caballo";
    if (tipo == ALFIL) return "Alfil";
    if (tipo == TORRE) return "Torre";
    return "Reina";
}

char simboloPieza(int tipo) {
    if (tipo == PEON) return 'P';
    if (tipo == CABALLO) return 'C';
    if (tipo == ALFIL) return 'A';
    if (tipo == TORRE) return 'T';
    return 'R';
}

bool amenazaPeon(int r1, int c1, int r2, int c2) {
    return (r1 - 1 == r2) && (abs(c1 - c2) == 1);
}

bool amenazaCaballo(int r1, int c1, int r2, int c2) {
    int dr = abs(r1 - r2);
    int dc = abs(c1 - c2);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

bool amenazaAlfil(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) == abs(c1 - c2);
}

bool amenazaTorre(int r1, int c1, int r2, int c2) {
    return (r1 == r2) || (c1 == c2);
}

bool amenazaReina(int r1, int c1, int r2, int c2) {
    return amenazaTorre(r1, c1, r2, c2) || amenazaAlfil(r1, c1, r2, c2);
}

bool seAmenazan(pair<int, int> a, pair<int, int> b, int tipo) {
    int r1 = a.first;
    int c1 = a.second;
    int r2 = b.first;
    int c2 = b.second;

    if (tipo == PEON) {
        return amenazaPeon(r1, c1, r2, c2) || amenazaPeon(r2, c2, r1, c1);
    }
    if (tipo == CABALLO) return amenazaCaballo(r1, c1, r2, c2);
    if (tipo == ALFIL) return amenazaAlfil(r1, c1, r2, c2);
    if (tipo == TORRE) return amenazaTorre(r1, c1, r2, c2);
    return amenazaReina(r1, c1, r2, c2);
}

bool esValida(const vector<pair<int, int>>& colocadas, pair<int, int> candidata, int tipo) {
    for (const auto& p : colocadas) {
        if (seAmenazan(p, candidata, tipo)) return false;
    }
    return true;
}

vector<pair<int, int>> generarCandidatas(int tamano) {
    vector<pair<int, int>> celdas;
    for (int r = 0; r < tamano; r++) {
        for (int c = 0; c < tamano; c++) {
            celdas.push_back({r, c});
        }
    }

    sort(celdas.begin(), celdas.end(), [tamano](const pair<int, int>& a, const pair<int, int>& b) {
        double centro = (tamano - 1) / 2.0;
        double da = (a.first - centro) * (a.first - centro) + (a.second - centro) * (a.second - centro);
        double db = (b.first - centro) * (b.first - centro) + (b.second - centro) * (b.second - centro);
        if (da != db) return da < db;
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });

    return celdas;
}

void mostrarTablero(const vector<pair<int, int>>& colocadas, int tipo, int tamano) {
    vector<vector<char>> tablero(tamano, vector<char>(tamano, '.'));
    for (const auto& p : colocadas) {
        tablero[p.first][p.second] = simboloPieza(tipo);
    }

    cout << "\nTablero " << tamano << "x" << tamano << ":\n\n";
    cout << "    ";
    for (int c = 0; c < tamano; c++) {
        cout << setw(3) << c << " ";
    }
    cout << "\n";

    for (int r = 0; r < tamano; r++) {
        cout << "    ";
        for (int c = 0; c < tamano; c++) cout << "+---";
        cout << "+\n";

        cout << setw(2) << r << "  |";
        for (int c = 0; c < tamano; c++) {
            cout << " " << tablero[r][c] << " |";
        }
        cout << "\n";
    }

    cout << "    ";
    for (int c = 0; c < tamano; c++) cout << "+---";
    cout << "+\n";
}

bool backtracking(const vector<pair<int, int>>& candidatas,
                 int idx,
                 int tipo,
                 vector<pair<int, int>>& colocadas,
                 int objetivo,
                 long long& paso,
                 int profundidad,
                 EstadisticasBusqueda& estadisticas) {
    string sangria(profundidad * 2, ' ');

    if ((int)colocadas.size() == objetivo) {
        cout << "\nPaso " << ++paso << ": " << sangria
             << "OBJETIVO ALCANZADO con " << objetivo << " piezas.\n";
        return true;
    }

    if (idx >= (int)candidatas.size()) {
        cout << "Paso " << ++paso << ": " << sangria
             << "ENCRUCIJADA -> no hay mas celdas para explorar en esta rama.\n";
        return false;
    }

    int restantes = candidatas.size() - idx;
    int faltan = objetivo - colocadas.size();
    if (restantes < faltan) {
        estadisticas.podas++;
        cout << "Paso " << ++paso << ": " << sangria
             << "PODA -> quedan " << restantes << " celdas y faltan " << faltan
             << " piezas.\n";
        return false;
    }

    pair<int, int> celda = candidatas[idx];
    estadisticas.evaluadas++;
    cout << "Paso " << ++paso << ": " << sangria
         << "BUSQUEDA -> evaluar celda (" << celda.first << ", " << celda.second << ")\n";

    if (esValida(colocadas, celda, tipo)) {
        estadisticas.colocaciones++;
        cout << "Paso " << ++paso << ": " << sangria
             << "DECISION -> colocar " << nombrePieza(tipo)
             << " en (" << celda.first << ", " << celda.second << ")"
             << " porque no genera amenaza.\n";
        colocadas.push_back(celda);

        if (backtracking(candidatas, idx + 1, tipo, colocadas, objetivo, paso, profundidad + 1, estadisticas)) return true;

        cout << "Paso " << ++paso << ": " << sangria
             << "ENCRUCIJADA -> desde (" << celda.first << ", " << celda.second
             << ") no se logra completar una solucion.\n";

        estadisticas.retrocesos++;
        cout << "Paso " << ++paso << ": " << sangria
             << "VUELTA ATRAS -> quitar pieza de (" << celda.first << ", " << celda.second
             << ") porque esa rama no completo la solucion.\n";
        colocadas.pop_back();
    } else {
        estadisticas.conflictos++;
        cout << "Paso " << ++paso << ": " << sangria
             << "DESCARTE -> celda (" << celda.first << ", " << celda.second
             << ") genera amenaza con una pieza ya colocada.\n";
    }

    return backtracking(candidatas, idx + 1, tipo, colocadas, objetivo, paso, profundidad, estadisticas);
}

int leerOpcion() {
    int opcion;
    while (true) {
        cout << "\nElige la pieza para ubicar (K en tablero NxN):\n";
        cout << "1) Peones\n";
        cout << "2) Caballos\n";
        cout << "3) Alfiles\n";
        cout << "4) Torres\n";
        cout << "5) Reinas\n";
        cout << "Opcion: ";

        if (cin >> opcion && opcion >= 1 && opcion <= 5) return opcion;

        cout << "Entrada invalida. Intenta de nuevo.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int leerTamanoTablero() {
    int tamano;
    while (true) {
        cout << "\nIngresa el tamaño del tablero N (N >= 1): ";

        if (cin >> tamano && tamano >= 1) return tamano;

        cout << "Entrada invalida. Debe ser un entero mayor o igual a 1.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int leerCantidadFichas(int tamano) {
    int cantidad;
    int maximo = tamano * tamano;
    while (true) {
        cout << "\nIngresa la cantidad de fichas a ubicar (1 a " << maximo << "): ";

        if (cin >> cantidad && cantidad >= 1 && cantidad <= maximo) return cantidad;

        cout << "Entrada invalida. Debe estar entre 1 y " << maximo << ".\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int main() {
    cout << "\n==============================================\n";
    cout << "TABLERO NxN - UBICAR K PIEZAS SIN AMENAZAS\n";
    cout << "==============================================\n";
    cout << "Algoritmo usado: Backtracking con poda\n";

    int tamano = leerTamanoTablero();
    int objetivo = leerCantidadFichas(tamano);
    int tipo = leerOpcion();

    vector<pair<int, int>> candidatas = generarCandidatas(tamano);
    vector<pair<int, int>> colocadas;
    long long paso = 0;
    EstadisticasBusqueda estadisticas;

    cout << "\nBuscando mejores posiciones para " << objetivo << " " << nombrePieza(tipo)
         << "(s) en tablero " << tamano << "x" << tamano << "...\n\n";

    bool ok = backtracking(candidatas, 0, tipo, colocadas, objetivo, paso, 0, estadisticas);

    if (ok) {
        cout << "\nSolucion encontrada para " << objetivo << " " << nombrePieza(tipo) << "(s).\n";
        cout << "Posiciones (fila, columna):\n";
        for (const auto& p : colocadas) {
            cout << "- (" << p.first << ", " << p.second << ")\n";
        }
        mostrarTablero(colocadas, tipo, tamano);
    } else {
        cout << "\nNo se encontro una configuracion valida.\n";
    }

    cout << "\nResumen de decisiones del backtracking:\n";
    cout << "- Celdas evaluadas: " << estadisticas.evaluadas << "\n";
    cout << "- Colocaciones validas: " << estadisticas.colocaciones << "\n";
    cout << "- Conflictos detectados: " << estadisticas.conflictos << "\n";
    cout << "- Podas aplicadas: " << estadisticas.podas << "\n";
    cout << "- Retrocesos realizados: " << estadisticas.retrocesos << "\n";

    return 0;
}
