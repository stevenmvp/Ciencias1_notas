#include <iostream>
#include <vector>

using namespace std;

void cambioVoraz(vector<int> monedas, int monto) {
    vector<int> usadas(monedas.size(), 0);

    cout << "\n" << string(60, '=') << "\n";
    cout << "ALGORITMO VORAZ - CAMBIO DE MONEDAS\n";
    cout << string(60, '=') << "\n";
    cout << "Monto a devolver: " << monto << "\n\n";

    int restante = monto;

    for (size_t i = 0; i < monedas.size(); i++) {
        if (monedas[i] <= restante) {
            usadas[i] = restante / monedas[i];
            restante %= monedas[i];

            cout << "Tomar moneda " << monedas[i] << ": " << usadas[i]
                 << " vez/veces -> restante: " << restante << "\n";
        } else {
            cout << "Moneda " << monedas[i] << " no se toma (es mayor que "
                 << restante << ")\n";
        }
    }

    cout << "\nResultado final:\n";
    int totalMonedas = 0;
    for (size_t i = 0; i < monedas.size(); i++) {
        if (usadas[i] > 0) {
            cout << "- " << monedas[i] << " x " << usadas[i] << "\n";
            totalMonedas += usadas[i];
        }
    }

    cout << "Total de monedas usadas: " << totalMonedas << "\n";
    if (restante > 0) {
        cout << "Aviso: no se pudo completar exactamente el monto. Restante: "
             << restante << "\n";
    }
    cout << string(60, '=') << "\n\n";
}

int main() {
    vector<int> monedas = {100, 50, 20, 10, 5, 2, 1};
    int monto = 289;

    cout << "\nSistema de monedas disponible: ";
    for (size_t i = 0; i < monedas.size(); i++) {
        cout << monedas[i];
        if (i < monedas.size() - 1) cout << ", ";
    }
    cout << "\n";

    cambioVoraz(monedas, monto);

    return 0;
}
