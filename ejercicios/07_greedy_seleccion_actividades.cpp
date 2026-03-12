#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Actividad {
    int inicio;
    int fin;
    int id;
};

bool compararPorFin(const Actividad& a, const Actividad& b) {
    return a.fin < b.fin;
}

vector<Actividad> seleccionarActividades(vector<Actividad> actividades) {
    sort(actividades.begin(), actividades.end(), compararPorFin);

    cout << "\n" << string(65, '=') << "\n";
    cout << "ALGORITMO GREEDY - SELECCION DE ACTIVIDADES\n";
    cout << string(65, '=') << "\n";
    cout << "Estrategia: elegir primero la actividad que termina antes.\n\n";

    cout << "Actividades ordenadas por tiempo de fin:\n";
    for (const auto& act : actividades) {
        cout << "- A" << act.id << ": [" << act.inicio << ", " << act.fin << "]\n";
    }
    cout << "\n";

    vector<Actividad> seleccionadas;
    seleccionadas.push_back(actividades[0]);

    cout << "Seleccionar A" << actividades[0].id << " (primera por fin minimo).\n";
    int ultimoFin = actividades[0].fin;

    for (size_t i = 1; i < actividades.size(); i++) {
        cout << "Evaluar A" << actividades[i].id << ": [" << actividades[i].inicio
             << ", " << actividades[i].fin << "]";

        if (actividades[i].inicio >= ultimoFin) {
            seleccionadas.push_back(actividades[i]);
            ultimoFin = actividades[i].fin;
            cout << " -> SELECCIONADA\n";
        } else {
            cout << " -> DESCARTADA (se cruza con la ultima seleccionada)\n";
        }
    }

    cout << "\nResultado final (conjunto compatible maximo):\n";
    for (const auto& act : seleccionadas) {
        cout << "- A" << act.id << ": [" << act.inicio << ", " << act.fin << "]\n";
    }
    cout << "Total seleccionadas: " << seleccionadas.size() << "\n";
    cout << string(65, '=') << "\n\n";

    return seleccionadas;
}

int main() {
    vector<Actividad> actividades = {
        {1, 4, 1},
        {3, 5, 2},
        {0, 6, 3},
        {5, 7, 4},
        {3, 9, 5},
        {5, 9, 6},
        {6, 10, 7},
        {8, 11, 8},
        {8, 12, 9},
        {2, 14, 10},
        {12, 16, 11}
    };

    seleccionarActividades(actividades);

    return 0;
}
